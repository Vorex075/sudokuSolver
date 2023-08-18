#include "sudokuClass.hpp"

#include<chrono>

int main() {
    Sudoku sudoku("./sudokuInput.txt");
    std::cout << "Sudoku Input: \n";
    sudoku.print();
    auto start_time = std::chrono::high_resolution_clock::now();

    sudoku.solve();

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
    std::cout << "Sudoku Solved: \n";
    sudoku.print();

    double duration_seconds = static_cast<double>(duration_ns) / 1000000000;
    std::cout << "Execution time: " << duration_seconds << " seconds\n";
}