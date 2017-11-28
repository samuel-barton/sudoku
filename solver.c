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

/* Custom header files. */
#include "algorithms.h"

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
    int r,c,i,j = 0;

    int unsolved = 1;
    int cur_num = 1;

    printf("Backtrack algorithm start.\n");
    while (unsolved)
    {
        for (r = 0; r < PUZZLE_SIZE; r++)
        {
            printf("row %d\n", r);
            for (c = 0; c < PUZZLE_SIZE; c++)
            {
                printf("\tcol %d\n", c);

                if (puzzle[r][c] != 0)
                {
                    // already filled
                    printf("already filled with %d\n", puzzle[r][c]);
                    cur_num = 1;
                    continue;
                }

                while ((rowContains(puzzle, r, cur_num) || 
                       columnContains(puzzle, c, cur_num) ||
                       blockContains(puzzle, r, c, cur_num)) && cur_num <= 9)
                    cur_num++;

                if (cur_num > 9)
                {
                    // backtracking is needed.
                    //printf("Backtracking Required.\n");
                    //printf("Stopped at row %d, column %d\n", r, c);
                    unsolved = 0;
                }
                else
                {
                    puzzle[r][c] = cur_num;
                    printf("inserted %d at row %d col %d\n", cur_num, r,c);
                    cur_num = 1;
                }
            }
        }

        unsolved = 0;
    }
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
    /* Allocate a 2D array PUZZLE_SIZE x SIZE. */
    int** puzzle = malloc(sizeof(int*)*PUZZLE_SIZE);

    int i,j;
    for (i = 0; i < PUZZLE_SIZE; i++)
    {
        puzzle[i] = malloc(sizeof(int)*PUZZLE_SIZE);
    }

    /* read in puzzle from file. */
    int puzzle_file = open("puzzle", O_RDONLY);

    for (i = 0; i < PUZZLE_SIZE; i++)
    {
        char buf[2*PUZZLE_SIZE];
        read(puzzle_file, buf, 2*PUZZLE_SIZE);

        puzzle[i][0] = atoi(strtok(buf, " "));

        for (j = 1; j < PUZZLE_SIZE; j++)
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
    /* Set each square in the PUZZLE_SIZE x SIZE grid to 0 */
    int i,j;

    for (i = 0; i < PUZZLE_SIZE; i++)
    {
        for (j = 0; j < PUZZLE_SIZE; j++)
        {
            puzzle[i][j] = 0;
        }
    }
}

void printPuzzle(int** puzzle)
{
    int i,j;
    for (i = 0; i < PUZZLE_SIZE; i++)
    {
        for (j = 0; j < PUZZLE_SIZE; j++)
        {
            printf("%d ", puzzle[i][j]);
        }

        printf("\n");
    }
}


int main(int ac, char** av)
{
    int** puzzle = setupPuzzle();

    rowContains(puzzle, 0, 0);
    printPuzzle(puzzle);
    printf("RESULTS\n");
    backtrack(puzzle);
    printPuzzle(puzzle);

    return 0;
}
