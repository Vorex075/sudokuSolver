#include "sudokuClass.hpp"
#include <chrono>

int main() {
  Sudoku sudoku;
  std::cout << "Sudoku Input: \n";
  sudoku.print();
  auto now = std::chrono::steady_clock::now();
  sudoku.solve();
  auto then = std::chrono::steady_clock::now();

  std::cout << "Sudoku Solved: \n";
  sudoku.print();
  std::cout << "Time difference = "
            << std::chrono::duration_cast<std::chrono::milliseconds>(then - now)
                   .count()
            << "[µs]" << std::endl;
}
