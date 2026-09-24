#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Include functions for dynamic memory management

#define M 2000 // Maximum number of lines
#define N 100  // Maximum length of each line

// Store dynamically allocated text data and its current size
typedef struct text_t
{
    char **text;    // Store a dynamic array of strings
    int line_count; // Keep track of the number of allocated lines
} Text_t;

// Function prototypes
Text_t init_Text_t(void);
int get_choice(void);
void get_filename(char x[N], const char *s);
void get_text(Text_t *x, char y[N]);
void get_vocabulary(Text_t *x, char y[N]);
void edit_text(Text_t *x, Text_t *y);
void save_vocabulary(Text_t *x, char y[N]);
void calculate_statistics(Text_t *x, char y[N]);
void save_statistics(char f[N], int t[N], int x, int y, int z, int k);
void print_menu(void);
void print_text(Text_t *x);
void print_vocabulary(Text_t *x);
void print_statistics(int t[N], int x, int y, int z, int k);
void free_input(Text_t *x);

int main(void)
{
    int choice;

    // Store the text filename
    char text_filename[N];

    // Store the vocabulary filename
    char vocabulary_filename[N];

    // Store the statistics output filename
    char statistics_filename[N];

    // Initialize dynamic text and vocabulary structures
    // The memory allocation will be handled when files are loaded
    Text_t text = init_Text_t();
    Text_t vocabulary = init_Text_t();

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
            get_text(&text, text_filename);
            break;
        case 2:
            // Get the vocabulary filename and load its contents
            get_filename(vocabulary_filename, "Enter the name of the vocabulary file: ");
            get_vocabulary(&vocabulary, vocabulary_filename);
            break;
        case 3:
            // Edit the text only if both files have been loaded
            if (text.line_count != 0 && vocabulary.line_count != 0)
            {
                edit_text(&text, &vocabulary);
                save_vocabulary(&vocabulary, vocabulary_filename);
            }
            else
            {
                printf("\nYou must first load both text and vocabulary files before editing text.\n");
            }
            break;
        case 4:
            // Calculate statistics only if a text file has been loaded
            if (text.line_count == 0)
            {
                printf("\nYou must first load a text file before calculating text statistics.\n");
            }
            else
            {
                // Get the output filename and generate the statistics file
                get_filename(statistics_filename, "Enter the name of the output statistics file: ");
                calculate_statistics(&text, statistics_filename);
            }
            break;
        case 5:
            // Print the loaded text
            if (text.line_count == 0)
            {
                printf("\nYou must first load a text file before printing text.\n");
            }
            else
            {
                print_text(&text);
            }
            break;
        case 6:
            // Print the loaded vocabulary
            if (vocabulary.line_count == 0)
            {
                printf("\nYou must first load a vocabulary file before printing vocabulary.\n");
            }
            else
            {
                print_vocabulary(&vocabulary);
            }
            break;
        default:
            // Handle invalid menu selections
            printf("\nInvalid choice, please try again.\n");
            break;
        }
    }

    // Release all dynamically allocated memory before program termination
    free_input(&text);
    free_input(&vocabulary);

    return 0;
}

Text_t init_Text_t(void)
{
    Text_t t;

    // Initialize the dynamic array pointer as empty
    t.text = NULL;

    // Initialize the number of stored lines
    t.line_count = 0;

    return t;
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

void get_text(Text_t *x, char filename[N])
{
    char line[N];

    // Open the text file in read mode
    FILE *file = fopen(filename, "r");

    // Check whether the file was opened successfully
    if (file == NULL)
    {
        printf("\nError opening file.\n");
        return;
    }

    // Read the text file line by line
    while (fgets(line, N, file) != NULL)
    {
        // Increase the number of stored lines
        x->line_count++;

        // Expand the dynamic array to store the new line pointer
        x->text = realloc(x->text, x->line_count * sizeof(char *));

        // Allocate memory for the new line entry
        x->text[x->line_count - 1] = malloc(N * sizeof(char));

        // Store the new text line
        strcpy(x->text[x->line_count - 1], line);
    }

    // Close the text file
    fclose(file);

    printf("\nText is saved.\n");
}

void get_vocabulary(Text_t *x, char y[N])
{
    char line[N];

    // Open the vocabulary file in read mode
    FILE *file = fopen(y, "r");

    // Check whether the file was opened successfully
    if (file == NULL)
    {
        printf("\nError opening file.\n");
        return;
    }

    // Read the vocabulary file line by line
    while (fgets(line, N, file) != NULL)
    {
        // Remove the trailing newline if it exists
        line[strcspn(line, "\n")] = '\0';

        // Increase the number of stored vocabulary entries
        x->line_count++;

        // Expand the dynamic array to store the new word pointer
        x->text = realloc(x->text, x->line_count * sizeof(char *));

        // Allocate memory for the new vocabulary entry
        x->text[x->line_count - 1] = malloc(N * sizeof(char));

        // Store the new vocabulary word
        strcpy(x->text[x->line_count - 1], line);
    }

    // Close the vocabulary file
    fclose(file);

    printf("\nVocabulary is saved.\n");
}

void edit_text(Text_t *x, Text_t *y)
{
    int i, j, choice;

    // Define the delimiters used to split text into individual words
    char delims[] = " .,;\n\t?!*:-/‘’\"()[]{}<>_‒–—“”";

    // Process every line of the text
    for (i = 0; i < x->line_count; i++)
    {
        // Allocate temporary memory for the current text line copy
        char *x_copy = (char *)malloc(N * sizeof(char));

        // Create a temporary copy because strtok() modifies the string
        strcpy(x_copy, (x->text)[i]);

        // Extract the first word from the current line
        char *word = strtok(x_copy, delims);

        // Process every word in the current line
        while (word != NULL)
        {
            int found = 0;

            // Search for the word in the vocabulary
            for (j = 0; j < y->line_count; j++)
            {
                // Check whether the word already exists in the vocabulary
                if (strcmp(word, y->text[j]) == 0)
                {
                    found = 1;
                    break;
                }
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
                        if ((y->line_count) >= M)
                        {
                            printf("\nVocabulary limit reached! Cannot add more words.\n");
                            break;
                        }

                        // Expand the dynamic vocabulary array
                        y->text = realloc(y->text, (y->line_count + 1) * sizeof(char *));

                        // Allocate memory for the new vocabulary entry
                        y->text[y->line_count] = malloc(N * sizeof(char));

                        // Store the new word
                        strcpy(y->text[y->line_count], word);

                        // Update vocabulary size
                        y->line_count++;

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
    }

    printf("\nText editing is completed.\n");
}

void save_vocabulary(Text_t *x, char y[N])
{
    int i;

    // Open the vocabulary file in write mode
    FILE *file = fopen(y, "w");

    // Check whether the file was opened successfully
    if (file == NULL)
    {
        printf("\nError saving vocabulary file.\n");
        return;
    }

    // Write every vocabulary entry to the file
    for (i = 0; i < x->line_count; i++)
    {
        fprintf(file, "%s\n", x->text[i]);
    }

    // Close the file
    fclose(file);

    printf("\nVocabulary file updated successfully.\n");
}

void calculate_statistics(Text_t *x, char y[N])
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

    // Access the dynamically allocated text lines through the structure pointer
    for (i = 0; i < x->line_count; i++)
    {
        // Allocate temporary memory for a modifiable copy of the current line
        char *x_copy = (char *)malloc(N * sizeof(char));

        // Copy the dynamically stored line because strtok() modifies the string
        strcpy(x_copy, (x->text)[i]);

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

void print_text(Text_t *x)
{
    int i;

    printf("\n");

    // Print every text entry
    for (i = 0; i < x->line_count; i++)
    {
        printf((x->text)[i]);
    }

    printf("\n");
}

void print_vocabulary(Text_t *x)
{
    int i;

    printf("\n");

    // Print every vocabulary entry
    for (i = 0; i < x->line_count; i++)
    {
        printf("%s\n", x->text[i]);
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

void free_input(Text_t *x)
{
    int i;

    // Release memory allocated for each individual line
    for (i = 0; i < x->line_count; i++)
    {
        free(x->text[i]);
    }

    // Release the dynamic array that stores the line pointers
    free(x->text);

    // Reset the structure after freeing the allocated memory
    x->text = NULL;
    x->line_count = 0;
}