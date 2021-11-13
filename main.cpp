#include <iostream>
#include "src/Board.h"

int main() {
    Board solver({{1,1}, {4}, {1,1,1}, {3}, {1}}, {{1}, {2}, {3}, {2,1}, {4}});
    for (const auto &item : solver.solve()) {
        for (const auto &i : item) {
            cout << " | " << i << " | ";
        }
        cout << '\n';
    }
    cout << endl;
}
