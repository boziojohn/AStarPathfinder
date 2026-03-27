# AStarPathfinder
Visualize and compute the optimal path through a room with obstacles using the A* algorithm. The program generates random rooms, marks obstacles, and displays the step-by-step pathfinding process, highlighting the robot's route from start to finish

A C program that uses the **A* algorithm** to find the optimal path from the entrance to the exit of a randomly generated room while avoiding obstacles. The program visualizes the step-by-step process and the final path on a grid.

## Features
- Generates random rooms with adjustable sizes and obstacle percentages
- Uses A* algorithm with Manhattan distance heuristic
- Step-by-step visualization of path exploration
- Marks the optimal path from start to finish
- Handles rooms of size 10x10 up to 20x20

## Files
- `main.c` – Main program implementing the A* algorithm and priority queue
- Additional helper files (if any) for queue and node management

## Usage

### Compile
```bash
gcc -o astar main.c -lm
