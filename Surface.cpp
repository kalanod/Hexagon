//
// Created by yaidf on 19.10.2022.
//

#include "Surface.h"
int boardSize = 18;
int boardWidth = 5;
int cellSize = 8;
int spaceSize = 4;
int gameSize = 4;
int intBonus = 48;
Surface::Surface() {
    surface.resize(18);
    line = 0;
    for (int i = 0; i < 18; i++) {
        surface[i] = "                                                                                               ";
    }
}

void Surface::loadBoard(vector<int> data) {
    for (int i = 0; i < 17; i++) {
        for (int j = 0; j < 5; j++) {
            if (data[i * 5 + j] != 4) {
                surface[i][j * 8 + (i % 2) * 4] = '/';
                surface[i][j * 8 + (i % 2) * 4 + 4] = '\\';
                surface[i + 1][j * 8 + (i % 2) * 4] = '\\';
                if (data[i * 5 + j] != 9) surface[i][j * 8 + (i % 2) * 4 + 2] = data[i * 5 + j] + 48;
                surface[i + 1][j * 8 + (i % 2) * 4 + 1] = '_';
                surface[i + 1][j * 8 + (i % 2) * 4 + 2] = '_';
                surface[i + 1][j * 8 + (i % 2) * 4 + 3] = '_';
                surface[i + 1][j * 8 + (i % 2) * 4 + 4] = '/';
            }
        }
    }
    int counter = 0;
    for (int i = 0; i < 17; i++) {
        for (int j = 0; j < 5; j++) {
            if (data[i * 5 + j] != 4) {
                surface[i][40 + j * 8 + (i % 2) * 4] = '/';
                surface[i][40 + j * 8 + (i % 2) * 4 + 4] = '\\';
                surface[i + 1][40 + j * 8 + (i % 2) * 4] = '\\';
                if (data[i * 5 + j] != 9) {
                    if (counter < 10) {
                        surface[i][40 + j * 8 + (i % 2) * 4 + 2] = (char) (counter % 10 + 48);
                    } else {
                        surface[i][40 + j * 8 + (i % 2) * 4 + 2] = (char) (counter / 10 + 48);
                        surface[i][40 + j * 8 + (i % 2) * 4 + 3] = (char) ((counter % 10) + 48);

                    }
                }
                surface[i + 1][40 + j * 8 + (i % 2) * 4 + 1] = '_';
                surface[i + 1][40 + j * 8 + (i % 2) * 4 + 2] = '_';
                surface[i + 1][40 + j * 8 + (i % 2) * 4 + 3] = '_';
                surface[i + 1][40 + j * 8 + (i % 2) * 4 + 4] = '/';
            }
            counter++;
        }
    }
}

void Surface::print() {
    for (const string &i: surface) {
        cout << i << endl;
    }
}
void Surface::setCan(int a){
    surface[a / boardWidth][(a % boardWidth) * cellSize + ((a / boardWidth) % 2) * spaceSize + 2] = '.';
}
void Surface::clr() {
    for (int i = 0; i < 18; i++) {
        surface[i] = "                                                                                               ";
    }
    line = 0;
}

void Surface::addText(string st) {
    line++;
    for (int i = 0; i < st.size(); i++) {
        surface[line][80 + i] = st[i];
    }
}
void Surface::addLongText(string st) {
    line++;
    for (int i = 0; i < st.size(); i++) {
        surface[line][10 + i] = st[i];
    }
}