#ifndef OOP_AMPLITUDE_DISPLAY_H
#define OOP_AMPLITUDE_DISPLAY_H
#include <map>
#include "node.h"
#include "complex_cell.h"
#include "imgui.h"

#ifndef OOP_AMPLITUDE_H
#define OOP_AMPLITUDE_H
#include <map>
#include "node.h"
#include "complex_cell.h"
#include "imgui.h"
#include <iostream>

class amplitude : public node {
private:
    std::vector<complex_cell> cells;
    std::map<int, std::pair<complex, complex>> qubit_states;
    int num_qubits = 0;

    int grid_cols = 1;
    int grid_rows = 1;

    sf::Texture iconTexture;
    sf::Sprite iconSprite;

public:
    amplitude(float x, float y) : node(x, y), iconSprite(iconTexture) {
        ResizeState(0);

        if (!iconTexture.loadFromFile("images/output/amps.png")) {
            this->text.setString("Amp");
            this->text.setCharacterSize(10);
            this->text.setFillColor(sf::Color::Black);
        } else {
            iconTexture.generateMipmap();
            iconTexture.setSmooth(true);
            iconSprite.setTexture(iconTexture, true);
        }
    }

    void ResizeState(int n_qubits) {
        if (n_qubits < 1){
            n_qubits=2;
        }

        if (num_qubits == n_qubits && !cells.empty()) return;

        num_qubits = n_qubits;
        int num_states = 1 << num_qubits;

        cells.resize(num_states);

        grid_cols = 1 << (num_qubits / 2);
        grid_rows = 1 << ((num_qubits + 1) / 2);

        float cellSize = set_sizex / 2.0f;

        float new_width = grid_cols * cellSize;
        float new_height = grid_rows * cellSize;

        this->sizex = new_width;
        this->sizey = new_height;

        this->shape.setSize({sizex, sizey});
        this->selected_shape.setSize({sizex + 5.0f, sizey + 5.0f});

        for (auto& cell : cells) {
            cell.setup(cellSize);
        }
    }

    void DisplaySpecific(sf::RenderWindow& window) override {
        window.draw(shape);
        if (qubit_states.empty()) {
            if (iconTexture.getSize().x > 0) {
                sf::Vector2u texSize = iconTexture.getSize();
                float padding = 4.0f;

                float scaleX = (sizex - padding) / (float)texSize.x;
                float scaleY = (sizey - padding) / (float)texSize.y;
                float finalScale = std::min(scaleX, scaleY);

                iconSprite.setScale({finalScale, finalScale});
                iconSprite.setOrigin({texSize.x / 2.0f, texSize.y / 2.0f});
                iconSprite.setPosition({posx + sizex / 2.0f, posy + sizey / 2.0f});

                window.draw(iconSprite);
            } else {
                this->text.setPosition({posx + sizex/2 - 10.f, posy + sizey/2 - 5.f});
                window.draw(text);
            }
        }
        else {
            CalculateGlobalState();

            float cellSize = set_sizex / 2.0f;

            for (int i = 0; i < cells.size(); i++) {
                int row = i / grid_cols;
                int col = i % grid_cols;

                float cellX = posx + (col * cellSize);
                float cellY = posy + (row * cellSize);

                cells[i].setPosition(cellX, cellY);
                cells[i].draw(window);
            }
        }
    }

    void LogicToDo(complex ca, complex cb, sf::Time dt, int qubit_index) override {
        (void)dt;
        qubit_states[qubit_index] = {ca, cb};

        if (!qubit_states.empty()) {
            int max_index = qubit_states.rbegin()->first;
            if (max_index + 1 != num_qubits) {
                ResizeState(max_index + 1);
            }
        }
    }

private:
    void CalculateGlobalState() {
        if (qubit_states.empty()) return;

        std::vector<complex> global_state;
        global_state.push_back({1.0f, 0.0f});

        for (auto const& [index, state] : qubit_states) {
            complex alpha = state.first;
            complex beta = state.second;

            std::vector<complex> next_state;
            next_state.reserve(global_state.size() * 2);

            for (auto& amp : global_state) {
                next_state.push_back(amp * alpha);
                next_state.push_back(amp * beta);
            }
            global_state = next_state;
        }

        for (size_t i = 0; i < global_state.size() && i < cells.size(); i++) {
            cells[i].update(global_state[i]);
        }
    }

public:
    void ShowContextMenu() override {
        ImGui::Text("Amplitude Display");
        ImGui::Text("Qubits: %d", num_qubits);
        ImGui::Text("Grid: %dx%d", grid_cols, grid_rows);
    }
};

#endif //OOP_AMPLITUDE_H

#endif //OOP_AMPLITUDE_H