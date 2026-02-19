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
        print_text = std::to_string(ca.absolute_squared()*100) + "%";
    }
    void ShowContextMenu() override {
        ImGui::Text("Probability when being measured");
    }
};

#endif //OOP_CHANCE_H