#include "Qubit.h"
#include <random> 


qubit::qubit() {}

qubit::qubit(const Qubit& singleQubit) {
    qubits.push_back(singleQubit);
}

qubit::qubit(const std::vector<Qubit>& multipleQubits) {
    qubits = multipleQubits;
}

void qubit::printQubit(const Qubit& qubit) {
    std::cout << "[ ";
    for (const auto& amplitude : qubit.state_vector) {
        std::cout << amplitude << " ";
    }
    std::cout << "]\n";
}

Qubit qubit::tensorProduct() {
    if (qubits.empty()) return {};
    Qubit result = qubits[0];
    for (size_t i = 1; i < qubits.size(); i++) {
        Qubit temp;
        for (const auto& a : result.state_vector) {
            for (const auto& b : qubits[i].state_vector) {
                temp.state_vector.push_back(a * b);
            }
        }
        result = temp;
    }
    return result;
}


