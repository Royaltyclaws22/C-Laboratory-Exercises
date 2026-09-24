#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Include functions for dynamic memory management

#define M 2000 // Maximum number of lines
#define N 100  // Maximum length of each line

typedef struct node
{
    char *str;         // Store the text line associated with this node
    struct node *node; // Point to the next node in the linked list
} Node;

// Define a linked list as a pointer to its first node
typedef Node *Linked_List;

// Define a pointer type for individual linked list nodes
typedef Node *Linked_Node_Ptr;

Linked_Node_Ptr create_node(void);
int get_choice(void);
void get_filename(char x[N], const char *s);
void get_text(Linked_List x, char y[N], int *z);
void get_vocabulary(Linked_List x, char y[N], int *z);
void edit_text(Linked_List x, Linked_List y, int z, int *k);
void save_vocabulary(Linked_List x, char y[N]);
void calculate_statistics(Linked_List x, char y[N], int z);
void save_statistics(char f[N], int t[N], int x, int y, int z, int k);
void print_menu(void);
void print_text(Linked_List x, int y);
void print_vocabulary(Linked_List x, int y);
void print_statistics(int t[N], int x, int y, int z, int k);
void free_input(Linked_List x);

int main(void)
{
    int choice;

    // Store the number of loaded text lines
    int text_line_count = 0;

    // Store the number of loaded vocabulary lines
    int voc_line_count = 0;

    // Store the text filename
    char text_filename[N];

    // Store the vocabulary filename
    char vocabulary_filename[N];

    // Store the statistics output filename
    char statistics_filename[N];

    // Initialize empty linked lists for text and vocabulary
    // Each list starts with an allocated head node
    Linked_List text = create_node();
    Linked_List vocabulary = create_node();

    // Display the main menu
    printf("\n\n========================================\n");
    printf("             Text Analyzer\n");
    printf("========================================\n\n");

    // Keep displaying the menu until the user selects Exit
    for (;;)
    {
        // Display the main menu
        print_menu();

        choice = get_choice();

        if (choice == 7)
        {
            break;
        }

        switch (choice)
        {
        case 1:
            // Get the text filename and load its contents
            get_filename(text_filename, "Enter the name of the text file: ");
            get_text(text, text_filename, &text_line_count);
            break;
        case 2:
            // Get the vocabulary filename and load its contents
            get_filename(vocabulary_filename, "Enter the name of the vocabulary file: ");
            get_vocabulary(vocabulary, vocabulary_filename, &voc_line_count);
            break;
        case 3:
            // Edit the text only if both files have been loaded
            if (text_line_count != 0 && voc_line_count != 0)
            {
                edit_text(text, vocabulary, text_line_count, &voc_line_count);
                save_vocabulary(vocabulary, vocabulary_filename);
            }
            else
            {
                printf("\nYou must first load both text and vocabulary files before editing text.\n");
            }
            break;
        case 4:
            // Calculate statistics only if a text file has been loaded
            if (text_line_count == 0)
            {
                printf("\nYou must first load a text file before calculating text statistics.\n");
            }
            else
            {
                // Get the output filename and generate the statistics file
                get_filename(statistics_filename, "Enter the name of the output statistics file: ");
                calculate_statistics(text, statistics_filename, text_line_count);
            }
            break;
        case 5:
            // Print the loaded text
            if (text_line_count == 0)
            {
                printf("\nYou must first load a text file before printing text.\n");
            }
            else
            {
                print_text(text, text_line_count);
            }
            break;
        case 6:
            // Print the loaded vocabulary
            if (voc_line_count == 0)
            {
                printf("\nYou must first load a vocabulary file before printing vocabulary.\n");
            }
            else
            {
                print_vocabulary(vocabulary, voc_line_count);
            }
            break;
        default:
            // Handle invalid menu selections
            printf("\nInvalid choice, please try again.\n");
            break;
        }
    }

    // Release all dynamically allocated nodes and stored strings
    free_input(text);
    free_input(vocabulary);

    return 0;
}

Linked_Node_Ptr create_node(void)
{
    // Allocate memory dynamically for a new linked list node
    Linked_Node_Ptr ptr = (Linked_Node_Ptr)malloc(sizeof(Node));

    // Initialize the next pointer and string pointer
    ptr->node = NULL;
    ptr->str = NULL;

    // Return the newly created node
    return ptr;
}

int get_choice(void)
{
    int choice;

    // Prompt the user to enter a menu option
    printf("\nPlease enter your number of choice: ");

    // Keep asking until a valid integer is entered
    while (scanf("%d", &choice) != 1)
    {
        printf("\nInvalid input. Please enter a number: ");

        // Clear the invalid input from the buffer
        while (getchar() != '\n')
            ;
    }

    // Return the selected menu option
    return choice;
}

void get_filename(char x[N], const char *s)
{
    char filename[N];

    // Prompt the user to enter a filename
    printf("\n");
    printf(s);

    // Read the filename
    scanf("\n%s", filename);

    // Store the filename in the output parameter
    strcpy(x, filename);
}

void get_text(Linked_List x, char y[N], int *z)
{
    char *line;

    // Open the text file in read mode
    FILE *file = fopen(y, "r");

    // Check whether the file was opened successfully
    if (file == NULL)
    {
        printf("\nError opening file.\n");
        return;
    }

    // Allocate memory dynamically for each line read from the file
    while ((line = malloc(N * sizeof(char))) != NULL &&
           fgets(line, N, file) != NULL)
    {
        // Store the current line in the current node
        x->str = line;

        // Increase the number of lines stored in the linked list
        (*z)++;

        // Create the next node for the following line
        x->node = create_node();

        // Move the list pointer to the newly created node
        x = x->node;
    }

    // Close the file
    fclose(file);

    printf("\nText is saved.\n");
}

void get_vocabulary(Linked_List x, char y[N], int *z)
{
    char *line;

    // Open the vocabulary file in read mode
    FILE *file = fopen(y, "r");

    // Check whether the file was opened successfully
    if (file == NULL)
    {
        printf("\nError opening file.\n");
        return;
    }

    // Allocate memory dynamically for each line read from the file
    while ((line = malloc(N * sizeof(char))) != NULL &&
           fgets(line, N, file) != NULL)
    {
        // Remove the trailing newline if it exists
        line[strcspn(line, "\n")] = '\0';

        // Store the current line in the current node
        x->str = line;

        // Increase the number of lines stored in the linked list
        (*z)++;

        // Create the next node for the following line
        x->node = create_node();

        // Move the list pointer to the newly created node
        x = x->node;
    }

    // Close the file
    fclose(file);

    printf("\nVocabulary is saved.\n");
}

void edit_text(Linked_List x, Linked_List y, int z, int *k)
{
    int i, j, choice;

    // Define the delimiters used to split text into individual words
    char delims[] = " .,;\n\t?!*:-/‘’\"()[]{}<>_‒–—“”";

    // Process every line of the text
    for (i = 0; i < z; i++)
    {
        // Allocate temporary memory for the current text line copy
        char *x_copy = (char *)malloc(N * sizeof(char));

        // Access the current text line through the linked list node
        strcpy(x_copy, x->str);

        // Extract the first word from the current line
        char *word = strtok(x_copy, delims);

        // Process every word in the current line
        while (word != NULL)
        {
            int found = 0;

            Linked_List temp = y;

            // Search for the word in the vocabulary
            for (j = 0; j < (*k); j++)
            {
                // Check whether the word already exists in the vocabulary
                if (strcmp(word, temp->str) == 0)
                {
                    found = 1;
                    break;
                }

                temp = temp->node;
            }

            // Handle words that do not exist in the vocabulary
            if (!found)
            {
                int valid_choice = 0;

                while (!valid_choice)
                {
                    printf("\nWord -%s- from text does not exist in vocabulary.\n", word);
                    printf("\n----Options----\n1 => Add Word to Vocabulary\n2 => Continue Text Edit\n3 => Exit Text Edit\n");

                    choice = get_choice();

                    switch (choice)
                    {
                    case 1:
                        // Prevent exceeding the maximum vocabulary size
                        if ((*k) >= M)
                        {
                            printf("\nVocabulary limit reached! Cannot add more words.\n");
                            break;
                        }

                        Linked_List temp = y;

                        // Move to the last vocabulary node
                        while (temp->node != NULL)
                        {
                            temp = temp->node;
                        }

                        // Store the new vocabulary word in the current node
                        temp->str = (char *)malloc(N * sizeof(char));

                        strcpy(temp->str, word);

                        // Create a new empty node for future vocabulary additions
                        temp->node = create_node();

                        // Update vocabulary size
                        (*k)++;

                        printf("\nWord -%s- was added successfully to vocabulary.\n", word);

                        valid_choice = 1;
                        break;
                    case 2:
                        // Continue processing the remaining text
                        valid_choice = 1;
                        break;
                    case 3:
                        // Free all dynamically allocated memory created during editing
                        free(x_copy);

                        // Exit text editing
                        printf("\nText editing is completed.\n");
                        return;
                    default:
                        // Handle invalid menu selections
                        printf("\nInvalid choice, please try again.\n");
                        break;
                    }
                }
            }
            // Continue with the next word
            word = strtok(NULL, delims);
        }
        // Release the temporary copy of the current text line
        free(x_copy);

        // Move to the next text node in the linked list
        x = x->node;
    }

    printf("\nText editing is completed.\n");
}

void save_vocabulary(Linked_List x, char y[N])
{
    // Open the vocabulary file in write mode
    FILE *file = fopen(y, "w");

    // Check whether the file was opened successfully
    if (file == NULL)
    {
        printf("\nError saving vocabulary file.\n");
        return;
    }

    // Write every vocabulary entry to the file
    while (x->str != NULL)
    {
        fprintf(file, "%s\n", x->str);

        x = x->node;
    }

    // Close the file
    fclose(file);

    printf("\nVocabulary file updated successfully.\n");
}

void calculate_statistics(Linked_List x, char y[N], int z)
{
    // Note: The file "sample_text.txt" contains several non-ASCII
    // characters, so the calculated statistics may not be perfectly accurate.

    int i, j, choice;

    // Define the delimiters used to split text into words
    char delims[] = " .,;\n\t?!*:-/‘’ \"()[]{}<>_‒–—“”";

    // Store the total number of words
    int word_count = 0;

    // Store the number of non-space characters
    int char_without_spaces = 0;

    // Store the number of space characters
    int char_with_spaces = 0;

    // Store the maximum detected word length
    int max_len = 0;

    // Store the frequency of each word length
    int word_length[N] = {0};

    // Process every line of the text
    for (i = 0; i < z; i++)
    {
        // Allocate temporary memory for a modifiable copy of the current line
        char *x_copy = (char *)malloc(N * sizeof(char));

        // Access the current text line through the linked list node
        strcpy(x_copy, x->str);

        int len_1 = strlen(x_copy);

        // Count characters with and without spaces
        for (j = 0; j < len_1; j++)
        {
            if (x_copy[j] != '\0')
            {
                if (x_copy[j] == ' ')
                {
                    char_with_spaces++;
                }
                else
                {
                    char_without_spaces++;
                }
            }
        }

        // Extract the first word from the current line
        char *word = strtok(x_copy, delims);

        // Process every word in the current line
        while (word != NULL)
        {
            int len_2 = strlen(word);

            // Update the histogram using the word length
            if (len_2 > 0 && len_2 < N)
            {
                word_length[len_2]++;

                // Keep track of the longest word
                if (len_2 > max_len)
                {
                    max_len = len_2;
                }
            }

            // Count the current word
            word_count++;

            // Continue with the next word
            word = strtok(NULL, delims);
        }

        // Move to the next text node after processing the current line
        x = x->node;

        // Release the temporary copy created for the current line
        free(x_copy);
    }

    // Save the calculated statistics to the output file
    save_statistics(y, word_length, word_count, char_without_spaces, char_with_spaces, max_len);

    // Ask the user whether to print the statistics
    printf("\n----Options----\n0 => Exit Text Statistics\n1 => Print Text Statistics\n");

    choice = get_choice();

    switch (choice)
    {
    case 0:
        // Return to the main menu
        return;
        break;
    case 1:
        // Display the calculated statistics on the screen
        print_statistics(word_length, word_count, char_without_spaces, char_with_spaces, max_len);
        break;
    default:
        // Handle invalid menu selections
        printf("\nInvalid choice, please try again.\n");
        break;
    }
}

void save_statistics(char f[N], int t[N], int x, int y, int z, int k)
{
    int i;

    // Create the output statistics file
    FILE *file = fopen(f, "w");

    // Check whether the file was created successfully
    if (file == NULL)
    {
        printf("\nError creating file.\n");
        return;
    }

    // Write the calculated statistics to the output file
    fprintf(file, "\n----Text Statistics----\n");
    fprintf(file, "\nThe text has %d words.", x);
    fprintf(file, "\nThe text has %d characters without spaces.", y);
    fprintf(file, "\nThe text has %d characters and spaces.\n", (y + z));

    // Write the word-length histogram
    fprintf(file, "\n----Histogram----\n");

    for (i = 1; i <= k; i++)
    {
        fprintf(file, "Words with length %2d: %d\n", i, t[i]);
    }

    // Close the output file
    fclose(file);

    printf("\nText statistics are saved to -%s- file.\n", f);
}

void print_menu(void)
{
    // Display the main menu
    printf("\n----Menu----\n");
    printf("1 => Add Text\n");
    printf("2 => Add Vocabulary\n");
    printf("3 => Edit Text\n");
    printf("4 => Calculate Text Statistics\n");
    printf("5 => Print Text\n");
    printf("6 => Print Vocabulary\n");
    printf("7 => Exit\n");
}

void print_text(Linked_List x, int y)
{
    int i;

    printf("\n");

    // Print every text entry
    for (i = 0; i < y; i++)
    {
        printf("%s", x->str);

        x = x->node;
    }

    printf("\n");
}

void print_vocabulary(Linked_List x, int y)
{
    int i;

    printf("\n");

    // Print every vocabulary entry
    for (i = 0; i < y; i++)
    {
        printf("%s\n", x->str);

        x = x->node;
    }

    printf("\n");
}

void print_statistics(int t[N], int x, int y, int z, int k)
{
    int i;

    // Display the calculated statistics
    printf("\n----Text Statistics----\n");
    printf("\nThe text has %d words.", x);
    printf("\nThe text has %d characters without spaces.", y);
    printf("\nThe text has %d characters and spaces.\n", (y + z));

    // Display the word-length histogram
    printf("\n----Histogram----\n");
    for (i = 1; i <= k; i++)
    {
        printf("Words with length %2d: %d\n", i, t[i]);
    }
}

void free_input(Linked_List x)
{
    Node *temp;

    // Traverse the linked list and release all dynamically allocated memor
    while (x != NULL)
    {
        // Store the current node before moving to the next one
        temp = x;

        // Move to the next node in the linked list
        x = x->node;

        // Release memory allocated for the string stored in the current node
        free(temp->str);

        // Release memory allocated for the current node
        free(temp);
    }
}