#ifndef OOP_LOGIC_H
#define OOP_LOGIC_H
#include <vector>
#include <memory>
#include "node.h"
#include "qubit.h"

class logic {
public:
    void RunLogic(std::vector<std::unique_ptr<node>>& nodes) {
        for (int i=0;i<nodes.size();i++) {
            if (dynamic_cast<qubit*>(nodes[i].get()) != nullptr) {
                qubit* q = dynamic_cast<qubit*>(nodes[i].get());
                complex a,b;
                q->LogicToDo(a,b);
            }
        }
    }
};


#endif //OOP_LOGIC_H