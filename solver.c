/*============================================================================
 *
 * Name: solver.c
 *
 * Created by: Samuel Barton
 *
 * Project: SudokuSolver
 *
 * Description: This program will run the algorithms created to solve Sudoku
 *              puzzles, and will display the solutions to the user.
 *
 *              The algorithms which can be run will be defined in 
 *              algorithms.h
 *
 *==========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

/* Custom header files. */
#include "algorithms.h"

// the size of the puzzle
const int SIZE = 9;

/*============================================================================
 *
 * Function: backtrack
 *
 * Arguments: int** puzzle - The puzzle
 * 
 * Returns: none
 *
 * Description: This function will perform a simple backtracking algorithm to
 *              find a solution to the sudoku puzzle provided.
 *
 *==========================================================================*/
void backtrack(int** puzzle)
{
    /* begin at the top left corner of the puzzle. */
    int r,c = 0;

    int unsolved = 1;

    while (unsolved)
    {
        
    }

}

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
    for (column = 0; column < SIZE; column++)
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
    for (row= 0; row < SIZE; row++)
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
/*============================================================================
 *
 * Function: setupPuzzle
 *
 * Arguments: none
 * 
 * Returns int** - The puzzle
 *
 * Description: This function allocates the space the puzzle will occupy, and
 *              reads in the puzzle to use from the text file "puzzle"
 *
 *==========================================================================*/
int** setupPuzzle()
{
    /* Allocate a 2D array SIZE x SIZE. */
    int** puzzle = malloc(sizeof(int*)*SIZE);

    int i,j;
    for (i = 0; i < SIZE; i++)
    {
        puzzle[i] = malloc(sizeof(int)*SIZE);
    }

    /* read in puzzle from file. */
    int puzzle_file = open("puzzle", O_RDONLY);

    for (i = 0; i < SIZE; i++)
    {
        char buf[2*SIZE];
        read(puzzle_file, buf, 2*SIZE);

        puzzle[i][0] = atoi(strtok(buf, " "));

        for (j = 1; j < SIZE; j++)
        {
            puzzle[i][j] = atoi(strtok(NULL, " "));
        }
    }

    return puzzle;
}

/*============================================================================
 *
 * Function: zeroPuzzle 
 *
 * Arguments: int** puzzle - the puzzle
 * 
 * Returns void
 *
 * Description: This function zeros out the puzzle.
 *
 *==========================================================================*/
void zeroPuzzle(int** puzzle)
{
    /* Set each square in the SIZE x SIZE grid to 0 */
    int i,j;

    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            puzzle[i][j] = 0;
        }
    }
}


int main(int ac, char** av)
{
    int** puzzle = setupPuzzle();

    int i,j;

    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            printf("%d ", puzzle[i][j]);
        }

        printf("\n");
    }

    return 0;
}
