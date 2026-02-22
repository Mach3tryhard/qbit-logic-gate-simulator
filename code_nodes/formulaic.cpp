#include "formulaic.h"

void formulaic::DisplaySpecific(sf::RenderWindow& window){
    window.draw(shape);
    iconSprite.setPosition({posx + sizex/2, posy + sizey/2});
    window.draw(iconSprite);
}

void formulaic::LogicToDo(complex ca, complex cb, sf::Time time,int index){
    float t_seconds = time.asSeconds();

    float val = EvaluateFunction(t_seconds);

    float theta = 0.0f;

    bool isPowerGate = (gatetype == formulaic_type::Z_pow ||
                        gatetype == formulaic_type::Y_pow ||
                        gatetype == formulaic_type::X_pow);

    if (isPowerGate) {
        theta = val * 3.14159265f;
    } else {
        theta = val;
    }
    theta = std::fmod(theta, 2.0f * 3.14159265f);

    UpdateMatrix(theta);

    for (auto& neighbor : lista_adiacenta) {
        std::pair<complex, complex> state;
        state = complex::MatrixMultiply(ca, cb, mat);
        neighbor->LogicToDo(state.first, state.second, time,index);
    }
}

void formulaic::ShowContextMenu() {
    ImGui::Text("Formulaic Gate Settings");
    ImGui::Separator();
    if (ImGui::BeginMenu("Change Gate Type")) {
        if (ImGui::MenuItem("Z^f(t)")) { gatetype = formulaic_type::Z_pow; SetGateImage(); }
        if (ImGui::MenuItem("Rz(f(t))")) { gatetype = formulaic_type::RZ; SetGateImage(); }
        ImGui::Separator();
        if (ImGui::MenuItem("Y^f(t)")) { gatetype = formulaic_type::Y_pow; SetGateImage(); }
        if (ImGui::MenuItem("Ry(f(t))")) { gatetype = formulaic_type::RY; SetGateImage(); }
        ImGui::Separator();
        if (ImGui::MenuItem("X^f(t)")) { gatetype = formulaic_type::X_pow; SetGateImage(); }
        if (ImGui::MenuItem("Rx(f(t))")) { gatetype = formulaic_type::RX; SetGateImage(); }
        ImGui::EndMenu();
    }

    ImGui::Separator();
    ImGui::Text("Function f(t):");
    if (ImGui::RadioButton("Linear (t)", functionType == math_func::Linear)) functionType = math_func::Linear;
    if (ImGui::RadioButton("Quadratic (t^2)", functionType == math_func::Quadratic)) functionType = math_func::Quadratic;
    if (ImGui::RadioButton("Sine", functionType == math_func::Sine)) functionType = math_func::Sine;
    if (ImGui::RadioButton("Cosine", functionType == math_func::Cosine)) functionType = math_func::Cosine;
    if (ImGui::RadioButton("Pulse", functionType == math_func::Pulse)) functionType = math_func::Pulse;

    ImGui::Separator();
    ImGui::Text("Params: A * func(F*t) + Off");
    ImGui::DragFloat("Freq (F)", &frequency, 0.1f, 0.01f, 1.0f);
    ImGui::DragFloat("Amp (A)", &amplitude, 0.1f, 0.0f, 10.0f);
    ImGui::DragFloat("Offset", &offset, 0.1f, -5.0f, 5.0f);
}

float formulaic::EvaluateFunction(float t) {
    float x = t * frequency;
    float raw_y = 0.0f;

    switch (functionType) {
        case math_func::Linear:     raw_y = x; break;
        case math_func::Quadratic:  raw_y = x * x; break;
        case math_func::Sine:       raw_y = std::sin(x); break;
        case math_func::Cosine:     raw_y = std::cos(x); break;
        case math_func::Pulse:      raw_y = (std::fmod(x, 1.0f) < 0.5f) ? 1.0f : 0.0f; break;
    }

    return (raw_y * amplitude) + offset;
}

void formulaic::UpdateMatrix(float theta) {
    float c = std::cos(theta);
    float s = std::sin(theta);

    bool isZ = (gatetype == formulaic_type::Z_pow || gatetype == formulaic_type::RZ);
    bool isY = (gatetype == formulaic_type::Y_pow || gatetype == formulaic_type::RY);
    bool isX = (gatetype == formulaic_type::X_pow || gatetype == formulaic_type::RX);

    if (isZ) {
        mat[0][0] = {1, 0};  mat[0][1] = {0, 0};
        mat[1][0] = {0, 0};  mat[1][1] = {c, s};
    }
    else if (isY) {
        mat[0][0] = {c, 0}; mat[0][1] = {-s, 0};
        mat[1][0] = {s, 0}; mat[1][1] = {c, 0};
    }
    else if (isX) {
        mat[0][0] = {c, 0};   mat[0][1] = {0, -s};
        mat[1][0] = {0, -s};  mat[1][1] = {c, 0};
    }
}

void formulaic::SetGateImage() {
    std::string filename;
    switch(gatetype) {
        case formulaic_type::Z_pow: filename = "images/gates/gate_z_ft.png"; break;
        case formulaic_type::RZ:    filename = "images/gates/gate_rz_ft.png"; break;
        case formulaic_type::Y_pow: filename = "images/gates/gate_y_ft.png"; break;
        case formulaic_type::RY:    filename = "images/gates/gate_ry_ft.png"; break;
        case formulaic_type::X_pow: filename = "images/gates/gate_x_ft.png"; break;
        case formulaic_type::RX:    filename = "images/gates/gate_rx_ft.png"; break;
    }

    if (!iconTexture.loadFromFile(filename)) {}
    else {
        iconTexture.setSmooth(true);
        if (iconTexture.generateMipmap()){}
        iconSprite.setTexture(iconTexture, true);
    }
}