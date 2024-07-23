// Mustafa Batin EFE - 29272
// CS300 - Data Structures - Homework 1

# define DEBUG_3DARRAY false // Debugging - Creating Maze Members
# define DEBUG_STACK false // Debugging - Stack Members
# define DEBUG_CELL_WALL_SELECTION true // Debugging - Stack Members

#include <iostream>
#include <string>
#include <random>

#include "stack.h"

using namespace std;


// Check if the current cell has unvisited neighbors
bool CheckUVneighbor(Cell<int>** maze, int M, int N, Cell<int> c){
    // Lets check if the current cell has unvisited neighbors
    // If there is an unvisited neighbor, return true
    
    int row = -1;
    int col = -1;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (maze[i][j].x == c.x && maze[i][j].y == c.y){
                //cout << "Current Cell Values .x and .y: " << c.x << " " << c.y << endl;
                //cout << "Index of Current Cell (c): " << i << " " << j << endl;
                row = i;
                col = j;
                // End the loop
                j = N;
                i = M;
            }
        }
    }

    cout << "Searching for unvisited neighbors of maze[" << row << ", " << col << "]";
    int count = 0;

    if(col-1 >= 0 && maze[row][col-1].visited == 0){ // Left
        count++;
    }  
    
    if(col+1 < N && maze[row][col+1].visited == 0){ // Right
        count++;
    } 
     
    if(row+1 < M && maze[row+1][col].visited == 0){ // Down
        count++;
    } 
    
    if(row-1 >= 0 && maze[row-1][col].visited == 0){ // Up
        count++;
    }

    if(count > 0){
        cout <<  "->>>> There exist a neighbor!!!!! " << endl << endl;
        return true;
    } else{
        cout << "->>>> There is no neighbor! " << endl << endl;
        return false;
    }
}


// Lets create a function to select unvisited neighbors randomly
Cell<int> SelectNeighbor(Cell<int>**& maze, int M, int N, Cell<int>& c){
    // Lets select a random neighbor of current cell and return it after checking

    // 0 : Up, 1 : Down, 2 : Right, 3 : Left

    // There might be cont loop here, we can store previous random values and stop selecting more than 4 times in the future

    // If all numbers are selected, we can return the current cell meaning there is no unvisited neighbors left

    Cell<int> n; // Neigbor cell
    mt19937 engine(random_device{}()); // Random number engine
    uniform_int_distribution<int> dist(0, 3); // Distribution in range [0, 3]

    // If random selected all 4 numbers and all neighbors are visited, return the current
    // Create the list - Lets not use vectors, lets use arrays
    int selected[4] = {-1, -1, -1, -1}; // Index numbers of 0,1,2,3  

    // Lets check the random number
    while(true){
        if(selected[0] == 1 && selected[1] == 1 && selected[2] == 1 && selected[3] == 1){
            // All numbers are selected
            return c;
        }

        int random = dist(engine);

        // It selects sometimes too many times the same rundom number, fix it------------------------------------------------------------------------------------------------
        selected[random] = 1;
        
        int row = -1;
        int col = -1;
        // Lets find c in the maze
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (maze[i][j].x == c.x && maze[i][j].y == c.y){
                    row = i;
                    col = j;
                    
                    maze[i][j].visited = 1; // Guarantee current cell is visited
                    // End the loop
                    j = N;
                    i = M;
                }
            }
        }

        switch (random){
            case 0:
                // Up
                // First check if the cell on the maze
                if (row-1 >= 0 && maze[row-1][col].visited == 0){
                    if(DEBUG_CELL_WALL_SELECTION){
                        cout << "Index of Current Cell (c): " << row << " " << col << endl;
                        cout << "Current Cell Values .x and .y: " << c.x << " " << c.y << endl;
                    }
                    n = maze[row-1][col];
                    n.visited =1;
                    n.D = 0;
                    maze[row][col].U = 0;
                    cout << "Selected Up TO: maze["<< row-1 << ", " << col <<  "]"<< endl<< endl;
                    return n;
                }
                break;
            case 1:
                // Down
                // First check if the cell on the maze
                if (row+1 < M && maze[row+1][col].visited == 0){
                    if(DEBUG_CELL_WALL_SELECTION){
                        cout << "Index of Current Cell (c): " << row << " " << col << endl;
                        cout << "Current Cell Values .x and .y: " << c.x << " " << c.y << endl;
                    }
                    n = maze[row+1][col];
                    n.visited =1;
                    n.U = 0;
                    maze[row][col].D = 0;
                    cout << "Selected Down TO: maze["<< row+1 << ", " << col <<  "]"<< endl<< endl;
                    return n;
                }
                break;
            case 2:
                // Right
                // First check if the cell on the maze
                if (col+1 < N && maze[row][col+1].visited == 0){
                    if(DEBUG_CELL_WALL_SELECTION){
                        cout << "Index of Current Cell (c): " << row << " " << col << endl;
                        cout << "Current Cell Values .x and .y: " << c.x << " " << c.y << endl;
                    }
                    n = maze[row][col+1];
                    n.visited =1;
                    n.L = 0;
                    maze[row][col].R = 0;
                    cout << "Selected Right TO: maze["<< row << ", " << col+1 <<  "]"<< endl << endl;
                    return n;
                }
                break;
            case 3:
                // Left
                // First check if the cell on the maze
                if (col-1 >= 0 && maze[row][col-1].visited == 0){
                    if(DEBUG_CELL_WALL_SELECTION){
                        cout << "Index of Current Cell (c): " << row << " " << col << endl;
                        cout << "Current Cell Values .x and .y: " << c.x << " " << c.y << endl;
                    }
                    n = maze[row][col-1];
                    n.visited =1;
                    n.R = 0;
                    maze[row][col].L = 0;
                    cout << "Selected Left TO: maze[" << row << ", " << col-1 << "]"<< endl<< endl;
                    return n;
                }
                break;
        }

    }

    return n;
}

// Lets create a function to create maze
void CreateMaze(int K, int M, int N){
    // I will use 3D arrays for this
    // K number of mazes and M rows and N columns
    // So that I will have access to all mazes with one array
    
    // Create the maze
    Cell<int>*** maze = new Cell<int>**[K];    // Allocate memory for maze
    // Fill the maze with all walls according to the x-y rules
    // I want bottom left corner to be x=0, y=0 and top right to be x=N-1, y=M-1
    
    cout << endl;

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
            cout << "Maze " << k+1  << "maze[M = row][N = col]"<< endl;
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

            /*
                Rest of the selections
            */
            // Lets continue to search for other unvisited neighbors and remove walls.
            // We will use a while loop to check if there is any unvisited neighbors
            // If we need to backtrack because no root available, we will use stack to pop last element and continue from there
            // Lets start with the first stack

            while(CheckUVneighbor(maze[k], M, N, askedStack->top())){
                Cell<int> temp_rest;
                Cell<int> temp_rest_base = askedStack->top();
                askedStack->pop();

                temp_rest = SelectNeighbor(maze[k], M, N, temp_rest_base);
                // cout << "Selected Neighbor Rest: " << temp_rest.x << " " << temp_rest.y << endl;

                int row = -1;
                int col = -1;
                for (int i = 0; i < M; i++) {
                    for (int j = 0; j < N; j++) {
                        if (maze[k][i][j].x == temp_rest.x && maze[k][i][j].y == temp_rest.y){
                            //cout << "Current Cell Values .x and .y: " << c.x << " " << c.y << endl;
                            //cout << "Index of Current Cell (c): " << i << " " << j << endl;
                            row = i;
                            col = j;
                            maze[k][row][col].visited = temp_rest.visited;
                            maze[k][row][col].L = temp_rest.L;
                            maze[k][row][col].R = temp_rest.R;
                            maze[k][row][col].U = temp_rest.U;
                            maze[k][row][col].D = temp_rest.D;
                            // End the loop
                            j = N;
                            i = M;
                        }
                    }
                }
                    
                // Push maze, push source row, col, push destination row, col
                // Or do it on SelectNeighbor function
                askedStack->push(temp_rest_base);
                askedStack->push(maze[k][row][col]);

            }
            cout << "Maze has no neighbors! Time to backtrack! " << endl;
        

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