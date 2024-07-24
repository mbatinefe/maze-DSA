// Mustafa Batin EFE - 29272
// CS300 - Data Structures - Homework 1

# define DEBUG_3DARRAY true // Debugging - Creating Maze Members
# define DEBUG_STACK false // Debugging - Stack Members
# define DEBUG_CELL_WALL_SELECTION true // Debugging - Stack Members

#include <iostream>
#include <string>
#include <random>
#include <fstream>

#include "stack.h"

using namespace std;


// Lets save the maze
void saveMaze(Cell<int>** maze, int M, int N, int K){
    // Lets save the maze to a file
    // We will save the maze as a text file

    // Create the file
    string filename = "maze_" + to_string(K) + ".txt";
    ofstream file(filename);

    // Write the maze to the file
    file << M <<  " " << N << endl;
    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){
            file << "x=" <<maze[M-i-1][j].x << " y=" << maze[M-i-1][j].y << " l=" << maze[M-i-1][j].L << " r=" << maze[M-i-1][j].R << " u=" << maze[M-i-1][j].U << " d=" << maze[M-i-1][j].D << endl;
        }
    }
    file.close();
}

// Check if the current cell has unvisited neighbors
bool CheckUVneighbor(Cell<int>** maze, int M, int N, Cell<int> c){
    // Lets check if the current cell has unvisited neighbors
    // If there is an unvisited neighbor, return true

    cout << "Searching for unvisited neighbors of maze[" << c.row << ", " << c.col << "]";
    int count = 0;

    if(c.col-1 >= 0 && maze[c.row][c.col-1].visited == 0){ // Left
        count++;
    }  
    
    if(c.col+1 < N && maze[c.row][c.col+1].visited == 0){ // Right
        count++;
    } 
     
    if(c.row+1 < M && maze[c.row+1][c.col].visited == 0){ // Down
        count++;
    } 
    
    if(c.row-1 >= 0 && maze[c.row-1][c.col].visited == 0){ // Up
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

        if(selected[random] == -1){
            // It selects sometimes too many times the same rundom number, fix it------------------------------------------------------------------------------------------------
            selected[random] = 1;
            
            switch (random){
                case 0:
                    // Up
                    // First check if the cell on the maze
                    if (c.row-1 >= 0 && maze[c.row-1][c.col].visited == 0){
                        if(DEBUG_CELL_WALL_SELECTION){
                            cout << "Index of Current Cell (c): " << c.row << " " << c.col << endl;
                            cout << "Current Cell Values .x and .y: " << c.x << " " << c.y << endl;
                        }
                        maze[c.row-1][c.col].visited =1;
                        maze[c.row-1][c.col].D = 0;
                        c.U = 0;
                        cout << "Selected Up TO: maze["<< c.row-1 << ", " << c.col <<  "]"<< endl<< endl;
                        return maze[c.row-1][c.col];
                    }
                    break;
                case 1:
                    // Down
                    // First check if the cell on the maze
                    if (c.row+1 < M && maze[c.row+1][c.col].visited == 0){
                        if(DEBUG_CELL_WALL_SELECTION){
                            cout << "Index of Current Cell (c): " << c.row << " " << c.col << endl;
                            cout << "Current Cell Values .x and .y: " << c.x << " " << c.y << endl;
                        }
                        maze[c.row+1][c.col].visited =1;
                        maze[c.row+1][c.col].U = 0;
                        c.D = 0;
                        cout << "Selected Down TO: maze["<< c.row+1 << ", " << c.col <<  "]"<< endl<< endl;
                        return maze[c.row+1][c.col];
                    }
                    break;
                case 2:
                    // Right
                    // First check if the cell on the maze
                    if (c.col+1 < N && maze[c.row][c.col+1].visited == 0){
                        if(DEBUG_CELL_WALL_SELECTION){
                            cout << "Index of Current Cell (c): " << c.row << " " << c.col << endl;
                            cout << "Current Cell Values .x and .y: " << c.x << " " << c.y << endl;
                        }
                        maze[c.row][c.col+1].visited =1;
                        maze[c.row][c.col+1].L = 0;
                        c.R = 0;
                        cout << "Selected Right TO: maze["<< c.row << ", " << c.col+1 <<  "]"<< endl << endl;
                        return maze[c.row][c.col+1];
                    }
                    break;
                case 3:
                    // Left
                    // First check if the cell on the maze
                    if (c.col-1 >= 0 && maze[c.row][c.col-1].visited == 0){
                        if(DEBUG_CELL_WALL_SELECTION){
                            cout << "Index of Current Cell (c): " << c.row << " " << c.col << endl;
                            cout << "Current Cell Values .x and .y: " << c.x << " " << c.y << endl;
                        }
                        maze[c.row][c.col-1].visited =1;
                        maze[c.row][c.col-1].R = 0;
                        c.L = 0;
                        cout << "Selected Left TO: maze[" << c.row << ", " << c.col-1 << "]"<< endl<< endl;
                        return maze[c.row][c.col-1];
                    }
                    break;
            }

        }

    }

    return c;
}

// Lets create a function to create maze
void CreateMaze(ListOfStacks<Cell<int>>& stacks_all, Cell<int>***& maze, int K, int M, int N){
    // I will use 3D arrays for this
    // K number of mazes and M       rows and N columns
    // So that I will have access to all mazes with one array
    
    // Fill the maze with all walls according to the x-y rules
    // I want bottom left corner to be x=0, y=0 and top right to be x=N-1, y=M-1
    
    cout << endl;

    /*
        Lets create the maze with all walls and row and col values
    */
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
                maze[k][i][j].row = i;
                maze[k][i][j].col = j;
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
                    cout << "(" << maze[k][i][j].row << "," << maze[k][i][j].col << ") ";
                }
                cout << endl;
            }
            cout << endl;
        }

        
    }


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
            int visit_count = M*N -1 ;// First cell is already visited
            while(CheckUVneighbor(maze[k], M, N, askedStack->top())){
                Cell<int> temp_rest_next;
                Cell<int> temp_rest_base = askedStack->top();
                // temp_rest_base = [k][m][n]
                askedStack->pop();

                // Returned updated next cell
                temp_rest_next = SelectNeighbor(maze[k], M, N, temp_rest_base);
                // cout << "Selected Neighbor Rest: " << temp_rest.x << " " << temp_rest.y << endl;
                
                // Temp_rest_base passed by reference su update their values on our maze
                maze[k][temp_rest_base.row][temp_rest_base.col].visited = temp_rest_base.visited;
                maze[k][temp_rest_base.row][temp_rest_base.col].L = temp_rest_base.L;
                maze[k][temp_rest_base.row][temp_rest_base.col].R = temp_rest_base.R;
                maze[k][temp_rest_base.row][temp_rest_base.col].U = temp_rest_base.U;
                maze[k][temp_rest_base.row][temp_rest_base.col].D = temp_rest_base.D;

                // Temp_rest_next returned directly update as well
                maze[k][temp_rest_next.row][temp_rest_next.col].visited = temp_rest_next.visited;
                maze[k][temp_rest_next.row][temp_rest_next.col].L = temp_rest_next.L;
                maze[k][temp_rest_next.row][temp_rest_next.col].R = temp_rest_next.R;
                maze[k][temp_rest_next.row][temp_rest_next.col].U = temp_rest_next.U;
                maze[k][temp_rest_next.row][temp_rest_next.col].D = temp_rest_next.D;
                
                visit_count--;

                // Push maze, push source row, col, push destination row, col
                // Or do it on SelectNeighbor function
                askedStack->push(temp_rest_base);
                askedStack->push(temp_rest_next);

            }

            while(!askedStack->isEmpty() && visit_count > 0){
                Cell<int> temp_rest_next;
                Cell<int> temp_rest_base = askedStack->top();
                askedStack->pop();

                if(CheckUVneighbor(maze[k], M, N, temp_rest_base) != false){
                    // If there is no unvisited neighbors, pop the last element
                    // and continue to search for unvisited neighbors
                                    // Returned updated next cell
                    temp_rest_next = SelectNeighbor(maze[k], M, N, temp_rest_base);
                    // cout << "Selected Neighbor Rest: " << temp_rest.x << " " << temp_rest.y << endl;
                    
                    // Temp_rest_base passed by reference su update their values on our maze
                    maze[k][temp_rest_base.row][temp_rest_base.col].visited = temp_rest_base.visited;
                    maze[k][temp_rest_base.row][temp_rest_base.col].L = temp_rest_base.L;
                    maze[k][temp_rest_base.row][temp_rest_base.col].R = temp_rest_base.R;
                    maze[k][temp_rest_base.row][temp_rest_base.col].U = temp_rest_base.U;
                    maze[k][temp_rest_base.row][temp_rest_base.col].D = temp_rest_base.D;

                    // Temp_rest_next returned directly update as well
                    maze[k][temp_rest_next.row][temp_rest_next.col].visited = temp_rest_next.visited;
                    maze[k][temp_rest_next.row][temp_rest_next.col].L = temp_rest_next.L;
                    maze[k][temp_rest_next.row][temp_rest_next.col].R = temp_rest_next.R;
                    maze[k][temp_rest_next.row][temp_rest_next.col].U = temp_rest_next.U;
                    maze[k][temp_rest_next.row][temp_rest_next.col].D = temp_rest_next.D;
                    
                    visit_count--;
                    askedStack->push(temp_rest_next);
                    
                } 
            }
            cout << "Maze " << k+1 << " is completed." << endl;

            saveMaze(maze[k], M, N, k);

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


void CreatePath(ListOfStacks<Cell<int>>& stacks_all, Cell<int>***& maze, int K, int M, int N, int entry_X, int entry_Y, int exit_X, int exit_Y){
    // Lets create a path for the given maze
    // We will use the stack to store the path

    Stack<Cell<int>>* askedStack = stacks_all.getStackAtIndex(K-1);
    askedStack->makeEmpty();

    // Lets find the entry and exit points
    Cell<int> entry = maze[K-1][M-entry_Y-1][entry_X];
    Cell<int> exit = maze[K-1][M-exit_Y-1][exit_X];

    // Check if we have the right entry and exit points
    if(entry.x == entry_X && entry.y == entry_Y && exit.x == exit_X && exit.y == exit_Y){
        cout << "Entry and Exit points are correct." << endl;

        // Lets start from the entry point
        askedStack->push(entry);
        // Lets create the path
        while(askedStack->top() != exit){
            // Create the algorithm here

        }


    } else {
        cout << "Entry and Exit points are not correct." << endl;
        return;
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

    // Lets create our stack list
    ListOfStacks<Cell<int>> stacks_all = ListOfStacks<Cell<int>>(K);

    // Create the maze
    Cell<int>*** maze = new Cell<int>**[K];

    // Create the maze
    CreateMaze(stacks_all, maze, K, M, N);
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
    CreatePath(stacks_all, maze, maze_id, M, N, entry_X, entry_Y, exit_X, exit_Y);

    // Deallocate maze and stacks_all
    // Also, check for temp ones.

}    