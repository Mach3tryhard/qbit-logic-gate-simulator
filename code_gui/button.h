#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#ifndef OOP_BUTTON_H
#define OOP_BUTTON_H


class Button {
private:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Font font;

    bool activeState = false;

    sf::Color colorSelect = sf::Color(70, 150, 70); // Greenish
    sf::Color colorDelete = sf::Color(200, 70, 70); // Reddish

public:
    Button(float x, float y, float w, float h):text(font) {

        shape.setPosition({x, y});
        shape.setSize({w, h});
        shape.setOutlineThickness(2);
        shape.setOutlineColor(sf::Color::White);

        if (!font.openFromFile("fonts/font.ttf")) {
            std::cout << "GUI Error: Font not found\n";
        }

        text.setFont(font);
        text.setCharacterSize(18);
        text.setFillColor(sf::Color::White);

        updateVisuals();
    }

    bool isClicked(const sf::Event& event, const sf::RenderWindow& window) {
        if (const auto* mousePress = event.getIf<sf::Event::MouseButtonPressed>()) {
            if (mousePress->button == sf::Mouse::Button::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (shape.getGlobalBounds().contains({static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                    activeState = !activeState;
                    updateVisuals();
                    return true;
                }
            }
        }
        return false;
    }

    void updateVisuals() {
        if (activeState) {
            shape.setFillColor(colorDelete);
            text.setString("MODE: DELETE");
        } else {
            shape.setFillColor(colorSelect);
            text.setString("MODE: SELECT");
        }

        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin({textBounds.position.x + textBounds.size.x / 2.0f,
                        textBounds.position.y + textBounds.size.y / 2.0f});
        text.setPosition({shape.getPosition().x + shape.getSize().x / 2.0f,
                          shape.getPosition().y + shape.getSize().y / 2.0f});
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
        window.draw(text);
    }

    bool isDeleteMode() const {
        return activeState;
    }
};

#endif //OOP_BUTTON_H