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
    while (inGame) {
        newTurn();
    }

}

void Game::whereTest() {
    board.refreshBoard();
    while (true);
}

void Game::start() {
    int ans = 5;
    while (ans != 1 && ans != 2) {
        surface.addLongText("Hiii! It's HEXAGON game");
        surface.addLongText("select to continue");
        surface.addLongText("");
        surface.addLongText("1) play 1 player");
        surface.addLongText("2) play 2 player");
        surface.addLongText("3) about game");
        surface.addLongText("4) exit");
        surface.print();
        surface.clr();
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
                surface.addLongText(
                        "left-you playing field, 0-it's hex is free, 1-hex player's 1, 2-fild player's 2");
                surface.addLongText("right-field map, in this field you can see the number of each hexagons");
                surface.addLongText("use coordinates from field map to chose a hexagon for you turn");
                surface.addLongText("enter to continue..");
                surface.print();
                surface.clr();
                getchar();
                getchar();
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
    if (turn % 2) {
        if (mode == 2) {
            surface.addText("Player's 2 turn");
        } else {
            surface.clr();
            cout << "----" << autoTurnFirst(1) << endl;
            if (board.getRuby() + board.getPerl() >= 58 || board.getRuby() == 0 || board.getPerl() == 0) endGame();
            return;
        }
    } else {
        surface.addText("Player's 1 turn");
    }
    ruby = board.getRuby();
    perl = board.getPerl();
    surface.addText("rubies: " + to_string(ruby));
    surface.addText("perls: " + to_string(perl));
    for (int i = 0; i < board.get().size(); i++) {
        if (board.canMove(i, turn)) surface.setCan(i);
    }
    surface.print();
    int can = 0;
    while (!can) {
        cout << "1) {where from} {where to} ex: 3 7 for make your turn" << endl;
        cout << "2) 0 0 for exit" << endl;
        cin >> x1 >> x2;
        if (x1 == 0) {
            inGame = 0;
            break;
        }
        can = board.canMove(x1, x2, turn);
        if (can == 1) {
            board.move(x2, turn);
            break;
        }
        if (can == 2) {
            board.jump(x1, x2, turn);
            break;
        }
        cout << "incorrect move or format" << endl;
    }
    surface.clr();
    turn++;
    if (board.getRuby() + board.getPerl() >= 58 || board.getRuby() == 0 || board.getPerl() == 0) endGame();
}

void Game::endGame() {
    surface.addText("game end " + to_string(perl > ruby ? perl : ruby));
    surface.addText("win " + to_string(perl > ruby ? perl : ruby));
    surface.print();
    inGame = 0;
}

int Game::countWays(Board &tmpBoard, int i, int turn, int step) {
    int b = 0, r = 0;
    b = tmpBoard.getByTurn(turn);
    tmpBoard.jump(i + step, i, turn);
    b = tmpBoard.getByTurn(turn) - b;
    if ((turn % 2) + 1 != (this->turn % 2) + 1) b -= autoTurn(0, 1, turn + 1, tmpBoard);

    return b;
}

int Game::autoTurn(int best, int deep, int turn, Board &board1) {
//    surface.loadBoard(board1.get());
//    surface.print();
    int b = best;
    int b1 = -9;
    Board tmpBoard;
    if (deep <= 0) return best;
    vector<int> tmp = board1.get();
    for (int i = 0; i < tmp.size(); i++) {
        if (board1.canMove(i, turn) == 1) {
            tmpBoard = board1.copy();
            b = countWays(tmpBoard, i, turn, -i);
            b = autoTurn(b + best, deep - 1, turn, tmpBoard);
            if (b > b1) {
                b1 = b;
            }

        }
        if (board1.canMove(i, turn) == 2) {
            for (int j: jumps) {
                if (board1.canMove(i + j, i, turn)) {
                    tmpBoard = board.copy();
                    b = countWays(tmpBoard, i, turn, j);
                    b = autoTurn(b + best, deep - 1, turn, tmpBoard);
                    if (b > b1) {
                        b1 = b;
                    }
                }
            }
        }
    }
    return best + b1;
}
void Game::print() {
    surface.clr();
    surface.loadBoard(board.get());
    surface.print();
    surface.clr();
}
int Game::autoTurnFirst(int deep) {
    int best = -9;
    int pos = 0;
    int pos1 = 0;
    int b = 0;

    Board tmpBoard;
    vector<int> tmp = board.get();
    for (int i = 0; i < tmp.size(); i++) {
        if (board.canMove(i, turn) == 1) {
            tmpBoard = board.copy();
            b = countWays(tmpBoard, i, turn, -i);
            //cout << "move to " << i << " = " << b << endl ;
            b = autoTurn(b, deep - 1, turn, tmpBoard);
            //cout << "move to " << i << " = " << b << endl ;
            if (b > best) {
                pos = i;
                pos1 = 0;
                best = b;

            }
        }

        if (board.canMove(i, turn) == 2) {
            for (int j: jumps) {
                if (board.canMove(i + j, i, turn)) {
                    tmpBoard = board.copy();
                    b = countWays(tmpBoard, i, turn, j);
                    //cout << "jump from " << i + j << " to " << i << " = " << b << endl;
                    b = autoTurn(b, deep - 1, turn, tmpBoard);
                    //cout << "jump from " << i + j << " to " << i << " = " << b << endl;
                    if (b > best) {
                        pos = i;
                        pos1 = i + j;
                        best = b;
                    }
                }
            }
        }
    }
    board.jump(pos1, pos, turn);
    turn++;
    return pos;
}
