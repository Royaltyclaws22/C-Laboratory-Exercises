// 2D Heat Diffusion Simulation on a Temperature Plate

// Simulate the temperature evolution of a 10x20 plate using a discrete heat diffusion equation.
// Determine whether the plate has reached a steady state using a 1 Celsius degree convergence criterion.

#include <stdio.h>

#define M 10 // Define the number of rows
#define N 20 // Define the number of columns

#define temp1 2
#define temp2 -5
#define temp3 3
#define temp4 4
#define temp5 1

int initialize_plate(float x[M][N]);
int print_temperature_matrix(float x[M][N]);
float update_temperature(float x[M][N], float y[M][N]);
int create_temperature_map(float x[M][N], int y[M][N]);
int print_temperature_map(int x[M][N]);
int get_simulation_time(void);
int print_temperature_histogram(int x[M][N]);
int print_histogram_bar(int x, int y);
float absolute_difference(float x);
int print_temperature_range(float x[M][N]);

int main(void)
{
    float current_temperature[M][N];
    float next_temperature[M][N];
    int temperature_map[M][N];

    int i, time;
    float difference;

    // Display the program title
    printf("\n=====================================");
    printf("\n      Heat Diffusion Simulation");
    printf("\n=====================================\n");

    // Get the simulation time from the user
    time = get_simulation_time();

    printf("\nSimulation time: %d seconds\n", time);

    // Initialize the temperature plate
    initialize_plate(current_temperature);

    if (time == 0)
    {
        // Display the initial temperature distribution
        printf("\nInitial temperature distribution:\n");
        printf("---------------------------------\n");

        print_temperature_matrix(current_temperature);
    }
    else
    {
        // Display the initial temperature distribution
        printf("\nInitial temperature distribution:\n");
        printf("---------------------------------\n");

        print_temperature_matrix(current_temperature);

        if (time == 1)
        {
            // Calculate the temperature distribution after one time step
            update_temperature(current_temperature, next_temperature);

            // Convert temperatures into histogram categories
            create_temperature_map(next_temperature, temperature_map);
        }
        else
        {
            // Repeat the temperature update for the required number of time steps
            for (i = 1; i < time; i++)
            {
                // Calculate the next temperature state of the plate
                update_temperature(current_temperature, next_temperature);

                // Convert temperatures into histogram categories
                create_temperature_map(next_temperature, temperature_map);
            }
        }

        // Display the final temperature distribution
        printf("\nFinal temperature distribution after %d seconds:\n", time);
        printf("------------------------------------------------\n");

        print_temperature_matrix(next_temperature);

        // Display the minimum and maximum temperatures
        print_temperature_range(next_temperature);

        // Display the temperature category matrix
        printf("\nTemperature category map:\n");
        printf("-------------------------\n");

        print_temperature_map(temperature_map);

        // Display the temperature histogram
        printf("\nTemperature histogram:\n");
        printf("----------------------\n");

        print_temperature_histogram(temperature_map);

        // Calculate the total temperature variation
        difference = absolute_difference(update_temperature(current_temperature, next_temperature));

        printf("\n\nSimulation completed after %d time steps.\n", time);

        printf("\nTotal absolute difference: %.4f Celsius\n", difference);

        // Check whether the plate has reached steady state
        if (difference < 1)
        {
            printf("\nThe plate has reached a steady state.\n");
        }
        else
        {
            printf("\nThe plate has not reached a steady state yet.\n");
        }

        printf("\n==============================================\n");
    }

    return 0;
}

int initialize_plate(float x[M][N])
{
    int i, j;

    // Set the fixed temperatures on the plate boundaries
    for (i = 1; i < N - 1; i++)
    {
        x[0][i] = temp1;
        x[M - 1][i] = temp3;
    }

    for (i = 1; i < M - 1; i++)
    {
        x[i][N - 1] = temp2;
        x[i][0] = temp4;
    }

    // Fill the internal elements with the initial temperature
    for (i = 1; i < M - 1; i++)
    {
        for (j = 1; j < N - 1; j++)
        {
            x[i][j] = temp5;
        }
    }

    // Calculate the corner temperatures as the average of adjacent sides
    x[0][0] = (x[0][1] + x[1][0]) / 2;

    x[0][N - 1] = (x[0][N - 2] + x[1][N - 1]) / 2;

    x[M - 1][N - 1] = (x[M - 1][N - 2] + x[M - 2][N - 1]) / 2;

    x[M - 1][0] = (x[M - 1][1] + x[M - 2][0]) / 2;

    return 0;
}

int print_temperature_matrix(float x[M][N])
{
    int i, j;

    // Print the temperature matrix
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf("%5.2f", x[i][j]);
        }

        printf("\n");
    }

    return 0;
}

float update_temperature(float x[M][N], float y[M][N])
{
    int i, j;

    float sum = 0;

    // Calculate the next temperature values using the heat diffusion equation
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            // Keep the boundary temperatures constant
            if (i == 0 && j != 0 && j != N - 1)
                y[i][j] = temp1;

            else if (i == M - 1 && j != N - 1 && j != 0)
                y[i][j] = temp3;

            else if (j == N - 1 && i != M - 1 && i != 0)
                y[i][j] = temp2;

            else if (j == 0 && i != 0 && i != M - 1)
                y[i][j] = temp4;

            // Keep the corner temperatures unchanged
            else if (i == 0 && j == 0)
                y[i][j] = x[0][0];

            else if (i == 0 && j == N - 1)
                y[i][j] = x[0][N - 1];

            else if (i == M - 1 && j == N - 1)
                y[i][j] = x[M - 1][N - 1];

            else if (i == M - 1 && j == 0)
                y[i][j] = x[M - 1][0];

            else
            {
                // Apply the temperature update formula to internal cells
                y[i][j] = 0.1 * (x[i - 1][j - 1] + x[i - 1][j] +
                                 x[i - 1][j + 1] + x[i][j - 1] +
                                 2 * x[i][j] + x[i][j + 1] +
                                 x[i + 1][j - 1] + x[i + 1][j] +
                                 x[i + 1][j + 1]);

                // Calculate the total temperature change
                sum += absolute_difference(y[i][j] - x[i][j]);
            }
        }
    }

    // Copy the new temperature state back to the original matrix
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            x[i][j] = y[i][j];
        }
    }

    return sum;
}

int create_temperature_map(float x[M][N], int y[M][N])
{
    int i, j;

    float min = 0;
    float max = 0;

    float width, step;

    // Find the minimum and maximum temperature values
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            if (x[i][j] < min)
            {
                min = x[i][j];
            }

            if (x[i][j] > max)
            {
                max = x[i][j];
            }
        }
    }

    // Divide the temperature range into 10 equal regions
    width = max - min;

    step = width / 10;

    // Assign each temperature value to a category from 0 to 9
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            if (min <= x[i][j] && x[i][j] <= min + step)
            {
                y[i][j] = 0;
            }

            else if (min + step < x[i][j] && x[i][j] <= min + 2 * step)
            {
                y[i][j] = 1;
            }

            else if (min + 2 * step < x[i][j] && x[i][j] <= min + 3 * step)
            {
                y[i][j] = 2;
            }

            else if (min + 3 * step < x[i][j] && x[i][j] <= min + 4 * step)
            {
                y[i][j] = 3;
            }

            else if (min + 4 * step < x[i][j] && x[i][j] <= min + 5 * step)
            {
                y[i][j] = 4;
            }

            else if (min + 5 * step < x[i][j] && x[i][j] <= min + 6 * step)
            {
                y[i][j] = 5;
            }

            else if (min + 6 * step < x[i][j] && x[i][j] <= min + 7 * step)
            {
                y[i][j] = 6;
            }

            else if (min + 7 * step < x[i][j] && x[i][j] <= min + 8 * step)
            {
                y[i][j] = 7;
            }

            else if (min + 8 * step < x[i][j] && x[i][j] <= min + 9 * step)
            {
                y[i][j] = 8;
            }

            else if (min + 9 * step <= x[i][j])
            {
                y[i][j] = 9;
            }
        }
    }

    return 0;
}

int print_temperature_map(int x[M][N])
{
    int i, j;

    // Print the temperature category matrix
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf("%d  ", x[i][j]);
        }

        printf("\n");
    }

    return 0;
}

int get_simulation_time(void)
{
    int x;

    // Ask the user to enter the simulation duration
    printf("\nEnter the simulation time in seconds: ");

    scanf("%d", &x);

    return x;
}

int print_temperature_histogram(int x[M][N])
{
    int i, j;

    // Initialize counters for each temperature category
    int number_of_0 = 0;
    int number_of_1 = 0;
    int number_of_2 = 0;
    int number_of_3 = 0;
    int number_of_4 = 0;
    int number_of_5 = 0;
    int number_of_6 = 0;
    int number_of_7 = 0;
    int number_of_8 = 0;
    int number_of_9 = 0;

    // Count the occurrences of each temperature category
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            switch (x[i][j])
            {
            case 0:
                number_of_0 += 1;
                break;

            case 1:
                number_of_1 += 1;
                break;

            case 2:
                number_of_2 += 1;
                break;

            case 3:
                number_of_3 += 1;
                break;

            case 4:
                number_of_4 += 1;
                break;

            case 5:
                number_of_5 += 1;
                break;

            case 6:
                number_of_6 += 1;
                break;

            case 7:
                number_of_7 += 1;
                break;

            case 8:
                number_of_8 += 1;
                break;

            case 9:
                number_of_9 += 1;
                break;
            }
        }
    }

    // Display the histogram for every temperature category
    print_histogram_bar(0, number_of_0);
    print_histogram_bar(1, number_of_1);
    print_histogram_bar(2, number_of_2);
    print_histogram_bar(3, number_of_3);
    print_histogram_bar(4, number_of_4);
    print_histogram_bar(5, number_of_5);
    print_histogram_bar(6, number_of_6);
    print_histogram_bar(7, number_of_7);
    print_histogram_bar(8, number_of_8);
    print_histogram_bar(9, number_of_9);

    return 0;
}

int print_histogram_bar(int x, int y)
{
    int i;

    // Print the temperature category label
    printf("\n[%d] ", x);

    // Print the histogram bars
    for (i = 0; i < y; i++)
    {
        printf("%c", '#');
    }

    return 0;
}

float absolute_difference(float x)
{
    // Return the absolute value of the given number
    return (x < 0) ? -x : x;
}

int print_temperature_range(float x[M][N])
{
    int i, j;

    float min = x[0][0];
    float max = x[0][0];

    // Find the minimum and maximum temperature values
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            if (x[i][j] < min)
            {
                min = x[i][j];
            }

            if (x[i][j] > max)
            {
                max = x[i][j];
            }
        }
    }

    // Display the temperature range
    printf("\nTemperature range:\n");
    printf("------------------\n");
    printf("Minimum temperature: %.2f Celsius\n", min);
    printf("Maximum temperature: %.2f Celsius\n", max);

    return 0;
}