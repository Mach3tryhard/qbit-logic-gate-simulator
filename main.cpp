#include <iostream>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>

#include "qbit.h"

int main() {

    sf::RenderWindow window;

    window.create(sf::VideoMode({800, 700}), "qlgs", sf::Style::Default);

    window.setVerticalSyncEnabled(true);

    qbit qubit;

    while(window.isOpen()) {
        bool shouldExit = false;

        while(const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                std::cout << "Fereastra a fost închisă\n";
            }
            else if (event->is<sf::Event::Resized>()) {
                std::cout << "New width: " << window.getSize().x << '\n'
                          << "New height: " << window.getSize().y << '\n';
            }
            else if (event->is<sf::Event::KeyPressed>()) {
                const auto* keyPressed = event->getIf<sf::Event::KeyPressed>();
                std::cout << "Received key " << (keyPressed->scancode == sf::Keyboard::Scancode::X ? "X" : "(other)") << "\n";
                if(keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                    shouldExit = true;
                }
            }
        }
        if(shouldExit) {
            window.close();
            std::cout << "Fereastra a fost închisă (shouldExit == true)\n";
            break;
        }
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(300ms);

        window.clear();

        /// MAIN DRAWING PLACE
        qubit.Display(window);

        window.display();
    }

    std::cout << "Programul a terminat execuția\n";
    return 0;
}
