#ifndef GATES_H
#define GATES_H

#include <vector>
#include <string>
#include <complex>
#include <iostream>
#include <math.h>
#include <locale>
#include <codecvt>
#include <array>
#include "Qubit.h"




class gates
{
  private:
   

   Qubit qubit1, qubit2;


   std::vector<std::complex<double> > singleQubitGateCalculator(std::vector<std::vector<std::complex<double> > > gate, std::vector<std::complex<double> >qubit);
   std::vector<std::vector<std::complex<double> > > gateMatrixRetreiver(std::string gateName);

  public:

  gates();
  gates(Qubit qubit1);
  gates(Qubit qubit1, Qubit qubit2);
  Qubit singleBitGate(std::string gateType);
  Qubit CNotGate();
  


};
#endif // GATES_H
