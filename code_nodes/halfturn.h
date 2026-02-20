#ifndef OOP_HALFTURN_H
#define OOP_HALFTURN_H
#include <cmath>
#include "node.h"
#include "imgui.h"

const float SQ2 = 1.0f / std::sqrt(2.0f);
const complex C_0 = {0.0f, 0.0f};
const complex C_1 = {1.0f, 0.0f};
const complex C_N1 = {-1.0f, 0.0f};
const complex C_i = {0.0f, 1.0f};
const complex C_Ni = {0.0f, -1.0f};

enum class halfturn_type {
    PauliZ,
    PauliY,
    PauliX,
    Hadamard
};

class halfturn: public node {
private:
    complex mat[2][2];
    std::string print_text;
    halfturn_type gatetype;
public:
    halfturn(float x, float y,halfturn_type gatetype_par) : node(x, y) {
        gatetype = gatetype_par;
        SetGate();
    }
    void DisplaySpecific(sf::RenderWindow& window) override {
        this->text.setString(print_text);
        window.draw(text);
    }
    void LogicToDo(complex ca,complex cb) override {
        for (int i=0;i<lista_adiacenta.size();i++) {
            std::pair<complex,complex> state;
            state = complex::MatrixMultiply(ca,cb,mat);
            lista_adiacenta[i]->LogicToDo(state.first,state.second);
        }
    }
    void ShowContextMenu() override {
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
    void SetGate() {
        if (gatetype==halfturn_type::PauliX) {
            mat[0][0]=C_0;
            mat[0][1]=C_1;
            mat[1][0]=C_1;
            mat[1][1]=C_0;
            print_text = "X";
        }
        if (gatetype==halfturn_type::PauliY) {
            mat[0][0]=C_0;
            mat[0][1]=C_Ni;
            mat[1][0]=C_i;
            mat[1][1]=C_0;
            print_text = "Y";
        }
        if (gatetype==halfturn_type::PauliZ) {
            mat[0][0]=C_1;
            mat[0][1]=C_0;
            mat[1][0]=C_0;
            mat[1][1]=C_N1;
            print_text = "Z";
        }
        if (gatetype==halfturn_type::Hadamard) {
            mat[0][0]={SQ2,0};
            mat[0][1]={SQ2,0};
            mat[1][0]={SQ2,0};
            mat[1][1]={-SQ2,0};
            print_text = "H";
        }
    }
};


#endif //OOP_HALFTURN_H