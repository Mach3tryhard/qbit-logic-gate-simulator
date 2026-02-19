#ifndef OOP_QBIT_H
#define OOP_QBIT_H
#include <iostream>
#include <winsock2.h>
#include <memory>
#include <SFML/Graphics.hpp>

class node {
protected:
    sf::Font font;
    sf::Text text;
    sf::RectangleShape shape;
    sf::RectangleShape selected_shape;

    std::vector<sf::RectangleShape> lines;
    sf::RectangleShape draft_line;

    float posx,posy;

    bool selected=false,drafting=false,connected=false;

    std::vector<node*> lista_adiacenta;
public:
    virtual ~node() = default;
    node(float x,float y) : text(font), shape({50.0f,50.0f}),
    selected_shape({55.0f,55.0f}), posx(x),posy(y){
        if (!this->font.openFromFile("fonts/font.ttf"))
        {
            std::cout<<"EROARE LA LOAD FONT\n";
        }

        this->text.setCharacterSize(18);
        this->text.setFillColor(sf::Color::Black);
        this->text.setPosition({posx,posy});

        this->selected_shape.setFillColor(sf::Color(0,200,0));
        this->selected_shape.setPosition({posx-2.5f,posy-2.5f});

        this->draft_line.setFillColor(sf::Color(200,200,0));

        this->shape.setFillColor(sf::Color(255, 255, 255));
        this->shape.setPosition({posx,posy});
    }

    virtual void ShowContextMenu()=0;
    virtual void DisplaySpecific(sf::RenderWindow& window)=0;

    void UpdatePosition(float x, float y);
    void updateLineGeometry(sf::RectangleShape& line, float x1, float y1, float x2, float y2, sf::Color color);
    void DisplayLines(sf::RenderWindow& window);
    void DisplayNode(sf::RenderWindow& window);
    void update_draft_line(float mouseX, float mouseY);
    void addConnection(node* target);
    bool isConnectedTo(node* other);
    void removeConnection(node* targetToRemove);
    void DeleteSpecificNode(std::vector<std::unique_ptr<node>>& nodes, node* targetToDelete);
    float get_posx() {
        return posx;
    }
    float get_posy() {
        return posy;
    }
    bool get_selected() const {
        return selected;
    }
    void set_drafting(const bool val)  {
        drafting = val;
    }
    void set_selected(const bool val) {
        selected = val;
    }
    const std::vector<node*>& get_connections() const {
        return lista_adiacenta;
    }
};


#endif //OOP_QBIT_H