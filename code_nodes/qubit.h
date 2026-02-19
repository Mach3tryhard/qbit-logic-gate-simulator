#ifndef OOP_QUBIT_H
#define OOP_QUBIT_H
#include <cmath>

#include "node.h"
#include "complex.h"
#include "imgui.h"

class qubit : public node {
private:
    complex a,b;
    std::string print_text;
public:
    qubit(float x, float y) : node(x, y) {
        a.real=0;a.imag=0;
        b.real=1;b.imag=0;
        print_text="|0>";
    }
    void DisplaySpecific(sf::RenderWindow& window) override {

        this->text.setString(print_text);
        window.draw(text);
    }
    void ShowContextMenu() override {
        ImGui::Text("Set State:");
        ImGui::Separator();

        if (ImGui::MenuItem("|0>")) {
            a.real=0;a.imag=0;
            b.real=1;b.imag=0;
            print_text="|0>";
        }
        if (ImGui::MenuItem("|1>")) {
            a.real=1;a.imag=0;
            b.real=0;b.imag=0;
            print_text="|1>";
        }
        ImGui::Separator();
        if (ImGui::MenuItem("|+>")) {
            a.real=1/std::sqrt(2);a.imag=0;
            b.real=1/std::sqrt(2);b.imag=0;
            print_text="|+>";
        }
        if (ImGui::MenuItem("|->")) {
            a.real=1/std::sqrt(2);a.imag=0;
            b.real=-1/std::sqrt(2);b.imag=0;
            print_text="|->";
        }
        ImGui::Separator();
        if (ImGui::MenuItem("|i>")) {
            a.real=1/std::sqrt(2);a.imag=0;
            b.real=0;b.imag=1/std::sqrt(2);
            print_text="|i>";
        }
        if (ImGui::MenuItem("|-i>")) {
            a.real=1/std::sqrt(2);a.imag=0;
            b.real=1;b.imag=-1/std::sqrt(2);
            print_text="|-i>";
        }
    }
};


#endif //OOP_QUBIT_H