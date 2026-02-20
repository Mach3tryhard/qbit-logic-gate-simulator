#include "factory.h"
#include "qubit.h"
#include "chance.h"
#include "halfturn.h"

std::unique_ptr<node> factory::CreateNode(NodeType type, float x, float y) {
    switch (type) {
        case NodeType::Qubit:
            return std::make_unique<qubit>(x,y);
        case NodeType::Chance:
            return std::make_unique<chance>(x,y);
        case NodeType::PauliX:
            return std::make_unique<halfturn>(x,y,halfturn_type::PauliX);
        case NodeType::PauliY:
            return std::make_unique<halfturn>(x,y,halfturn_type::PauliY);
        case NodeType::PauliZ:
            return std::make_unique<halfturn>(x,y,halfturn_type::PauliZ);
        case NodeType::Hadamard:
            return std::make_unique<halfturn>(x,y,halfturn_type::Hadamard);
        default:
            return nullptr;
    }
}
