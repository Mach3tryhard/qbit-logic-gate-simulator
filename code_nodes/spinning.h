#ifndef OOP_SPINNING_H
#define OOP_SPINNING_H

#include "node.h"
#include "imgui.h"
#include <cmath>
#include <iostream>

enum class spinning_type {
    Z_t,
    Z_nt,
    Y_t,
    Y_nt,
    X_t,
    X_nt
};

class spinning : public node {
private:
    complex mat[2][2];
    spinning_type gatetype;

    sf::Texture iconTexture;
    sf::Sprite iconSprite;

public:
    spinning(float x, float y, spinning_type gatetype_par) : node(x, y),iconSprite(iconTexture) {
        gatetype = gatetype_par;

        SetGateImage();

        sf::Vector2u size = iconTexture.getSize();
        if (size.x > 0) {
            iconSprite.setOrigin({size.x / 2.0f, size.y / 2.0f});
            float targetSize = 50.0f;
            float scale = targetSize / (float)size.x;
            iconSprite.setScale({scale, scale});
        }
    }

    void DisplaySpecific(sf::RenderWindow& window) override {
        window.draw(shape);
        iconSprite.setPosition({posx + 25.0f, posy + 25.0f});
        window.draw(iconSprite);
    }

    void LogicToDo(complex ca, complex cb, sf::Time time,int index) override {
        long double t = time.asSeconds();
        long double theta = t ;
        theta = std::fmod(theta, 2.0f * 3.14159265f);

        UpdateMatrix(theta);

        for (size_t i = 0; i < lista_adiacenta.size(); i++) {
            std::pair<complex, complex> state;
            state = complex::MatrixMultiply(ca, cb, mat);
            lista_adiacenta[i]->LogicToDo(state.first, state.second, time,index);
        }
    }

    void ShowContextMenu() override {
        ImGui::Text("Change Spinning Gate:");
        ImGui::Separator();

        if (ImGui::MenuItem("Z^t")) { gatetype = spinning_type::Z_t; SetGateImage(); }
        if (ImGui::MenuItem("Z^-t")) { gatetype = spinning_type::Z_nt; SetGateImage(); }
        ImGui::Separator();
        if (ImGui::MenuItem("Y^t")) { gatetype = spinning_type::Y_t; SetGateImage(); }
        if (ImGui::MenuItem("Y^-t")) { gatetype = spinning_type::Y_nt; SetGateImage(); }
        ImGui::Separator();
        if (ImGui::MenuItem("X^t")) { gatetype = spinning_type::X_t; SetGateImage(); }
        if (ImGui::MenuItem("X^-t")) { gatetype = spinning_type::X_nt; SetGateImage(); }
    }

private:
    void SetGateImage() {
        std::string filename;
        switch(gatetype) {
            case spinning_type::Z_t:  filename = "images/gates/gate_z_t.png"; break;
            case spinning_type::Z_nt: filename = "images/gates/gate_z_nt.png"; break;
            case spinning_type::Y_t:  filename = "images/gates/gate_y_t.png"; break;
            case spinning_type::Y_nt: filename = "images/gates/gate_y_nt.png"; break;
            case spinning_type::X_t:  filename = "images/gates/gate_x_t.png"; break;
            case spinning_type::X_nt: filename = "images/gates/gate_x_nt.png"; break;
        }

        if (!iconTexture.loadFromFile(filename)) {
            std::cout << "Error loading image: " << filename << "\n";
        } else {
            iconTexture.setSmooth(true);
            iconTexture.generateMipmap();
            // Force sprite update
            iconSprite.setTexture(iconTexture, true);
        }
    }

    void UpdateMatrix(float theta) {
        if (gatetype == spinning_type::Z_nt ||
            gatetype == spinning_type::Y_nt ||
            gatetype == spinning_type::X_nt) {
            theta = -theta;
        }

        long double c = std::cos(theta);
        long double s = std::sin(theta);

        if (gatetype == spinning_type::Z_t || gatetype == spinning_type::Z_nt) {
            mat[0][0] = {1, 0};   mat[0][1] = {0, 0};
            mat[1][0] = {0, 0};   mat[1][1] = {c, s};
        }
        else if (gatetype == spinning_type::Y_t || gatetype == spinning_type::Y_nt) {
            mat[0][0] = {c, 0};   mat[0][1] = {-s, 0};
            mat[1][0] = {s, 0};   mat[1][1] = {c, 0};
        }
        else if (gatetype == spinning_type::X_t || gatetype == spinning_type::X_nt) {
            mat[0][0] = {c, 0};   mat[0][1] = {0, -s};
            mat[1][0] = {0, -s};  mat[1][1] = {c, 0};
        }
    }
};

#endif //OOP_SPINNING_H