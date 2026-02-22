#ifndef OOP_FORMULAIC_H
#define OOP_FORMULAIC_H

#include "node.h"
#include "imgui.h"
#include <cmath>
#include <iostream>

enum class formulaic_type {
    Z_pow,
    RZ,
    Y_pow,
    RY,
    X_pow,
    RX
};

enum class math_func {
    Linear,
    Quadratic,
    Sine,
    Cosine,
    Pulse
};

class formulaic : public node {
private:
    complex mat[2][2];

    formulaic_type gatetype;
    math_func functionType;

    float frequency = 0.25f;
    float amplitude = 1.0f;
    float offset = 0.0f;

    sf::Texture iconTexture;
    sf::Sprite iconSprite;

public:
    formulaic(float x, float y, formulaic_type type_par) : node(x, y), iconSprite(iconTexture){
        gatetype = type_par;
        functionType = math_func::Sine;

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
    float EvaluateFunction(float t);
    void UpdateMatrix(float theta);
    void SetGateImage();
};

#endif //OOP_FORMULAIC_H