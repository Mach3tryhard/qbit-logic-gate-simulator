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

    void DisplaySpecific(sf::RenderWindow& window) override;
    void LogicToDo(complex ca,complex cb,sf::Time dt,int index) override;
    void ShowContextMenu() override;
};


#endif //OOP_QUBIT_H