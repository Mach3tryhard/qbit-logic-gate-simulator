#include "tools.h"
#include "gui.h"
#include <cmath>

float tools::distancePointToSegment(sf::Vector2f P, sf::Vector2f A, sf::Vector2f B) {
    float l2 = (B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y);

    if (l2 == 0.0f) return std::sqrt((P.x - A.x) * (P.x - A.x) + (P.y - A.y) * (P.y - A.y));

    float t = std::max(0.0f, std::min(1.0f, ((P.x - A.x) * (B.x - A.x) + (P.y - A.y) * (B.y - A.y)) / l2));

    sf::Vector2f projection = A + t * (B - A);

    return std::sqrt((P.x - projection.x) * (P.x - projection.x) + (P.y - projection.y) * (P.y - projection.y));
}

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

void tools::CheckSelect(sf::RenderWindow& window, std::vector<std::unique_ptr<node>>& nodes) {
    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosFloat(static_cast<float>(localPosition.x), static_cast<float>(localPosition.y));

    if (gui::getInstance().getMode() == 1) {

        for (int i = nodes.size() - 1; i >= 0; i--) {
            float posx = nodes[i]->get_posx();
            float posy = nodes[i]->get_posy();

            if (localPosition.x > posx && localPosition.x < posx + 50.f &&
                localPosition.y > posy && localPosition.y < posy + 50.f) {

                nodes[i]->DeleteSpecificNode(nodes, nodes[i].get());
                return;
            }
        }

        for (auto& sourceNode : nodes) {
            sf::Vector2f A(sourceNode->get_posx() + 25.f, sourceNode->get_posy() + 25.f);

            for (node* targetNode : sourceNode->get_connections()) {
                sf::Vector2f B(targetNode->get_posx() + 25.f, targetNode->get_posy() + 25.f);

                float dist = distancePointToSegment(mousePosFloat, A, B);

                if (dist < 8.0f) {
                    sourceNode->removeConnection(targetNode);
                    std::cout << "Conexiune stearsa manual!\n";
                    return;
                }
            }
        }

        return;
    }
    bool found = false;

    for (int i = 0; i < nodes.size(); i++) {
        float posx = nodes[i]->get_posx();
        float posy = nodes[i]->get_posy();

        if (localPosition.x > posx && localPosition.x < posx + 50.f &&
            localPosition.y > posy && localPosition.y < posy + 50.f ) {

            // Setăm variabilele de drag
            is_dragging_nodes = true;
            last_mouse_pos = localPosition;

            if (!nodes[i]->get_selected()) {
                for (auto& n : nodes) n->set_selected(false);
                nodes[i]->set_selected(true);
            }

            found = true;
            break;
        }
    }

    if (!found) {
        for (auto& n : nodes) n->set_selected(false);
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

void tools::EndConnection(sf::RenderWindow& window, std::vector<std::unique_ptr<node>>& nodes) {
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

void tools::UpdateConnectionDrag(sf::RenderWindow& window, std::vector<std::unique_ptr<node>>& nodes) {
    if (connection_index != -1) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        nodes[connection_index]->update_draft_line((float)mousePos.x, (float)mousePos.y);
    }
}

void tools::Deselect(std::vector<std::unique_ptr<node>>& nodes) {
    if (gui::getInstance().getMode()!=0) {
        for (size_t i=0;i<nodes.size();i++) {
            nodes[i]->set_selected(false);
        }
    }
}

void tools::DrawGhostNode(sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    sf::RectangleShape ghostShape(sf::Vector2f(50.f, 50.f));

    float ghostX = (float)mousePos.x - 25.f;
    float ghostY = (float)mousePos.y - 25.f;

    ghostShape.setPosition({ghostX, ghostY});

    ghostShape.setFillColor(sf::Color(100, 255, 100, 128));

    ghostShape.setOutlineThickness(2.f);
    ghostShape.setOutlineColor(sf::Color(255, 255, 255, 200));

    window.draw(ghostShape);
}