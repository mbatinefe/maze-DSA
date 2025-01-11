# Maze Generation and Pathfinding

A C++ implementation of random maze generation and pathfinding using linked list-based stack data structures and Depth-First Search (DFS) algorithm.

## Project Overview

This project implements:
1. Random maze generation using DFS
2. Path finding between entry/exit points
3. Custom template-based Stack implementation using LinkedList

## Data Structures

### Stack Implementation
- Template-based class
- LinkedList backing structure
- No STL vectors allowed
- Custom push/pop operations

### Maze Structure
- 2D grid representation
- Cell properties: left, right, up, down walls
- (0,0) coordinate at left bottom
- Perfect maze guarantee (unique paths)

## Features

- Random maze generation using DFS algorithm
- Multiple maze generation in a single run
- Pathfinding between any two points in the maze using DFS
- Custom maze dimensions (M x N)
- Save maze structures and paths to files

## File Structure

- `main.cpp` - Main program implementation
- `stack.h` - Stack data structure implementation
- `stack.cpp` - Stack methods implementation
- `examples/` - Sample maze and path files
- `mazeDrawer/` - Utility for visualizing mazes

## Usage

1. Compile the program:
```cpp
g++ main.cpp stack.cpp -o maze
```
2. Run the program:
```cpp
./maze
```

3. Follow the prompts:
- Enter number of mazes (K)
- Enter maze dimensions (M rows, N columns)
- Select a maze ID for pathfinding
- Enter entry point coordinates (x,y)
- Enter exit point coordinates (x,y)

## Output Files
- Maze files: maze_k.txt (where k is maze ID)
- Path files: maze_k_path_entryX_entryY_exitX_exitY.txt
- Visualization files: mazeDrawn_MxN.txt

## Example
```cpp
Enter the number of mazes: 1
Enter the number of rows and columns (M and N): 50 50
All mazes are generated.

Enter a maze ID between 1 to 1 inclusive to find a path: 1
Enter x and y coordinates of the entry points (x,y): 0 0
Enter x and y coordinates of the exit points (x,y): 49 49
```

