//
// Created by yaidf on 19.Parameters::maxLine.2022.
//

#include "Surface.h"
#include "Parameters.h"
Surface::Surface() {
    surface.resize(Parameters::boardSize);
    line = 0;
    for (int i = 0; i < Parameters::boardSize; i++) {
        surface[i] = "                                                                                               ";
    }
}

void Surface::loadBoard(vector<int> data) {
    for (int i = 0; i < Parameters::boardSize - 1; i++) {
        for (int j = 0; j < Parameters::boardWidth; j++) {
            if (data[i * Parameters::boardWidth + j] != Parameters::spaceSize) {
                surface[i][j * Parameters::cellSize + (i % 2) * Parameters::spaceSize] = '/';
                surface[i][j * Parameters::cellSize + (i % 2) * Parameters::spaceSize + Parameters::spaceSize] = '\\';
                surface[i + 1][j * Parameters::cellSize + (i % 2) * Parameters::spaceSize] = '\\';
                if (data[i * Parameters::boardWidth + j] != 9) surface[i][j * Parameters::cellSize + (i % 2) * Parameters::spaceSize + 2] = data[i * Parameters::boardWidth + j] + Parameters::intBonus;
                surface[i + 1][j * Parameters::cellSize + (i % 2) * Parameters::spaceSize + 1] = '_';
                surface[i + 1][j * Parameters::cellSize + (i % 2) * Parameters::spaceSize + 2] = '_';
                surface[i + 1][j * Parameters::cellSize + (i % 2) * Parameters::spaceSize + 3] = '_';
                surface[i + 1][j * Parameters::cellSize + (i % 2) * Parameters::spaceSize + Parameters::spaceSize] = '/';
            }
        }
    }
    int counter = 0;
    for (int i = 0; i < Parameters::boardSize - 1; i++) {
        for (int j = 0; j < Parameters::boardWidth; j++) {
            if (data[i * Parameters::boardWidth + j] != Parameters::spaceSize) {
                surface[i][Parameters::firstSpace + j * Parameters::cellSize + (i % 2) * Parameters::spaceSize] = '/';
                surface[i][Parameters::firstSpace + j * Parameters::cellSize + (i % 2) * Parameters::spaceSize + Parameters::spaceSize] = '\\';
                surface[i + 1][Parameters::firstSpace + j * Parameters::cellSize + (i % 2) * Parameters::spaceSize] = '\\';
                if (data[i * Parameters::boardWidth + j] != 9) {
                    if (counter < Parameters::maxLine) {
                        surface[i][Parameters::firstSpace + j * Parameters::cellSize + (i % 2) * Parameters::spaceSize + 2] = (char) (counter % Parameters::maxLine + Parameters::intBonus);
                    } else {
                        surface[i][Parameters::firstSpace + j * Parameters::cellSize + (i % 2) * Parameters::spaceSize + 2] = (char) (counter / Parameters::maxLine + Parameters::intBonus);
                        surface[i][Parameters::firstSpace + j * Parameters::cellSize + (i % 2) * Parameters::spaceSize + 3] = (char) ((counter % Parameters::maxLine) + Parameters::intBonus);

                    }
                }
                surface[i + 1][Parameters::firstSpace + j * Parameters::cellSize + (i % 2) * Parameters::spaceSize + 1] = '_';
                surface[i + 1][Parameters::firstSpace + j * Parameters::cellSize + (i % 2) * Parameters::spaceSize + 2] = '_';
                surface[i + 1][Parameters::firstSpace + j * Parameters::cellSize + (i % 2) * Parameters::spaceSize + 3] = '_';
                surface[i + 1][Parameters::firstSpace + j * Parameters::cellSize + (i % 2) * Parameters::spaceSize + Parameters::spaceSize] = '/';
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
    surface[a / Parameters::boardWidth][(a % Parameters::boardWidth) * Parameters::cellSize + ((a / Parameters::boardWidth) % 2) * Parameters::spaceSize + 2] = '.';
}
void Surface::clr() {
    for (int i = 0; i < Parameters::boardSize; i++) {
        surface[i] = "                                                                                               ";
    }
    line = 0;
}

void Surface::addText(string st) {
    line++;
    for (int i = 0; i < st.size(); i++) {
        surface[line][Parameters::firstSpace * 2 + i] = st[i];
    }
}
void Surface::addLongText(string st) {
    line++;
    for (int i = 0; i < st.size(); i++) {
        surface[line][Parameters::maxLine + i] = st[i];
    }
}