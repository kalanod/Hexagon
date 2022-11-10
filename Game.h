//
// Created by yaidf on 18.10.2022.
//

#ifndef HEXAGON_GAME_H
#define HEXAGON_GAME_H


#include "Board.h"
#include "Surface.h"

class Game {
private:
    Board board2;
    Surface surface;
    int turn;
    int ruby;
    int perl;
    int x1, x2;
    int inGame;
    int mode;
    int jumps[14] = {1, -1, 10, -10, 15, -15, 9, -9, 14, -14, 16, -16, 20, -20};
public:
    void startGame();
    void newTurn();
    Game();
    void endGame();
    void start();

    int autoTurn(int, int, int, Board&);

    int autoTurnFirst(int deep);

    void whereTest();
    void print();
    int countWays(Board&, int i, int turn, int delta);

    Board board;

    void newAutoTurn();
};


#endif //HEXAGON_GAME_H
