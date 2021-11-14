#include <iostream>
#include "src/Board.h"

void print(auto& solver) {
    for (const auto &item : solver.solve()) {
        for (const auto &i : item) {
            cout << i << " ";
        }
        cout << '\n';
    }
    cout << endl;
}

int main() {
    Board solver1({{1,1}, {4}, {1,1,1}, {3}, {1}}, {{1}, {2}, {3}, {2,1}, {4}}, 5, 5);
    print(solver1);
    cout << endl;
    Board solver2({{3,}, {4,}, {2, 2, 2}, {2, 4, 2}, {6,}, {3,}},
                  {{4,}, {6,}, {2, 2}, {2, 2}, {2,}, {2,}, {2,}, {2,}, {}, {2,}, {2,}},
                  6, 11);
    print(solver2);
}
