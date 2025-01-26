#include<iostream>
#include<vector>
#include<string>
#include<complex>
#include<math.h>
#include"gates.h"
#include"Qubit.h"

using namespace std;



int main()
{
     
   try
   {
      Qubit qubit1, qubit2, qubit3, bellState, tensor;
      
      qubit1.state = "|1>";
      qubit2.state = "|0>";
      
      qubit qubita(qubit1,qubit2);
   
      qubit1.qubit = qubita.vectorForStates(qubit1.state);
      qubit2.qubit = qubita.vectorForStates(qubit2.state);
      
      gates gate1(qubit1);
      
      qubit3 = gate1.singleBitGate("Hadamard");
      
      gates gate2(qubit3,qubit2);
      
      bellState = gate2.CNotGate();

      qubita.printQubit(bellState);      
      
      float measured = qubita.measure(bellState);
      cout<<"Measurement: "<< measured;
      qubita.printQubit(qubita.collapse(measured));
      std::cin.get();
      return 0;

   }

   catch (string ex)
   {
      cout<<"Error: "<<ex;
   }

}