#ifndef OOP_BLOCH_H
#define OOP_BLOCH_H
#include "node.h"
#include "complex.h"
#include "imgui.h"
#include <cstdint>

class bloch : public node {
private:
    sf::CircleShape sphere_outline;
    sf::CircleShape equator;
    sf::CircleShape meridian;
    sf::RectangleShape needle_shape;
    sf::CircleShape needle_tip;
    sf::VertexArray axes;

    float phys_x = 0;
    float phys_y = 0;
    float phys_z = 1;
public:
    bloch(float x, float y) : node(x, y) {
        float radius = 22.0f;
        sphere_outline.setRadius(radius);
        sphere_outline.setOrigin({radius, radius});
        sphere_outline.setFillColor(sf::Color::Transparent);
        sphere_outline.setOutlineColor(sf::Color(150, 150, 150,255));
        sphere_outline.setOutlineThickness(1.5f);

        equator.setRadius(radius);
        equator.setOrigin({radius, radius});
        equator.setScale({1.0f, 0.3f});
        equator.setFillColor(sf::Color::Transparent);
        equator.setOutlineColor(sf::Color(150, 150, 150, 255));
        equator.setOutlineThickness(2.0f);

        meridian.setRadius(radius);
        meridian.setOrigin({radius, radius});
        meridian.setScale({0.3f, 1.0f});
        meridian.setFillColor(sf::Color::Transparent);
        meridian.setOutlineColor(sf::Color(150, 150, 150, 255));
        meridian.setOutlineThickness(2.0f);

        needle_shape.setFillColor(sf::Color::Black);

        needle_tip.setRadius(2.5f);
        needle_tip.setOrigin({2.5f, 2.5f});
        needle_tip.setFillColor(sf::Color::Red);

        axes.setPrimitiveType(sf::PrimitiveType::Lines);
        axes.resize(6);
        sf::Color axisColor(150, 150, 150);

        axes[0].position = {0.f, -radius};
        axes[0].color = axisColor;
        axes[1].position = {0.f, radius};
        axes[1].color = axisColor;

        axes[2].position = {-radius, 0.f};
        axes[2].color = axisColor;
        axes[3].position = {radius, 0.f};
        axes[3].color = axisColor;

        float depth = radius * 0.3f;

        axes[4].position = {-depth, depth};
        axes[4].color = axisColor;
        axes[5].position = {depth, -depth};
        axes[5].color = axisColor;
    }
    void DisplaySpecific(sf::RenderWindow& window) override {
        window.draw(shape);
        sf::Vector2f center = {posx + 25.0f, posy + 25.0f};

        sphere_outline.setPosition(center);
        equator.setPosition(center);
        meridian.setPosition(center);

        window.draw(sphere_outline);
        window.draw(equator);
        window.draw(meridian);

        float radius = 22.0f;
        float scale = 0.3f;

        float u = radius * (phys_y + scale * phys_x);
        float v = radius * (-phys_z + scale * phys_x);

        sf::Vector2f endPoint = center + sf::Vector2f(u, v);

        sf::Vector2f diff = endPoint - center;
        float len = std::sqrt(diff.x * diff.x + diff.y * diff.y);
        float angle = std::atan2(diff.y, diff.x) * 180.0f / 3.14159265f;
        float thickness = 2.5f;

        needle_shape.setSize({len, thickness});
        needle_shape.setOrigin({0.0f, thickness / 2.0f});
        needle_shape.setPosition(center);
        needle_shape.setRotation(sf::degrees(angle));

        sf::Transform transform;
        transform.translate(center);
        window.draw(axes, transform);

        window.draw(needle_shape);
        needle_tip.setPosition(endPoint);
        window.draw(needle_tip);
    }
    void LogicToDo(complex ca, complex cb, sf::Time dt,int index) override {
        complex b_conj = {cb.real, -cb.imag};

        complex prod = ca*b_conj;

        phys_x = 2.0f * prod.real;
        phys_y = 2.0f * prod.imag;
        phys_z = ca.absolute_squared() - cb.absolute_squared();

        sf::Color c;

        c.r = static_cast<unsigned char>(std::abs(phys_z) * 255);
        c.g = static_cast<unsigned char>(std::abs(phys_y) * 255);
        c.b = static_cast<unsigned char>(std::abs(phys_x) * 255);
        c.a = 255;

        if (c.r < 20 && c.g < 20 && c.b < 20) {
            c = sf::Color::Black;
        }

        needle_tip.setFillColor(c);
    }
    void ShowContextMenu() override {
        ImGui::Text("Bloch Sphere Visualization");
        ImGui::Text("Red = Z Axis (|0>, |1>)");
        ImGui::Text("Blue = X Axis (|+>, |->)");
        ImGui::Text("Green = Y Axis (|i>, |-i>)");
        ImGui::Separator();
        ImGui::Text("Vector: (%.2f, %.2f, %.2f)", phys_x, phys_y, phys_z);
    }
};

#endif //OOP_BLOCH_H