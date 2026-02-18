#include "gui.h"
#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"
#include "node.h"

void gui::RunGui(sf::RenderWindow & window,sf::Time& dt,std::vector<node>& nodes) {
    ImGui::SFML::Update(window, dt);


    ImGui::Begin("Toolbox");

    ImGui::Text("Nodes: %zu", nodes.size());
    ImGui::Separator();
    ImGui::RadioButton("Select Mode", &mode, 0);
    ImGui::SameLine();
    ImGui::RadioButton("Delete Mode", &mode, 1);

    if (ImGui::Button("Delete Selected Node", ImVec2(200, 30))) {
        for (auto it = nodes.begin(); it != nodes.end(); ) {
            if (it->get_selected()) {
                it = nodes.erase(it);
                // Note: You also need to clean up lista_adiacenta for the logic to be perfect!
            } else {
                ++it;
            }
        }
    }
    ImGui::End();
    //ImGui::ShowDemoWindow();
}