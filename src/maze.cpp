#include "../include/maze.h"

Maze::Maze(int size = 10){
    srand(time(NULL));

    _size = size;
    _board.resize(_size, vector<char>(_size, _chSpace));
    
    _start.x  = _size-2;
    _start.y  = 1;
    _finish.x = 1;
    _finish.y = size-2;
    _cur.x = _start.x;
    _cur.y = _start.y;
}

void Maze::initMaze(){
    initWall();
    generateMaze();
    initPoints();
}


void Maze::initWall(){
    for(int i=0; i<_size; i++){
        _board[0][i]        = _chWall;
        _board[_size-1][i]  = _chWall;
        _board[i][0]        = _chWall;
        _board[i][_size-1]  = _chWall;
    }
}

void Maze::generateMaze(){
    int x, y;
    for(int i=0; i<(_size*_size)/4; i++){
        x = rand()%(_size-1)+1;
        y = rand()%(_size-1)+1;
        _board[x][y] = _chWall;
    }
}

void Maze::initPoints(){
    _board[_start.x][_start.y] = _chStart;
    _board[_finish.x][_finish.y] = _chFinish;
    _board[_cur.x][_cur.y] = _chCur;
}

void Maze::printMaze(){
    initPoints();
    for(int i=0; i<_size; i++){
        for(int j=0; j<_size; j++){
            cout << _board[j][i] << " ";
        }
        cout << endl;
    }
} 

void Maze::printLastState(){
    // clear board which is not wall_chWall
    for(int i=1; i<_size-1; i++){ 
        for(int j=1; j<_size-1; j++){
         //   if(_board[i][j] != _chWall)
                _board[i][j] = _chSpace;
        }
    }

    // filling the board with point which will reach the finis point
    while( !_way.empty() ){
        _board[_way.back().x][_way.back().y] = _chPassed;
        _way.pop_back();
    }
    printMaze();
}

void Maze::findTheFuckinWay(){
    initMaze();
    int i=0;
    while( !isDone() ){
       // cout << ++i << " " << checkDirections() << " " << findDirection() << endl; // for debug 
        if( checkDirections() == 1 ){
            move( findDirection() );
        }else if( checkDirections() > 1){
            _sepPoints.push_back(_cur);
            move( findDirection() );
        } else{
            if( !_sepPoints.empty() ){ 
                while( (_way.back().x != _sepPoints.back().x) || (_way.back().y != _sepPoints.back().y)){
                    _way.pop_back();
                }
                _board[_cur.x][_cur.y] = _chStackPoint;
                _cur.x = _sepPoints.back().x;
                _cur.y = _sepPoints.back().y;
                _sepPoints.pop_back();
                
            } else{ // stack is empty and there is no directions
                cout << "There is no way to reach finish point!" << endl;
                return;
            }
        }
        cout << string(100,'\n'); // Clear screen
        printMaze();
        delay();
    }
    printLastState();
}

int Maze::checkDirections(){    // it returns number of possible moves
    int count=0;
    if(_board[_cur.x+1][_cur.y] == _chSpace) count++; // R
    if(_board[_cur.x-1][_cur.y] == _chSpace) count++; // L
    if(_board[_cur.x][_cur.y-1] == _chSpace) count++; // U
    if(_board[_cur.x][_cur.y+1] == _chSpace) count++; // D

    return count;
}

int Maze::findDirection(){      // it returns first direction
    // priority
    // if finish point right side of the start point, 
    // we can increase the priority of which direction 
    // is more important for reach the finish point
    if(_start.x < _finish.x){
        if(_board[_cur.x+1][_cur.y] == _chSpace) return 0; // R
    }        
    if(_start.y < _finish.y){
        if(_board[_cur.x][_cur.y+1] == _chSpace) return 3; // D
    }

    if(_board[_cur.x-1][_cur.y] == _chSpace) return 1; // L
    if(_board[_cur.x][_cur.y-1] == _chSpace) return 2; // U
    if(_board[_cur.x][_cur.y+1] == _chSpace) return 3; // D
    if(_board[_cur.x+1][_cur.y] == _chSpace) return 0; // R

    return 4;
}

void Maze::move(int moveDir ){
    _way.push_back(_cur);   // every time when cursor moving, it save the position 
    _board[_cur.x][_cur.y] = _chPassed; // old position is 'o'
    switch (moveDir){
        case 0: 
            _cur.x = _cur.x+1;
            break;
        case 1: 
            _cur.x = _cur.x-1;
            break;
        case 2: 
            _cur.y = _cur.y-1;
            break;
        case 3: 
            _cur.y = _cur.y+1;
            break;
        default: 
            break;
    }
}

bool Maze::isDone(){
    // if cursor near one block of finish point, it returns true. 
    // true means that I found the finish point. YAY!
    if( (_cur.x-1 == _finish.x) && (_cur.y == _finish.y) ) return 1;
    if( (_cur.x+1 == _finish.x) && (_cur.y == _finish.y) ) return 1;
    if( (_cur.x == _finish.x) && (_cur.y-1 == _finish.y) ) return 1;
    if( (_cur.x == _finish.x) && (_cur.y+1 == _finish.y) ) return 1;

    return 0;

}

void Maze::delay(){
    // its just a delay function
    for(int i=0; i<1000000; i++){
        for(int j=0; j<50; j++);
    }
}