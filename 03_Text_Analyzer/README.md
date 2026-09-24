# 📝 Text Analyzer

A C console application designed for managing and analyzing `.txt` files. 

The program loads text and vocabulary files, processes text content, calculates statistics, and allows users to update the vocabulary during text editing. 

It demonstrates file handling, text processing, and multiple data structure implementations, including static arrays, dynamic arrays, and linked lists.


## 🔎 Preview


## ⚙️ Features

- Manage and analyze `.txt` files through an interactive console menu.
- Load text files and store their contents using different data structures.
- Load vocabulary files and manage words efficiently.
- Preserve the original formatting of the loaded text.
- Check whether words exist in the vocabulary during text editing.
- Add missing words to the vocabulary during text editing.
- Calculate text statistics:
  - Total number of words.
  - Number of characters without spaces.
  - Number of characters including spaces.
  - Word length histogram.
- Print the loaded text and vocabulary directly in the console.
- Save the updated vocabulary back to a `.txt` file.
- Handle dynamic memory allocation and release allocated memory safely.
- Implement the same text analysis functionality using three different data structures:
  - **Static Array Version:**
    - Uses fixed-size arrays with predefined limits for storing text and vocabulary entries.
  - **Dynamic Array Version:**
    - Uses dynamically allocated arrays for flexible memory management.
  - **Linked List Version:**
    - Uses linked lists for dynamic storage and efficient vocabulary updates.
- Manage memory according to the selected implementation:
  - Static memory allocation for the array-based version.
  - Dynamic memory allocation and memory release for the dynamic array and linked list versions.


## 💻 Installation & Running

1. Clone the repository:
```bash
git clone https://github.com/Royaltyclaws22/C-Laboratory-Exercises.git
```
2. Navigate to the project folder:
```bash
cd C-Laboratory-Exercises/03_Text_Analyzer
```
3. Compile the desired program version (e.g. Static Array Version):
```bash
gcc Text_Analyzer_Static_Array.c -o Text_Analyzer_Static_Array
```
4. Run the program:

* **Windows (Command Prompt)**
  ```bash
  Text_Analyzer_Static_Array.exe
  ```

* **Linux / macOS**
  ```bash
  ./Text_Analyzer_Static_Array
  ```

Make sure that the input files `sample_text.txt` and `sample_vocabulary.txt` are located in the same directory as the program.


## 💡 Usage

The program is designed to manage `.txt` files containing text data and vocabulary entries.

The repository includes two sample files:
- `sample_text.txt`:
  - Contains the text that will be analyzed and edited.
- `sample_vocabulary.txt`:
  - Contains the list of valid vocabulary words.

You can either:
- Use these sample files directly for testing.
- Replace their contents with custom text or vocabulary data while keeping the same `.txt` format.

Run the program and select an option from the menu:
```text
========================================
             Text Analyzer
========================================


----Menu----
1 => Add Text
2 => Add Vocabulary
3 => Edit Text
4 => Calculate Text Statistics
5 => Print Text
6 => Print Vocabulary
7 => Exit
```

### (1) Add Text

Load a `.txt` text file into memory.

**Example:**

```text
Please enter your number of choice: 1

Enter the name of the text file: sample_text.txt

Text is saved.
```

The program stores each line of the file using the selected data structure while preserving the original text formatting.

### (2) Add Vocabulary

Load a `.txt` vocabulary file containing valid words.

**Example:**

```text
Please enter your number of choice: 2

Enter the name of the vocabulary file: sample_vocabulary.txt

Vocabulary is saved.
```

Each vocabulary entry is stored separately and used during text editing to check whether words are already included.

### (3) Edit Text

Analyze the loaded text and compare every word with the vocabulary.

**Example:**

```text
Please enter your number of choice: 3

Word -Richard- from text does not exist in vocabulary.

----Options----
1 => Add Word to Vocabulary
2 => Continue Text Edit
3 => Exit Text Edit

Please enter your number of choice: 1

Word -Richard- was added successfully to vocabulary.
```

If a word is not found, you can add it to the vocabulary (1), skip it and continue editing (2), or exit the text editing process (3). Any newly added words will later be saved back to the vocabulary `.txt` file.

### (4) Calculate Text Statistics

Generate statistics about the loaded text.

**Example:**

```text
Please enter your number of choice: 4

Enter the name of the output statistics file: statistics.txt

Text statistics are saved to -statistics.txt- file.

----Options----
0 => Exit Text Statistics
1 => Print Text Statistics

Please enter your number of choice: 1

----Text Statistics----

The text has 16230 words.
The text has 76677 characters without spaces.
The text has 91360 characters and spaces.

----Histogram----
Words with length  1: 894
Words with length  2: 3197
...
```

The program calculates:
- Number of words.
- Number of characters without spaces.
- Number of characters including spaces.
- Frequency of words based on their length.

After the statistics are generated, you can either return to the main menu (0) or display the calculated statistics directly in the console (1). The results are saved to an output `.txt` file that you choose. 

### (5) Print Text

Display the currently loaded text directly in the console.

### (6) Print Vocabulary

Display all vocabulary entries currently stored in memory.

### (7) Exit

Terminate the program and release any dynamically allocated memory.
