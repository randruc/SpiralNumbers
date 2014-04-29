#include <stdio.h>
#include <stdlib.h>

#define RightAndDown 0
#define LeftAndUp ~ RightAndDown

/* Print the grid */
void print_grid(int **grid, int grid_width)
{
  int i, j;

  for(i = 0; i < grid_width; i++) {
    fprintf(stdout, "|");
    for(j = 0; j < grid_width; j++) {
      fprintf(stdout, "%3d|", grid[i][j]);
    }
    fprintf(stdout, "\n");
  }
  fprintf(stdout, "\n");
}

/* Dynamically allocate new grid */
int **alloc_grid(int width)
{
  int i;
  
  int **grid = malloc(width * sizeof(int*));  
  
  if(grid == NULL) {
    fprintf(stderr, "Allocation error!\n");
    exit(EXIT_FAILURE);
  }

  for(i = 0; i < width; i++) {
    grid[i] = malloc(width * sizeof(int));

    if(grid[i] == NULL) {
      fprintf(stderr, "Allocation error!\n");
      exit(EXIT_FAILURE);
    }
  }

  return grid;
}

/* Free allocated grid */
void free_grid(int **grid, int width) {
  int i;

  for(i = 0; i < width; i++) {
    free(grid[i]);
  }

  free(grid);
}

/* Write the quarter corresponding to the current width */
void write_quarter(int **grid, int width, int direction)
{
  int i;  
  static int current_counter = 1;

  /* Current position in the grid */
  static int x = 0;
  static int y = -1;

  for(i = 0; i < width; i++) {
    if(direction == RightAndDown) {
      grid[x][++y] = current_counter++;
    } else {
      grid[x][--y] = current_counter++;
    }
  }

  for(i = 0; i < width - 1; i++) {
    if(direction == RightAndDown) {
      grid[++x][y] = current_counter++;
    } else {
      grid[--x][y] = current_counter++;
    }
  }
  
}

int main(int argc, char *argv[])
{
  int **grid; 

  int initial_width = atoi(argv[1]);
  int width = initial_width;
  int direction = RightAndDown;    

  grid = alloc_grid(width);
  
  while(width > 0) {
    write_quarter(grid, width, direction);
    direction = ~ direction;
    width--;
  }
  
  print_grid(grid, initial_width);
  free_grid(grid, initial_width);                  

  return EXIT_SUCCESS;
}
