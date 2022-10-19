//
// Created by yaidf on 18.10.2022.
//

#ifndef HEXAGON_GAME_H
#define HEXAGON_GAME_H


#include "Board.h"
#include "Surface.h"

class Game {
private:
    Board board;
    Surface surface;
    int turn;
    int ruby;
    int perl;
    int x1, x2;
    int inGame;
public:
    void startGame();
    void newTurn();
    Game();
    void endGame();
    void start();
};


#endif //HEXAGON_GAME_H
