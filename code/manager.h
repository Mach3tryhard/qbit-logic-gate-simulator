#pragma once
#ifndef OOP_MANAGER_H
#define OOP_MANAGER_H
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <memory>

#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"

#include "node.h"
#include "tools.h"
#include "gui.h"
#include "qubit.h"
#include "logic.h"

class manager {
private:
    sf::RenderWindow windowinst;
    std::vector<std::unique_ptr<node>> nodes;
    sf::Time global_time;
    tools instruments;
    sf::Clock deltaClock;
    logic logicEngine;
    sf::ContextSettings settings;

    manager() = default;
public:
    manager(const manager&) = delete;
    manager& operator=(const manager&) = delete;
    static manager& getInstance() {
        static manager instance;
        return instance;
    }
    void Initialize() {
        settings.antiAliasingLevel = 8;
        windowinst.create(sf::VideoMode({1920, 1009}), "qlgs", sf::Style::Default,sf::State::Windowed,settings);
        windowinst.setVerticalSyncEnabled(true);

        nodes.push_back(std::make_unique<qubit>(100.f, 200.f));
        nodes.push_back(std::make_unique<qubit>(100.f, 300.f));

        ImGui::SFML::Init(windowinst);
    }
    void Event_Loop(bool& shouldExit);
    void SnapNodes(std::vector<std::unique_ptr<node>>& nodes);

    int Run();
};


#endif //OOP_MANAGER_H