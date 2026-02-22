#ifndef OOP_QUARTERTURN_H
#define OOP_QUARTERTURN_H

#include "node.h"
#include "imgui.h"
#include <complex>

enum class quarterturn_type {
    S_Gate,
    S_Dagger,
    Y_Sqrt,
    Y_Sqrt_Dagger,
    X_Sqrt,
    X_Sqrt_Dagger
};

class quarterturn : public node {
private:
    complex mat[2][2];
    quarterturn_type gatetype;

    sf::Texture iconTexture;
    sf::Sprite iconSprite;

public:
    quarterturn(float x, float y, quarterturn_type gatetype_par) : node(x, y), iconSprite(iconTexture) {
        gatetype = gatetype_par;
        SetGate();

        iconSprite.setTexture(iconTexture, true);

        sf::Vector2u size = iconTexture.getSize();
        iconSprite.setOrigin({size.x / 2.0f, size.y / 2.0f});

        float targetSize = 50.0f;
        float scale = targetSize / (float) size.x;
        iconSprite.setScale({scale, scale});
    }

    void DisplaySpecific(sf::RenderWindow& window) override;
    void LogicToDo(complex ca, complex cb,sf::Time dt,int index) override;
    void ShowContextMenu() override;
    void SetGate();
};


#endif //OOP_QUARTERTURN_H