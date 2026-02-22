#ifndef OOP_CHANCE_H
#define OOP_CHANCE_H
#include "node.h"
#include "complex.h"
#include "imgui.h"

class chance : public node {
private:
    std::string print_text;
    sf::RectangleShape fill;

    float prob_on=0;
public:
    chance(float x, float y) : node(x, y) {
        print_text = "NaN";
        this->text.setCharacterSize(14);
        fill.setPosition({posx,posy+50.f});
        fill.setSize({50.f,-50.f});
        fill.setFillColor(sf::Color(144,189,166));
        if (!this->font.openFromFile("fonts/jetbrainsmono.ttf"))
        {
            std::cout<<"EROARE LA LOAD FONT\n";
        }
    }
    void DisplaySpecific(sf::RenderWindow& window) override {
        window.draw(shape);
        this->text.setString(print_text);

        sf::FloatRect textRect = this->text.getLocalBounds();

        this->text.setOrigin({textRect.position.x + textRect.size.x / 2.0f,
        textRect.position.y + textRect.size.y / 2.0f});

        this->text.setPosition({posx + sizex/2, posy + sizey/2});

        fill.setPosition({posx,posy+ sizey});
        fill.setSize({sizex,-prob_on / 100.0f * sizey});
        window.draw(fill);

        window.draw(text);
    }
    void LogicToDo(complex ca,complex cb,sf::Time dt,int index) override {
        prob_on = cb.absolute_squared() * 100.0f;
        if (prob_on > 100.0f) prob_on = 100.0f;
        if (prob_on < 0.0f)   prob_on = 0.0f;

        std::stringstream stream;
        stream << std::fixed << std::setprecision(1) << prob_on;
        if (prob_on>99.90f)
            print_text="On";
        else if (prob_on<0.1f)
            print_text="Off";
        else
            print_text = stream.str() + "%";
    }
    void ShowContextMenu() override {
        ImGui::Text("TO DO: Switch between multiple modes");
    }
};

#endif //OOP_CHANCE_H