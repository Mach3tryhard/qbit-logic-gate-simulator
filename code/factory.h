#pragma once
#ifndef OOP_FACTORY_H
#define OOP_FACTORY_H
#include <memory>
#include "node.h"

enum class NodeType {
    None = 0,
    Qubit,
    Chance,
    Bloch,
    Amplitutde,
    PauliX,
    PauliY,
    PauliZ,
    Hadamard,
    S_Gate,
    S_Dagger,
    Y_Sqrt,
    Y_Sqrt_Dagger,
    X_Sqrt,
    X_Sqrt_Dagger,
    Z_t,
    Z_nt,
    Y_t,
    Y_nt,
    X_t,
    X_nt,
    Z_pow,
    RZ,
    Y_pow,
    RY,
    X_pow,
    RX,
};

class factory {
public:
    static std::unique_ptr<node> CreateNode(NodeType type, float x, float y);
};

#endif //OOP_FACTORY_H