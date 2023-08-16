#include <string>
#include <iostream>
#include <vector>



struct threesome
{
    int row;
    int column;
    int* value;

};

class Sudoku {
    public:

        Sudoku();
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

    private:
        /**
         * @brief Reads the input file to fill the sudoku with values 
        */
        void fill_sudoku();
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
        bool is_valid_change(threesome& change);
        
        /**
         * @brief Solves the sudoku using backtracking
        */
        bool backtracking();

        /**
         * @brief Fills "zero_array_" with references to blank spaces in the
         * original sudoku and its position int the matrix
        */
        void fill_zero_array();
        
        int** sudoku_;
        int numbers_left_;

        threesome* zero_array_;
};