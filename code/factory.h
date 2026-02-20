#pragma once
#ifndef OOP_FACTORY_H
#define OOP_FACTORY_H
#include <memory>
#include "node.h"

enum class NodeType {
    None = 0,
    Qubit,
    Chance,
    PauliX,
    PauliY,
    PauliZ,
    Hadamard
};

class factory {
public:
    static std::unique_ptr<node> CreateNode(NodeType type, float x, float y);
};


#endif //OOP_FACTORY_H