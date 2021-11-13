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

public:
    Board() = delete;

    Board(vector<vector<int>> hClues, vector<vector<int>> vClues) {
        vector<vector<bool>> permutations;
        for (int i = 0; i <= 5; ++i) {
            vector<bool> per(5, false);
            fill(per.begin() + i, per.end(), true);
            do permutations.push_back(per); while (next_permutation(per.begin(), per.end()));
        }

        cout << permutations.size() << endl;

        for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
                cells.insert({{i, j}, -1});

        for (int i = 0; i < 5; ++i) {
            vector<int*> line1(5);
            vector<int*> line2(5);
            for (int j = 0; j < 5; ++j) {
                line1[j] = &cells[{j, i}];
                line2[j] = &cells[{i, j}];
            }
            hLines.emplace_back(line1, vClues[i], permutations);
            vLines.emplace_back(line2, hClues[i], permutations);
        }
    }

    vector<vector<bool>> solve() {
        auto solved = [](const Line& line) { return line.is_solved(); };
        while (!(
                all_of(hLines.begin(), hLines.end(), solved) &&
                all_of(vLines.begin(), vLines.end(), solved))) {
            for (auto& line: hLines) resolve(line);
            for (auto& line: vLines) resolve(line);

            for (int i = 0; i < 5; ++i) {
                for (int j = 0; j < 5; ++j) {
                    cout << '|' << *hLines[i].cells[j] << '|';
                }
                cout << endl;
            }

            cout << "---------------\n\n";

        }

        vector<vector<bool>> ret(5);
        for (int i = 0; i < 5; ++i) {
            ret[i].reserve(5);
            for (int j = 0; j < 5; ++j) {
                ret[i][j] = *hLines[i].cells[j];
            }
        }

        return ret;
    }

    void resolve(Line& line) {
        auto checks = [&line](const vector<bool>& per) {
            auto it = per.begin();
            for (auto clue: line.clues) {
                it = find(it, per.end(), 1);
                for (;it != per.end() && *it; it++, clue--);
                if (clue != 0) return false;
            }
            for (int i = 0; i < 5; ++i) {
                int cell = *line.cells[i];
                if(cell != -1 && cell != per[i]) return false;
            }
            return true;
        };

        vector<vector<bool>> checked;
        copy_if(line.possibilities.begin(), line.possibilities.end(), back_inserter(checked), checks);
        for (int i = 0; i < 5; ++i) {
            if (*line.cells[i] != -1) continue;
            auto sum = 0;
            for (const auto& per: checked) sum += per[i];
            *line.cells[i] = sum == 0 ? 0 : sum == checked.size() ? 1 : -1;
        }
        line.possibilities = checked;
    }
};


#endif //NONOGRAM_SOLVER_BOARD_H
