#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

typedef int bool;

#define true 1
#define false 0

// the size of the puzzle
extern const int PUZZLE_SIZE;
bool rowContains(int** puzzle, int row, int value);
bool columnContains(int** puzzle, int column, int value);
bool blockContains(int** puzzle, int row, int column, int value);
