#include "quarterturn.h"

void quarterturn::DisplaySpecific(sf::RenderWindow& window)  {
    window.draw(shape);
    iconSprite.setPosition({posx + 25.0f, posy + 25.0f});
    window.draw(iconSprite);
}

void quarterturn::LogicToDo(complex ca, complex cb,sf::Time dt,int index)  {
    for (size_t i=0;i<lista_adiacenta.size();i++) {
        std::pair<complex,complex> state;
        state = complex::MatrixMultiply(ca,cb,mat);
        lista_adiacenta[i]->LogicToDo(state.first,state.second,dt,index);
    }
}

void quarterturn::ShowContextMenu()  {
    ImGui::Text("Change Quarter Turn Gate:");
    ImGui::Separator();

    if (ImGui::MenuItem("S Gate")) {
        gatetype = quarterturn_type::S_Gate;
        SetGate();
    }
    if (ImGui::MenuItem("S Dagger Gate")) {
        gatetype = quarterturn_type::S_Dagger;
        SetGate();
    }
    ImGui::Separator();
    if (ImGui::MenuItem("Sqrt Y")) {
        gatetype = quarterturn_type::Y_Sqrt;
        SetGate();
    }
    if (ImGui::MenuItem("Sqrt Y Dagger")) {
        gatetype = quarterturn_type::Y_Sqrt_Dagger;
        SetGate();
    }
    ImGui::Separator();
    if (ImGui::MenuItem("Sqrt X")) {
        gatetype = quarterturn_type::X_Sqrt;
        SetGate();
    }
    if (ImGui::MenuItem("Sqrt X Dagger")) {
        gatetype = quarterturn_type::X_Sqrt_Dagger;
        SetGate();
    }
}

void quarterturn::SetGate() {
    std::string filename;
    if (gatetype == quarterturn_type::S_Gate) {
        mat[0][0] = {1, 0}; mat[0][1] = {0, 0};
        mat[1][0] = {0, 0}; mat[1][1] = {0, 1};
        filename = "images/gates/gate_s.png";
    }
    else if (gatetype == quarterturn_type::S_Dagger) {
        mat[0][0] = {1, 0}; mat[0][1] = {0, 0};
        mat[1][0] = {0, 0}; mat[1][1] = {0, -1};
        filename = "images/gates/gate_sdg.png";
    }
    else if (gatetype == quarterturn_type::X_Sqrt) {
        mat[0][0] = {0.5f, 0.5f}; mat[0][1] = {0.5f, -0.5f};
        mat[1][0] = {0.5f, -0.5f}; mat[1][1] = {0.5f, 0.5f};
        filename = "images/gates/gate_x_half.png";
    }
    else if (gatetype == quarterturn_type::X_Sqrt_Dagger) {
        mat[0][0] = {0.5f, -0.5f}; mat[0][1] = {0.5f, 0.5f};
        mat[1][0] = {0.5f, 0.5f}; mat[1][1] = {0.5f, -0.5f};
        filename = "images/gates/gate_x_nhalf.png";
    }
    else if (gatetype == quarterturn_type::Y_Sqrt) {
        mat[0][0] = {0.5f, 0.5f}; mat[0][1] = {-0.5f, -0.5f};
        mat[1][0] = {0.5f, 0.5f}; mat[1][1] = {0.5f, 0.5f};
        filename = "images/gates/gate_y_half.png";
    }
    else if (gatetype == quarterturn_type::Y_Sqrt_Dagger) {
        mat[0][0] = {0.5f, -0.5f}; mat[0][1] = {0.5f, -0.5f};
        mat[1][0] = {-0.5f, 0.5f}; mat[1][1] = {0.5f, -0.5f};
        filename = "images/gates/gate_y_nhalf.png";
    }

    if (!iconTexture.loadFromFile(filename)) {
        std::cout<<"Eroare la imagine pentru quater turn gate!\n";
    } else {
        iconTexture.setSmooth(true);
        if (iconTexture.generateMipmap()){}
        iconSprite.setTexture(iconTexture, true);
    }
}