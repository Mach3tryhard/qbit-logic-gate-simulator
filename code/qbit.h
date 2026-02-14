#ifndef OOP_QBIT_H
#define OOP_QBIT_H
#include <iostream>

#include "complex.h"
#include <SFML/Graphics.hpp>

class qbit {
private:
    complex a,b;
    sf::Font font;
    sf::Text text;
    sf::RectangleShape shape;
public:
    qbit() : text(font), shape({50.0f,50.0f}) {
        if (!this->font.openFromFile("fonts/font.ttf"))
        {
            std::cout<<"EROARE LA LOAD FONT\n";
        }

        this->text.setCharacterSize(16);
        this->text.setFillColor(sf::Color::White);

        shape.setFillColor(sf::Color(100, 100, 110));
    }
    void Display(sf::RenderWindow& window) {
        //std::cout<<a.real<<" "<<a.imag<<" "<<b.real<<" "<<b.imag<<"\n";
        std::string value = std::to_string(a.real) + " " + std::to_string(a.imag) + "*i \n" + std::to_string(b.real) + " " + std::to_string(b.imag) + "*i \n";
        this->text.setString(value);
        window.draw(shape);
        window.draw(text);
    }
};


#endif //OOP_QBIT_H