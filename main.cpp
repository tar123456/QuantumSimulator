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

    Qubit BellState;

    BellState = quantumGates.CNotGate(0, 1); 

    qubit q(BellState);
   
    std::cout << "Entangled Qubit State:\n";
    
    q.printQubit(BellState); 

    return 0;
}