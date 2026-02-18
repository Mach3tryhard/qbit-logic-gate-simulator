#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"

#include "node.h"
#include "tools.h"
#include "gui.h"

int main() {

    sf::RenderWindow window;
    window.create(sf::VideoMode({1920, 1009}), "qlgs", sf::Style::Default,sf::State::Windowed);
    window.setVerticalSyncEnabled(true);

    std::vector<node> nodes;
    std::vector<int> lista_adiacenta[1000];
    node qubit(100,100),qubit2(200,100),qubit3(300,100);
    nodes.push_back(qubit);
    nodes.push_back(qubit2);
    nodes.push_back(qubit3);

    tools instruments;

    if (!ImGui::SFML::Init(window)) return -1;
    sf::Clock deltaClock;


    while(window.isOpen()) {
        bool shouldExit = false;

        sf::Time dt = deltaClock.restart();

        while(const std::optional event = window.pollEvent()) {

            ImGui::SFML::ProcessEvent(window, *event);

            if (event->is<sf::Event::Closed>()) {
                window.close();
                std::cout << "Fereastra a fost închisă\n";
            }
            else if (event->is<sf::Event::Resized>()) {
                std::cout << "New width: " << window.getSize().x << '\n'
                          << "New height: " << window.getSize().y << '\n';
            }
            else if (event->is<sf::Event::KeyPressed>()) {
                const auto* keyPressed = event->getIf<sf::Event::KeyPressed>();
                std::cout << "Received key " << (keyPressed->scancode == sf::Keyboard::Scancode::X ? "X" : "(other)") << "\n";
                if(keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                    shouldExit = true;
                }
            }

            if (!ImGui::GetIO().WantCaptureMouse) {
                if (const auto* mousePress = event->getIf<sf::Event::MouseButtonPressed>()) {
                    if (mousePress->button == sf::Mouse::Button::Left) instruments.CheckSelect(window, nodes);
                    if (mousePress->button == sf::Mouse::Button::Right) instruments.StartConnection(window, nodes);
                }
                if (const auto* mouseRelease = event->getIf<sf::Event::MouseButtonReleased>()) {
                    if (mouseRelease->button == sf::Mouse::Button::Right) instruments.EndConnection(window, nodes, lista_adiacenta);
                }
            }

        }
        if(shouldExit) {
            window.close();
            std::cout << "Fereastra a fost închisă (shouldExit == true)\n";
            break;
        }
        using namespace std::chrono_literals;
        //std::this_thread::sleep_for(100ms);

        ///DOING GUI HERE APPARENTLY
        gui::getInstance().RunGui(window,dt,nodes);

        if (!ImGui::GetIO().WantCaptureMouse) {
            instruments.DragSelected(window, nodes);
            instruments.UpdateConnectionDrag(window, nodes);
        }

        window.clear();

        /// MAIN DRAWING PLACE
        for (int i=0;i<nodes.size();i++) {
            nodes[i].DisplayLines(window,nodes,lista_adiacenta[i]);
        }
        for (int i=0;i<nodes.size();i++) {
            nodes[i].DisplayNode(window);
        }

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}
