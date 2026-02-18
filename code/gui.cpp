#include "gui.h"
#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"
#include "node.h"

void gui::MakeNodeCreator(std::vector<std::unique_ptr<node>>& nodes) {
    ImGui::Begin("NodeCreator");
    ImGui::Text("Nodes: %zu", nodes.size());
    ImGui::Separator();
    if (ImGui::Button("New Node", ImVec2(100, 50))) {
        nodes.push_back(std::make_unique<node>(100,200));
    }
    ImGui::End();
}

void gui::MakeToolbox(std::vector<std::unique_ptr<node>>& nodes) {
    ImGui::Begin("Toolbox");
    ImGui::Text("Nodes: %zu", nodes.size());
    ImGui::Separator();
    ImGui::RadioButton("Select Mode", &mode, 0);
    ImGui::SameLine();
    ImGui::RadioButton("Delete Mode", &mode, 1);
    ImGui::End();
}

void gui::RunGui(sf::RenderWindow & window,sf::Time& dt,std::vector<std::unique_ptr<node>>& nodes) {
    ImGui::SFML::Update(window, dt);

    MakeNodeCreator(nodes);
    MakeToolbox(nodes);

    //ImGui::ShowDemoWindow();
}