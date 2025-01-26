#include "gates.h"



 std::vector<std::complex<double> > gates::singleQubitGateCalculator(std::vector<std::vector<std::complex<double> > > gate, std::vector<std::complex<double> >qubit)
   {
     std::vector<std::complex<double> > result;
     for (int i = 0; i<gate.size();i++)
       {
        std::complex<double> value = 0;
        for (int j =0; j<gate[i].size();j++)
           { 
              value += gate[i][j]* qubit[j];
           }
           result.push_back(value);
       }
    return result;
   }

gates::gates()
   {
    this->qubit1.qubit = {};
    this->qubit1.state = "";
   }
gates::gates(Qubit qubit1)
   {
       this->qubit1 = qubit1;
       
   }
gates::gates(Qubit qubit1, Qubit qubit2)
   {
      this->qubit1 = qubit1;
      this->qubit2 = qubit2;
   }


 std::vector<std::vector<std::complex<double> > > gates::gateMatrixRetreiver(std::string gateName)
 {

   std::vector<std::vector<std::complex<double> > > gateMatrix;
      
      
      if (gateName == "PauliX")
      {
          gateMatrix = {{std::complex<double>(0.0, 0.0), std::complex<double>(1.0, 0.0)},
                        {std::complex<double>(1.0, 0.0), std::complex<double>(0.0, 0.0)}};
      }
      else if (gateName == "PauliZ")
      {
          gateMatrix = {{std::complex<double>(1.0, 0.0), std::complex<double>(0.0, 0.0)},
                        {std::complex<double>(0.0, 0.0), std::complex<double>(-1.0, 0.0)}};
      }
      
      else if (gateName == "PauliY")
      {
          gateMatrix = {{std::complex<double>(0.0, 0.0), std::complex<double>(0.0, -1.0)},
                        {std::complex<double>(0.0, 1.0), std::complex<double>(0.0, 0.0)}};
      }
      else if (gateName == "Hadamard")
      {
        gateMatrix = {{std::complex<double>(1.0, 0.0)/sqrt(2), std::complex<double>(1.0, 0.0)/sqrt(2)},
                        {std::complex<double>(1.0, 0.0)/sqrt(2), std::complex<double>(0.0, -1.0)/sqrt(2)}};
      }
      else if (gateName == "SGate")
      {
     gateMatrix = {{std::complex<double>(1.0, 0.0), std::complex<double>(0.0, 0.0)},
                    {std::complex<double>(0.0, 0.0), std::complex<double>(0.0, 1.0)}};

      }
      
      else
      {
         throw std::runtime_error("Invalid Gate type.");
      }
      
      return gateMatrix;

 }



Qubit gates::singleBitGate(std::string gateType)
   {
     
     qubit qubita(qubit1);
     
     std::vector<std::vector<std::complex<double> > > gateMatrix= gateMatrixRetreiver(gateType);
     std::vector<std::complex<double> > resultVector = singleQubitGateCalculator(gateMatrix, qubit1.qubit);

     Qubit result;
     
     result.qubit = resultVector;

     result.state = qubita.stateForVector(result.qubit);
   
     return result; 

   }



Qubit gates::CNotGate()
{
  
  Qubit tensorResult,CNotResult;
  
  
  std::array<std::array<std::complex<double>, 4>, 4> gateMatrix = {
    std::array<std::complex<double>, 4>{
        std::complex<double>(1.0, 0.0),
        std::complex<double>(0.0, 0.0),
        std::complex<double>(0.0, 0.0),
        std::complex<double>(0.0, 0.0)
    },
    std::array<std::complex<double>, 4>{
        std::complex<double>(0.0, 0.0),
        std::complex<double>(1.0, 0.0),
        std::complex<double>(0.0, 0.0),
        std::complex<double>(0.0, 0.0)
    },
    std::array<std::complex<double>, 4>{
        std::complex<double>(0.0, 0.0),
        std::complex<double>(0.0, 0.0),
        std::complex<double>(0.0, 0.0),
        std::complex<double>(1.0, 0.0)
    },
    std::array<std::complex<double>, 4>{
        std::complex<double>(0.0, 0.0),
        std::complex<double>(0.0, 0.0),
        std::complex<double>(1.0, 0.0),
        std::complex<double>(0.0, 0.0)
    }
};

  qubit qubita(qubit1,qubit2);
  
  tensorResult = qubita.tensorProduct();
  
  for (int i = 0; i <4; i++)
  {
    std::complex<double> value = 0;
    for (int j = 0; j<4;j++)
    {
      value += gateMatrix[i][j]*tensorResult.qubit[j];
    }
    CNotResult.qubit.push_back(value);
  }
  CNotResult.state = qubit1.state+ "CNOT" + qubit2.state;
  
  

  return CNotResult;
}
