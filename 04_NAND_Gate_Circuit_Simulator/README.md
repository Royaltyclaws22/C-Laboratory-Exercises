# 🔌 NAND Gate Circuit Simulator

A simple C console application that simulates a digital circuit consisting of multiple NAND logic gates connected in sequence.


## 🔎 Preview
<img width="1280" height="679" alt="NAND_Gate_Circuit_Simulator" src="https://github.com/user-attachments/assets/87461f7a-0b35-437a-ba6c-95a2e3bb5fe1" />


## ⚙️ Features

- Simulate a circuit of multiple NAND logic gates.
- Represent each gate using a dynamically allocated linked list node.
- Apply NAND logic operations using function pointers.
- Generate random binary inputs for each gate.
- Pass the output of each gate as the input of the next gate.
- Display the input and output values of every gate in the circuit.
- Manage dynamic memory allocation and deallocation safely.


## 💻 Installation & Running

1. Clone the repository:
```bash
git clone https://github.com/Royaltyclaws22/C-Laboratory-Exercises.git
```
2. Navigate to the project folder:
```bash
cd C-Laboratory-Exercises/04_NAND_Gate_Circuit_Simulator
```
3. Compile the program:
```bash
gcc NAND_Gate_Circuit_Simulator.c -o NAND_Gate_Circuit_Simulator
```
4. Run the program:

* **Windows (Command Prompt)**
  ```bash
  NAND_Gate_Circuit_Simulator.exe
  ```

* **Linux / macOS**
  ```bash
  ./NAND_Gate_Circuit_Simulator
  ```


## 💡 Usage

Run the program to simulate the NAND gate circuit.

**Example:**

```text
          ----NAND GATE----

GATE No1        IN_1:1  IN_2:0  OUT:1
GATE No2        IN_1:1  IN_2:1  OUT:0
GATE No3        IN_1:0  IN_2:1  OUT:1
GATE No4        IN_1:1  IN_2:1  OUT:0
GATE No5        IN_1:0  IN_2:0  OUT:1
GATE No6        IN_1:1  IN_2:0  OUT:1
GATE No7        IN_1:1  IN_2:1  OUT:0
GATE No8        IN_1:0  IN_2:0  OUT:1
GATE No9        IN_1:1  IN_2:0  OUT:1
GATE No10       IN_1:1  IN_2:1  OUT:0
```

The program automatically:
- Creates a linked list containing multiple NAND gates.
- Assigns the NAND behavior to every gate.
- Generates random binary values as the second input.
- Calculates the output of each gate.
- Transfers each output to the next gate as its input.

After the simulation is completed, all dynamically allocated memory is released.
