#include <new>
#define GRID_SIZE 10 // width and height of one cell in pixels
#define DEAD 0 
#define ALIVE 1
#define CELL_AMOUNT 50
const int length_in_bytes = CELL_AMOUNT * CELL_AMOUNT;

/*
For the user to be able to determine the board size
we would need a dynamic array for the cell_map[].
This can be done at runtime. This could be alot of work
to change the constants of the current implementation.
Investigate, see if there's enough time to do it.
*/

/*
unsigned char *cell_map;
unsigned char *temp_cell_map;

void createCellMap(){
    cell_map = new unsigned char[CELL_AMOUNT * CELL_AMOUNT];
    temp_cell_map = new unsigned char[CELL_AMOUNT * CELL_AMOUNT];
}

*/

typedef struct {
    // Single byte can be used with bit manipulation to
    // store dead/alive state, and the "alive neighbours"
    // count;
    // 000xxxxy; y = current state of cell (dead/alive)
    //           x = number of neighbouring cells that are alive
    // CELL_AMOUNT * CELL_AMOUNT
    
    unsigned char cell_map2[length_in_bytes];
    unsigned char cell_map_temp[length_in_bytes];
    
} game_t;