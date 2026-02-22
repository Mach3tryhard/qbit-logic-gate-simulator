#ifndef OOP_LOGIC_H
#define OOP_LOGIC_H
#include <map>
#include <vector>
#include <memory>
#include "node.h"
#include "qubit.h"

enum class MsgType { Error, Warning, Info };

struct CompilerMessage {
    MsgType type;
    std::string text;
};

class logic {
private:
    std::vector<CompilerMessage> messages;
    std::map<node*, int> visit_state;
    std::map<node*, int> input_counts;
    bool system_is_safe = false;

    bool DetectCycles(const std::vector<std::unique_ptr<node>>& nodes) {
        visit_state.clear();
        for (const auto& n : nodes) visit_state[n.get()] = 0;

        for (const auto& n : nodes) {
            if (visit_state[n.get()] == 0) {
                if (VisitNode(n.get())) return true;
            }
        }
        return false;
    }

    bool VisitNode(node* n) {
        visit_state[n] = 1;

        for (auto* neighbor : n->get_connections()) {
            if (visit_state[neighbor] == 1) {
                messages.push_back({MsgType::Error, "Error: Infinite Loop detected!"});
                return true;
            }
            if (visit_state[neighbor] == 0) {
                if (VisitNode(neighbor)) return true;
            }
        }

        visit_state[n] = 2;
        return false;
    }

    void AnalyzeConnections(const std::vector<std::unique_ptr<node>>& nodes) {
        input_counts.clear();
        for (const auto& n : nodes) {
            for (auto* target : n->get_connections()) {
                input_counts[target]++;
            }
        }

        for (const auto& n : nodes) {
            if (input_counts[n.get()] > 1) {
                messages.push_back({MsgType::Warning, "Node has multiple inputs! Signals will overwrite."});
            }

            if (input_counts[n.get()] == 0 && dynamic_cast<qubit*>(n.get()) == nullptr) {
                if (!n->get_connections().empty()) {
                    messages.push_back({MsgType::Warning, "Gate has no input source."});
                }
            }
        }
    }
public:
    void Update(std::vector<std::unique_ptr<node>>& nodes,sf::Time dt) {
        messages.clear();
        system_is_safe = true;
        if (DetectCycles(nodes)) {
            system_is_safe = false;
        }
        AnalyzeConnections(nodes);

        if (system_is_safe) {
            RunExecution(nodes,dt);
        }
    }
    void RunExecution(std::vector<std::unique_ptr<node>>& nodes,sf::Time dt) {
        int sourceCount = 0;
        for (auto& n : nodes) {
            if (auto* q = dynamic_cast<qubit*>(n.get())) {
                complex dummy1, dummy2;
                q->LogicToDo(dummy1, dummy2,dt,sourceCount);
                sourceCount++;
            }
        }

        if (sourceCount == 0 && !nodes.empty()) {
            messages.push_back({MsgType::Info, "No Qubits found. Circuit is empty."});
        }
    }
    std::vector<CompilerMessage>& get_messages() {
        return messages;
    }
};


#endif //OOP_LOGIC_H