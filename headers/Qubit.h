#ifndef QUBIT_H
#define QUBIT_H

#include <vector>
#include <complex>
#include <iostream>
#include <math.h>

struct Qubit {
    std::vector<std::complex<double>> state_vector;

};

class qubit {
private:
    std::vector<Qubit> qubits;
    std::vector<std::complex<double>> system_state; 
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
};

#endif
