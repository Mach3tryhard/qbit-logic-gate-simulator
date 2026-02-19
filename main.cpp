#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <memory>

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

    std::vector<std::unique_ptr<node>> nodes;
    nodes.push_back(std::make_unique<node>(100.f, 200.f));
    nodes.push_back(std::make_unique<node>(200.f, 200.f));
    nodes.push_back(std::make_unique<node>(300.f, 200.f));

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
                    if (mouseRelease->button == sf::Mouse::Button::Right) instruments.EndConnection(window, nodes);
                    instruments.set_multiple_select(false);
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

        window.clear();

        if (!ImGui::GetIO().WantCaptureMouse) {
            instruments.MultipleSelect(window,nodes);
            instruments.DragSelected(window, nodes);
            if (!instruments.get_multiple_select()) {
                instruments.UpdateConnectionDrag(window, nodes);
            }
        }

        /// MAIN DRAWING PLACE
        for (int i=0;i<nodes.size();i++) {
            nodes[i]->DisplayLines(window);
        }
        for (int i=0;i<nodes.size();i++) {
            nodes[i]->DisplayNode(window);
        }

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}
