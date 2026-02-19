#include "factory.h"
#include "qubit.h"
#include "chance.h"

std::unique_ptr<node> factory::CreateNode(NodeType type, float x, float y) {
    switch (type) {
        case NodeType::Qubit:
            return std::make_unique<qubit>(x, y);
        case NodeType::Chance:
            return std::make_unique<chance>(x,y);
        default:
            return nullptr;
    }
}