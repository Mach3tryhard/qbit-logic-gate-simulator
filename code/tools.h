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
public:
    tools() {
        select_shape.setOutlineThickness(2.f);
        select_shape.setOutlineColor(sf::Color(255, 255, 255));
        select_shape.setFillColor(sf::Color(100, 100, 100,50));
        select_shape.setOrigin({0.f, 0.f});
    }

    void MultipleSelect(sf::RenderWindow& window,std::vector<std::unique_ptr<node>>& nodes);

    void CheckSelect(sf::RenderWindow& window,std::vector<std::unique_ptr<node>>& nodes);
    void DragSelected(sf::RenderWindow& window, std::vector<std::unique_ptr<node>>& nodes);

    void StartConnection(sf::RenderWindow& window,std::vector<std::unique_ptr<node>>& nodes);

    void EndConnection(sf::RenderWindow& window, std::vector<std::unique_ptr<node>>& nodes) {
        if (connection_index == -1) return;

        nodes[connection_index]->set_drafting(false);

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        for (int i = 0; i < nodes.size(); i++) {
            if (i == connection_index) continue;

            float posx = nodes[i]->get_posx();
            float posy = nodes[i]->get_posy();

            if (mousePos.x > posx && mousePos.x < posx + 50.f &&
                mousePos.y > posy && mousePos.y < posy + 50.f) {

                node* sourceNode = nodes[connection_index].get();
                node* targetNode = nodes[i].get();

                if (targetNode->isConnectedTo(sourceNode)) {
                    std::cout << "Conexiune refuzata: Exista deja sens invers!\n";
                    break;
                }
                sourceNode->addConnection(targetNode);
                }
        }
        connection_index = -1;
    }

    void UpdateConnectionDrag(sf::RenderWindow& window, std::vector<std::unique_ptr<node>>& nodes) {
        if (connection_index != -1) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            nodes[connection_index]->update_draft_line((float)mousePos.x, (float)mousePos.y);
        }
    }
    bool get_multiple_select() {
        return multiple_select;
    }
    void set_multiple_select(bool val) {
        multiple_select=val;
    }

};

#endif //OOP_TOOLS_H