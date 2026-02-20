#ifndef OOP_CHANCE_H
#define OOP_CHANCE_H
#include "node.h"
#include "complex.h"
#include "imgui.h"

class chance : public node {
private:
    std::string print_text;
public:
    chance(float x, float y) : node(x, y) {

    }
    void DisplaySpecific(sf::RenderWindow& window) override {
        this->text.setString(print_text);
        window.draw(text);
    }
    void LogicToDo(complex ca,complex cb) override {
        float prob_on = cb.absolute_squared() * 100.0f;

        std::stringstream stream;
        stream << std::fixed << std::setprecision(1) << prob_on;

        print_text = stream.str() + "%";
    }
    void ShowContextMenu() override {
        ImGui::Text("TO DO: Switch between multiple modes");
    }
};

#endif //OOP_CHANCE_H