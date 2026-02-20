#ifndef OOP_TOOLS_H
#define OOP_TOOLS_H
#include <SFML/Graphics.hpp>
#include "node.h"

class tools {
private:
    int connection_index = -1;
    bool multiple_select = false;
    int msposx=0,msposy=0;

    sf::Vector2i last_mouse_pos;
    bool is_dragging_nodes = false;

    sf::RectangleShape select_shape;

    node* nodeWithOpenMenu = nullptr;

    float drag_accumulator_x = 0.0f;
    float drag_accumulator_y = 0.0f;
public:
    tools() {
        select_shape.setOutlineThickness(2.f);
        select_shape.setOutlineColor(sf::Color(255, 255, 255));
        select_shape.setFillColor(sf::Color(100, 100, 100,50));
        select_shape.setOrigin({0.f, 0.f});
    }

    float distancePointToSegment(sf::Vector2f P, sf::Vector2f A, sf::Vector2f B);
    void MultipleSelect(sf::RenderWindow& window,std::vector<std::unique_ptr<node>>& nodes);
    void CheckSelect(sf::RenderWindow& window,std::vector<std::unique_ptr<node>>& nodes);
    void DragSelected(sf::RenderWindow& window, std::vector<std::unique_ptr<node>>& nodes);
    void StartConnection(sf::RenderWindow& window,std::vector<std::unique_ptr<node>>& nodes);
    void EndConnection(sf::RenderWindow& window, std::vector<std::unique_ptr<node>>& nodes);
    void UpdateConnectionDrag(sf::RenderWindow& window, std::vector<std::unique_ptr<node>>& nodes);
    void Deselect(std::vector<std::unique_ptr<node>>& nodes);
    void DrawGhostNode(sf::RenderWindow& window);
    void HandleNodeContextMenu(sf::RenderWindow& window, std::vector<std::unique_ptr<node>>& nodes);
    void DrawGrid(sf::RenderWindow& window);

    bool get_multiple_select() {
        return multiple_select;
    }
    void set_multiple_select(bool val) {
        multiple_select=val;
    }

};

#endif //OOP_TOOLS_H