#ifndef QUBIT_H
#define QUBIT_H

#include <vector>
#include <string>
#include <complex>
#include <iostream>
#include <math.h>
#include <locale>
#include <codecvt>
#include <array>




struct Qubit{
     std::vector<std::complex<double>> qubit;
     std::string state;
   };


class qubit{
    private:
    Qubit qubit1, qubit2;


    public:
    qubit();
    qubit(Qubit qubit1);
    qubit(Qubit qubit1,Qubit qubit2);

    std::vector<std::complex<double>> vectorForStates(std::string state);
    std::string stateForVector(std::vector<std::complex<double>> qubit);
    void printQubit(Qubit qubit);
    Qubit tensorProduct();
    float measure(Qubit qubit);
};


#endif