//
// Created by PTB on 11/13/2021.
//

#include "Line.h"

Line::Line(vector<int*> cells, vector<int> clues, vector<vector<bool>> possibilities)
        : cells(move(cells)),
          clues(move(clues)),
          possibilities(move(possibilities)) {}

bool Line::is_solved() const {
    return all_of(cells.begin(), cells.end(), [](const int* const cell) {
        return *cell != -1;
    });
}
