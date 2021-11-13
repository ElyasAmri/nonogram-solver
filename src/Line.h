//
// Created by PTB on 11/13/2021.
//

#ifndef NONOGRAM_SOLVER_LINE_H
#define NONOGRAM_SOLVER_LINE_H

#include <vector>
#include <algorithm>

using namespace std;

struct Line {
    vector<int*> cells;
    vector<int> clues;
    vector<vector<bool>> possibilities;

    [[nodiscard]] bool is_solved() const;

    Line(vector<int*> cells, vector<int> clues, vector<vector<bool>> possibilities);
};


#endif //NONOGRAM_SOLVER_LINE_H
