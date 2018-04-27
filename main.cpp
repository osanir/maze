#include <iostream>
#include "include/maze.h"
using namespace std;

int main(int argc, char** argv){
    int size=50;
    
    if(argc > 1){
        size = atoi(argv[1]);
        if(size <= 3){
            cout << "Size must be more than 3!" << endl;
            return 0;   
        }
    }

    Maze maze(size);
    maze.findTheFWay();
    
    return 0;
}
