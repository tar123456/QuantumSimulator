Problem Statement: We aim to develop a quantum simulator that emulates various aspects of quantum computing.

Particular Scenario Provided: In this scenario, we focus on simulating quantum entanglement using our custom-built quantum simulator. Quantum entanglement is a core phenomenon in quantum computing where the states of quantum particles 
become correlated regardless of distance, with applications in quantum algorithms and protocols.




Execution Method:

The entire quantum simulator was built in C++ and the execution environment used is the MinGW g++ libraries.

To interact with the quantum simulator, follow these steps:

To See Output of Quantum Entanglement:

Run the QuantumEntanglement.exe executable to observe the output, which represents the quantum state of two entangled qubits and the associated quantum operations.
For Compiling the Code After Changes:

Use the g++ compiler with the following commands to compile the code after exploring and making changes to the code:

Compile individual sections:
g++ -c main.cpp -o main.o -I./headers
g++ -c headers/Qubit.cpp -o Qubit.o -I./headers
g++ -c headers/gates.cpp -o gates.o -I./headers

Linking the object files:
g++ main.o Qubit.o gates.o -o program

run the code
./program



Areas Where I Struggled the Most:

Mathematical Complexity (Dirac Notation):
Challenge: The mathematical complexity inherent in quantum computing, particularly in understanding and working with Dirac notation, posed a significant hurdle.
Specific Challenge: Dirac notation, which is a concise and fundamental language in quantum mechanics, proved challenging to grasp and apply effectively.

Translating Mathematical Aspects to Code:
Challenge: Translating the mathematical foundations of quantum computing into functional code presented its own set of difficulties.
Specific Challenge: Converting complex mathematical operations into accurate code representations was a particularly challenging aspect of the project.
These challenges highlighted the need for a deeper understanding of quantum mathematics and the ability to bridge the gap between mathematical theory and practical code implementation. Overcoming these hurdles required dedicated 
study, practice, and attention to detail.



Key Area of Focus:

We encourage you to explore our quantum simulator fully. You have the flexibility to edit the main.cpp file and delve into other parts of the code. The most significant effort was dedicated to understanding the underlying concepts
and accurately simulating it within the program.

Please refer to the brief documentation below:


This simulator consists of 2 classes:

Qubit class:

Overview
The qubit class represents quantum qubits and provides various methods for creating, manipulating, and measuring quantum states. It is designed for quantum computing simulations and state operations.

Constructors

qubit::qubit()
Default constructor.
Initializes a qubit with an empty state.

qubit::qubit(Qubit qubit1)
Constructor that copies the state of another qubit.
Parameters:
qubit1: Another qubit whose state is to be copied.

qubit::qubit(Qubit qubit1, Qubit qubit2)
Constructor that combines the states of two qubits.
Parameters:
qubit1: The first qubit.
qubit2: The second qubit.

Member Functions
std::vector<std::complex<double>> qubit::vectorForStates(std::string state)
Converts a state label (e.g., "|0>", "|1>") to a vector of complex numbers representing the qubit's state.
Parameters:
state: The state label to be converted.
Returns:
A vector of complex numbers representing the quantum state.


std::string qubit::stateForVector(std::vector<std::complex<double>> qubit)
Converts a vector of complex numbers representing a qubit's state back to a state label.
Parameters:
qubit: The vector representing the quantum state.
Returns:
The state label as a string.

Qubit qubit::tensorProduct()
Computes the tensor product of two qubits and returns a new qubit.
Returns:
A new qubit resulting from the tensor product of two input qubits.

float qubit::measure(Qubit qubit)
Calculates the measurement probability for a given qubit.
Parameters:
qubit: The qubit to be measured.
Returns:
The measurement probability as a floating-point value.


void qubit::printQubit(Qubit qubit)
Prints the state of a qubit.
Parameters:
qubit: The qubit whose state will be printed.



Gates Class

Overview
The gates class is designed for quantum computing simulations and provides methods for performing quantum gate operations on quantum qubits represented by the Qubit class. It includes functions for applying single-qubit gates like Pauli-X, 
Pauli-Y, Pauli-Z, Hadamard, and S-gate, as well as a CNOT (controlled-not) gate for two-qubit operations.

Constructors

gates::gates()
Default constructor.
Initializes a gates object with an empty qubit.

gates::gates(Qubit qubit1)
Constructor that takes a single qubit as input.
Parameters:
qubit1: A single-qubit Qubit object.

gates::gates(Qubit qubit1, Qubit qubit2)
Constructor that takes two qubits as input for two-qubit operations.
Parameters:
qubit1: The first qubit.
qubit2: The second qubit.


Member Functions

Qubit gates::singleBitGate(std::string gateType)
Applies a single-qubit gate to a quantum state.
Parameters:
gateType: The type of gate to apply (e.g., "PauliX", "Hadamard").
Returns:
A new Qubit object representing the quantum state after the gate operation.


Qubit gates::CNotGate()
Applies a CNOT (controlled-not) gate to two-qubits.
Returns:
A new Qubit object representing the quantum state after the CNOT gate operation.




Specific Reference File:

No specific external reference was used in this project.
