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
    inGame = 1;
}
void Game::startGame() {
    board.refreshBoard();
    while (inGame){
        newTurn();
    }

}
void Game::whereTest(){
    board.refreshBoard();
    while (true);
}
void  Game::start(){
    int ans = 5;
    while (ans != 1 && ans != 2 && ans != 4 && ans != 3){
        surface.addLongText("Hiii! It's HEXAGON game");
        surface.addLongText("select to continue");
        surface.addLongText("");
        surface.addLongText("1) play 1 player");
        surface.addLongText("2) play 2 player");
        surface.addLongText("3) about game");
        surface.addLongText("4) exit");
        surface.print();
        surface.clr();
        mode = 1;
        startGame();
        return;
        cin >> ans;
        switch (ans) {
            case 1:
                mode = 1;
                startGame();
                break;
            case 2:
                mode = 2;
                startGame();
                break;
            case 3:
                surface.addLongText("HEXAGON game v1.1");
                surface.addLongText("made by Andrey Trofimov");
                surface.addLongText("for SUAI 2022");
                surface.addLongText("");
                surface.addLongText("How to play: in surface you can see two figures");
                surface.addLongText("left - you playing field, 0 - it's hex is free, 1 - hex player's 1, 2 - fild player's 2");
                surface.addLongText("right - field map, in this field you can see the number of each hexagons");
                surface.addLongText("use coordinates from field map to chose a hexagon for you turn");
                surface.addLongText("enter to continue..");
                surface.print();
                surface.clr();
                break;
            case 4:
                surface.addLongText("good bye! hope to see you later");
                surface.print();
                surface.clr();
                break;
        }
    }
}
void Game::newTurn() {
    surface.loadBoard(board.get());
    surface.addText("p1 - rubies");
    surface.addText("p2 - perls");
    surface.addText("");
    surface.addText("");
    if (turn % 2){
        if (mode == 2) {
            surface.addText("Player's 2 turn");
        } else{
            surface.clr();
            turn ++;
            return;
            cout << "----" <<autoTurnFirst(1) << endl;
            if (ruby + perl >= 58) endGame();
            return;
        }
    } else{
        surface.addText("Player's 1 turn");
    }
    ruby = board.getRuby();
    perl = board.getPerl();
    surface.addText("rubies: " + to_string(ruby));
    surface.addText("perls: " + to_string(perl));
    for (int i = 0; i < board.get().size(); i++){
        if (board.canMove(60, i, 1)) surface.setCan(i);
    }
    surface.print();
    int can = 0;
    while (!can) {
        cout << "1) {where from} {where to} ex: 3 7 for make your turn" << endl;
        cout << "2) 0 0 for exit" << endl;
        cin >> x1 >> x2;
        if (x1 == 0){
            inGame = 0;
            break;
        }
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
    if (ruby + perl >= 58) endGame();
}

void Game::endGame() {
    surface.addText("game end " + to_string(perl > ruby ? perl:ruby));
    surface.addText("win " + to_string(perl > ruby ? perl:ruby));
    surface.print();
    inGame = 0;
}

int Game::autoTurn(int best, int deep, int turn, Board board1) {
    int b =best;
    Board tmpBoard;
    if (deep == 0) return best;
    vector<int> tmp = board1.get();
    for (int i = 0; i < tmp.size(); i++){
        if (tmp[i] == turn){
            if (board1.canMove(i, i + 10, turn) != 0){
                tmpBoard = board1.copy();
                if (turn == 2){
                    b = tmpBoard.getPerl();
                } else{
                    b = tmpBoard.getRuby();
                }
                tmpBoard.move(i + 10, (turn % 2) + 1);
                if (turn % 2){
                    b = tmpBoard.getPerl() - b;
                } else{
                    b = tmpBoard.getRuby() - b;
                }
                b -= autoTurn(b, 1, (turn + 1)% 2, tmpBoard);
                return autoTurn(b + best, deep - 1, turn, tmpBoard);
            }
        }
    }
    return best;
}
int Game::autoTurnFirst(int deep) {
    int best = -1;
    int pos = 0;
    int pos1 = 0;
    int b =0;
    Board tmpBoard;
    vector<int> tmp = board.get();
    for (int i = 0; i < tmp.size(); i++){
        if (tmp[i] == (turn % 2) + 1){
            if (board.canMove(i, i + 10, (turn % 2) + 1)  != 0){
                tmpBoard = board.copy();
                if (turn % 2){
                    b = tmpBoard.getPerl();
                } else{
                    b = tmpBoard.getRuby();
                }
                tmpBoard.move(i + 10, (turn % 2) + 1);
                if (turn % 2){
                    b = tmpBoard.getPerl() - b;
                } else{
                    b = tmpBoard.getRuby() - b;
                }
                b -= autoTurn(b, 1, ((turn + 1) % 2) + 1, tmpBoard);
                if (autoTurn(b, deep - 1, (turn % 2) + 1, tmpBoard) > best){
                    pos = i + 10;
                    pos1 = i;
                    best = b;
                }
            }
            if (board.canMove(i, i - 10, (turn % 2) + 1)  != 0){
                tmpBoard = board.copy();
                if (turn % 2){
                    b = tmpBoard.getPerl();
                } else{
                    b = tmpBoard.getRuby();
                }
                tmpBoard.move(i - 10, (turn % 2) + 1);
                if (turn % 2){
                    b = tmpBoard.getPerl() - b;
                } else{
                    b = tmpBoard.getRuby() - b;
                }
                b -= autoTurn(b, 1, ((turn + 1) % 2) + 1, tmpBoard);
                if (autoTurn(b, deep - 1, (turn % 2) + 1, tmpBoard) > best){
                    pos = i - 10;
                    pos1 = i;
                    best = b;
                }
            }
            if (board.canMove(i, i - 6, (turn % 2) + 1)  != 0){
                tmpBoard = board.copy();
                if (turn % 2){
                    b = tmpBoard.getPerl();
                } else{
                    b = tmpBoard.getRuby();
                }
                tmpBoard.move(i - 6, (turn % 2) + 1);
                if (turn % 2){
                    b = tmpBoard.getPerl() - b;
                } else{
                    b = tmpBoard.getRuby() - b;
                }
                b -= autoTurn(b, 1, ((turn + 1) % 2) + 1, tmpBoard);
                if (autoTurn(b, deep - 1, (turn % 2) + 1, tmpBoard) > best){
                    pos = i - 6;
                    pos1 = i;
                    best = b;
                }
            }
            if (board.canMove(i, i + 6, (turn % 2) + 1)  != 0){
                tmpBoard = board.copy();
                if (turn % 2){
                    b = tmpBoard.getPerl();
                } else{
                    b = tmpBoard.getRuby();
                }
                tmpBoard.move(i + 6, (turn % 2) + 1);
                if (turn % 2){
                    b = tmpBoard.getPerl() - b;
                } else{
                    b = tmpBoard.getRuby() - b;
                }
                b -= autoTurn(b, 1, ((turn + 1) % 2) + 1, tmpBoard);
                if (autoTurn(b, deep - 1, (turn % 2) + 1, tmpBoard) > best){
                    pos = i + 6;
                    pos1 = i;
                    best = b;
                }
            }
            if (board.canMove(i, i - 4, (turn % 2) + 1)  != 0){
                tmpBoard = board.copy();
                if (turn % 2){
                    b = tmpBoard.getPerl();
                } else{
                    b = tmpBoard.getRuby();
                }
                tmpBoard.move(i - 4, (turn % 2) + 1);
                if (turn % 2){
                    b = tmpBoard.getPerl() - b;
                } else{
                    b = tmpBoard.getRuby() - b;
                }
                b -= autoTurn(b, 1, ((turn + 1) % 2) + 1, tmpBoard);
                if (autoTurn(b, deep - 1, (turn % 2) + 1, tmpBoard) > best){
                    pos = i - 4;
                    pos1 = i;
                    best = b;
                }
            }
            if (board.canMove(i, i + 4, (turn % 2) + 1)  != 0){
                tmpBoard = board.copy();
                if (turn % 2){
                    b = tmpBoard.getPerl();
                } else{
                    b = tmpBoard.getRuby();
                }
                tmpBoard.move(i +4, (turn % 2) + 1);
                if (turn % 2){
                    b = tmpBoard.getPerl() - b;
                } else{
                    b = tmpBoard.getRuby() - b;
                }
                b -= autoTurn(b, 1, ((turn + 1) % 2) + 1, tmpBoard);
                if (autoTurn(b, deep - 1, (turn % 2) + 1, tmpBoard) > best){
                    pos = i +4;
                    pos1 = i;
                    best = b;
                }
            }
        }
    }
    cout << "++" << pos1 << "++" << pos << "++" << endl;
    board.move(pos, (turn % 2) + 1);
    return pos;
}
