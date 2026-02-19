#include "tools.h"
#include "gui.h"

void tools::MultipleSelect(sf::RenderWindow& window,std::vector<std::unique_ptr<node>>& nodes) {
    if (multiple_select==true) {
        sf::Vector2i localPosition = sf::Mouse::getPosition(window);

        float minposx=std::min(localPosition.x,msposx),minposy=std::min(localPosition.y,msposy)
        ,maxposx=std::max(localPosition.x,msposx),maxposy=std::max(localPosition.y,msposy);

        select_shape.setSize({abs((float)localPosition.x-msposx), abs((float)localPosition.y-msposy)});
        select_shape.setPosition({minposx, minposy});
        window.draw(select_shape);

        for (int i=0;i<nodes.size();i++) {
            if (nodes[i]->get_posx()+50.f>minposx && nodes[i]->get_posx()<maxposx && nodes[i]->get_posy()+50.f>minposy && nodes[i]->get_posy()<maxposy) {
                nodes[i]->set_selected(true);
            }
        }
    }
}

void tools::CheckSelect(sf::RenderWindow& window,std::vector<std::unique_ptr<node>>& nodes) {
    bool found=false;
    sf::Vector2i localPosition = sf::Mouse::getPosition(window);

    for (int i=0;i<nodes.size();i++) {
        float posx=nodes[i]->get_posx(),posy=nodes[i]->get_posy();
        if (localPosition.x > posx && localPosition.x <posx+50.f && localPosition.y > posy && localPosition.y <posy + 50.f ) {
            if (gui::getInstance().getMode()==0) {
                is_dragging_nodes = true;
                last_mouse_pos = localPosition;
                if (!nodes[i]->get_selected()) {
                    for (auto& n : nodes) n->set_selected(false);
                    nodes[i]->set_selected(true);
                }
                found=true;
                return;
            }
            if (gui::getInstance().getMode()==1) {
                nodes[i]->DeleteSpecificNode(nodes,nodes[i].get());
                return;
            }
        }
    }
    if (!found && gui::getInstance().getMode() == 0) {
        for (auto& n : nodes) {
            n->set_selected(false);
        }

        multiple_select = true;
        msposx = localPosition.x;
        msposy = localPosition.y;
    }
}

void tools::DragSelected(sf::RenderWindow& window, std::vector<std::unique_ptr<node>>& nodes) {
    if (is_dragging_nodes) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);

            float dx = static_cast<float>(currentMousePos.x - last_mouse_pos.x);
            float dy = static_cast<float>(currentMousePos.y - last_mouse_pos.y);
            if (dx != 0 || dy != 0) {
                for (auto& n : nodes) {
                    if (n->get_selected()) {
                        n->UpdatePosition(n->get_posx() + dx, n->get_posy() + dy);
                    }
                }
                last_mouse_pos = currentMousePos;
            }
        }
        else {
            is_dragging_nodes = false;
        }
    }
}

void tools::StartConnection(sf::RenderWindow& window,std::vector<std::unique_ptr<node>>& nodes) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    connection_index = -1;

    for (int i = 0; i < nodes.size(); i++) {
        float posx = nodes[i]->get_posx();
        float posy = nodes[i]->get_posy();
        if (mousePos.x > posx && mousePos.x < posx + 50.f && mousePos.y > posy && mousePos.y < posy + 50.f) {
            connection_index = i;
            nodes[i]->set_drafting(true);
            break;
        }
    }
}