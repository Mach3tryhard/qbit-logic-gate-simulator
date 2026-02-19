#include "factory.h"
#include "qubit.h"

std::unique_ptr<node> factory::CreateNode(NodeType type, float x, float y) {
    switch (type) {
        case NodeType::Qubit:
            return std::make_unique<qubit>(x, y);
        default:
            return nullptr;
    }
}