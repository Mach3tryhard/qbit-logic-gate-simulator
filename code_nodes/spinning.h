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

    void DisplaySpecific(sf::RenderWindow& window) override;
    void LogicToDo(complex ca, complex cb, sf::Time time,int index) override;
    void ShowContextMenu() override;
    void SetGateImage();
    void UpdateMatrix(float theta);
};

#endif //OOP_SPINNING_H