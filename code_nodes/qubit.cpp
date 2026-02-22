#include "qubit.h"

void qubit::DisplaySpecific(sf::RenderWindow& window) {
    iconSprite.setPosition({posx + 25.0f, posy + 25.0f});

    window.draw(shape);
    window.draw(iconSprite);
}

void qubit::LogicToDo(complex ca,complex cb,sf::Time dt,int index) {
    for (size_t i=0;i<lista_adiacenta.size();i++) {
        lista_adiacenta[i]->LogicToDo(a,b,dt,index);
    }
}

void qubit::ShowContextMenu() {
    ImGui::Text("Set State:");
    ImGui::Separator();

    if (ImGui::MenuItem("|0>")) {
        a.real=1;a.imag=0;
        b.real=0;b.imag=0;
        if (iconTexture.loadFromFile("images/qubit/state_0.png")) {
            std::cout<<"Error: images/qubit/state_0.png not found!";
        }
        iconTexture.setSmooth(true);
        if (iconTexture.generateMipmap()){}
    }
    if (ImGui::MenuItem("|1>")) {
        a.real=0;a.imag=0;
        b.real=1;b.imag=0;
        if (iconTexture.loadFromFile("images/qubit/state_1.png")) {
            std::cout<<"Error: images/qubit/state_1.png not found!";
        }
        iconTexture.setSmooth(true);
        if (iconTexture.generateMipmap()){}
    }
    if (ImGui::MenuItem("|+>")) {
        a.real=1/std::sqrt(2);a.imag=0;
        b.real=1/std::sqrt(2);b.imag=0;
        if (iconTexture.loadFromFile("images/qubit/state_plus.png")) {
            std::cout<<"Error: images/qubit/state_plus.png not found!";
        }
        iconTexture.setSmooth(true);
        if (iconTexture.generateMipmap()){}
    }
    if (ImGui::MenuItem("|->")) {
        a.real=1/std::sqrt(2);a.imag=0;
        b.real=-1/std::sqrt(2);b.imag=0;
        if (iconTexture.loadFromFile("images/qubit/state_minus.png")) {
            std::cout<<"Error: images/qubit/state_minus.png not found!";
        }
        iconTexture.setSmooth(true);
        if (iconTexture.generateMipmap()){}
    }
    if (ImGui::MenuItem("|i>")) {
        a.real=1/std::sqrt(2);a.imag=0;
        b.real=0;b.imag=1/std::sqrt(2);
        if (iconTexture.loadFromFile("images/qubit/state_i.png")) {
            std::cout<<"Error: images/qubit/state_i.png not found!";
        }
        iconTexture.setSmooth(true);
        if (iconTexture.generateMipmap()){}
    }
    if (ImGui::MenuItem("|-i>")) {
        a.real=1/std::sqrt(2);a.imag=0;
        b.real=0;b.imag=-1/std::sqrt(2);
        if (iconTexture.loadFromFile("images/qubit/state_ni.png")) {
            std::cout<<"Error: images/qubit/state_ni.png not found!";
        }
        iconTexture.setSmooth(true);
        if (iconTexture.generateMipmap()){}
    }
}