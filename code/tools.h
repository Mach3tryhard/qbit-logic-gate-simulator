#ifndef OOP_TOOLS_H
#define OOP_TOOLS_H
#include <SFML/Graphics.hpp>
#include "node.h"

class tools {
private:
    int connection_index = -1;
public:
    void CheckSelect(sf::RenderWindow& window,std::vector<node>& qbits);
    void DragSelected(sf::RenderWindow& window, std::vector<node>& qbits);

    void StartConnection(sf::RenderWindow& window,std::vector<node>& qbits) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        connection_index = -1;

        for (int i = 0; i < qbits.size(); i++) {
            float posx = qbits[i].get_posx();
            float posy = qbits[i].get_posy();
            if (mousePos.x > posx && mousePos.x < posx + 50.f && mousePos.y > posy && mousePos.y < posy + 50.f) {
                connection_index = i;
                qbits[i].set_connection(true);
                break;
            }
        }
    }

    void EndConnection(sf::RenderWindow& window, std::vector<node>& qbits, std::vector<int> (&lista_adiacenta)[1000]) {
        if (connection_index == -1) return;

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        for (int i = 0; i < qbits.size(); i++) {
            float posx = qbits[i].get_posx();
            float posy = qbits[i].get_posy();

            if (mousePos.x > posx && mousePos.x < posx + 50.f && mousePos.y > posy && mousePos.y < posy + 50.f) {
                qbits[connection_index].set_connection(false);
                if (i != connection_index) {
                    lista_adiacenta[i].push_back(connection_index);
                }
            }
        }
        connection_index = -1;
    }

};

#endif //OOP_TOOLS_H