#include "gui.h"
#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"
#include "node.h"

void gui::MakeNodeCreator(sf::RenderWindow& window, std::vector<std::unique_ptr<node>>& nodes) {
    ImGui::Begin("NodeCreator");
    ImGui::Text("Nodes: %zu", nodes.size());
    ImGui::Separator();
    ImGui::Button("New Node", ImVec2(100, 50));

    if (ImGui::IsItemActive()) {
        if (mode != 3) {
            previous_mode = mode;
            mode = 3;
        }
    }

    if (ImGui::IsItemDeactivated()) {
        mode = previous_mode;
        if (!ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow)) {
            nodes[0]->create_node(window,nodes);
        }
    }

    ImGui::End();
}

void gui::MakeToolbox(sf::RenderWindow& window) {
    sf::Vector2i localPosition = sf::Mouse::getPosition(window);

    ImGui::Begin("Toolbox");
    ImGui::Text("Mouse Position: %zu , %zu", localPosition.x,localPosition.y);
    ImGui::Separator();

    ImGui::RadioButton("Select Mode", &mode, 0);
    ImGui::SameLine();
    ImGui::RadioButton("Link Mode", &mode, 2);
    ImGui::RadioButton("Delete Mode", &mode, 1);
    ImGui::SameLine();
    ImGui::BeginDisabled();
    ImGui::RadioButton("Build Mode", &mode,3);
    ImGui::EndDisabled();

    ImGui::End();
}

void gui::RunGui(sf::RenderWindow & window,sf::Time& dt,std::vector<std::unique_ptr<node>>& nodes) {
    ImGui::SFML::Update(window, dt);

    MakeNodeCreator(window,nodes);
    MakeToolbox(window);

    //ImGui::ShowDemoWindow();
}