#include <iostream>
#include "Qubit.h"
#include "gates.h"

int main() {
    Qubit qubit1, qubit2;
    qubit1.state_vector = {1, 0};  
    qubit2.state_vector = {0, 1}; 

    std::vector<Qubit> qubits = {qubit1, qubit2};

   
    gates quantumGates(qubits);
    qubits[0] = quantumGates.singleBitGate("Hadamard", 0);

    
    qubits[1] = quantumGates.CNotGate(0, 1); 

    qubit q(qubits);
   
    std::cout << "Entangled Qubit State:\n";
    for (size_t i = 0; i < qubits.size(); ++i) {
        q.printQubit(qubits[i]); 
    }

   
    float measurement = q.measure(0); 
    std::cout << "Measurement result of Qubit 0: " << measurement << "\n";

    return 0;
}