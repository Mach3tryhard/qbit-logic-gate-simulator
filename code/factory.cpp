#include "factory.h"
#include "qubit.h"
#include "chance.h"
#include "formulaic.h"
#include "halfturn.h"
#include "quarterturn.h"
#include "spinning.h"
#include "bloch.h"
#include "amplitude.h"

std::unique_ptr<node> factory::CreateNode(NodeType type, float x, float y) {
    switch (type) {
        case NodeType::Qubit:
            return std::make_unique<qubit>(x,y);
        case NodeType::Chance:
            return std::make_unique<chance>(x,y);
        case NodeType::Bloch:
            return std::make_unique<bloch>(x,y);
        case NodeType::Amplitutde:
            return std::make_unique<amplitude>(x,y);

        case NodeType::PauliX:
            return std::make_unique<halfturn>(x,y,halfturn_type::PauliX);
        case NodeType::PauliY:
            return std::make_unique<halfturn>(x,y,halfturn_type::PauliY);
        case NodeType::PauliZ:
            return std::make_unique<halfturn>(x,y,halfturn_type::PauliZ);
        case NodeType::Hadamard:
            return std::make_unique<halfturn>(x,y,halfturn_type::Hadamard);

        case NodeType::S_Gate:
            return std::make_unique<quarterturn>(x,y,quarterturn_type::S_Gate);
        case NodeType::S_Dagger:
            return std::make_unique<quarterturn>(x,y,quarterturn_type::S_Dagger);
        case NodeType::Y_Sqrt:
            return std::make_unique<quarterturn>(x,y,quarterturn_type::Y_Sqrt);
        case NodeType::Y_Sqrt_Dagger:
            return std::make_unique<quarterturn>(x,y,quarterturn_type::Y_Sqrt_Dagger);
        case NodeType::X_Sqrt:
            return std::make_unique<quarterturn>(x,y,quarterturn_type::X_Sqrt);
        case NodeType::X_Sqrt_Dagger:
            return std::make_unique<quarterturn>(x,y,quarterturn_type::X_Sqrt_Dagger);

        case NodeType::Z_t:
            return std::make_unique<spinning>(x,y,spinning_type::Z_t);
        case NodeType::Z_nt:
            return std::make_unique<spinning>(x,y,spinning_type::Z_nt);
        case NodeType::Y_t:
            return std::make_unique<spinning>(x,y,spinning_type::Y_t);
        case NodeType::Y_nt:
            return std::make_unique<spinning>(x,y,spinning_type::Y_nt);
        case NodeType::X_t:
            return std::make_unique<spinning>(x,y,spinning_type::X_t);
        case NodeType::X_nt:
            return std::make_unique<spinning>(x,y,spinning_type::X_nt);

        case NodeType::RZ:
            return std::make_unique<formulaic>(x,y,formulaic_type::RZ);
        case NodeType::RY:
            return std::make_unique<formulaic>(x,y,formulaic_type::RY);
        case NodeType::RX:
            return std::make_unique<formulaic>(x,y,formulaic_type::RX);
        case NodeType::Z_pow:
            return std::make_unique<formulaic>(x,y,formulaic_type::Z_pow);
        case NodeType::Y_pow:
            return std::make_unique<formulaic>(x,y,formulaic_type::Y_pow);
        case NodeType::X_pow:
            return std::make_unique<formulaic>(x,y,formulaic_type::X_pow);

        default:
            return nullptr;
    }
}
