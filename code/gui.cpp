#include "gui.h"
#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"
#include "node.h"
#include "qubit.h"
#include "factory.h"

void gui::SpawnButton(sf::RenderWindow& window, std::vector<std::unique_ptr<node>>& nodes, const char* label, const std::string& imagePath, NodeType type) {

    sf::Texture& texture = GetTexture(imagePath);
    texture.setSmooth(true);
    texture.generateMipmap();

    if (ImGui::ImageButton(label,texture, sf::Vector2f({50.f, 50.f}))) {}
    if (ImGui::IsItemActive()) {
        build_type = type;

        if (mode != 3) {
            previous_mode = mode;
            mode = 3;
        }

        ImGui::SetTooltip("%s", label);
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
    ImGui::Begin("Input and Output");
    ImGui::Separator();

    SpawnButton(window,nodes,"Qubit","images/output/qubit.png", NodeType::Qubit);
    ImGui::SameLine();
    SpawnButton(window,nodes,"Chance","images/output/chance.png", NodeType::Chance);
    ImGui::SameLine();
    SpawnButton(window,nodes,"Bloch","images/output/bloch.png", NodeType::Bloch);

    SpawnButton(window,nodes,"Amplitutde","images/output/amps.png",NodeType::Amplitutde);

    ImGui::End();
}

void gui::MakeHalfTurns(sf::RenderWindow& window, std::vector<std::unique_ptr<node>>& nodes) {
    ImGui::Begin("Half Turn Gates");
    ImGui::Separator();
    SpawnButton(window,nodes,"Pauli X","images/gates/gate_x.png", NodeType::PauliX);
    ImGui::SameLine();
    SpawnButton(window,nodes,"Pauli Y","images/gates/gate_y.png", NodeType::PauliY);
    SpawnButton(window,nodes,"Pauli Z","images/gates/gate_z.png", NodeType::PauliZ);
    ImGui::SameLine();
    SpawnButton(window,nodes,"Hadamard","images/gates/gate_h.png", NodeType::Hadamard);
    ImGui::End();
}

void gui::MakeQuarterTurns(sf::RenderWindow& window, std::vector<std::unique_ptr<node>>& nodes) {
    ImGui::Begin("Quarter Turn Gates");
    ImGui::Separator();
    SpawnButton(window,nodes,"S Gate","images/gates/gate_s.png", NodeType::S_Gate);
    ImGui::SameLine();
    SpawnButton(window,nodes,"Y Square Root Gate","images/gates/gate_y_half.png", NodeType::Y_Sqrt);
    ImGui::SameLine();
    SpawnButton(window,nodes,"X Square Root Gate","images/gates/gate_x_half.png", NodeType::X_Sqrt);

    SpawnButton(window,nodes,"S Dagger Gate","images/gates/gate_sdg.png", NodeType::S_Dagger);
    ImGui::SameLine();
    SpawnButton(window,nodes,"Y Square Root Dagger Gate","images/gates/gate_y_nhalf.png", NodeType::Y_Sqrt_Dagger);
    ImGui::SameLine();
    SpawnButton(window,nodes,"X Square Root Dagger Gate","images/gates/gate_x_nhalf.png", NodeType::X_Sqrt_Dagger);
    ImGui::End();
}

void gui::MakeSpinning(sf::RenderWindow& window, std::vector<std::unique_ptr<node>>& nodes) {
    ImGui::Begin("Spinning Gates");
    ImGui::Separator();
    SpawnButton(window,nodes,"Z function t","images/gates/gate_z_t.png", NodeType::Z_t);
    ImGui::SameLine();
    SpawnButton(window,nodes,"Y function t","images/gates/gate_y_t.png", NodeType::Y_t);
    ImGui::SameLine();
    SpawnButton(window,nodes,"X function t","images/gates/gate_x_t.png", NodeType::X_t);

    SpawnButton(window,nodes,"Z Dagger function t","images/gates/gate_z_nt.png", NodeType::Z_nt);
    ImGui::SameLine();
    SpawnButton(window,nodes,"Y Dagger function t","images/gates/gate_y_nt.png", NodeType::Y_nt);
    ImGui::SameLine();
    SpawnButton(window,nodes,"X Dagger function t","images/gates/gate_x_nt.png", NodeType::X_nt);
    ImGui::End();
}

void gui::MakeFormulaic(sf::RenderWindow& window, std::vector<std::unique_ptr<node>>& nodes) {
    ImGui::Begin("Formulaic Gates");
    ImGui::Separator();
    SpawnButton(window,nodes,"Z power function","images/gates/gate_z_ft.png", NodeType::Z_pow);
    ImGui::SameLine();
    SpawnButton(window,nodes,"Y power function","images/gates/gate_y_ft.png", NodeType::Y_pow);
    ImGui::SameLine();
    SpawnButton(window,nodes,"X power function","images/gates/gate_x_ft.png", NodeType::X_pow);

    SpawnButton(window,nodes,"Formulaic RZ","images/gates/gate_rz_ft.png", NodeType::RZ);
    ImGui::SameLine();
    SpawnButton(window,nodes,"Formulaic RY","images/gates/gate_ry_ft.png", NodeType::RY);
    ImGui::SameLine();
    SpawnButton(window,nodes,"Formulaic RX","images/gates/gate_rx_ft.png", NodeType::RX);
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
    MakeQuarterTurns(window,nodes);
    MakeSpinning(window,nodes);
    MakeFormulaic(window,nodes);
    DrawDebugWindow(messages);
    MakeFPS(window,dt);

    //ImGui::ShowDemoWindow();
}

sf::Texture& gui::GetTexture(const std::string& filename) {
    if (button_textures.find(filename) == button_textures.end()) {
        sf::Texture tex;
        if (tex.loadFromFile(filename)) {
            tex.setSmooth(true);
            if (tex.generateMipmap()){}
        }
        button_textures[filename] = tex;
    }
    return button_textures[filename];
}