#include "tools.h"

void tools::CheckSelect(sf::RenderWindow& window,std::vector<node>& qbits) {
    bool found=false;
    int pos_found=-1;
    sf::Vector2i localPosition = sf::Mouse::getPosition(window);

    for (int i=0;i<qbits.size();i++) {
        float posx=qbits[i].get_posx(),posy=qbits[i].get_posy();
        if (localPosition.x > posx && localPosition.x <posx+50.f && localPosition.y > posy && localPosition.y <posy + 50.f ) {
            if (qbits[i].get_selected()==true)
                DragSelected(window, qbits);
            qbits[i].set_selected(true);
            found=true;
            pos_found=i;
        }
    }
    if (!found) {
        for (int i=0;i<qbits.size();i++) {
            qbits[i].set_selected(false);
        }
    }
    else {
        for (int i=0;i<qbits.size();i++) {
            if (i!=pos_found)
                qbits[i].set_selected(false);
        }
    }
}

void tools::DragSelected(sf::RenderWindow& window, std::vector<node>& qbits) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        for (int i = 0; i < qbits.size(); i++) {
            if (qbits[i].get_selected()) {
                qbits[i].UpdatePosition(static_cast<float>(mousePos.x) - 25.f,static_cast<float>(mousePos.y) - 25.f);
            }
        }
    }
}
