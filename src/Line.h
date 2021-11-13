//
// Created by PTB on 11/13/2021.
//

#ifndef NONOGRAM_SOLVER_LINE_H
#define NONOGRAM_SOLVER_LINE_H

#include <vector>
#include <algorithm>
#include "Cell.h"

struct Line {
    std::vector<Cell*> cells;
    std::vector<int> clues;

    bool is_solved() const {
        return std::all_of(cells.begin(), cells.end(), [](const Cell* const cell) {
            return cell->value != -1;
        });
    }
};


#endif //NONOGRAM_SOLVER_LINE_H
