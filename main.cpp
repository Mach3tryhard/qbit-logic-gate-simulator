#include <iostream>
#include <chrono>
#include <thread>

#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"

#include <vector>
#include "node.h"
#include "tools.h"

int main() {

    sf::RenderWindow window;
    window.create(sf::VideoMode({1920, 1009}), "qlgs", sf::Style::Default,sf::State::Windowed);
    window.setVerticalSyncEnabled(true);

    std::vector<node> nodes;
    std::vector<int> lista_adiacenta[1000];
    node qubit(20,20),qubit2(100,100),qubit3(200,200);
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

        // 4. UPDATE IMGUI FRAME ------------------------------------------
        ImGui::SFML::Update(window, dt);
        // ----------------------------------------------------------------

        // --- DEFINE YOUR GUI WINDOW HERE ---
        ImGui::Begin("Toolbox"); // Create a window called "Toolbox"

        ImGui::Text("Nodes: %zu", nodes.size()); // Display node count

        // SPACER
        ImGui::Separator();

        // DELETE BUTTON
        if (ImGui::Button("Delete Selected Node", ImVec2(200, 30))) {
            // Logic to find and remove selected node
            for (auto it = nodes.begin(); it != nodes.end(); ) {
                if (it->get_selected()) {
                    it = nodes.erase(it);
                    // Note: You also need to clean up lista_adiacenta for the logic to be perfect!
                } else {
                    ++it;
                }
            }
        }
        float nodeColor[3] = {0.39f, 0.39f, 0.43f};
        // COLOR PICKER
        if (ImGui::ColorEdit3("Node Color", nodeColor)) {
            // Update selected node color live
            // (You would need to add a setColor method to your node class)
        }

        ImGui::End(); // Close the window
        // -----------------------------------

        instruments.DragSelected(window, nodes);
        instruments.UpdateConnectionDrag(window, nodes);

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
