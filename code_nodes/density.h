#ifndef OOP_DENSITY_H
#define OOP_DENSITY_H

#include <map>
#include <vector>
#include <cmath>
#include "node.h"
#include "complex_cell.h"
#include "imgui.h"

class density : public node {
private:
    std::vector<complex_cell> cells;
    std::map<int, std::pair<complex, complex>> qubit_states;
    int num_qubits = 0;

    int grid_dim = 2;

    sf::Texture iconTexture;
    sf::Sprite iconSprite;

public:
    density(float x, float y) : node(x, y), iconSprite(iconTexture) {
        ResizeState(1);

        if (!iconTexture.loadFromFile("images/output/density.png")) {
            this->text.setString("Dens");
            this->text.setCharacterSize(10);
            this->text.setFillColor(sf::Color::Black);
        } else {
            if (iconTexture.generateMipmap()){}
            iconTexture.setSmooth(true);
            iconSprite.setTexture(iconTexture, true);
        }
    }

    void ResizeState(int n_qubits) {
        if (n_qubits < 1) n_qubits = 1;

        if (num_qubits == n_qubits && !cells.empty()) return;

        num_qubits = n_qubits;

        grid_dim = 1 << num_qubits;

        int num_cells = grid_dim * grid_dim;
        cells.resize(num_cells);

        float cellSize = set_sizex / 2.0f;

        float total_side_len = grid_dim * cellSize;

        this->sizex = total_side_len;
        this->sizey = total_side_len;

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
            CalculateDensityMatrix();

            float cellSize = set_sizex / 2.0f;

            for (int i = 0; i < cells.size(); i++) {
                int row = i / grid_dim;
                int col = i % grid_dim;

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
    void CalculateDensityMatrix() {
        if (qubit_states.empty()) return;

        std::vector<complex> state_vector;
        state_vector.push_back({1.0f, 0.0f});

        for (auto const& [index, state] : qubit_states) {
            complex alpha = state.first;
            complex beta = state.second;

            std::vector<complex> next_state;
            next_state.reserve(state_vector.size() * 2);

            for (auto& amp : state_vector) {
                next_state.push_back(amp * alpha);
                next_state.push_back(amp * beta);
            }
            state_vector = next_state;
        }

        if (state_vector.size() != grid_dim) return;

        for (int row = 0; row < grid_dim; row++) {
            for (int col = 0; col < grid_dim; col++) {

                complex row_val = state_vector[row];
                complex col_val = state_vector[col];

                complex col_conj = {col_val.real, -col_val.imag};
                complex density_val = row_val * col_conj;

                int index = row * grid_dim + col;
                if (index < cells.size()) {
                    cells[index].update(density_val);

                    if (row == col) {
                        cells[index].setProbability(density_val.real);
                    } else {
                        cells[index].setProbability(0.0f);
                    }
                }
            }
        }
    }

public:
    void ShowContextMenu() override {
        ImGui::Text("Density Matrix Display");
        ImGui::Text("Qubits: %d", num_qubits);
        ImGui::Text("Dimensions: %dx%d", grid_dim, grid_dim);
        ImGui::Separator();
        ImGui::Text("Shows: |Psi><Psi|");
    }
};

#endif //OOP_DENSITY_H