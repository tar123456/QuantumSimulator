#ifndef QUBIT_H
#define QUBIT_H

#include <vector>
#include <complex>
#include <iostream>
#include <math.h>

struct Qubit {
    std::vector<std::complex<double>> state_vector;
    bool isEntangled = false;
    std::vector<size_t> entangledWith;   
};

class qubit {
private:
    std::vector<Qubit> qubits;
    
    void updateSingleQubitStates();

public:
    // Constructors
    qubit();
    qubit(const Qubit& singleQubit);
    qubit(const std::vector<Qubit>& multipleQubits);

    // Methods
    void printQubit(const Qubit& qubit); 
    std::vector<Qubit> getQubits() const { return qubits; } // Getter function
    Qubit tensorProduct(); 
    float measure(size_t qubitIndex); 
};

#endif
