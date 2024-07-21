// Mustafa Batin EFE - 29272
// CS300 - Data Structures - Homework 1

# define DEBUG_3DARRAY true // Debugging - Creating Maze Members
# define DEBUG_STACK false // Debugging - Stack Members
# define DEBUG_CELL_WALL_SELECTION true // Debugging - Stack Members

#include <iostream>
#include <string>
#include <random>

#include "stack.h"

using namespace std;

// Lets create a function to remove wall
void RemoveWall(Cell<int>& c, Cell<int>& n){
    // c represent where we are
    // n represent where we want to go

    // Remove wall between c and n
    // Situation 1 : | c | n | or | n | c |
                    // Going left or right
    if (c.x != n.x && c.y == n.y){
        if (c.x < n.x){
            c.R = 0;
            n.L = 0;
        }else{
            c.L = 0;
            n.R = 0;
        }
    } else {
        // Situation 2 : | c | or | n |
        //               | n |    | c |
                        // Going up or down
        if(c.y < n.y){
            c.U = 0;
            n.D = 0;
        } else{
            c.D = 0;
            n.U = 0;
        }
    }
}

// Check if the current cell has unvisited neighbors
bool CheckUVneighbor(Cell<int>** maze, Cell<int> c){
    // Lets check if the current cell has unvisited neighbors
    // If there is an unvisited neighbor, return true
    
    if(maze[c.y+1][c.x].visited == 0){
        return true;
    } else if(maze[c.y-1][c.x].visited == 0){
        return true;
    } else if(maze[c.y][c.x+1].visited == 0){
        return true;
    } else if(maze[c.y][c.x-1].visited == 0){
        return true;
    }

    return false;
}

// Lets create a function to select unvisited neighbors randomly
Cell<int> SelectNeighbor(Cell<int>** maze, int K, int M, int N, Cell<int> c){
    // Lets select a random neighbor of current cell and return it after checking

    // 0 : Up, 1 : Down, 2 : Right, 3 : Left

    // There might be cont loop here, we can store previous random values and stop selecting more than 4 times in the future

    // If all numbers are selected, we can return the current cell meaning there is no unvisited neighbors left

    Cell<int> n; // Neigbor cell
    mt19937 engine(random_device{}()); // Random number engine
    uniform_int_distribution<int> dist(0, 3); // Distribution in range [0, 3]

    // If random selected all 4 numbers and all neighbors are visited, return the current
    // Create the list - Lets not use vectors, lets use arrays
     int selected[4] = {0, 0, 0, 0}; // Index numbers of 0,1,2,3  

    // Lets check the random number
    while(true){
        bool allAttempted = true;
        for(int i = 0; i < 4; i++){
            if(selected[i] == 0){
                allAttempted = false;
                break;
            }
        }

        if(allAttempted){
            // All directions attempted, return current cell
            return c;
        }
        int random = dist(engine);
        if(selected[random] == -1){
            // This direction was already attempted, try another
            continue;
        }
        // Mark this direction as attempted
        selected[random] = -1;

        switch (random){
            case 0:
                // Up
                // First check if the cell on the maze
                if (c.y-1 >= 0 && maze[c.y-1][c.x].visited == 0){ // Correct "Up" logic
                    n = maze[c.y-1][c.x];
                    maze[n.y][n.x].visited = 1; // Mark the new cell as visited
                    cout << "Up: maze["<< n.y << ", " << n.x << "]"<< endl;
                    return n;
                }
            case 1:
                // Down
                if (c.y+1 < N && maze[c.y+1][c.x].visited == 0){ // Correct "Down" logic
                    n = maze[c.y+1][c.x];
                    maze[n.y][n.x].visited = 1; // Mark the new cell as visited
                    cout << "Down: maze["<< n.y << ", " << n.x << "]"<< endl;
                    return n;
                }
                break;
            case 2:
                // Left
                if (c.x-1 >= 0 && maze[c.y][c.x-1].visited == 0){
                    n = maze[c.y][c.x-1];
                    maze[n.y][n.x].visited = 1; // Mark the new cell as visited
                    cout << "Left: maze["<< n.y << ", " << n.x << "]"<< endl;
                    return n;
                }
                break;
            case 3:
                // Right
                if (c.x+1 < M && maze[c.y][c.x+1].visited == 0){
                    n = maze[c.y][c.x+1];
                    maze[n.y][n.x].visited = 1; // Mark the new cell as visited
                    cout << "Right: maze["<< n.y << ", " << n.x << "]"<< endl;
                    return n;
                }
                break;
        } break;

    }

    return n;
}


/*
        switch (random){
            case 0:
                // Up
                // First check if the cell on the maze
                if ((c.y)+1 < M && maze[(c.y)+1][c.x].visited == 0){
                    n = maze[c.y+1][c.x];
                    cout << "Selected Up: maze["<< c.y+1 << ", " << c.x <<  "]"<< endl;
                    return n;
                }
                break;
            case 1:
                // Down
                // First check if the cell on the maze
                if ((c.y)-1 >= 0 && maze[c.x+1][c.x].visited == 0){
                    n = maze[c.x+1][c.x];
                    cout << "Selected Down: maze["<< c.x+1 << ", " << c.x <<  "]"<< endl;
                    return n;
                }
                break;
            case 2:
                // Right
                // First check if the cell on the maze
                if ((c.x)+1 < N && maze[N-(c.x)-1][N-(c.x)].visited == 0){
                    n = maze[N-(c.x)-1][N-(c.x)];
                    cout << "Selected Right: maze["<< c.x << ", " << (c.y)+1 <<  "]"<< endl;
                    return n;
                }
                break;
            case 3:
                // Left
                // First check if the cell on the maze
                if (c.y-1 <= 0 && maze[c.y][c.x-1].visited == 0){
                    n = maze[c.y][c.x-1];
                    cout << "Selected Left: maze[" << c.y << ", " << c.x-1 << "]"<< endl;
                    return n;
                }
                break;
        }
        
*/

// Lets create a function to create maze
void CreateMaze(int K, int M, int N){
    // I will use 3D arrays for this
    // K number of mazes and M rows and N columns
    // So that I will have access to all mazes with one array
    
    // Create the maze
    Cell<int>*** maze = new Cell<int>**[K];    // Allocate memory for maze
    // Fill the maze with all walls according to the x-y rules
    // I want bottom left corner to be x=0, y=0 and top right to be x=N-1, y=M-1
    for (int k = 0; k < K; k++) {
        maze[k] = new Cell<int>*[M];    // Allocate memory for maze
        for (int i = 0; i < M; i++) { // Rows
            maze[k][i] = new Cell<int>[N];    // Allocate memory for maze
            for (int j = 0; j < N; j++) { // Cols
                maze[k][i][j].x = j;
                maze[k][i][j].y = M-i-1; // We want bottom left to be 0,0
                // If cell type is int, how can we store true or false? 
                // We can use 1 for true and 0 for false
                maze[k][i][j].L = 1;
                maze[k][i][j].R = 1;
                maze[k][i][j].U = 1;
                maze[k][i][j].D = 1;
                maze[k][i][j].visited = 0;

                if(DEBUG_3DARRAY){
                    cout << maze[k][i][j].L << maze[k][i][j].R << maze[k][i][j].U << maze[k][i][j].D;
                }
            }
        }
        if(DEBUG_3DARRAY){ 
            cout << endl;
        }
    }

    if(DEBUG_3DARRAY){
        // Lets print the maze with x and y coordinates
        for (int k = 0; k < K; k++) {
            cout << "Maze " << k+1  << "According to inside values .x .y"<< endl;
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    cout << "(" << maze[k][i][j].x << "," << maze[k][i][j].y << ") ";
                }
                cout << endl;
            }
            cout << endl;
        }

        for (int k = 0; k < K; k++) {
            cout << "Maze " << k+1  << "According to inside values maze[FIRST][SECOND]"<< endl;
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    cout << "(" << i << "," << j << ") ";
                }
                cout << endl;
            }
            cout << endl;
        }
    }

    // Lets create our stack list
    ListOfStacks<Cell<int>> stacks_all = ListOfStacks<Cell<int>>(K);

    // Lets add mazes to the stack's first element in order to list
    for(int k = 0; k < K; k++){
        Stack<Cell<int>>* askedStack = stacks_all.getStackAtIndex(k);

        if (askedStack != nullptr) {
            // Lets add (0,0) to the stack
            maze[k][M-1][0].visited = 1;
            askedStack->push(maze[k][M-1][0]);

            cout << "Start: maze" << maze[k][M-1][0].y << " " << maze[k][M-1][0].x << endl;
            cout << "Selected Start: " << M-1 << " " << 0 << endl;
             /*
                First selection of road
            */
            Cell<int> temp;
            temp = SelectNeighbor(maze[k], K, M, N, maze[k][M-1][0]); // First selection of neighbor

            // Lets print temp
            cout << "Selected Neighbor: " << temp.y << " " << temp.x << endl;

            if(maze[k][temp.y][temp.x] != maze[k][M-1][0]){
                RemoveWall(maze[k][M-1][0], maze[k][temp.y][temp.x]);
                maze[k][temp.y][temp.x].visited = 1;
                askedStack->push(maze[k][temp.y][temp.x]);
            } else {
                cout << "Maze is 1x1 !!!" << endl;
            }

            /*
                Rest of the selections
            */
            // Lets continue to search for other unvisited neighbors and remove walls.
            // We will use a while loop to check if there is any unvisited neighbors
            // If we need to backtrack because no root available, we will use stack to pop last element and continue from there
            // Lets start with the first stack

            while(CheckUVneighbor(maze[k], askedStack->top())){
                Cell<int> temp_rest;
                temp_rest = SelectNeighbor(maze[k], K, M, N, askedStack->top());
                cout << "Selected Neighbor Rest: " << temp_rest.x << " " << temp_rest.y << endl;

                Cell<int> temp_rest_main = askedStack->top();
                if(maze[k][temp_rest.y][temp_rest.x] != temp_rest_main){
                    RemoveWall(temp_rest_main, maze[k][temp_rest.y][temp_rest.x]);
                    maze[k][temp_rest.y][temp_rest.x].visited = 1;
                    askedStack->push(maze[k][temp_rest.y][temp_rest.x]);
                } else {
                    cout << "Maze has no neighbors! Time to backtrack! " << endl;
                    break;
                    // DO BACKTRACKING ALGORITHM FOR STACKS
                }
            }

            if (DEBUG_STACK) {
                cout << "Stack " << k+1 << " : ";
                while (!askedStack->isEmpty()) {
                    Cell<int> temp = askedStack->topAndPop();
                    cout << "(" << temp.x << "," << temp.y << ") ";
                }
                cout << endl;
            }
            
            // Lets construct the maze path/wall algorithm now

    
        } else {
            if (DEBUG_STACK) {
                cout << "THERE IS NO STACK AVAILABLE" << endl;
            }
        }
        if(DEBUG_CELL_WALL_SELECTION){
            // Lets print the maze and their selected neighbors
            cout << "Maze " << k+1 << endl;
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    cout << "(" << maze[k][i][j].x << "," << maze[k][i][j].y << ") " << maze[k][i][j].U << maze[k][i][j].D << maze[k][i][j].R << maze[k][i][j].L << " " << maze[k][i][j].visited << " | ";
                }
                cout << endl;
            }
            cout << endl;

        }
    }
}



int main() {

    // Get input for maze number
    int K;
    cout << "Enter the number of mazes: ";
        // Assume K is positive integer
    cin >> K;

    // Get input for 2D Maze
    int M, N;
    cout << "Enter the number of rows and columns (M and N): ";
        // Assume M and N > 1
    cin >> M >> N;

    // Create the maze
    CreateMaze(K, M, N);
    cout << "All mazes are generated." << endl << endl;

    // Now, we will ask for entry, exit points and maze ID
    int maze_id;
    cout << "Enter a maze ID between 1 to " + to_string(K) + " inclusive to find a path: ";
    cin >> maze_id;

    int entry_X, entry_Y, exit_X, exit_Y;
    cout << "Enter x and y coordinates of the entry points (x,y) or (column,row): ";
    cin >> entry_X >> entry_Y;
    cout << "Enter x and y coordinates of the exit points (x,y) or (column,row): ";
    cin >> exit_X >> exit_Y;

    // Now, lets figure it out the path



}    