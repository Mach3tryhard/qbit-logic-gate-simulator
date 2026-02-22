#ifndef OOP_COMPLEX_CELL_H
#define OOP_COMPLEX_CELL_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include "complex.h"

class complex_cell {
private:
    sf::RectangleShape background;
    sf::RectangleShape fill;
    sf::CircleShape circle;
    sf::RectangleShape radius_line;
    sf::Vector2f position;
    float size;

public:
    void setup(float s) {
        size = s;

        background.setSize({size, size});
        background.setFillColor(sf::Color(245, 245, 245));
        background.setOutlineColor(sf::Color(200, 200, 200));
        background.setOutlineThickness(1.0f);

        fill.setFillColor(sf::Color(100, 200, 200, 200));

        float circleRadius = size * 0.4f;
        circle.setRadius(circleRadius);
        circle.setOrigin({circleRadius, circleRadius});
        circle.setFillColor(sf::Color::Transparent);
        circle.setOutlineColor(sf::Color(150, 150, 150));
        circle.setOutlineThickness(1.5f);
        circle.setPointCount(30);

        radius_line.setFillColor(sf::Color::Black);
    }

    void update(complex z) {
        float magnitude = std::sqrt(z.real*z.real + z.imag*z.imag);
        float phase = std::atan2(z.imag, z.real);
        float probability = magnitude * magnitude;

        if (probability > 1.0f) probability = 1.0f;

        float fillHeight = probability * size;
        fill.setSize({size, -fillHeight});
        fill.setPosition({position.x, position.y + size});

        float max_radius = size * 0.4f;
        float line_len = max_radius;
        float thickness = 2.0f;

        radius_line.setSize({line_len, thickness});
        radius_line.setOrigin({0.0f, thickness / 2.0f});
        radius_line.setPosition({position.x + size/2.0f, position.y + size/2.0f});
        radius_line.setRotation(sf::degrees(-phase * 180.0f / 3.14159f));
    }

    void draw(sf::RenderWindow& window) {
        window.draw(background);
        window.draw(fill);
        window.draw(circle);
        window.draw(radius_line);
    }

    void setPosition(float x, float y) {
        sf::Vector2f center = {x + size / 2.0f, y + size / 2.0f};

        background.setPosition({x, y});

        fill.setPosition({x, y + size});

        circle.setPosition(center);
        radius_line.setPosition(center);
    }
};

#endif //OOP_COMPLEX_CELL_H