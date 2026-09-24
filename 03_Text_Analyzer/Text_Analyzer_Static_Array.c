#include <stdio.h>
#include <string.h>

#define M 2000 // Maximum number of lines
#define N 100  // Maximum length of each line

// Function prototypes
int get_choice(void);  
void get_filename(char x[N], const char *s);
int get_text(char x[M][N], char y[N], char z[N]);
int get_vocabulary(char x[M][N], char y[N], char z[N]);
int edit_text(char x[M][N], char y[M][N], int z, int k);
void save_vocabulary(char x[M][N], int y, char z[N]);
void calculate_statistics(char x[M][N], int y, char z[N]);
void save_statistics(char f[N], int t[N], int x, int y, int z, int k);
void print_menu(void);
void print_text(char x[M][N], int y);
void print_vocabulary(char x[M][N], int y);
void print_statistics(int t[N], int x, int y, int z, int k);

int main(void)
{
    int choice;

    // Store the number of loaded text lines
    int text_line_count = 0;

    // Store the number of loaded vocabulary lines
    int voc_line_count = 0;

    // Store the text file contents
    char text[M][N];

    // Store the vocabulary file contents
    char vocabulary[M][N];

    // Temporarily store a single line while reading files
    char line[N];

    // Store the text filename
    char text_filename[N];

    // Store the vocabulary filename
    char vocabulary_filename[N];

    // Store the statistics output filename
    char statistics_filename[N];

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
            text_line_count = get_text(text, line, text_filename);
            break;
        case 2:
            // Get the vocabulary filename and load its contents
            get_filename(vocabulary_filename, "Enter the name of the vocabulary file: ");
            voc_line_count = get_vocabulary(vocabulary, line, vocabulary_filename);
            break;
        case 3:
            // Edit the text only if both files have been loaded
            if (text_line_count != 0 && voc_line_count != 0)
            {
                voc_line_count = edit_text(text, vocabulary, text_line_count, voc_line_count);
                save_vocabulary(vocabulary, voc_line_count, vocabulary_filename);
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
                calculate_statistics(text, text_line_count, statistics_filename);
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

int get_text(char x[M][N], char y[N], char z[N])
{
    int i = 0;

    // Store the total number of text lines read from the file
    int text_line_count = 0;

    // Open the text file in read mode
    FILE *file = fopen(z, "r");

    // Check whether the file was opened successfully
    if (file == NULL)
    {
        printf("\nError opening file.\n");
        return text_line_count;
    }

    // Read the file line by line and store each line
    while (fgets(y, N, file) != NULL)
    {
        text_line_count++;
        strcpy(x[i++], y);
    }

    // Close the file
    fclose(file);

    printf("\nText is saved.\n");

    // Return the number of loaded text lines
    return text_line_count;
}

int get_vocabulary(char x[M][N], char y[N], char z[N])
{
    int i = 0;

    // Store the total number of vocabulary entries read from the file
    int voc_line_count = 0;

    // Open the vocabulary file in read mode
    FILE *file = fopen(z, "r");

    // Check whether the file was opened successfully
    if (file == NULL)
    {
        printf("\nError opening file.\n");
        return voc_line_count;
    }

    // Read the file line by line and store each word
    while (fgets(y, N, file) != NULL)
    {
        // Remove the trailing newline if it exists
        y[strcspn(y, "\n")] = '\0';

        strcpy(x[i++], y);
        voc_line_count++;
    }

    // Close the file
    fclose(file);

    printf("\nVocabulary is saved.\n");

    // Return the number of loaded vocabulary entries
    return voc_line_count;
}

int edit_text(char x[M][N], char y[M][N], int z, int k)
{
    int i, j, choice;

    // Count the number of newly added vocabulary words
    int r = 0;

    // Define the delimiters used to split text into individual words
    char delims[] = " .,;\n\t?!*:-/‘’\"()[]{}<>_‒–—“”";

    // Process every line of the text
    for (i = 0; i < z; i++)
    {
        // Create a temporary copy because strtok() modifies the string
        char x_copy[N];
        strcpy(x_copy, x[i]);

        // Extract the first word from the current line
        char *word = strtok(x_copy, delims);

        // Process every word in the current line
        while (word != NULL)
        {
            int found = 0;

            // Search for the word in the vocabulary
            for (j = 0; j < k + r; j++)
            {
                // Check whether the word already exists in the vocabulary
                if (strcmp(word, y[j]) == 0)
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
                        if ((k + r) >= M)
                        {
                            printf("\nVocabulary limit reached! Cannot add more words.\n");
                            break;
                        }

                        // Add the new word to the temporary vocabulary
                        strcpy(y[k + r], word);

                        printf("\nWord -%s- was added successfully to vocabulary.\n", y[k + r]);

                        r++;
                        valid_choice = 1;
                        break;
                    case 2:
                        // Continue processing the remaining text
                        valid_choice = 1;
                        break;
                    case 3:
                        // Exit text editing and return the updated vocabulary size
                        printf("\nText editing is completed.\n");
                        return (k + r);
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
    }
    printf("\nText editing is completed.\n");

    // Return the updated vocabulary size
    return (k + r);
}

void save_vocabulary(char x[M][N], int y, char z[N])
{
    int i;

    FILE *file = fopen(z, "w");

    if (file == NULL)
    {
        printf("\nError saving vocabulary file.\n");
        return;
    }

    // Update the vocabulary file
    for (i = 0; i < y; i++)
    {
        fprintf(file, "%s\n", x[i]);
    }

    fclose(file);

    printf("\nVocabulary file updated successfully.\n");
}

void calculate_statistics(char x[M][N], int y, char z[N])
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

    // Create the output statistics file
    FILE *file = fopen(z, "w");

    // Check whether the file was created successfully
    if (file == NULL)
    {
        printf("\nError creating file.\n");
        return;
    }

    // Process every line of the text
    for (i = 0; i < y; i++)
    {
        // Create a temporary copy because strtok() modifies the string
        char x_copy[N];
        strcpy(x_copy, x[i]);

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
    }

    // Save the calculated statistics to the output file
    save_statistics(z, word_length, word_count, char_without_spaces, char_with_spaces, max_len);

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

void print_text(char x[M][N], int y)
{
    int i;

    printf("\n");

    // Print every line of the loaded text
    for (i = 0; i < y; i++)
    {
        printf("%s", x[i]);
    }

    printf("\n");
}

void print_vocabulary(char x[M][N], int y)
{
    int i;

    printf("\n");

    // Print every vocabulary entry
    for (i = 0; i < y; i++)
    {
        printf("%s\n", x[i]);
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