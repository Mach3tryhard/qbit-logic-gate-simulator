#pragma once
#ifndef OOP_GUI_H
#define OOP_GUI_H
#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"
#include "node.h"

class gui {
private:
    gui() = default;
    int mode = 0;
    int previous_mode = 0;

public:
    gui(const gui&) = delete;
    gui& operator=(const gui&) = delete;
    static gui& getInstance() {
        static gui instance;
        return instance;
    }

    void MakeNodeCreator(sf::RenderWindow & window,std::vector<std::unique_ptr<node>>& nodes);
    void MakeToolbox(sf::RenderWindow& window);
    void RunGui(sf::RenderWindow & window,sf::Time& dt,std::vector<std::unique_ptr<node>>& nodes);

    int getMode() const {
        return mode;
    }
};


#endif //OOP_GUI_H