#include "algorithms.h"

const int PUZZLE_SIZE = 9;

/*============================================================================
 *
 * Function: rowContains
 *
 * Arguments: int** puzzle - The puzzle
 *            int row       - The row we are considering
 *            int value     - The value we are checking for
 * 
 * Returns: bool - whether or not the row contains the value in question
 *
 * Description: This function determines if the row in question contains the
 *              value passed in as an argument.
 *
 *==========================================================================*/
bool rowContains(int** puzzle, int row, int value)
{
    int column;
    for (column = 0; column < PUZZLE_SIZE; column++)
        if (puzzle[row][column] == value)
            return true;

    return false;
}

/*============================================================================
 *
 * Function: backtrack
 *
 * Arguments: int** puzzle - The puzzle
 *            int column    - The column we are considering
 *            int value     - The value we are checking for
 * 
 * Returns: bool - whether or not the column contains the value in question
 *
 * Description: This function determines if the column in question contains 
 *              the alue passed in as an argument.
 *
 *==========================================================================*/
bool columnContains(int** puzzle, int column, int value)
{
    int row;
    for (row= 0; row < PUZZLE_SIZE; row++)
        if (puzzle[row][column] == value)
            return true;

    return false;
}

/*============================================================================
 *
 * Function: blockContains
 *
 * Arguments: int** puzzle  - The puzzle
 *            int row       - The row we are considering
 *            int column    - The column we are considering
 *            int value     - The value we are checking for
 * 
 * Returns: bool - whether or not the specified block contains the value
 *
 * Description: This function determines if the block where the square defined
 *              by row, column sits contains the value. 
 *
 *              NOTE: this will currently only work on 9x9 boards as the block
 *              boundaries are determined by taking the row/column mod 3.
 *
 *==========================================================================*/
bool blockContains(int** puzzle, int row, int column, int value)
{
    /* Determine the edges of the current block */
    int r = row % 3;
    int c = column % 3;

    int r_start = -r;
    int r_end = 2 - r;

    int c_start = -c;
    int c_end = 2 - c;

    int i,j;

    for (i = row+r_start; i <= row+r_end; i++)
    {
        for (j = column+c_start; j <= column+c_end; j++)
        {
            if (puzzle[i][j] == value)
                return true;
        }
    }

    return false;
}
