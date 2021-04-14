// CELL & SCREEN DEFINITIONS
#define GRID_SIZE 10 // CHANGE TO CELL_SIZE later (determines height and width of grid, hardcoded for now, user input later)
#define CELL_AMOUNT 40 // number of cells
// CELL STATES
#define DEAD 0 
#define ALIVE 1


typedef struct {
    // Only boolean array needed for dead/alive state
    // Change to Uint8 map where
    // xxxx0000; x = number of neighbouring cells that are alive
    // 0000000y; y = current state of cell (dead/alive) 
    bool cell_map[CELL_AMOUNT * CELL_AMOUNT];
    // char cell_map[CELL_AMOUNT * CELL_AMOUNT];

} game_t;