#include "node.h"

void node::UpdatePosition(float x, float y) {
    posx = x;
    posy = y;
    shape.setPosition({posx, posy});
    text.setPosition({posx, posy});
    selected_shape.setPosition({posx - 2.5f, posy - 2.5f});
}

void node::Display(sf::RenderWindow& window) {

    std::string value = "\n  H";
    this->text.setString(value);

    if (selected) {
        selected_shape.setFillColor(sf::Color(0,200,0));
        window.draw(selected_shape);
    }
    if (connection) {
        this->selected_shape.setFillColor(sf::Color(200,200,0));
        window.draw(selected_shape);
    }

    window.draw(shape);
    window.draw(text);
}