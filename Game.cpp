//
// Created by yaidf on 18.10.2022.
//

#include "Game.h"
#include "Board.cpp"
#include "Surface.cpp"


Game::Game() {
    turn = 0;
    ruby = 3;
    perl = 3;
    x1 = 0;
    x2 = 0;
}
void Game::startGame() {
    board.refreshBoard();
    board.print();
    while (true){
        newTurn();
    }

}

void Game::newTurn() {

    surface.loadBoard(board.get());
    surface.addText("p1 - rubies");
    surface.addText("p2 - perls");
    surface.addText("");
    surface.addText("");
    if (turn % 2){
        surface.addText("Player's 2 turn");
    } else{
        surface.addText("Player's 1 turn");
    }
    ruby = board.getRuby();
    perl = board.getPerl();





    surface.addText("rubies: " + to_string(ruby));
    surface.addText("perls: " + to_string(perl));
    surface.print();
    int can = 0;
    while (!can) {
        cout << "{where from} {where to} ex: 3 7" << endl;
        cin >> x1 >> x2;
        can = board.canMove(x1, x2, (turn % 2) + 1);
        if (can == 1){
            board.move(x2, (turn % 2) + 1);
            break;
        }
        if (can == 2) {
            board.jump(x1, x2, (turn % 2) + 1);
            break;
        }
        cout << "incorrect move or format" << endl;
    }
    surface.clr();
    turn ++;
}