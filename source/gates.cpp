#include "gates.h"
#include <stdexcept>
#include <cmath>





gates::gates(const Qubit& singleQubit) {
    qubits.push_back(singleQubit);
}

gates::gates(const std::vector<Qubit>& multipleQubits) {
    qubits = multipleQubits;
}


std::vector<std::vector<std::complex<double>>> gates::gateMatrixRetriever(const std::string& gateName) {
   if (gateName == "PauliX") {
       return {{0, 1}, {1, 0}};
   } else if (gateName == "PauliY") {
       return {{std::complex<double>(0, -1.0), std::complex<double>(0, 1.0)}, 
               {std::complex<double>(0, 1.0), std::complex<double>(0, 0)}};
   } else if (gateName == "PauliZ") {
       return {{1, 0}, {0, -1}};
   } else if (gateName == "Hadamard") {
       double s = 1 / std::sqrt(2);
       return {{s, s}, {s, -s}};
   } else if (gateName == "SGate") {
       return {{1, 0}, {0, std::complex<double>(0, 1.0)}};
   } else {
       throw std::runtime_error("Invalid Gate type.");
   }
}



Qubit gates::singleBitGate(const std::string& gateType, size_t qubitIndex) {
    if (qubitIndex >= qubits.size()) {
        throw std::out_of_range("Qubit index out of range.");
    }
    
    auto gateMatrix = gateMatrixRetriever(gateType);
    auto& targetQubit = qubits[qubitIndex];
    std::vector<std::complex<double>> resultVector(targetQubit.state_vector.size(), {0, 0});

    for (size_t i = 0; i < gateMatrix.size(); ++i) {
        for (size_t j = 0; j < gateMatrix[i].size(); ++j) {
            resultVector[i] += gateMatrix[i][j] * targetQubit.state_vector[j];
        }
    }

    targetQubit.state_vector = resultVector;
    return targetQubit;
}


Qubit gates::CNotGate(size_t controlIndex, size_t targetIndex) {
   if (controlIndex >= qubits.size() || targetIndex >= qubits.size()) {
       throw std::out_of_range("Qubit index out of range.");
   }

   // Create the full two-qubit state vector
   std::vector<std::complex<double>> fullState(4, {0, 0});
   fullState[0] = qubits[controlIndex].state_vector[0] * qubits[targetIndex].state_vector[0]; // |00⟩
   fullState[1] = qubits[controlIndex].state_vector[0] * qubits[targetIndex].state_vector[1]; // |01⟩
   fullState[2] = qubits[controlIndex].state_vector[1] * qubits[targetIndex].state_vector[0]; // |10⟩
   fullState[3] = qubits[controlIndex].state_vector[1] * qubits[targetIndex].state_vector[1]; // |11⟩

   // Define CNOT matrix
   std::array<std::array<std::complex<double>, 4>, 4> cnotMatrix = {
       {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 1}, {0, 0, 1, 0}}
   };

   // Apply CNOT gate to the state
   std::vector<std::complex<double>> resultVector(4, {0, 0});
   for (size_t i = 0; i < 4; ++i) {
       for (size_t j = 0; j < 4; ++j) {
           resultVector[i] += cnotMatrix[i][j] * fullState[j];
       }
   }

   // Store the full state in the system 
   // (We'll need to add a fullStateVector member to the gates class)
   this->fullStateVector = resultVector;

   // For backward compatibility, we still return the target qubit
   // but now we just store a reference to the fact that this qubit
   // is part of an entangled system
   qubits[targetIndex].isEntangled = true;
   qubits[controlIndex].isEntangled = true;
   
   // Store references to which qubits are entangled
   qubits[targetIndex].entangledWith.push_back(controlIndex);
   qubits[controlIndex].entangledWith.push_back(targetIndex);

   return qubits[targetIndex];
}