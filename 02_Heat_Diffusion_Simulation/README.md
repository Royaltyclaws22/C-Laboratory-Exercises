# 🌡️ Heat Diffusion Simulation

A C console application that simulates heat diffusion on a two-dimensional temperature plate. The program models the temperature evolution of a 10×20 plate over time using a discrete heat diffusion equation and evaluates whether the system reaches a steady state.


## ⚙️ Features

- Initialize a 10×20 temperature plate with:
  - Different fixed temperatures on each boundary.
  - Average temperatures at the four corner elements.
  - An initial temperature value for the internal elements.
- Simulate heat diffusion over multiple time steps using the numerical temperature update equation:

$$
\begin{aligned}
\Theta_t(i, j) = 0.1 \cdot \Big( & \Theta_{t-1}(i-1, j-1) + \Theta_{t-1}(i-1, j) + \Theta_{t-1}(i-1, j+1) + \Theta_{t-1}(i, j-1) + 2 \cdot \Theta_{t-1}(i, j) \\
& + \Theta_{t-1}(i, j+1) + \Theta_{t-1}(i+1, j-1) + \Theta_{t-1}(i+1, j) + \Theta_{t-1}(i+1, j+1) \Big)
\end{aligned}
$$

- Maintain constant boundary temperatures during the simulation.
- Display:
  - Initial temperature distribution.
  - Final temperature distribution after the selected simulation time.
  - Temperature category map.
  - Temperature histogram.
- Calculate the total absolute temperature difference between simulation steps.
- Determine whether the plate has reached a steady state using a 1 Celsius degree convergence criterion.
- Organize the program into modular functions for initialization, simulation, visualization, and analysis.


## 💻 Installation & Running

1. Clone the repository:
```bash
git clone https://github.com/Royaltyclaws22/C-Laboratory-Exercises.git
```
2. Navigate to the project folder:
```bash
cd C-Laboratory-Exercises/02_Heat_Diffusion_Simulation
```
3. Compile the program:
```bash
gcc Heat_Diffusion_Simulation.c -o Heat_Diffusion_Simulation
```
4. Run the program:

* **Windows (Command Prompt)**
  ```bash
  Heat_Diffusion_Simulation.exe
  ```

* **Linux / macOS**
  ```bash
  ./Heat_Diffusion_Simulation
  ```


## 💡 Usage

Run the program and enter the desired simulation time:

```text
=====================================
      Heat Diffusion Simulation
=====================================

Enter the simulation time in seconds: 22

Simulation time: 22 seconds
```

The program first initializes the temperature plate and displays the initial state:

```text
Initial temperature distribution:
---------------------------------
 3.00 2.00 2.00 2.00 ...
 4.00 1.00 1.00 1.00 ...
 ...
```

After completing the simulation steps, the program displays the final temperature distribution:

```text
Final temperature distribution after 22 seconds:
------------------------------------------------
 3.00 2.00 2.00 2.00 ...
 4.00 2.91 2.40 2.17 ...
 ...
```

The program also provides additional analysis:

```text
Temperature range:
------------------
Minimum temperature: -5.00 Celsius
Maximum temperature: 4.00 Celsius

Temperature category map:
-------------------------
8  7  7  7 ...  
9  8  8  7 ...
...

Temperature histogram:
----------------------

[0] ########
[1] ##
...

Simulation completed after 22 time steps.

Total absolute difference: 2.4680 Celsius

The plate has not reached a steady state yet.

==============================================
```

The steady-state condition is satisfied when:

```text
Total absolute difference < 1 Celsius degree
```

indicating that the temperature distribution no longer changes significantly over time.
