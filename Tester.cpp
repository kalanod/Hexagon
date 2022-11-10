//
// Created by yaidf on 21.10.2022.
//

#include "Tester.h"
#include "Game.cpp"

void Tester::makeTest(){
    game.board.jump(82, 71, 1);
    game.print();
    game.autoTurnFirst(1);
    game.print();
}
void Tester::test2(){
    game.board.jump(82, 71, 1);
    Board tmpBoard = game.board.copy();
    game.print();
    int b = game.countWays(tmpBoard, 61, 0, -1);
    cout << b << endl;

}