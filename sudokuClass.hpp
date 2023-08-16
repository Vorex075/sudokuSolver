#include <string>
#include <iostream>

class Sudoku {
    public:

        Sudoku();
        ~Sudoku();
        /**
         * @return The number of empty cells that are left in the sudoku
        */
        const int& get_empty_spaces() const;

        void print_sudoku() const;



    private:
        /**
         * @brief Reads the input file to fill the sudoku info
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

        
        int** sudoku_;
        int numbers_left_;
};