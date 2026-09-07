# 📐 ASCII Shape Generator

A simple C console application that generates geometric ASCII shapes. Users can choose the shape, size, and drawing character.


## 🔎 Preview
<img width="1280" height="679" alt="ASCII_Shape_Generator" src="https://github.com/user-attachments/assets/f4e41a81-7797-421e-9e6d-de1c86ba23b4" />


## ⚙️ Features

- Generate geometric ASCII shapes:
  - Square
  - Rhombus
  - Triangle
  - Pyramid
- Select the desired shape through an interactive menu.
- Customize the size of each generated shape.
- Choose the character used to draw the pattern.
- Validate user input and reject invalid values.
- Handle different shape dimensions using modular functions.
- Generate patterns directly in the console.


## 💻 Installation & Running

1. Clone the repository:
```bash
git clone https://github.com/Royaltyclaws22/C-Laboratory-Exercises.git
```
2. Navigate to the project folder:
```bash
cd C-Laboratory-Exercises/01_ASCII_Shape_Generator
```
3. Compile the program:
```bash
gcc ASCII_Shape_Generator.c -o ASCII_Shape_Generator
```
4. Run the program:

* **Windows (Command Prompt)**
  ```bash
  ASCII_Shape_Generator.exe
  ```

* **Linux / macOS**
  ```bash
  ./ASCII_Shape_Generator
  ```


## 💡 Usage

Run the program and select a shape from the menu:

```text
========================================
          ASCII Shape Generator
========================================

  0. Square
  1. Rhombus
  2. Triangle
  3. Pyramid
 -1. Exit

----------------------------------------
```

### (0-3) Generate a shape

Enter the corresponding number to select the desired shape.

**Example:**

```text
Enter your choice: 1

Please enter a positive number for size: 25

Please enter a single non-numeric character: B
```

The program checks:
- If the selected option is available.
- If the size is a positive integer.
- If the drawing character is a single non-numeric character.

After valid input is provided, the selected ASCII shape is generated in the console.


### (-1) Exit

Enter `-1` to terminate the program.
