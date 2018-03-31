#include <iostream> 
#include <vector>   // for maze
#include <list>     // for stack
#include <cstdlib>  // for atoi function and ...
#include <ctime>    // for random function
using namespace std;

struct Point{
    int x, y;
};

class Maze{
public:
    Maze(int size);
    void initMaze();    // initialising wall, maze, points
    void initWall();    // the maze surrounds the walls
    void generateMaze(); // it create random wall into maze
    void initPoints();  // start, finish and current point

    void printMaze();   
    void printLastState();

    void findTheFuckinWay();    // tries brute force to reach finish point

    int checkDirections();  // returns number of directions + Left Right Up Down
    int findDirection();    // returns a direction for move function
    void move(int direction);   // moves the cursor with given parameter
    bool isDone();  // when cursor reach the finish point it returns true

    void delay();  //standart delay function with for loops

private:
    int _size;
    vector< vector<char> > _board;  // maze
    Point _start, _finish, _cur;    // points
    list<Point> _sepPoints; // road seperations points
    list<Point> _way;       // last station

    char _chWall = '.';
    char _chSpace = ' ';
    char _chStart = 'S';
    char _chFinish = 'F';
    char _chCur = '@';
    char _chPassed = '#'; // 
    char _chStackPoint = '+';
};