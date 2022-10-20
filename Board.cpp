#include "Board.h"

Board::Board() {
    refreshBoard();
}

void Board::refreshBoard() {
    ifstream in("C:\\Users\\yaidf\\CLionProjects\\HEXAGON\\map.txt"); // окрываем файл для чтения
    if (in.is_open()) {
        string line;
        getline(in, line);
        for (char a: line) {
            board.push_back(a - 48);
        }
        board.resize(85);
    }
    in.close();

}

void Board::print() {
    for (int i = 0; i < 17; i++) {
        if (i % 2) cout << " ";
        for (int j = 0; j < 5; j++) {
            if (board[i * 5 + j] != 1) {
                cout << board[i * 5 + j] << " ";
            } else {
                cout << "  ";
            }
        }
        cout << endl;
    }
}

void Board::print2() {
    for (int i = 0; i < 17; i++) {
        if (i % 2) cout << "    ";
        for (int j = 0; j < 5; j++) {
            if (board[i * 5 + j] == 0) {
                cout << "/   \\___";
            } else {
                cout << "        ";
            }
        }
        cout << endl;
    }
}

vector<int> Board::get() {
    return board;
}

int Board::canMove(int x1, int x2, int turn) {
    int dif = abs(x2 - x1);
    if (board[x1] != turn || board[x2] != 0) {
        return 0;
    }
    if (board[x2 - 5] == turn || board[x2 + 5] == turn ||
        board[x2 - 10] == turn || board[x2 + 10] == turn ||
        (board[x2 - 6] == turn && (x2 / 5) % 2 == 0) || (board[x2 + 6] == turn && (x2 / 5) % 2 == 1 && x2 % 5 != 0) ||
        (board[x2 - 4] == turn && (x2 / 5) % 2 == 1 && x2 % 5 != 0) || (board[x2 + 4] == turn && (x2 / 5) % 2 == 0))
        return 1;

    if ((x2 / 5) % 2 == 1) {
        if (board[x2 - 20] == turn || board[x2 + 20] == turn ||
            (board[x2 - 11] == turn && x2 % 5 != 0) || board[x2 + 11] == turn ||
            (board[x2 - 1] == turn && x2 % 5 != 0) || board[x2 + 1] == turn ||
            board[x2 - 15] == turn || board[x2 + 15] == turn ||
            (board[x2 - 9] == turn) || (board[x2 + 9] == turn && x2 % 5 != 0) ||
            board[x2 + 16] == turn || board[x2 - 14] == turn)
            return 2;
    } else {
        if (board[x2 - 20] == turn || board[x2 + 20] == turn ||
            (board[x2 - 11] == turn) || board[x2 + 11] == turn ||
            (board[x2 - 1] == turn) || board[x2 + 1] == turn ||
            board[x2 - 15] == turn || board[x2 + 15] == turn ||
            (board[x2 - 9] == turn && x2 % 5 != 4) || (board[x2 + 9] == turn) ||
            board[x2 - 16] == turn || board[x2 + 14] == turn)
            return 2;
    }

    return 0;
}

void Board::move(int x2, int turn) {
    board[x2] = turn;
    if (board[x2 - 5] == (1 + (turn % 2))) board[x2 - 5] = turn;
    if (board[x2 + 5] == (1 + (turn % 2))) board[x2 + 5] = turn;
    if (board[x2 - 10] == (1 + (turn % 2))) board[x2 - 10] = turn;
    if (board[x2 + 10] == (1 + (turn % 2))) board[x2 + 10] = turn;
    if ((x2 / 5) % 2) {
        if (board[x2 + 6] == (1 + (turn % 2))) board[x2 + 6] = turn;
        if (board[x2 - 4] == (1 + (turn % 2))) board[x2 - 4] = turn;
    } else {
        if (board[x2 - 6] == (1 + (turn % 2))) board[x2 - 6] = turn;
        if (board[x2 + 4] == (1 + (turn % 2))) board[x2 + 4] = turn;
    }
}

void Board::jump(int x1, int x2, int turn) {
    board[x1] = 0;
    board[x2] = turn;
    if (board[x2 - 5] == (1 + (turn % 2))) board[x2 - 5] = turn;
    if (board[x2 + 5] == (1 + (turn % 2))) board[x2 + 5] = turn;
    if (board[x2 - 10] == (1 + (turn % 2))) board[x2 - 10] = turn;
    if (board[x2 + 10] == (1 + (turn % 2))) board[x2 + 10] = turn;
    if (board[x2 - 6] == (1 + (turn % 2))) board[x2 - 6] = turn;
    if (board[x2 + 6] == (1 + (turn % 2))) board[x2 + 6] = turn;
    if (board[x2 - 4] == (1 + (turn % 2))) board[x2 - 4] = turn;
    if (board[x2 + 4] == (1 + (turn % 2))) board[x2 + 4] = turn;
}

int Board::getPerl() {
    int count = 0;
    for (int i: board) {
        if (i == 2) count++;
    }
    return count;
}

int Board::getRuby() {
    int count = 0;
    for (int i: board) {
        if (i == 1) count++;
    }
    return count;
}

Board Board::copy() {
    Board board1;
    for (int i = 0; i < board.size(); i++) board1.board[i] = board[i];
    return board1;
}
