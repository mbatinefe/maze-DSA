// Mustafa Batin EFE - 29272
// CS300 - Data Structures - Homework 1

#include <iostream>
#include <string>
#include <random>
#include <fstream>

#include "stack.h"

using namespace std;

// Lets save the maze
void SaveMaze(Cell<int>*** maze, int M, int N, int K){
    for (int k = 0; k < K; k++){

        // Create the file
        string filename = "maze_" + to_string(k+1) + ".txt";
        ofstream file(filename);

        // Write maze to file
        file << M <<  " " << N << endl;
        for(int i = 0; i < M; i++){
            for(int j = 0; j < N; j++){
                file << "x=" <<maze[k][M-i-1][j].x << " y=" << maze[k][M-i-1][j].y << " l=" << maze[k][M-i-1][j].L << " r=" 
                << maze[k][M-i-1][j].R << " u=" << maze[k][M-i-1][j].U << " d=" << maze[k][M-i-1][j].D << endl;
            }
        }
        file.close();
    }
}

void SaveRoad(ListOfStacks<Cell<int>>& stacks_all, int M, int N, int K, int entry_X, int entry_Y, int exit_X, int exit_Y){
    // We need to reverse the stack and write into file
   
    Stack<Cell<int>>* askedStack = stacks_all.getStackAtIndex(K);
    // Create the file
    string filename = "maze_" + to_string(K+1) + "_path_" + to_string(entry_X) + "_" + to_string(entry_Y) + "_" + to_string(exit_X) + "_" + to_string(exit_Y) + ".txt";
    ofstream file(filename);

    // Reverse the stack
    Stack<Cell<int>>* reversedStack = new Stack<Cell<int>>();
    while(!askedStack->isEmpty()){
        reversedStack->push(askedStack->topAndPop());
    }

    // Write stacks x and y values to a file
    while(!reversedStack->isEmpty()){
        Cell<int> current = reversedStack->topAndPop();
        file << current.x << " " << current.y << endl;
    }
    
    file.close();
    reversedStack->makeEmpty();
    delete reversedStack;

}


// Check if the current cell has unvisited neighbors
bool CheckUVneighbor(Cell<int>*** maze, int K, int M, int N, Cell<int> c){

    cout << "Searching for unvisited neighbors of maze[" << c.row << ", " << c.col << "]";
    int count = 0;

    if(c.col-1 >= 0 && maze[K][c.row][c.col-1].visited == 0){ // Left
        count++;
    }  
    
    if(c.col+1 < N && maze[K][c.row][c.col+1].visited == 0){ // Right
        count++;
    } 
     
    if(c.row+1 < M && maze[K][c.row+1][c.col].visited == 0){ // Down
        count++;
    } 
    
    if(c.row-1 >= 0 && maze[K][c.row-1][c.col].visited == 0){ // Up
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

Cell<int> SelectNeighbor(Cell<int>***& maze, int K, int M, int N, Cell<int>& current){
    Cell<int> candidate;
    mt19937 engine(random_device{}());
    uniform_int_distribution<int> dist(0, 3);
    int selected[4] = {0, 0, 0, 0};

    while(true){
        if(selected[0] == 1 && selected[1] == 1 && selected[2] == 1 && selected[3] == 1){
            // All numbers are selected
            return current;
        }

        int random = dist(engine);
        if(selected[random] == 0){
            selected[random] = 1;

            switch (random){
                case 0:
                    // Up
                    // First check if the cell on the maze
                    if (current.row-1 >= 0 && maze[K][current.row-1][current.col].visited == 0){

                        cout << "[" << current.row << "]["<< current.col <<"] = {" << current.x <<"," << current.y << "} "
                        << "-->" <<  "[" << current.row-1 << "]["<< current.col <<"] = {" 
                        << maze[K][current.row-1][current.col].row <<"," << maze[K][current.row-1][current.col].col << "} " << endl;

                        maze[K][current.row-1][current.col].visited =1;
                        maze[K][current.row-1][current.col].D = 0;
                        current.U = 0;
                        return maze[K][current.row-1][current.col];
                    }
                    break;
                case 1:
                    // Down
                    // First check if the cell on the maze
                    if (current.row+1 < M && maze[K][current.row+1][current.col].visited == 0){
                        cout << "[" << current.row << "]["<< current.col <<"] = {" << current.x <<"," << current.y << "} "
                        << "-->" <<  "[" << current.row+1 << "]["<< current.col <<"] = {" 
                        << maze[K][current.row+1][current.col].row <<"," << maze[K][current.row+1][current.col].col << "} " << endl;

                        maze[K][current.row+1][current.col].visited =1;
                        maze[K][current.row+1][current.col].U = 0;
                        current.D = 0;
                        return maze[K][current.row+1][current.col];
                    }
                    break;
                case 2:
                    // Right
                    // First check if the cell on the maze
                    if (current.col+1 < N && maze[K][current.row][current.col+1].visited == 0){

                        cout << "[" << current.row << "]["<< current.col <<"] = {" << current.x <<"," << current.y << "} "
                        << "-->" <<  "[" << current.row << "]["<< current.col+1 <<"] = {" 
                        << maze[K][current.row][current.col+1].row <<"," << maze[K][current.row][current.col+1].col << "} " << endl;

                        maze[K][current.row][current.col+1].visited =1;
                        maze[K][current.row][current.col+1].L = 0;
                        current.R = 0;
                        
                        return maze[K][current.row][current.col+1];
                    }
                    break;
                case 3:
                    // Left
                    // First check if the cell on the maze
                    if (current.col-1 >= 0 && maze[K][current.row][current.col-1].visited == 0){
                        cout << "[" << current.row << "]["<< current.col <<"] = {" << current.x <<"," << current.y << "} "
                        << "-->" <<  "[" << current.row << "]["<< current.col-1 <<"] = {" 
                        << maze[K][current.row][current.col-1].row <<"," << maze[K][current.row][current.col-1].col << "} " << endl;

                        maze[K][current.row][current.col-1].visited =1;
                        maze[K][current.row][current.col-1].R = 0;
                        current.L = 0;
                        return maze[K][current.row][current.col-1];
                    }
                    break;
            }

        } else{
            continue;
        }
    }

}

void CreateMaze(ListOfStacks<Cell<int>>& stacks_all, Cell<int>***& maze, int K, int M, int N){
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
            }
        }
    }

    for(int k=0; k <K; k++){

        Stack<Cell<int>>* askedStack = stacks_all.getStackAtIndex(k);

        maze[k][M-1][0].visited = 1;
        askedStack->push(maze[k][M-1][0]);
        int visit_count = M * N - 1; // -1: Since first cell is visited
        while(CheckUVneighbor(maze, k, M, N, askedStack->top())){
            Cell<int> current = askedStack->topAndPop();
            Cell<int> candidate;

            candidate = SelectNeighbor(maze, k, M, N, current);
            if(candidate == current){
                continue;
            }
            // Lets update current without passing around
            maze[k][current.row][current.col].visited = current.visited;
            maze[k][current.row][current.col].L = current.L;
            maze[k][current.row][current.col].R = current.R;
            maze[k][current.row][current.col].U = current.U;
            maze[k][current.row][current.col].D = current.D;

            visit_count--;
            askedStack->push(current);
            askedStack->push(candidate);
        }

        while(!askedStack->isEmpty() && visit_count > 0){
            Cell<int> current = askedStack->topAndPop();
            Cell<int> candidate;

            bool isDead = CheckUVneighbor(maze, k, M, N, current);
            if(!isDead){
                continue;
            } else{
                candidate = SelectNeighbor(maze, k, M, N, current);
                if(candidate == current){
                    continue;
                }

                // Lets update current without passing around
                maze[k][current.row][current.col].visited = current.visited;
                maze[k][current.row][current.col].L = current.L;
                maze[k][current.row][current.col].R = current.R;
                maze[k][current.row][current.col].U = current.U;
                maze[k][current.row][current.col].D = current.D;
                
                visit_count--;
                askedStack->push(current);
                askedStack->push(candidate);
            }

        }

    }
}


Cell<int> ChooseWall(Cell<int>***& maze, int K, int M, int N, Cell<int>& current){
    Cell<int> candidate;
    mt19937 engine(random_device{}());
    uniform_int_distribution<int> dist(0, 3);
    int selected[4] = {0, 0, 0, 0};

    while(true){
        if(selected[0] == 1 && selected[1] == 1 && selected[2] == 1 && selected[3] == 1){
            // All numbers are selected
            return current;
        }

        int random = dist(engine);
        if(selected[random] == 0){
            selected[random] = 1;

            switch (random){
                case 0:
                    // Up
                    // First check if the cell on the maze
                    if (current.U == 0 && maze[K][current.row-1][current.col].visited == 0){

                        cout << "[" << current.row << "]["<< current.col <<"] = {" << current.x <<"," << current.y << "} "
                        << "-->" <<  "[" << current.row-1 << "]["<< current.col <<"] = {" 
                        << maze[K][current.row-1][current.col].row <<"," << maze[K][current.row-1][current.col].col << "} " << endl;

                        maze[K][current.row-1][current.col].visited =1;
                        return maze[K][current.row-1][current.col];
                    }
                    break;
                case 1:
                    // Down
                    // First check if the cell on the maze
                    if (current.D == 0 && maze[K][current.row+1][current.col].visited == 0){
                        cout << "[" << current.row << "]["<< current.col <<"] = {" << current.x <<"," << current.y << "} "
                        << "-->" <<  "[" << current.row+1 << "]["<< current.col <<"] = {" 
                        << maze[K][current.row+1][current.col].row <<"," << maze[K][current.row+1][current.col].col << "} " << endl;

                        maze[K][current.row+1][current.col].visited =1;
                        return maze[K][current.row+1][current.col];
                    }
                    break;
                case 2:
                    // Right
                    // First check if the cell on the maze
                    if (current.R == 0 && maze[K][current.row][current.col+1].visited == 0){

                        cout << "[" << current.row << "]["<< current.col <<"] = {" << current.x <<"," << current.y << "} "
                        << "-->" <<  "[" << current.row << "]["<< current.col+1 <<"] = {" 
                        << maze[K][current.row][current.col+1].row <<"," << maze[K][current.row][current.col+1].col << "} " << endl;

                        maze[K][current.row][current.col+1].visited =1;
                        
                        return maze[K][current.row][current.col+1];
                    }
                    break;
                case 3:
                    // Left
                    // First check if the cell on the maze
                    if (current.L == 0 && maze[K][current.row][current.col-1].visited == 0){
                        cout << "[" << current.row << "]["<< current.col <<"] = {" << current.x <<"," << current.y << "} "
                        << "-->" <<  "[" << current.row << "]["<< current.col-1 <<"] = {" 
                        << maze[K][current.row][current.col-1].row <<"," << maze[K][current.row][current.col-1].col << "} " << endl;

                        maze[K][current.row][current.col-1].visited =1;
                        return maze[K][current.row][current.col-1];
                    }
                    break;
            
            }
        } else {
            continue;
        }
    
    }

}

void CreatePath(ListOfStacks<Cell<int>>& stacks_all, Cell<int>***& maze, int maze_id, 
            int M, int N, int entry_X, int entry_Y, int exit_X, int exit_Y){

    Stack<Cell<int>>* askedStack = stacks_all.getStackAtIndex(maze_id-1);
    askedStack->makeEmpty();

    Cell<int> entry = maze[maze_id-1][M-entry_Y-1][entry_X];
    Cell<int> exit = maze[maze_id-1][M-exit_Y-1][exit_X];

    /*
    cout << "Entry:" << entry.x << " " << entry.y << endl;
    cout << "Entry:" <<entry_X  << " " <<   entry_Y<< endl;
    cout << "Exit:" << exit.x << " " << exit.y << endl;
    cout << "Exit:" <<exit_X  << " " <<   exit_Y<< endl;
    */
    
    // First lets empty all the visited cells
    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){
            maze[maze_id-1][i][j].visited = 0;
        }
    }

    maze[maze_id-1][M-entry_Y-1][entry_X].visited = 1;
    entry.visited = 1; // Same as above -- better view

    askedStack->push(entry);
    while(!askedStack->isEmpty()){
        if(exit == askedStack->top()){
            cout << "Exit is found" << endl;
            break;
        }
        
        Cell<int> current = askedStack->topAndPop();
        Cell<int> candidate;
        // Idx;      0: Up, 1: Down, 2: Right, 3: Left
        candidate = ChooseWall(maze, maze_id-1, M, N, current);

        cout << "Current (" <<current.x <<"," << current.y << ")" <<"=" <<"[" << current.row << "]["<< current.col << "]"<< endl;
        cout << "Candidate (" <<candidate.x <<"," << candidate.y << ")" <<"=" <<"[" << candidate.row << "]["<< candidate.col << "]"<< endl;

        if(candidate == current){
            cout << "Going Back in Time" << endl;
            continue;
        } else{
            maze[maze_id-1][current.row][current.col].visited = current.visited;
            maze[maze_id-1][current.row][current.col].L = current.L;
            maze[maze_id-1][current.row][current.col].R = current.R;
            maze[maze_id-1][current.row][current.col].U = current.U;
            maze[maze_id-1][current.row][current.col].D = current.D;
            askedStack->push(current);
            askedStack->push(candidate);
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

    // Lets create our stack list
    ListOfStacks<Cell<int>> stacks_all = ListOfStacks<Cell<int>>(K);

    // Create the maze
    Cell<int>*** maze = new Cell<int>**[K];
    // Create the maze
    CreateMaze(stacks_all, maze, K, M, N);

    // Save the maze
    SaveMaze(maze, M, N, K);
    
    // Print the maze
    for (int k = 0; k < K; k++) {
        cout << "Maze " << k+1 << endl;
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                cout << "x=" << maze[k][i][j].x << " y=" << maze[k][i][j].y << " l=" << maze[k][i][j].L << " r=" << maze[k][i][j].R << " u=" << maze[k][i][j].U << " d=" << maze[k][i][j].D << endl;
            }
        }
    }
    for (int k = 0; k < K; k++) {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                cout << "(" << maze[k][i][j].x << "," << maze[k][i][j].y << ")" << "&[" << maze[k][i][j].row << "," << maze[k][i][j].col << "] "

                << maze[k][i][j].U << maze[k][i][j].D << maze[k][i][j].R << maze[k][i][j].L << " " << maze[k][i][j].visited << " | ";
            }
            cout << endl;
        }
        cout << endl;

    }
    

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

    // Save the road
    SaveRoad(stacks_all, M, N, maze_id-1, entry_X, entry_Y, exit_X, exit_Y);

    /// DELETE MAZES AND STACKS

}    