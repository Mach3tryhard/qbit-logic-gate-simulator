#include "gui.h"
#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"
#include "node.h"
#include "qubit.h"
#include "factory.h"

void gui::SpawnButton(sf::RenderWindow& window, std::vector<std::unique_ptr<node>>& nodes, const char* label, NodeType type) {
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
            float finalX = (float)mousePos.x - 25.f,finalY = (float)mousePos.y - 25.f;
            if (settings::getInstance().snapping) {
                finalX = round(finalX / settings::getInstance().snapping_val) * settings::getInstance().snapping_val;
                finalY = round(finalY / settings::getInstance().snapping_val) * settings::getInstance().snapping_val;
            }

            auto newNode = factory::CreateNode(type, finalX, finalY);

            if (newNode != nullptr) {
                nodes.push_back(std::move(newNode));
                std::cout << "Spawned: " << label << "\n";
            }
        }

        build_type = NodeType::None;
    }
}

void gui::MakeNodeCreator(sf::RenderWindow& window, std::vector<std::unique_ptr<node>>& nodes) {
    ImGui::Begin("NodeCreator");
    ImGui::Text("Nodes: %zu", nodes.size());
    ImGui::Separator();

    ImGui::Text("Qubits:");
    ImGui::SameLine();
    ImGui::Text("Output:");
    SpawnButton(window,nodes,"Qubit", NodeType::Qubit);
    ImGui::SameLine();
    SpawnButton(window,nodes,"Chance", NodeType::Chance);
    ImGui::End();
}

void gui::MakeHalfTurns(sf::RenderWindow& window, std::vector<std::unique_ptr<node>>& nodes) {
    ImGui::Begin("Half Turn Gates");
    ImGui::Separator();
    SpawnButton(window,nodes,"Pauli X", NodeType::PauliX);
    ImGui::SameLine();
    SpawnButton(window,nodes,"Pauli Y", NodeType::PauliY);
    SpawnButton(window,nodes,"Pauli Z", NodeType::PauliZ);
    ImGui::SameLine();
    SpawnButton(window,nodes,"Hadamard", NodeType::Hadamard);
    ImGui::End();
}

void gui::MakeSettings(std::vector<std::unique_ptr<node>>& nodes) {
    ImGui::Begin("Settings");

    ImGui::Text("Visuals");
    ImGui::Separator();
    ImGui::Checkbox("Show Grid", &settings::getInstance().show_grid);
    ImGui::Checkbox("Show FPS Counter", &settings::getInstance().show_fps);

    ImGui::Spacing();

    ImGui::Text("Editor Logic");
    ImGui::Separator();
    ImGui::Checkbox("Snap Nodes to Grid", &settings::getInstance().snapping);

    if (ImGui::SliderInt("Grid Size", &settings::getInstance().snapping_val, 10, 50)) {
        if (settings::getInstance().snapping) {
            settings::getInstance().snapping=false;
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

void DrawDebugWindow(std::vector<CompilerMessage>& messages) {
    ImGui::Begin("Circuit Compiler");

    bool system_is_ok=true;
    if (messages.empty()) {
        ImGui::TextColored(ImVec4(0, 1, 0, 1), "Status: OK");
    }
    else {
        for (const auto& msg : messages) {
            if (msg.type == MsgType::Error) {
                system_is_ok=false;
                ImGui::TextColored(ImVec4(1, 0, 0, 1), "[ERROR] %s", msg.text.c_str());
            }
            else if (msg.type == MsgType::Warning)
                ImGui::TextColored(ImVec4(1, 1, 0, 1), "[WARN]  %s", msg.text.c_str());
            else
                ImGui::TextColored(ImVec4(0.7, 0.7, 0.7, 1), "[INFO]  %s", msg.text.c_str());
        }
    }

    if (!system_is_ok) {
        ImGui::Separator();
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "SIMULATION PAUSED DUE TO ERRORS");
    }

    ImGui::End();
}

void gui::MakeFPS(sf::RenderWindow & window,sf::Time& dt) {
    if (settings::getInstance().show_fps) {
        ImGui::SetNextWindowPos(ImVec2(window.getSize().x - 75.f, 0.f));
        ImGui::Begin("FPS", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("%.1f FPS", 1.0f / dt.asSeconds());
        ImGui::End();
    }
}

void gui::RunGui(sf::RenderWindow & window,sf::Time& dt,std::vector<std::unique_ptr<node>>& nodes,std::vector<CompilerMessage>& messages) {
    ImGui::SFML::Update(window, dt);

    MakeSettings(nodes);
    MakeNodeCreator(window,nodes);
    MakeToolbox(window);
    MakeHalfTurns(window,nodes);
    DrawDebugWindow(messages);
    MakeFPS(window,dt);

    //ImGui::ShowDemoWindow();
}

