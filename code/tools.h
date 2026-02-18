#ifndef OOP_TOOLS_H
#define OOP_TOOLS_H
#include <SFML/Graphics.hpp>
#include "node.h"

class tools {
private:
    int connection_index = -1;
public:
    void CheckSelect(sf::RenderWindow& window,std::vector<node>& nodes);
    void DragSelected(sf::RenderWindow& window, std::vector<node>& nodes);

    void StartConnection(sf::RenderWindow& window,std::vector<node>& nodes);

    void EndConnection(sf::RenderWindow& window, std::vector<node>& nodes) {
        if (connection_index == -1) return;

        nodes[connection_index].set_drafting(false);

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        for (int i = 0; i < nodes.size(); i++) {
            if (i == connection_index) continue;

            float posx = nodes[i].get_posx();
            float posy = nodes[i].get_posy();

            if (mousePos.x > posx && mousePos.x < posx + 50.f &&
                mousePos.y > posy && mousePos.y < posy + 50.f) {

                node* sourceNode = &nodes[connection_index];
                node* targetNode = &nodes[i];

                if (targetNode->isConnectedTo(sourceNode)) {
                    std::cout << "Conexiune refuzata: Exista deja sens invers!\n";
                    break;
                }
                sourceNode->addConnection(targetNode);
                }
        }
        connection_index = -1;
    }

    void UpdateConnectionDrag(sf::RenderWindow& window, std::vector<node>& nodes) {
        if (connection_index != -1) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            nodes[connection_index].update_draft_line((float)mousePos.x, (float)mousePos.y);
        }
    }

};

#endif //OOP_TOOLS_H