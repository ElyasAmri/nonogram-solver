//
// Created by PTB on 11/13/2021.
//

#ifndef NONOGRAM_SOLVER_LINE_H
#define NONOGRAM_SOLVER_LINE_H

#include <vector>
#include <algorithm>
#include "Cell.h"

using namespace std;

struct Line {
    vector<Cell*> cells;
    vector<int> clues;
    vector<vector<bool>> possibilities;

    [[nodiscard]] bool is_solved() const {
        return all_of(cells.begin(), cells.end(), [](const Cell* const cell) {
            return cell->value != -1;
        });
    }

    Line(vector<Cell*> cells, vector<int> clues, vector<vector<bool>> possibilities)
            : cells(move(cells)),
              clues(move(clues)),
              possibilities(move(possibilities)) {}
};


#endif //NONOGRAM_SOLVER_LINE_H
