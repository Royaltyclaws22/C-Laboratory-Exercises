#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10 // Define the number of gates in the circuit

typedef enum
{
    false = 0,
    true = 1
} bool; // Define a boolean data type

typedef bool (*FUNC)(bool, bool); // Define a gate behavior function pointer

typedef struct gate
{
    bool in;           // Store the gate input
    bool out;          // Store the gate output
    FUNC behavior;     // Store the gate logic function
    struct gate *next; // Point to the next gate
} GATE;                // Define a logic gate structure

bool get_random_in(void);
bool gate_func_NAND(bool, bool);
GATE *create_gate();
void create_linked_list(GATE *);
void calculate_circuit_output(GATE *);
void free_gates(GATE *);

int main(void)
{
    // Initialize the random number generator
    srand(time(NULL));

    // Create the first gate of the circuit
    GATE *head = create_gate();

    // Assign the initial input to the first gate
    head->in = 1;

    // Create the remaining gates as a linked list
    create_linked_list(head);

    // Simulate the circuit and display the results
    calculate_circuit_output(head);

    // Release all dynamically allocated memory
    free_gates(head);

    return 0;
}

bool get_random_in(void)
{
    // Generate a random binary input value
    bool in = rand() % 2;

    return in;
}

bool gate_func_NAND(bool in_1, bool in_2)
{
    // Return the output of a NAND logic gate
    return !(in_1 && in_2);
}

GATE *create_gate()
{
    GATE *gate;

    // Allocate memory for a new gate
    gate = (GATE *)malloc(sizeof(GATE));

    // Stop the program if memory allocation fails
    if (gate == NULL)
    {
        printf("Memory not allocated.\n");
        exit(0);
    }
    else
    {
        // Assign the NAND behavior to the gate
        gate->behavior = gate_func_NAND;

        // Mark the gate as the last node initially
        gate->next = NULL;
    }

    return gate;
}

void create_linked_list(GATE *head)
{
    // Start from the first gate
    GATE *tmp = head;

    // Create and link the remaining gates
    for (int i = 1; i < N; i++)
    {
        tmp->next = create_gate();
        tmp = tmp->next;
    }
}

void calculate_circuit_output(GATE *head)
{
    // Start from the first gate
    GATE *tmp = head;

    printf("\n\t  ----NAND GATE----\n\n");

    // Process each gate in the circuit
    for (int i = 1; i <= N; i++)
    {
        // Generate the second input randomly
        bool in_2 = get_random_in();

        // Compute the gate output
        tmp->out = tmp->behavior(tmp->in, in_2);

        // Display the gate inputs and output
        printf("GATE No%d\tIN_1:%d  IN_2:%d  OUT:%d\n", i, tmp->in, in_2, tmp->out);

        // Pass the current output to the next gate as its first input
        if (tmp->next != NULL)
        {
            tmp->next->in = tmp->out;
        }

        // Move to the next gate
        tmp = tmp->next;
    }
}

void free_gates(GATE *head)
{
    // Release each gate in the linked list
    while (head)
    {
        GATE *tmp = head;
        head = head->next;
        free(tmp);
    }
}