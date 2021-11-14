//
// Created by PTB on 11/13/2021.
//

#include "Board.h"

Board::Board(vector<vector<int>> vClues, vector<vector<int>> hClues, int width, int height)
        : width(width), height(height) {
    vector<vector<bool>> hPermutations;
    vector<vector<bool>> vPermutations;

    for (int i = 0; i <= height; ++i) {
        vector<bool> per(height, false);
        fill(per.begin() + i, per.end(), true);
        do vPermutations.push_back(per); while (next_permutation(per.begin(), per.end()));
    }

    if (width == height)
        copy(vPermutations.begin(), vPermutations.end(), back_inserter(hPermutations));
    else {
        for (int i = 0; i <= width; ++i) {
            vector<bool> per(width, false);
            fill(per.begin() + i, per.end(), true);
            do hPermutations.push_back(per); while (next_permutation(per.begin(), per.end()));
        }
    }
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            cells.insert({{i, j}, -1});

    for (int i = 0; i < height; ++i) {
        vector<int*> line(width);
        for (int j = 0; j < width; ++j) {
            line[j] = &cells[{i, j}];
        }
        hLines.emplace_back(line, hClues[i], hPermutations);
    }

    for (int i = 0; i < width; ++i) {
        vector<int*> line(height);
        for (int j = 0; j < height; ++j) {
            line[j] = &cells[{j, i}];
        }
        vLines.emplace_back(line, vClues[i], vPermutations);
    }
}

vector<vector<bool>> Board::solve() {
    auto unsolved = [](const pair<pair<int, int>, int>& keyval) { return keyval.second == -1; };
    map<pair<int, int>, int> previousCells = cells;
    while (any_of(cells.begin(),  cells.end(), unsolved)) {
        for (auto& line: hLines) resolve(line, width);
        for (auto& line: vLines) resolve(line, height);
        if(previousCells == cells) {
            cout << "Stuck" << endl;
            for (int i = 0; i < height; ++i) {
                for (int j = 0; j < width; ++j) {
                    cout << cells[{i,j}] << " ";
                }
                cout << endl;
            }
            cout << endl;
            break;
        }
        previousCells = cells;
    }

    vector<vector<bool>> ret(height);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            ret[i].push_back(cells[{i, j}]);
        }
    }

    return ret;
}

void Board::resolve(Line& line, int side) {
    auto checks = [&line, side](const vector<bool>& per) {
        auto it = per.begin();
        for (auto clue: line.clues) {
            it = find(it, per.end(), 1);
            for (; it != per.end() && *it; it++, clue--);
            // if we either didn't suffice or over exceeded the clue
            if (clue != 0) return false;
        }
        // are there any remaining checks
        it = find(it, per.end(), 1);
        if (it != per.end()) return false;
        for (int i = 0; i < side; ++i) {
            int cell = *line.cells[i];
            // if the determined cell is not equal to the respective value of the permutation
            if(cell != -1 && cell != per[i]) return false;
        }
        return true;
    };

    vector<vector<bool>> checked;
    copy_if(line.possibilities.begin(), line.possibilities.end(), back_inserter(checked), checks);
    for (int i = 0; i < side; ++i) {
        // if the current cell is already determined
        if (*line.cells[i] != -1) continue;
        // check if a specific index is the same across all possibilities
        auto sum = 0;
        for (const auto& per: checked) sum += per[i];
        *line.cells[i] = sum == 0 ? 0 : sum == checked.size() ? 1 : -1;
    }
    line.possibilities = checked;
}
