# GAME OF LIFE
This project implements the Game of Life using matrices where '+' represents a dead cell and 'X' represents alive cells, with the following features:
- Task 1: advance the game by n generations  
- Task 2: display cell changes per generation as a stack of lists of coordinates
  - Bonus: starting from the last matrix and the stack of changes, recreate the original matrix
- Task 3: use a binary tree to show how the game changes with different sets of rules
- Task 4: find the longest hamiltonian chain in a conected component in a graph representing the game matrix

For more details, you can check the PROJECT section on this website: https://site-pa.netlify.app/proiecte/ 

## TASKS
### 1. Task 1 
Print the matrices corresponding to the first n generations of the game.
### 2. Task 2
Print a list of coordinates for the cells that have changed their status for the first n generations.
### 3. Task 3
Build a binary tree containing stacks created in task 2 and display the game matrices. The tree has the following structure: 
- The root contains a list with all the alive cells at the begining
- The left child contains the next generation of the game but with a single rule: any cell with exactly 2 neighbours will come to life
- The right child contains the next generation of the game with the standard rules
### 4. Task 4
Generate a graph from the alive cells where the vertices represent the cells and edges connect adjacent alive cells
Print the length of the longest hamiltonian chain in each generation and the coordinates of the vertices that composed it 

## HOW TO USE
The code uses two arguments: the input file name and the output file name
The input file has the following structure: 

T

m, n

K

(the original matrix)

where: 

T -> number of the task

m, n -> number of rows and columns of the matrix

K -> number of generations to calculate

For testing, you can download the checker tool from the website provided above and follow the installation instructions.
After installing, run the command ./checker -i for interactive mode.

 ## Project Structure and Details
 - FILES
   - gol.c: contains the main logic of the Game of life
   - gol.h: contains function declarations, struct definitions, and include guards to share code between source files
   - gameoflife.c: handles input/output and program execution.
 - Data structures used
   - matrices, corresponding to different generations
   - linked lists, that show the changes of the cells
   - stack, for storing the lists
   - binary tree, used to show how the game changes with different sets of rules
   - graph, to find the longest hamiltonian chain 
