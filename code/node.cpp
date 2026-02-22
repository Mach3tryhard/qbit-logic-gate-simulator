#include "node.h"

void node::UpdatePosition(float x, float y) {
    posx = x;
    posy = y;
    shape.setPosition({posx, posy});
    text.setPosition({posx, posy});
    selected_shape.setPosition({posx-2.5f, posy-2.5f});
}

void node::DisplayLines(sf::RenderWindow& window) {
    float myX,myY;
    myX = posx + sizex/2;
    myY = posy + sizey/2;

    if (lines.size() != lista_adiacenta.size()) {
        lines.resize(lista_adiacenta.size());
    }

    for (size_t i = 0; i < lista_adiacenta.size(); i++) {
        node* target = lista_adiacenta[i];

        if (target!=nullptr) {
            float targetX,targetY;
            targetX = target->get_posx() + sizex/2;
            targetY = target->get_posy()+ sizey/2;

            updateLineGeometry(lines[i], myX, myY, targetX, targetY, sf::Color::White);

            window.draw(lines[i]);
        }
    }
}

void node::DisplayPopup(sf::RenderWindow& window) {
    ImGui::PushID(this);
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    bool isHovered = shape.getGlobalBounds().contains({(float)mousePos.x, (float)mousePos.y});
    if (isHovered && sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
        ImGui::OpenPopup("NodeMenu");
    }
    if (ImGui::BeginPopup("NodeMenu")) {
        ShowContextMenu();
        ImGui::EndPopup();
    }

    ImGui::PopID();
}

void node::DisplayNode(sf::RenderWindow& window) {
    selected_shape.setSize({sizex+5.f,sizey+5.f});
    shape.setSize({sizex,sizey});

    if (selected) {
        selected_shape.setFillColor(sf::Color(0,200,0));
        window.draw(selected_shape);
    }
    if (drafting) {
        this->selected_shape.setFillColor(sf::Color(200,200,0));
        window.draw(selected_shape);
        window.draw(draft_line);
    }

    DisplayPopup(window);

    DisplaySpecific(window);
}

void node::updateLineGeometry(sf::RectangleShape& line, float x1, float y1, float x2, float y2, sf::Color color) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float length = std::sqrt(dx*dx + dy*dy);
    float angle = std::atan2(dy, dx) * 180.f / 3.14159f;

    line.setSize({length, 2.0f});
    line.setOrigin({0, 1.0f});
    line.setPosition({x1, y1});
    line.setRotation(sf::degrees(angle));
    line.setFillColor(color);
}

void node::update_draft_line(float mouseX, float mouseY) {
    updateLineGeometry(draft_line, posx + sizex/2, posy + sizey/2, mouseX, mouseY, sf::Color::Yellow);
}

void node::DeleteSpecificNode(std::vector<std::unique_ptr<node>>& nodes, node* targetToDelete) {
    if (targetToDelete == nullptr) return;
    for (auto& n : nodes) {
        n->removeConnection(targetToDelete);
    }

    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        if (it->get() == targetToDelete) {
            nodes.erase(it);
            return;
        }
    }
}

void node::removeConnection(node* targetToRemove) {
    for (auto it = lista_adiacenta.begin(); it != lista_adiacenta.end(); ) {
        if (*it == targetToRemove) {
            long index = std::distance(lista_adiacenta.begin(), it);

            if (index < lines.size()) {
                lines.erase(lines.begin() + index);
            }

            it = lista_adiacenta.erase(it);

        } else {
            ++it;
        }
    }
}

bool node::isConnectedTo(node* other) {
    for (node* n : lista_adiacenta) {
        if (n == other) return true;
    }
    return false;
}

void node::addConnection(node* target) {
    if (isConnectedTo(target)) return;

    lista_adiacenta.push_back(target);
    lines.emplace_back();
}