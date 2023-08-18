#ifndef SUDOKU_CLASS
#define SUDOKU_CLASS

#include <string>
#include <iostream>
#include <vector>

namespace BlankSpace {
    struct threesome {
        int row;
        int column;
        int* value;
        void operator=(BlankSpace::threesome another_threesome) {
            this->row = another_threesome.row;
            this->column = another_threesome.column;
            this->value = another_threesome.value;
        }
    };
}


class Sudoku {
    public:

        /**
         * Default constructor 
        */
        Sudoku();

        /**
         * Constructor with input
        */
        Sudoku(const std::string& input_file);

        /**
         * Copy constructor
        */
        Sudoku(const Sudoku& another_sudoku);

        /**
         * Destructor
        */
        ~Sudoku();
        /**
         * @return The number of empty cells that are left in the sudoku
        */
        const int& get_empty_spaces() const;

        /**
         * @brief Print in console the sudoku with the number of empty cells left
        */
        void print() const;

        /**
         * @brief Solves the sudoku
        */
        void solve();

        const int* operator[](int row) const;

        int* operator[](int row);

        

    private:
        /**
         * @brief Reads the input file to fill the sudoku with values 
        */
        void fill_sudoku(const std::string& input_name);
        /**
         * @brief Check if a line is valid to continue solving the sudoku
         * @param column True if it is a column. False if is a row
         * @param index The index of the column/row
         * @return True if is valid. False otherwise
        */
        bool is_valid_line(bool column, int index) const;

        /**
         * @brief Check if a sub-matrix is valid. 
         * @param row The row index of one position from the sub-matrix
         * @param column The column index of one position form the sub-matrix
        */
        bool is_valid_subMatrix(int row, int column) const;

        /**
         * @brief Check if the sudoku is initially solvable
        */
        bool is_valid_sudoku() const;

        /**
         * @brief Check if the change is a valid change.
         * @param change An struct with a reference to a position, a row value and a column value.
         * This struct is called "threesome"
         * @return True if it is valid. False otherwise.
        */
        bool is_valid_change(BlankSpace::threesome& change);

        /**
         * @brief Looks over the sudoku matrix and finds the
         * line with the lowest number of blank spaces.
         * @attention With line we include rows and columns
         * @param value A pointer to the first blank space of the smallest line
         * @param position A pair with the coordinates of 'value' in the matrix
         * @return False if there is no blank space left. True otherwise
        */
        bool smallest_line_position(BlankSpace::threesome& BlankSpace);
        
        int smallest_row(BlankSpace::threesome& blank_Space);

        int smallest_column(BlankSpace::threesome& blank_Space);


        /**
         * @brief Solves the sudoku using backtracking
        */
        bool backtracking();
        
        int** sudoku_;
        int numbers_left_;

        
};


#endif