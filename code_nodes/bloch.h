#ifndef OOP_BLOCH_H
#define OOP_BLOCH_H
#include "node.h"
#include "complex.h"
#include "imgui.h"
#include <cstdint>
#include <cmath>

class bloch : public node {
private:
    sf::CircleShape sphere_outline;
    sf::CircleShape equator;
    sf::VertexArray axes_lines;
    sf::CircleShape meridian;

    sf::RectangleShape needle_line;
    sf::CircleShape needle_tip;

    float phys_x = 0;
    float phys_y = 0;
    float phys_z = 1;

public:
    bloch(float x, float y) : node(x, y) {
        float radius = 21.5f;

        sphere_outline.setRadius(radius);
        sphere_outline.setOrigin({radius, radius});
        sphere_outline.setFillColor(sf::Color::Transparent);
        sphere_outline.setOutlineColor(sf::Color(100, 100, 100, 255));
        sphere_outline.setOutlineThickness(1.0f);

        equator.setRadius(radius);
        equator.setOrigin({radius, radius});
        equator.setScale({1.0f, 0.4f});
        equator.setFillColor(sf::Color::Transparent);
        equator.setOutlineColor(sf::Color(100, 100, 100, 255));
        equator.setOutlineThickness(1.0f);

        meridian.setRadius(radius);
        meridian.setOrigin({radius, radius});
        meridian.setScale({0.4f, 1.0f});
        meridian.setFillColor(sf::Color::Transparent);
        meridian.setOutlineColor(sf::Color(100, 100, 100, 255));
        meridian.setOutlineThickness(1.0f);

        axes_lines.setPrimitiveType(sf::PrimitiveType::Lines);

        needle_line.setFillColor(sf::Color::Black);
        needle_tip.setRadius(3.0f);
        needle_tip.setOrigin({3.0f, 3.0f});
        needle_tip.setFillColor(sf::Color(144,189,166));
    }

    void DisplaySpecific(sf::RenderWindow& window) override {
        window.draw(shape);
        sf::Vector2f center = {posx + sizex/2, posy + sizey/2};
        float radius = 21.5f;

        sphere_outline.setPosition(center);
        equator.setPosition(center);
        meridian.setPosition(center);

        window.draw(sphere_outline);
        window.draw(equator);
        window.draw(meridian);

        axes_lines.clear();
        sf::Color axisColor(100, 100, 100, 255);

        sf::Vector2f z_top   = center + GetProjection(0, 0, 1, radius);
        sf::Vector2f z_bot   = center + GetProjection(0, 0, -1, radius);
        sf::Vector2f y_right = center + GetProjection(0, 1, 0, radius);
        sf::Vector2f y_left  = center + GetProjection(0, -1, 0, radius);
        sf::Vector2f x_front = center + GetProjection(1, 0, 0, radius);
        sf::Vector2f x_back  = center + GetProjection(-1, 0, 0, radius);

        axes_lines.append(sf::Vertex(z_top, axisColor));
        axes_lines.append(sf::Vertex(z_bot, axisColor));
        axes_lines.append(sf::Vertex(y_left, axisColor));
        axes_lines.append(sf::Vertex(y_right, axisColor));
        axes_lines.append(sf::Vertex(x_back, axisColor));
        axes_lines.append(sf::Vertex(x_front, axisColor));

        window.draw(axes_lines);

        sf::Vector2f tipPos = center + GetProjection(phys_x, phys_y, phys_z, radius);

        sf::Vector2f diff = tipPos - center;
        float len = std::sqrt(diff.x * diff.x + diff.y * diff.y);
        float angle = std::atan2(diff.y, diff.x) * 180.0f / 3.14159265f;
        float thickness = 2.0f;

        needle_line.setSize({len, thickness});
        needle_line.setOrigin({0.0f, thickness / 2.0f});
        needle_line.setPosition(center);
        needle_line.setRotation(sf::degrees(angle));

        window.draw(needle_line);
        needle_tip.setPosition(tipPos);
        window.draw(needle_tip);
    }

    void LogicToDo(complex ca, complex cb, sf::Time dt, int index) override {

        float ab_star_real = ca.real * cb.real + ca.imag * cb.imag;
        float ab_star_imag = ca.imag * cb.real - ca.real * cb.imag;

        phys_x = 2.0f * ab_star_real;
        phys_y = -2.0f * ab_star_imag;
        phys_z = ca.absolute_squared() - cb.absolute_squared();
    }

    void ShowContextMenu() override {
        ImGui::Text("Bloch Sphere");
        ImGui::Separator();
        ImGui::Text("State Vector:");
        ImGui::Text("X: %.2f (|+> front)", phys_x);
        ImGui::Text("Y: %.2f (|i> right)", phys_y);
        ImGui::Text("Z: %.2f (|0> up)", phys_z);
    }

private:
    sf::Vector2f GetProjection(float x, float y, float z, float radius) {

        float depth_x = -0.4f;
        float depth_y =  0.4f;

        float screen_x = (y * 1.0f) + (x * depth_x);
        float screen_y = (-z * 1.0f) + (x * depth_y);

        return { screen_x * radius, screen_y * radius };
    }
};

#endif //OOP_BLOCH_H