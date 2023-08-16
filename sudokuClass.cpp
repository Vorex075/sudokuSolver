#include "sudokuClass.hpp"
#include <fstream>



//-----------CONSTRUCTOR-----------------

Sudoku::Sudoku() {
    sudoku_ = new int*[9];
    for (unsigned i{0}; i < 9; i++) {
        sudoku_[i] = new int[9];
    }

    fill_sudoku();
    
    if (is_valid_sudoku()) {
        std::cout << "It is a valid initial sudoku\n";
    } else {
        std::cout << "It is not a valid initial sudoku because there is at least";
        std::cout << " one repeated number in a row, column or sub-matrix.\n";
        std::cout << "Check the input and try again.\n Execution stopped.\n";
        std::exit(EXIT_FAILURE);
    }
    
}

//-----------DESTRUCTOR------------------

Sudoku::~Sudoku() {
    for (unsigned i{0}; i < 9; i++) {
        delete sudoku_[i];
    }
    delete sudoku_;
    sudoku_ = nullptr;
}


void Sudoku::fill_sudoku() {
    std::cout << "Type the name of the input file: ";
    std::string input;
    std::cin >> input;
    std::ifstream input_file(input);
    if (!input_file) {
        std::cout << "There was an error while trying to open the input file\n";
        std::cout << "Make sure you typed the correct file name. It has to include";
        std::cout << " the file extension\n";
        std::cout << "Execution stopped.\n";
        std::exit(EXIT_FAILURE);
    }
    int value; 
    numbers_left_ = 81;
    unsigned int i{0}, j{0};
    while (input_file >> value) {
        if (value < 0 || value > 9) {
            std::cout << "There is a value lower than 0 or higher than 9 in the input file.\n";
            std::cout << "A sudoku with this input cannot be solved.\n";
            std::cout << "Input should be numbers from 0 to 9 (both included)\n";
            std::cout << "Execution stopped.\n";
            std::exit(EXIT_FAILURE);
        } else if (value != 0) {
            numbers_left_--;
        }
        sudoku_[i][j++] = value;
        if (j > 8) {
            j = 0;
            i++;
        }
    }
    return;
}

const int& Sudoku::get_empty_spaces() const {
    return numbers_left_;
}


void Sudoku::print_sudoku() const {
    std::cout << "\n";
    for (unsigned i{0}; i < 9; i++) {
        for (unsigned j{0}; j < 9; j++) {
            std::cout << sudoku_[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "There are " << get_empty_spaces() << " spaces left\n";
}



bool Sudoku::is_valid_line(bool column, int index) const {
    if (column) {
        for (unsigned i = 0; i < 8; i++) {
            if (sudoku_[i][index] == 0) {
                continue;
            }
            for (unsigned j = i+1; j < 9; j++) {
                if (sudoku_[i][index] == sudoku_[j][index]) { // There is at least 1 value repeated
                    return false;
                }
            }
        }
    } else {
        for (unsigned i = 0; i < 8; i++) {
            if (sudoku_[index][i] == 0) {
                continue;
            }
            for (unsigned j = i+1; j < 9; j++) {
                if (sudoku_[index][i] == sudoku_[index][j]) { // There is at least 1 value repeated
                    return false;
                }
            }
        }
    }
    return true;
}

bool Sudoku::is_valid_subMatrix(int row, int column) const {
    int matrix_as_row[9];
    unsigned position = 0;
    if (row >= 6) {

        if (column >= 6) {
            for (unsigned i{6}; i < 9; i++) {
                for (unsigned j{6}; j < 9; j++) {
                    matrix_as_row[position++] = sudoku_[i][j];
                }
            }
        } else if (column >= 3) {
            for (unsigned i{6}; i < 9; i++) {
                for (unsigned j{3}; j < 6; j++) {
                    matrix_as_row[position++] = sudoku_[i][j];
                }
            }

        } else {
            for (unsigned i{6}; i < 9; i++) {
                for (unsigned j{0}; j < 3; j++) {
                    matrix_as_row[position++] = sudoku_[i][j];
                }
            }
        }
    } else if (row >= 3) {

        if (column >= 6) {

            for (unsigned i{3}; i < 6; i++) {
                for (unsigned j{6}; j < 9; j++) {
                    matrix_as_row[position++] = sudoku_[i][j];
                }
            }

        } else if (column >= 3) {

            for (unsigned i{3}; i < 6; i++) {
                for (unsigned j{3}; j < 6; j++) {
                    matrix_as_row[position++] = sudoku_[i][j];
                }
            }

        } else {

            for (unsigned i{3}; i < 6; i++) {
                for (unsigned j{0}; j < 3; j++) {
                    matrix_as_row[position++] = sudoku_[i][j];
                }
            }
            
        }
    } else {

        if (column >= 6) {

            for (unsigned i{0}; i < 3; i++) {
                for (unsigned j{6}; j < 9; j++) {
                    matrix_as_row[position++] = sudoku_[i][j];
                }
            }

        } else if (column >= 3) {

            for (unsigned i{0}; i < 3; i++) {
                for (unsigned j{3}; j < 6; j++) {
                    matrix_as_row[position++] = sudoku_[i][j];
                }
            }

        } else {

            for (unsigned i{0}; i < 3; i++) {
                for (unsigned j{0}; j < 3; j++) {
                    matrix_as_row[position++] = sudoku_[i][j];
                }
            }
            
        }
    }

    // Now we have the sub-matrix as an array. 

    bool is_valid = true;
    for (unsigned i = 0; i < 8; i++) {
        if (matrix_as_row[i] == 0) {
            continue;
        }
        for (unsigned j = i+1; j < 9; j++) {
            if (matrix_as_row[i] == matrix_as_row[j]) { // There is at least 1 value repeated
                is_valid = false;
            }
        }
    }
    return is_valid;
}

bool Sudoku::is_valid_sudoku() const {
    // Firstly we'll check over every line and every column
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j < 9; j++) {
            if (!is_valid_line(i, j)) {
                return false;
            }
        }
    }

    for (unsigned i = 0; i < 8; i += 3) {
        for (unsigned j = 0; j < 8; j += 3) {
            if (!is_valid_subMatrix(i, i)) {
                return false;
            }
        }
    }
    return true;
}
int main() {
    Sudoku sudoku;
    sudoku.print_sudoku();
}