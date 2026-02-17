#ifndef OOP_QBIT_H
#define OOP_QBIT_H
#include <iostream>
#include <winsock2.h>

#include "complex.h"
#include <SFML/Graphics.hpp>

class node {
private:
    sf::Font font;
    sf::Text text;
    sf::RectangleShape shape;
    sf::RectangleShape selected_shape;

    float posx,posy;

    bool selected=false,connection=false;
public:
    node(float x,float y) : text(font), shape({50.0f,50.0f}),selected_shape({55.0f,55.0f}), posx(x),posy(y) {
        if (!this->font.openFromFile("fonts/font.ttf"))
        {
            std::cout<<"EROARE LA LOAD FONT\n";
        }

        this->text.setCharacterSize(16);
        this->text.setFillColor(sf::Color::White);
        this->text.setPosition({posx,posy});

        this->selected_shape.setFillColor(sf::Color(0,200,0));
        this->selected_shape.setPosition({posx-2.5f,posy-2.5f});

        this->shape.setFillColor(sf::Color(100, 100, 110));
        this->shape.setPosition({posx,posy});
    }
    void UpdatePosition(float x, float y);
    void Display(sf::RenderWindow& window);
    float get_posx() {
        return posx;
    }
    float get_posy() {
        return posy;
    }
    bool get_selected() const {
        return selected;
    }
    void set_connection(const bool val)  {
        connection = val;
    }
    void set_selected(const bool val) {
        selected = val;
    }

};


#endif //OOP_QBIT_H