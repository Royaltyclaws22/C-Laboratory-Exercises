#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

// Declare function prototypes

// Input functions
int getchoice(void);
int getsize(void);
char getcharacter(void);

// Character printing functions
void print_character1(int min, int max, char character);
void print_character2(int max, int min, char character);
void call_print_character1(int min, int max, char character1, char character2);
void call_print_character2(int max, int min, char character1, char character2);

// Shape drawing functions
void printsquare(int size, char character);
void printrhombus(int size, char character);
void printtriangle(int size, char character);
void printpyramid(int size, char character);

int main(void)
{
    // Declare the required variables
    int choice, size;
    char character;

    // Keep running until the user chooses to exit
    for (; (choice = getchoice()) != -1;)
    {
        // Read the shape size and drawing character
        size = getsize();
        character = getcharacter();

        // Separate the menu from the drawing output
        printf("\n");

        // Draw the selected shape
        switch (choice)
        {
        case 0:
            printsquare(size, character);
            break;

        case 1:
            printrhombus(size, character);
            break;

        case 2:
            printtriangle(size, character);
            break;

        case 3:
            printpyramid(size, character);
            break;

        default:
            break;
        }
    }

    return 0;
}

/* =========================================================
   Input functions
   ========================================================= */

int getchoice(void)
{
    char input[100];
    char *endptr;
    long choice;

    // Keep asking until a valid menu option is entered
    while (1)
    {
        // Display the main menu
        printf("\n\n========================================\n");
        printf("          ASCII Shape Generator\n");
        printf("========================================\n\n");

        printf("  0. Square\n");
        printf("  1. Rhombus\n");
        printf("  2. Triangle\n");
        printf("  3. Pyramid\n");
        printf(" -1. Exit\n");

        printf("\n----------------------------------------\n");
        printf("Enter your choice: ");

        // Read the user's input safely
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("\nInput error. Program terminated.\n");
            return -1;
        }

        // Convert the input string to an integer
        choice = strtol(input, &endptr, 10);

        // Skip any trailing whitespace characters
        while (isspace((unsigned char)*endptr))
        {
            endptr++;
        }

        // Reject any extra non-numeric characters
        if (*endptr != '\0')
        {
            printf("Invalid input. Please enter a number from 0 to 3, or -1.\n");
            continue;
        }

        // Verify that the value fits in an int
        if (choice < INT_MIN || choice > INT_MAX)
        {
            printf("Invalid input. The number is out of range.\n");
            continue;
        }

        // Accept only the available menu options
        if (choice != -1 && (choice < 0 || choice > 3))
        {
            printf("Invalid choice. Please enter 0, 1, 2, 3, or -1.\n");
            continue;
        }

        return (int)choice;
    }
}

int getsize(void)
{
    char input[100];
    char *endptr;
    long size;

    // Keep asking until a valid size is entered
    while (1)
    {
        printf("\nPlease enter a positive number for size: ");

        // Read the user's input safely
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("\nInput error. Program terminated.\n");
            exit(EXIT_FAILURE);
        }

        // Convert the input string to an integer
        size = strtol(input, &endptr, 10);

        // Skip any trailing whitespace characters
        while (isspace((unsigned char)*endptr))
        {
            endptr++;
        }

        // Reject any extra non-numeric characters
        if (*endptr != '\0')
        {
            printf("Invalid input. Please enter a positive integer.\n");
            continue;
        }

        // Accept only positive integer values
        if (size <= 0 || size > INT_MAX)
        {
            printf("Invalid size. Please enter a positive integer.\n");
            continue;
        }

        return (int)size;
    }
}

char getcharacter(void)
{
    char input[100];

    // Keep asking until a valid character is entered
    while (1)
    {
        printf("\nPlease enter a single non-numeric character: ");

        // Read the user's input safely
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("\nInput error. Program terminated.\n");
            exit(EXIT_FAILURE);
        }

        // Accept exactly one non-numeric character followed by Enter
        if (input[0] != '\n' &&
            input[1] == '\n' &&
            !isdigit((unsigned char)input[0]))
        {
            return input[0];
        }

        printf("Invalid input. Please enter exactly one non-numeric character.\n");
    }
}

/* =========================================================
   Character printing functions
   ========================================================= */

// Print a character repeatedly from the minimum value up to the maximum value
void print_character1(int min, int max, char character)
{
    int i;

    // Repeat the character for the specified range
    for (i = min; i < max; ++i)
    {
        printf("%c", character);
    }
}

// Print a character repeatedly from the maximum value down to the minimum value
void print_character2(int max, int min, char character)
{
    int i;

    // Repeat the character while decreasing the counter
    for (i = max; i > min; --i)
    {
        printf("%c", character);
    }
}

// Print a sequence of characters followed by a final character
void call_print_character1(int min, int max, char character1, char character2)
{
    print_character1(min, max, character1);

    // Print the ending character
    printf("%c", character2);
}

// Print a reversed sequence of characters followed by a final character
void call_print_character2(int max, int min, char character1, char character2)
{
    print_character2(max, min, character1);

    // Print the ending character
    printf("%c", character2);
}

/* =========================================================
   Shape drawing functions
   ========================================================= */

// Draw a square pattern using the given character
void printsquare(int size, char character)
{
    int k;

    // Handle the special case of a single-character square
    if (size == 1)
    {
        printf("%c", character);
    }
    else
    {
        // Print the top border of the square
        print_character1(0, size, character);

        // Print the upper empty rows
        for (k = 0; k < (size - 3) / 2; ++k)
        {
            printf("\n%c", character);
            call_print_character1(0, size - 2, '-', character);
        }

        // Handle the middle row for odd-sized squares
        if (size % 2 != 0 && size > 3)
        {
            printf("\n%c", character);

            call_print_character1(0, (size - 2) / 2, '-', character);
            call_print_character1(0, (size - 2) / 2, '-', character);
        }

        // Handle the middle rows for even-sized squares
        else if (size % 2 == 0 && size > 3)
        {
            for (k = size / 2; k < (size / 2) + 2; ++k)
            {
                printf("\n%c", character);

                print_character1(0, (size - 3) / 2, '-');
                print_character1(0, 2, character);

                call_print_character1(0, (size - 3) / 2, '-', character);
            }
        }

        // Handle the smallest possible square with size three
        else if (size == 3)
        {
            printf("\n%c", character);

            call_print_character1(0, size - 2, '-', character);
        }

        // Print the lower empty rows
        for (k = 0; k < (size - 3) / 2; ++k)
        {
            printf("\n%c", character);

            call_print_character1(0, size - 2, '-', character);
        }

        // Print the bottom border of the square
        printf("\n");
        print_character1(0, size, character);
    }
}

// Draw a rhombus pattern using the given character
void printrhombus(int size, char character)
{
    int k;
    int m = size / 2;

    // Handle rhombuses with odd dimensions
    if (size % 2 != 0)
    {
        // Print the upper half of the rhombus
        for (k = m; k >= 0; --k)
        {
            // Print the first row containing only the center character
            if (k == m)
            {
                print_character2(k, 0, '-');
                call_print_character2(1, 0, character, '\n');
            }
            else
            {
                // Print the left side of the current row
                call_print_character2(k, 0, '-', character);

                // Handle the middle row spacing
                if (k == 0)
                {
                    call_print_character1(
                        0, (2 * (m - k) - 1) / 2, '-', character);

                    print_character1(
                        0, (2 * (m - k) - 1) / 2, '-');
                }
                else
                {
                    print_character1(0, (2 * (m - k) - 1), '-');
                }

                // Print the right side and move to the next row
                call_print_character1(0, 1, character, '\n');
            }
        }

        // Print the lower half of the rhombus
        for (k = 1; k < m + 1; ++k)
        {
            // Print the left side indentation and character
            call_print_character1(0, k, '-', character);

            // Print the inner spacing except for the last row
            if (k != m)
            {
                call_print_character2(
                    (2 * (m - k) - 1), 0, '-', character);

                printf("\n");
            }
        }
    }

    // Handle rhombuses with even dimensions
    else if (size % 2 == 0)
    {
        // Print the upper half of the rhombus
        for (k = m - 1; k >= 0; --k)
        {
            // Print the first row containing the top character
            if (k == m - 1)
            {
                call_print_character2(k, 0, '-', character);
                call_print_character2(1, 0, character, '\n');
            }
            else
            {
                // Print the left side of the current row
                call_print_character2(k, 0, '-', character);

                // Handle the center row spacing
                if (k == 0)
                {
                    call_print_character1(
                        2, (2 * (m - k)) / 2, '-', character);

                    printf("%c", character);

                    print_character1(
                        2, (2 * (m - k)) / 2, '-');
                }
                else
                {
                    print_character1(2, 2 * (m - k), '-');
                }

                // Print the ending character and move to the next row
                call_print_character1(0, 1, character, '\n');
            }
        }

        // Print the lower half of the rhombus
        for (k = 0; k <= m - 1; ++k)
        {
            // Print the left indentation and character
            call_print_character1(0, k, '-', character);

            // Handle the center row
            if (k == 0)
            {
                call_print_character1(
                    2, (2 * (m - k)) / 2, '-', character);

                printf("%c", character);

                call_print_character1(
                    2, (2 * (m - k)) / 2, '-', character);

                printf("\n");
            }

            // Print the inner rows of the lower half
            else if (k != m - 1 && k != 0)
            {
                call_print_character2(
                    2 * (m - 1 - k), 0, '-', character);

                printf("\n");
            }

            // Print the last character of the rhombus
            else if (k == m - 1)
            {
                printf("%c", character);
            }
        }
    }
}

// Draw a triangle pattern using the given character
void printtriangle(int size, char character)
{
    int k;

    // Print each row of the triangle except the final row
    for (k = 1; k < size; k++)
    {
        // Handle the first two rows separately
        if (k < 3)
        {
            call_print_character1(0, k, character, '\n');
        }
        else
        {
            // Print the left side, spacing, and right side
            printf("%c", character);

            call_print_character1(2, k, '-', character);

            printf("\n");
        }
    }

    // Print the bottom row of the triangle
    print_character1(0, size, character);
}

// Draw a pyramid pattern using the given character
void printpyramid(int size, char character)
{
    int k;

    // Print all rows except the bottom one
    for (k = 1; k < size; k++)
    {
        // Handle the top row of the pyramid
        if (k == 1)
        {
            call_print_character1(0, size - k, ' ', character);

            printf("\n");
        }
        else
        {
            // Print leading spaces to center the row
            call_print_character1(0, size - k, ' ', character);

            // Print the internal spacing and border characters
            call_print_character1(2, (2 * k - 1), '-', character);

            printf("\n");
        }
    }

    // Print the base of the pyramid
    print_character1(0, (2 * size - 1), character);
}