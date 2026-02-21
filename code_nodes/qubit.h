#ifndef OOP_QUBIT_H
#define OOP_QUBIT_H
#include <cmath>

#include "node.h"
#include "complex.h"
#include "imgui.h"

class qubit : public node {
private:
    complex a,b;

    sf::Texture iconTexture;
    sf::Sprite iconSprite;
public:
    qubit(float x, float y) : node(x, y), iconSprite(iconTexture) {
        a.real = 1;a.imag = 0;
        b.real = 0;b.imag = 0;
        if (!iconTexture.loadFromFile("images/qubit/state_0.png"));
        iconTexture.setSmooth(true);
        if (iconTexture.generateMipmap()){}
        iconSprite.setTexture(iconTexture,true);

        sf::Vector2u size = iconTexture.getSize();
        iconSprite.setOrigin({size.x / 2.0f, size.y / 2.0f});

        float targetSize = 40.0f;
        float scale = targetSize / (float) size.x;
        iconSprite.setScale({scale, scale});
    }

    void DisplaySpecific(sf::RenderWindow& window) override {
        iconSprite.setPosition({posx + 25.0f, posy + 25.0f});
        window.draw(iconSprite);
    }
    void LogicToDo(complex ca,complex cb,sf::Time dt) override {
        for (size_t i=0;i<lista_adiacenta.size();i++) {
            lista_adiacenta[i]->LogicToDo(a,b,dt);
        }
    }
    void ShowContextMenu() override {
        ImGui::Text("Set State:");
        ImGui::Separator();

        if (ImGui::MenuItem("|0>")) {
            a.real=1;a.imag=0;
            b.real=0;b.imag=0;
            iconTexture.loadFromFile("images/qubit/state_0.png");
            iconTexture.setSmooth(true);
            if (iconTexture.generateMipmap()){}
        }
        if (ImGui::MenuItem("|1>")) {
            a.real=0;a.imag=0;
            b.real=1;b.imag=0;
            iconTexture.loadFromFile("images/qubit/state_1.png");
            iconTexture.setSmooth(true);
            if (iconTexture.generateMipmap()){}
        }
        ImGui::Separator();
        if (ImGui::MenuItem("|+>")) {
            a.real=1/std::sqrt(2);a.imag=0;
            b.real=1/std::sqrt(2);b.imag=0;
            iconTexture.loadFromFile("images/qubit/state_plus.png");
            iconTexture.setSmooth(true);
            if (iconTexture.generateMipmap()){}
        }
        if (ImGui::MenuItem("|->")) {
            a.real=1/std::sqrt(2);a.imag=0;
            b.real=-1/std::sqrt(2);b.imag=0;
            iconTexture.loadFromFile("images/qubit/state_minus.png");
            iconTexture.setSmooth(true);
            if (iconTexture.generateMipmap()){}
        }
        ImGui::Separator();
        if (ImGui::MenuItem("|i>")) {
            a.real=1/std::sqrt(2);a.imag=0;
            b.real=0;b.imag=1/std::sqrt(2);
            iconTexture.loadFromFile("images/qubit/state_i.png");
            iconTexture.setSmooth(true);
            if (iconTexture.generateMipmap()){}
        }
        if (ImGui::MenuItem("|-i>")) {
            a.real=1/std::sqrt(2);a.imag=0;
            b.real=0;b.imag=-1/std::sqrt(2);
            iconTexture.loadFromFile("images/qubit/state_ni.png");
            iconTexture.setSmooth(true);
            if (iconTexture.generateMipmap()){}
        }
    }
};


#endif //OOP_QUBIT_H