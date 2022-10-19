//
// Created by yaidf on 19.10.2022.
//

#ifndef HEXAGON_SURFACE_H
#define HEXAGON_SURFACE_H


class Surface {
private:
    vector<string> surface;
    int line;
public:
    Surface();
    void loadBoard(vector<int>);
    void print();
    void addText(string);
    void clr();
};


#endif //HEXAGON_SURFACE_H
