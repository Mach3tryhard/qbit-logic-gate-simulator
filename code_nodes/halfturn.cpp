#include "halfturn.h"

void halfturn::DisplaySpecific(sf::RenderWindow& window) {
    window.draw(shape);
    iconSprite.setPosition({posx + 25.0f, posy + 25.0f});
    window.draw(iconSprite);
}

void halfturn::LogicToDo(complex ca,complex cb,sf::Time dt,int index) {
    for (size_t i=0;i<lista_adiacenta.size();i++) {
        std::pair<complex,complex> state;
        state = complex::MatrixMultiply(ca,cb,mat);
        lista_adiacenta[i]->LogicToDo(state.first,state.second,dt,index);
    }
}

void halfturn::ShowContextMenu() {
    ImGui::Text("Change to another HalfTurn gate:");
    ImGui::Separator();
    if (ImGui::MenuItem("Pauli X Gate")) {
        gatetype = halfturn_type::PauliX;
        SetGate();
    }
    if (ImGui::MenuItem("Pauli Y Gate")) {
        gatetype = halfturn_type::PauliY;
        SetGate();
    }
    if (ImGui::MenuItem("Pauli Z Gate")) {
        gatetype = halfturn_type::PauliZ;
        SetGate();
    }
    if (ImGui::MenuItem("Hadamard Gate")) {
        gatetype = halfturn_type::Hadamard;
        SetGate();
    }
}

void halfturn::SetGate() {
    std::string filename;
    if (gatetype==halfturn_type::PauliX) {
        mat[0][0]=C_0;
        mat[0][1]=C_1;
        mat[1][0]=C_1;
        mat[1][1]=C_0;
        filename="images/gates/gate_x.png";
        iconTexture.setSmooth(true);
        if (iconTexture.generateMipmap()){}
    }
    if (gatetype==halfturn_type::PauliY) {
        mat[0][0]=C_0;
        mat[0][1]=C_Ni;
        mat[1][0]=C_i;
        mat[1][1]=C_0;
        filename="images/gates/gate_y.png";
        iconTexture.setSmooth(true);
        if (iconTexture.generateMipmap()){}
    }
    if (gatetype==halfturn_type::PauliZ) {
        mat[0][0]=C_1;
        mat[0][1]=C_0;
        mat[1][0]=C_0;
        mat[1][1]=C_N1;
        filename="images/gates/gate_z.png";
        iconTexture.setSmooth(true);
        if (iconTexture.generateMipmap()){}
    }
    if (gatetype==halfturn_type::Hadamard) {
        mat[0][0]={SQ2,0};
        mat[0][1]={SQ2,0};
        mat[1][0]={SQ2,0};
        mat[1][1]={-SQ2,0};
        filename="images/gates/gate_h.png";
        iconTexture.setSmooth(true);
        if (iconTexture.generateMipmap()){}
        iconSprite.setTexture(iconTexture, true);
    }
    if (!iconTexture.loadFromFile(filename)) {
        std::cout<<"Eroare la imagine pentru half turn gate!\n";
    } else {
        iconTexture.setSmooth(true);
        if (iconTexture.generateMipmap()){}
        iconSprite.setTexture(iconTexture, true);
    }
}