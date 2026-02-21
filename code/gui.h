#pragma once
#ifndef OOP_GUI_H
#define OOP_GUI_H
#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"
#include "node.h"
#include "factory.h"
#include "logic.h"
#include "settings.h"

class gui {
private:
    gui() = default;
    int mode = 0;
    int previous_mode = 0;

    NodeType build_type = NodeType::None;

    std::map<std::string, sf::Texture> button_textures;

    void SpawnButton(sf::RenderWindow& window, std::vector<std::unique_ptr<node>>& nodes, const char* label, const std::string& imagePath, NodeType type);
public:
    gui(const gui&) = delete;
    gui& operator=(const gui&) = delete;
    static gui& getInstance() {
        static gui instance;
        return instance;
    }
    void MakeFPS(sf::RenderWindow & window,sf::Time& dt);
    void MakeSettings(std::vector<std::unique_ptr<node>>& nodes);
    void MakeHalfTurns(sf::RenderWindow& window, std::vector<std::unique_ptr<node>>& nodes);
    void MakeQuarterTurns(sf::RenderWindow& window, std::vector<std::unique_ptr<node>>& nodes);
    void MakeNodeCreator(sf::RenderWindow & window,std::vector<std::unique_ptr<node>>& nodes);
    void MakeSpinning(sf::RenderWindow& window, std::vector<std::unique_ptr<node>>& nodes);
    void MakeFormulaic(sf::RenderWindow& window, std::vector<std::unique_ptr<node>>& nodes);
    void MakeToolbox(sf::RenderWindow& window);
    void RunGui(sf::RenderWindow & window,sf::Time& dt,std::vector<std::unique_ptr<node>>& nodes,std::vector<CompilerMessage>& messages);

    sf::Texture& GetTexture(const std::string& filename);

    int getMode() const {
        return mode;
    }
};


#endif //OOP_GUI_H