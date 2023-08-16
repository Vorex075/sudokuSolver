#include "sudokuClass.hpp"

int main() {
    Sudoku sudoku;
    std::cout << "Sudoku Input: \n";
    sudoku.print();

    sudoku.solve();

    std::cout << "Sudoku Solved: \n";
    sudoku.print();
}