#include "Qubit.h"


qubit::qubit()
   {
    this->qubit1.qubit = {};
    this->qubit1.state = "";
   }
qubit::qubit(Qubit qubit1)
   {
       this->qubit1.qubit = qubit1.qubit;
       this->qubit1.state = qubit1.state;
   }
qubit::qubit(Qubit qubit1, Qubit qubit2)
   {
      this->qubit1.qubit = qubit1.qubit;
      this->qubit1.state = qubit1.state;
      this->qubit2.qubit = qubit2.qubit;
      this->qubit2.state = qubit2.state;
   }


std::vector<std::complex<double>> qubit::vectorForStates(std::string state)
   {
   std::vector<std::complex<double>> qubit;
    if (state == "|0>")
    { 
        qubit.push_back(std::complex<double>(1.0, 0.0));
        qubit.push_back(std::complex<double>(0.0, 0.0));
        
        return(qubit);
    }
    else if (state == "|1>")
    {
        qubit.push_back(std::complex<double>(0.0, 0.0));
        qubit.push_back(std::complex<double>(1.0, 0.0));
        
        return(qubit);
    }
    else if (state == "|+>")
    {
        qubit.push_back(std::complex<double>(1.0 , 0.0)/ sqrt(2));
        qubit.push_back(std::complex<double>(1.0 , 0.0)/ sqrt(2));
        return(qubit);
    }
    else if (state == "|->")
    {
        qubit.push_back(std::complex<double>(1.0 , 0.0)/ sqrt(2));
        qubit.push_back(std::complex<double>(-1.0, 0.0)/ sqrt(2));
        return(qubit);
    }
    else if (state == "|i>")
    {
        qubit.push_back(std::complex<double>(1.0, 0.0)/ sqrt(2));
        qubit.push_back(std::complex<double>(0.0, 1.0)/ sqrt(2));
        return(qubit);
    }
    else if (state == "|-i>")
    {
        qubit.push_back(std::complex<double>(1.0, 0.0)/ sqrt(2));
        qubit.push_back(std::complex<double>(0.0, -1.0)/ sqrt(2));
        return(qubit);
    }

    else
    {
      return {};
    }
   }


std::string qubit::stateForVector(std::vector<std::complex<double>> qubit)
    {
      if (qubit.size() != 2) {
        return "Invalid vector size.";
       }

      if (qubit[0] == std::complex<double>(1.0, 0.0) && qubit[1] == std::complex<double>(0.0, 0.0)) {
          return "|0>";
      } 
      else if (qubit[0] == std::complex<double>(0.0, 0.0) && qubit[1] == std::complex<double>(1.0, 0.0)) {
          return "|1>";
      }
      else if (qubit[0] == std::complex<double>(1.0, 0.0)/sqrt(2) && qubit[1] == std::complex<double>(1.0, 0.0)/sqrt(2)) {
          return "|+>";
      }
       else if (qubit[0] == std::complex<double>(1.0, 0.0)/sqrt(2) && qubit[1] == std::complex<double>(-1.0, 0.0)/sqrt(2)) {
          return "|->";
      }
       else if (qubit[0] == std::complex<double>(1.0, 0.0)/sqrt(2) && qubit[1] == std::complex<double>(0.0, 1.0)/sqrt(2)) {
          return "|i>";
      }
      else if (qubit[0] == std::complex<double>(1.0, 0.0)/sqrt(2) && qubit[1] == std::complex<double>(0.0, -1.0)/sqrt(2)) {
          return "|-i>";
      }
      else {
          return "Unknown State";
          
      }

    }

Qubit qubit::tensorProduct()
{
   Qubit result;
   std::string tensorProductSymbol = "\u2297";
   result.qubit.reserve(qubit1.qubit.size()*qubit2.qubit.size());
   for (const auto qubita : qubit1.qubit)
   {
     for(const auto qubitb : qubit2.qubit)
     {
       result.qubit.push_back(qubita*qubitb);
     }
     
   }
    result.state = qubit1.state+" "+tensorProductSymbol+" "+qubit2.state;
    return result;
}



float qubit::measure(Qubit qubit)
{
  float value = 0.0;
  std::vector<std::complex<double>> vector1;
  vector1.push_back(std::complex<double>(1.0, 0.0)/sqrt(3));
  vector1.push_back(std::complex<double>(0.0, 0.0)/sqrt(3));

  std::vector<std::complex<double>> vector2;
  vector2.push_back((sqrt(2)*std::complex<double>(0.0, 0.0))/sqrt(3));
  vector2.push_back((sqrt(2)*std::complex<double>(1.0, 0.0))/sqrt(3));


  std::vector<std::complex<double>> psi;
  std::vector<std::complex<double>> stateToBeMeasured;

  for(int i = 0; i<2;i++)
  {
    psi.push_back(vector1[i]+vector2[i]);
    stateToBeMeasured.push_back(std::conj(qubit.qubit[i]));;
  }
  
  for (int i =0 ; i<2; i++)
  {
    value = value + (stateToBeMeasured[i].real()*psi[i].real());
  }
   
  value = pow(value,2);
  return value;
}



void qubit::printQubit(Qubit qubit)
{
  const char* desiredLocale = "en_US.UTF-8";
    std::setlocale(LC_ALL, desiredLocale);

  std::cout<<"[ ";
  for (int i = 0; i < qubit.qubit.size(); i++) {
    if (qubit.qubit[i].imag() != 0.0) {
        std::cout<< qubit.qubit[i].imag() << "i";
    } else {
        std::cout<< qubit.qubit[i].real() << " ";
    }
}

std::cout << "]\n State:\n";
std::cout<<qubit.state.c_str();

}

Qubit qubit::collapse(float measurement)
{
    Qubit collapsedQubit;

    if (measurement<=0.5)
    {
      collapsedQubit.qubit = {1.0,0.0};
      collapsedQubit.state = "|0>";
    }
    else
    {
      collapsedQubit.qubit = {0.0,1.0};
      collapsedQubit.state = "|1>";
    }
return collapsedQubit;
}