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

    sf::Texture iconTexture;
    sf::Sprite iconSprite;
public:
    halfturn(float x, float y,halfturn_type gatetype_par) : node(x, y), iconSprite(iconTexture) {
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
    void LogicToDo(complex ca,complex cb,sf::Time dt,int index) override;
    void ShowContextMenu() override;
    void SetGate();
};


#endif //OOP_HALFTURN_H