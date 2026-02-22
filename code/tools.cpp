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

        for (size_t i=0;i<nodes.size();i++) {
            if (nodes[i]->get_posx()+nodes[i]->getsizex()>minposx && nodes[i]->get_posx()<maxposx && nodes[i]->get_posy()+nodes[i]->getsizey()>minposy && nodes[i]->get_posy()<maxposy) {
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

            if (localPosition.x > posx && localPosition.x < posx + nodes[i]->getsizex() &&
                localPosition.y > posy && localPosition.y < posy + nodes[i]->getsizey()) {

                nodes[i]->DeleteSpecificNode(nodes, nodes[i].get());
                return;
            }
        }

        for (auto& sourceNode : nodes) {
            sf::Vector2f A(sourceNode->get_posx() + sourceNode->getsizex()/2, sourceNode->get_posy() + sourceNode->getsizey()/2);

            for (node* targetNode : sourceNode->get_connections()) {
                sf::Vector2f B(targetNode->get_posx() + sourceNode->getsizex()/2, targetNode->get_posy() + sourceNode->getsizey()/2);

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

    for (size_t i = 0; i < nodes.size(); i++) {
        float posx = nodes[i]->get_posx();
        float posy = nodes[i]->get_posy();

        if (localPosition.x > posx && localPosition.x < posx + nodes[i]->getsizex() &&
            localPosition.y > posy && localPosition.y < posy + nodes[i]->getsizey() ) {

            drag_accumulator_x = 0.0f;
            drag_accumulator_y = 0.0f;

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

            float real_dx = static_cast<float>(currentMousePos.x - last_mouse_pos.x);
            float real_dy = static_cast<float>(currentMousePos.y - last_mouse_pos.y);

            drag_accumulator_x += real_dx;
            drag_accumulator_y += real_dy;

            float move_x = 0.0f;
            float move_y = 0.0f;

            if (settings::getInstance().snapping) {
                float snap = (float)settings::getInstance().snapping_val;

                float potential_snap_x = round(drag_accumulator_x / snap) * snap;
                float potential_snap_y = round(drag_accumulator_y / snap) * snap;

                if (potential_snap_x != 0) {
                    move_x = potential_snap_x;
                    drag_accumulator_x -= potential_snap_x;
                }
                if (potential_snap_y != 0) {
                    move_y = potential_snap_y;
                    drag_accumulator_y -= potential_snap_y;
                }
            }
            else {
                move_x = real_dx;
                move_y = real_dy;
            }

            if (move_x != 0 || move_y != 0) {
                for (auto& n : nodes) {
                    if (n->get_selected()) {
                        float newX = n->get_posx() + move_x;
                        float newY = n->get_posy() + move_y;

                        if (settings::getInstance().snapping) {
                            float snap = (float)settings::getInstance().snapping_val;
                            newX = round(newX / snap) * snap;
                            newY = round(newY / snap) * snap;
                        }

                        n->UpdatePosition(newX, newY);
                    }
                }
            }
            last_mouse_pos = currentMousePos;
        }
        else {
            is_dragging_nodes = false;
        }
    }
}

void tools::StartConnection(sf::RenderWindow& window,std::vector<std::unique_ptr<node>>& nodes) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    connection_index = -1;

    for (size_t i = 0; i < nodes.size(); i++) {
        float posx = nodes[i]->get_posx();
        float posy = nodes[i]->get_posy();
        if (mousePos.x > posx && mousePos.x < posx + nodes[i]->getsizex() && mousePos.y > posy && mousePos.y < posy + nodes[i]->getsizey()) {
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

    for (size_t i = 0; i < nodes.size(); i++) {
        if (i == connection_index) continue;

        float posx = nodes[i]->get_posx();
        float posy = nodes[i]->get_posy();

        if (mousePos.x > posx && mousePos.x < posx + nodes[i]->getsizex() &&
            mousePos.y > posy && mousePos.y < posy + nodes[i]->getsizey()) {

            node* sourceNode = nodes[connection_index].get();
            node* targetNode = nodes[i].get();

            /*if (targetNode->isConnectedTo(sourceNode)) {
                std::cout << "Conexiune refuzata: Exista deja sens invers!\n";
                break;
            }*/
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

    float rawX = (float)mousePos.x - 25.f;
    float rawY = (float)mousePos.y - 25.f;

    float ghostX = std::round(rawX / settings::getInstance().snapping_val) * settings::getInstance().snapping_val;
    float ghostY = std::round(rawY / settings::getInstance().snapping_val) * settings::getInstance().snapping_val;

    ghostShape.setPosition({ghostX, ghostY});

    ghostShape.setFillColor(sf::Color(100, 255, 100, 128));

    ghostShape.setOutlineThickness(2.f);
    ghostShape.setOutlineColor(sf::Color(255, 255, 255, 200));

    window.draw(ghostShape);
}

void tools::HandleNodeContextMenu(sf::RenderWindow& window, std::vector<std::unique_ptr<node>>& nodes) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && !ImGui::GetIO().WantCaptureMouse) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        for (auto& n : nodes) {
            float px = n->get_posx();
            float py = n->get_posy();
            if (mousePos.x > px && mousePos.x < n->getsizex() &&
                mousePos.y > py && mousePos.y < py + n->getsizey()) {
                nodeWithOpenMenu = n.get();
                ImGui::OpenPopup("NodeContextMenu");
                break;
                }
        }
    }

    if (ImGui::BeginPopup("NodeContextMenu")) {

        if (nodeWithOpenMenu != nullptr) {
            nodeWithOpenMenu->ShowContextMenu();
        }

        ImGui::EndPopup();
    } else {
        if (!ImGui::IsPopupOpen("NodeContextMenu")) {
            nodeWithOpenMenu = nullptr;
        }
    }
}

void tools::DrawGrid(sf::RenderWindow& window) {
    int gridSize = settings::getInstance().snapping_val;
    if (gridSize <= 0) return;

    sf::View view = window.getView();
    sf::Vector2f center = view.getCenter();
    sf::Vector2f size = view.getSize();

    float left = center.x - (size.x / 2.0f);
    float top = center.y - (size.y / 2.0f);
    float right = left + size.x;
    float bottom = top + size.y;

    int startX = (int)(std::floor(left / gridSize) * gridSize);
    int startY = (int)(std::floor(top / gridSize) * gridSize);

    sf::VertexArray gridLines(sf::PrimitiveType::Lines);

    sf::Color gridColor = sf::Color(60, 60, 60, 100);

    for (float x = (float)startX; x < right; x += (float)gridSize) {
        gridLines.append(sf::Vertex(sf::Vector2f(x, top), gridColor));
        gridLines.append(sf::Vertex(sf::Vector2f(x, bottom), gridColor));
    }

    for (float y = (float)startY; y < bottom; y += (float)gridSize) {
        gridLines.append(sf::Vertex(sf::Vector2f(left, y), gridColor));
        gridLines.append(sf::Vertex(sf::Vector2f(right, y), gridColor));
    }

    window.draw(gridLines);
}