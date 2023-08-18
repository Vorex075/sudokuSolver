#include "sudokuClass.hpp"
#include <fstream>





//-----------CONSTRUCTOR-----------------


Sudoku::Sudoku() {

}



Sudoku::Sudoku(const std::string& input_name) {
    sudoku_ = new int*[9];
    for (unsigned i{0}; i < 9; i++) {
        sudoku_[i] = new int[9];
    }

    fill_sudoku(input_name);

    
    if (is_valid_sudoku()) {
        std::cout << "It is a valid initial sudoku\n";
    } else {
        std::cout << "It is not a valid initial sudoku because there is at least";
        std::cout << " one repeated number in a row, column or sub-matrix.\n";
        std::cout << "Check the input and try again.\n Execution stopped.\n";
        std::exit(EXIT_FAILURE);
    }

}

Sudoku::Sudoku(const Sudoku& another_sudoku) {
    sudoku_ = new int*[9];
    for (unsigned int i{0}; i < 9; i++) {
        sudoku_[i] = new int[9];
    }

    for (unsigned int i{0}; i < 9; i++) {
        for (unsigned int j{0}; j < 9; j++) {
            sudoku_[i][j] = another_sudoku[i][j];
        }
    }

    // Since we're copying an existing sudoku, we don't need to check if this sudoku is valid again
}

//-----------DESTRUCTOR------------------

Sudoku::~Sudoku() {
    for (unsigned i{0}; i < 9; i++) {
        delete[] sudoku_[i];
    }
    delete[] sudoku_;
    sudoku_ = nullptr;
}

//-----------FILLERS---------------------

void Sudoku::fill_sudoku(const std::string& input) {
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

//-----------GETTER-------------------

const int& Sudoku::get_empty_spaces() const {
    return numbers_left_;
}

const int* Sudoku::operator[](int row) const{
    return sudoku_[row];
}



int* Sudoku::operator[](int row) {
    return sudoku_[row];
}

//-----------PRINTER------------------

void Sudoku::print() const {
    std::cout << "\n";
    for (unsigned i{0}; i < 9; i++) {
        for (unsigned j{0}; j < 9; j++) {
            std::cout << sudoku_[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "There are " << get_empty_spaces() << " spaces left\n";
}

//-----------VALIDATORS---------------

bool Sudoku::is_valid_line(bool column, int index) const {
    if (column) {
        for (unsigned i = 0; i < 8; i++) {
            if (sudoku_[i][index] == 0) {
                continue;
            }
            for (unsigned j = i+1; j < 9; j++) {
                if (sudoku_[i][index] == sudoku_[j][index]) { 
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
                if (sudoku_[index][i] == sudoku_[index][j]) { 
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

    // Now we have the sub-matrix as an array, so it is easier to check repeated values.

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

bool Sudoku::is_valid_change(BlankSpace::threesome& change) {
    return (is_valid_line(0, change.row) && is_valid_line(1, change.column) && is_valid_subMatrix(change.row, change.column));
}

//-----------SOLVER------------------

void Sudoku::solve() {
    if (numbers_left_ == 0) {
        std::cout << "The sudoku is already solved\n";
        return;
    }
    

    backtracking();
}

int Sudoku::smallest_row(BlankSpace::threesome& blank_space) {
    int min_blank = 10;
    for (int i = 0; i < 9; i++) {
        int total_row = 0;
        for (int j = 0; j < 9; j++) {
            if (sudoku_[i][j] == 0) {
                total_row++;
            }
        }
        if (total_row < min_blank && total_row != 0) {
            blank_space.row = i;
            min_blank = total_row;
        }
    }

    // Now need to look after the first blank space in the row

    if (min_blank == 10) {
        return false;
    }
    for (int i = 0; i < 9; i++) {
        if (sudoku_[blank_space.row][i] == 0) {
            blank_space.column = i;
            blank_space.value = &sudoku_[blank_space.row][blank_space.column];
            return min_blank;
        }
    }
    return min_blank; // This should not be reached
}
int Sudoku::smallest_column(BlankSpace::threesome& blank_space) {
    int min_blank = 10;
    for (int j = 0; j < 9; j++) {
        int total_col = 0;
        for (int i = 0; i < 9; i++) {
            if (sudoku_[i][j] == 0) {
                total_col++;
            }
        }
        if (total_col < min_blank && total_col != 0) {
            blank_space.column = j;
            min_blank = total_col;
        }
    }

    // Now need to look after the first blank space in the column

    if (min_blank == 10) {
        return 0;
    }
    for (int i = 0; i < 9; i++) {
        if (sudoku_[i][blank_space.column] == 0) {
            blank_space.row = i;
            blank_space.value = &sudoku_[blank_space.row][blank_space.column];
            return true;
        }
    }
    return min_blank; // This should not be reached
}

bool Sudoku::smallest_line_position(BlankSpace::threesome& BlankSpace) {

    BlankSpace::threesome blank_space_row;
    BlankSpace::threesome blank_space_col;

    int row = smallest_row(blank_space_row);
    int col = smallest_column(blank_space_col);

    if (row < col && row != 0) {
        BlankSpace = blank_space_row;
        return true;

    } else if (col < row && col != 0){
        BlankSpace = blank_space_col;
        return true;
    } else if (col == row && col != 0) {
        BlankSpace = blank_space_col;
        return true;
    } 
    return false; // If everything fails, there is no blank space left in the sudoku
}



bool Sudoku::backtracking() {
    BlankSpace::threesome blank_space;
    blank_space.row = 0;
    blank_space.column = 0;
    while (smallest_line_position(blank_space)) {
        for (int i = 1; i <= 9; i++) {
            *blank_space.value = i;
            if (is_valid_change(blank_space)) {
                if (backtracking()) {
                    return true;
                }
            }
            *blank_space.value = 0; // Its not a valid change, so we discard the last one
        }
        return false; // This branch has no solution. None of the 9 values could solve it
    }
    numbers_left_ = 0;
    return true; // There is no empty position in the sudoku, so it is solved
}
