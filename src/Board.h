//
// Created by PTB on 11/13/2021.
//

#ifndef NONOGRAM_SOLVER_BOARD_H
#define NONOGRAM_SOLVER_BOARD_H

#include <map>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include "Line.h"

using namespace std;


class Board {
    map<pair<int, int>, int> cells;
    vector<Line> hLines;
    vector<Line> vLines;
    int width;
    int height;

    static void resolve(Line& line, int side);
public:
    Board() = delete;

    Board(vector<vector<int>> vClues, vector<vector<int>> hClues, int width, int height);

    vector<vector<bool>> solve();
};


#endif //NONOGRAM_SOLVER_BOARD_H
