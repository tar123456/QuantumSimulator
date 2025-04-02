#ifndef GATES_H
#define GATES_H

#include <vector>
#include <complex>
#include <iostream>
#include <math.h>
#include "Qubit.h"

class gates
{
private:
    std::vector<Qubit> qubits;

    std::vector<std::complex<double>> singleQubitGateCalculator(
        const std::vector<std::vector<std::complex<double>>>& gate, 
        const std::vector<std::complex<double>>& qubit);
    std::vector<std::vector<std::complex<double>>> gateMatrixRetriever(const std::string& gateName);
    std::vector<std::complex<double>> fullStateVector;

public:

    gates(const Qubit& singleQubit);
    gates(const std::vector<Qubit>& multipleQubits);
    
    Qubit singleBitGate(const std::string& gateType, size_t qubitIndex);
    Qubit CNotGate(size_t controlIndex, size_t targetIndex); 
};
#endif // GATES_H
