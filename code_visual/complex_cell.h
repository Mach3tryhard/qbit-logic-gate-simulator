#ifndef OOP_COMPLEX_CELL_H
#define OOP_COMPLEX_CELL_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include "complex.h"

class complex_cell {
private:
    sf::RectangleShape background;
    sf::RectangleShape probability_fill;
    sf::CircleShape reference_ring;
    sf::CircleShape filled_circle;
    sf::RectangleShape needle;

    float size;
    float center_x, center_y;

public:
    complex_cell() {
        reference_ring.setFillColor(sf::Color::Transparent);
        reference_ring.setOutlineColor(sf::Color(200, 200, 200, 100));
        reference_ring.setOutlineThickness(1.0f);

        filled_circle.setFillColor(sf::Color(100, 200, 220, 200));
        needle.setFillColor(sf::Color::Black);

        background.setFillColor(sf::Color::White);
        background.setOutlineColor(sf::Color(220, 220, 220));
        background.setOutlineThickness(1.0f);

        probability_fill.setFillColor(sf::Color(100, 200, 100, 100));
        probability_fill.setSize({0.f, 0.f});
    }

    void setup(float cell_size) {
        size = cell_size;
        float half_size = size / 2.0f;

        background.setSize({size, size});
        background.setOrigin({half_size, half_size});

        probability_fill.setSize({size, 0.f});
        probability_fill.setOrigin({half_size, 0.f});

        float max_radius = half_size - 2.0f;
        reference_ring.setRadius(max_radius);
        reference_ring.setOrigin({max_radius, max_radius});

        filled_circle.setRadius(0.f);
        filled_circle.setOrigin({0.f, 0.f});

        float thickness = std::max(1.0f, size * 0.04f);
        needle.setSize({0.f, thickness});
        needle.setOrigin({0.f, thickness / 2.0f});
    }

    void setPosition(float x, float y) {
        center_x = x + size / 2.0f;
        center_y = y + size / 2.0f;

        background.setPosition({center_x, center_y});
        reference_ring.setPosition({center_x, center_y});
        filled_circle.setPosition({center_x, center_y});
        needle.setPosition({center_x, center_y});

        probability_fill.setPosition({center_x, center_y + size/2.0f});
    }

    void setProbability(float prob) {
        if (prob < 0.0f) prob = 0.0f;
        if (prob > 1.0f) prob = 1.0f;

        float h = prob * size;
        probability_fill.setSize({size, h});
        probability_fill.setOrigin({size / 2.0f, h});
    }

    void update(complex z) {
        float magnitude = std::sqrt(z.real * z.real + z.imag * z.imag);
        if (magnitude > 1.0f) magnitude = 1.0f;

        float phase_rad = std::atan2(z.imag, z.real);
        float phase_deg = phase_rad * 180.0f / 3.14159265f;

        float max_radius = (size / 2.0f) - 2.0f;
        float current_radius = max_radius * magnitude;

        filled_circle.setRadius(current_radius);
        filled_circle.setOrigin({current_radius, current_radius});

        needle.setSize({size/2, needle.getSize().y});
        needle.setRotation(sf::degrees(phase_deg));
    }

    void draw(sf::RenderWindow& window) {
        window.draw(background);
        if (probability_fill.getSize().y > 0.5f) {
            window.draw(probability_fill);
        }

        window.draw(reference_ring);

        if (filled_circle.getRadius() > 0.5f) {
            window.draw(filled_circle);
            window.draw(needle);
        }
    }
};


#endif //OOP_COMPLEX_CELL_H