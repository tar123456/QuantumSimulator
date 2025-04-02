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



float qubit::measure(size_t qubitIndex) {
    if (qubits.empty() || qubitIndex >= qubits.size()) {
        throw std::invalid_argument("Invalid qubit index");
    }

    Qubit& measuredQubit = qubits[qubitIndex];

    // If not entangled, measure normally
    if (!measuredQubit.isEntangled) {
        double prob0 = std::norm(measuredQubit.state_vector[0]);
        double prob1 = std::norm(measuredQubit.state_vector[1]);

        // Normalize probabilities
        double totalProb = prob0 + prob1;
        if (totalProb == 0) throw std::runtime_error("Invalid state: probabilities sum to zero.");

        prob0 /= totalProb;
        prob1 /= totalProb;

        // Generate random number
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dist(0.0, 1.0);
        double random = dist(gen);

        // Collapse the state
        if (random < prob0) {
            measuredQubit.state_vector = {1.0, 0.0}; // Collapse to |0⟩
            return 0;
        } else {
            measuredQubit.state_vector = {0.0, 1.0}; // Collapse to |1⟩
            return 1;
        }
    }

    // If entangled, we must measure the full state
    if (qubits.size() != 2) throw std::runtime_error("Only 2-qubit entanglement is supported for now.");

    // Get reference to both qubits
    Qubit& q0 = qubits[0];
    Qubit& q1 = qubits[1];

    // Compute probability of measuring qubitIndex as |0⟩
    double prob0, prob1;
    if (qubitIndex == 0) {
        // Measuring first qubit
        prob0 = std::norm(q0.state_vector[0]);
        prob1 = std::norm(q0.state_vector[1]);
    } else {
        // Measuring second qubit
        prob0 = std::norm(q1.state_vector[0]);
        prob1 = std::norm(q1.state_vector[1]);
    }

    // Normalize probabilities
    double totalProb = prob0 + prob1;
    if (totalProb == 0) throw std::runtime_error("Invalid state: probabilities sum to zero.");
    
    prob0 /= totalProb;
    prob1 /= totalProb;

    // Randomly determine measurement outcome
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    double random = dist(gen);

    int result = (random < prob0) ? 0 : 1;

    // Collapse both qubits accordingly
    if (result == 0) {
        q0.state_vector = {1.0, 0.0};
        q1.state_vector = {1.0, 0.0};  // Ensures entanglement collapse
    } else {
        q0.state_vector = {0.0, 1.0};
        q1.state_vector = {0.0, 1.0};  // Ensures entanglement collapse
    }

    return result;
}
