// Mustafa Batin EFE - 29272
// CS300 - Data Structures - Homework 1

# define DEBUG_3DARRAY true // Debugging - Creating Maze Members
# define DEBUG_STACK true // Debugging - Stack Members

#include <iostream>
#include <string>

#include "stack.h"

using namespace std;

void CreateMaze(int K, int M, int N){
    // Lets create the maze from stack.h
    // We will use 3D arrays for this
    // K number of mazes and M rows and N columns
    // So that we will have access to all mazes with one array
    
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
            cout << "Maze " << k+1 << endl;
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    cout << "(" << maze[k][i][j].x << "," << maze[k][i][j].y << ") ";
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
            askedStack->push(maze[k][M-1][0]);

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