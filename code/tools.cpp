#include "tools.h"

void tools::CheckSelect(sf::RenderWindow& window,std::vector<node>& nodes) {
    bool found=false;
    int pos_found=-1;
    sf::Vector2i localPosition = sf::Mouse::getPosition(window);

    for (int i=0;i<nodes.size();i++) {
        float posx=nodes[i].get_posx(),posy=nodes[i].get_posy();
        if (localPosition.x > posx && localPosition.x <posx+50.f && localPosition.y > posy && localPosition.y <posy + 50.f ) {
            if (nodes[i].get_selected()==true)
                DragSelected(window, nodes);
            nodes[i].set_selected(true);
            found=true;
            pos_found=i;
        }
    }
    if (!found) {
        for (int i=0;i<nodes.size();i++) {
            nodes[i].set_selected(false);
        }
    }
    else {
        for (int i=0;i<nodes.size();i++) {
            if (i!=pos_found)
                nodes[i].set_selected(false);
        }
    }
}

void tools::DragSelected(sf::RenderWindow& window, std::vector<node>& nodes) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes[i].get_selected()) {
                nodes[i].UpdatePosition(static_cast<float>(mousePos.x) - 25.f,static_cast<float>(mousePos.y) - 25.f);
            }
        }
    }
}
