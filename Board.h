//
// Created by yaidf on 18.10.2022.
//

#ifndef HEXAGON_BOARD_H
#define HEXAGON_BOARD_H
#include "vector"

using namespace std;
class Board {
private:
    vector<int> board;
public:
    Board();
    void refreshBoard();
    void print();
    void print2();
    vector<int> get();
    int canMove(int, int, int);
    void move(int, int);
    void jump(int, int, int);
    int getPerl();
    int getRuby();

    Board copy();

    int canMove(int x2, int turn);
};


#endif //HEXAGON_BOARD_H
