#include "gui.h"
#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"
#include "node.h"
#include "qubit.h"
#include "factory.h"

void gui::MakeNodeCreator(sf::RenderWindow& window, std::vector<std::unique_ptr<node>>& nodes) {
    ImGui::Begin("NodeCreator");
    ImGui::Text("Nodes: %zu", nodes.size());
    ImGui::Separator();

    auto SpawnButton = [&](const char* label, NodeType type) {
        ImGui::Button(label, ImVec2(100, 50));

        if (ImGui::IsItemActive()) {
            build_type = type;

            if (mode != 3) {
                previous_mode = mode;
                mode = 3;
            }

            ImGui::SetTooltip("Dragging %s", label);
        }

        if (ImGui::IsItemDeactivated()) {
            mode = previous_mode;
            if (!ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow)) {

                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                auto newNode = factory::CreateNode(type, (float)mousePos.x - 25.f, (float)mousePos.y - 25.f);

                if (newNode != nullptr) {
                    nodes.push_back(std::move(newNode));
                    std::cout << "Spawned: " << label << "\n";
                }
            }

            build_type = NodeType::None;
        }
    };

    ImGui::Text("Qubits:");
    ImGui::SameLine();
    ImGui::Text("Output:");
    SpawnButton("Qubit", NodeType::Qubit);
    ImGui::SameLine();
    SpawnButton("Chance", NodeType::Chance);

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