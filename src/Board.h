//
// Created by PTB on 11/13/2021.
//

#ifndef NONOGRAM_SOLVER_BOARD_H
#define NONOGRAM_SOLVER_BOARD_H

#include <map>
#include <vector>
#include <algorithm>
#include "Cell.h"
#include "Line.h"

using namespace std;


class Board {
    map<pair<int, int>, Cell> cells;
    vector<Line> hLines;
    vector<Line> vLines;

public:
    Board() = delete;

    Board(vector<vector<int>> hClues, vector<vector<int>> vClues) {
        for (int i = 0; i < 5; ++i)
            for (int j = 0; j < 5; ++j)
                cells.insert({{i, j}, Cell()});

        for (int i = 0; i < 5; ++i) {
            Line line1;
            Line line2;
            for (int j = 0; j < 5; ++j) {
                line1.cells.push_back(&cells[{j, i}]);
                line2.cells.push_back(&cells[{i, j}]);
            }
            line1.clues = vClues[i];
            line2.clues = hClues[i];
            hLines.push_back(line1);
            vLines.push_back(line2);
        }
    }

    vector<vector<bool>> solve() {
        auto solved = [](const Line& line) { return line.is_solved(); };
        while (!(
                all_of(hLines.begin(), hLines.end(), solved) &&
                all_of(vLines.begin(), vLines.end(), solved))) {
            for (const auto &line : hLines) {
                line.resolve();
            }
            for (const auto &line : vLines) {
                line.resolve();
            }
        }
    }
};


#endif //NONOGRAM_SOLVER_BOARD_H
