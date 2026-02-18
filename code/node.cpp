#include "node.h"

#include <cmath>

void node::UpdatePosition(float x, float y) {
    posx = x;
    posy = y;
    shape.setPosition({posx, posy});
    text.setPosition({posx, posy});
    selected_shape.setPosition({posx - 2.5f, posy - 2.5f});
}

void node::DisplayLines(sf::RenderWindow& window) {

    float myX = posx + 25.f;
    float myY = posy + 25.f;

    if (lines.size() != lista_adiacenta.size()) {
        lines.resize(lista_adiacenta.size());
    }

    for (int i = 0; i < lista_adiacenta.size(); i++) {
        node* target = lista_adiacenta[i];

        if (target!=nullptr) {
            float targetX = target->get_posx() + 25.f;
            float targetY = target->get_posy() + 25.f;

            updateLineGeometry(lines[i], myX, myY, targetX, targetY, sf::Color::White);

            window.draw(lines[i]);
        }
    }

    if (drafting) {
        window.draw(draft_line);
    }

    std::string value = "\n  H";
    this->text.setString(value);

    if (selected) {
        selected_shape.setFillColor(sf::Color(0,200,0));
        window.draw(selected_shape);
    }
    if (drafting) {
        this->selected_shape.setFillColor(sf::Color(200,200,0));
        window.draw(selected_shape);
    }

    window.draw(shape);
    window.draw(text);
}

void node::DisplayNode(sf::RenderWindow& window) {

    if (drafting) {
        window.draw(draft_line);
    }

    std::string value = "\n  H";
    this->text.setString(value);

    if (selected) {
        selected_shape.setFillColor(sf::Color(0,200,0));
        window.draw(selected_shape);
    }
    if (drafting) {
        this->selected_shape.setFillColor(sf::Color(200,200,0));
        window.draw(selected_shape);
    }

    window.draw(shape);
    window.draw(text);
}

void node::updateLineGeometry(sf::RectangleShape& line, float x1, float y1, float x2, float y2, sf::Color color) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float length = std::sqrt(dx*dx + dy*dy);
    float angle = std::atan2(dy, dx) * 180.f / 3.14159f;

    line.setSize({length, 2.0f});
    line.setOrigin({0, 1.0f});
    line.setPosition({x1, y1});
    line.setRotation(sf::degrees(angle));
    line.setFillColor(color);
}

void node::update_draft_line(float mouseX, float mouseY) {
    updateLineGeometry(draft_line, posx + 25.f, posy + 25.f, mouseX, mouseY, sf::Color::Yellow);
}
