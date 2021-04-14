#include <iostream>
#include "game.h"
#include "logic.h"

void printCellMap(game_t *game){
    /*
    for (int i = 0; i < CELL_AMOUNT; i++) {
        for (int j = 0; j < CELL_AMOUNT; j++) {
            std::cout << game->cell_map[i + j]; // not working correctly. 
        }
        // std::cout << std::endl;
        std::cout << " ";
    }
    std::cout << std::endl;
    */
    // Is the print flipped or values assign in a wrong way?
    // Dumb dumb print function, make a better one
    for(int i = 0; i < (CELL_AMOUNT * CELL_AMOUNT); i++){
        std::cout << game->cell_map[i];
    }
    std::cout << std::endl;

}

// Toggles cell alive/dead
// (game, x coord, y coord)
void toggleCell(game_t *game, unsigned int row, unsigned int col){

    // Toggle cell state
    
    game->cell_map[col * CELL_AMOUNT + row] = !game->cell_map[col * CELL_AMOUNT + row];

    /*  Check to see if there's a better way to do the thing below
        Basically, flips the first bit of the byte, which indicates
        cell state (dead/alive)
        if (game->cell_map[col * CELL_AMOUNT + row] & 0x01 == 1){
            game->cell_map[col * CELL_AMOUNT + row] |= 0x00
        } else {
            game->cell_map[col * CELL_AMOUNT + row] |= 0x01
        }
    */

    // OLD FUNCTION:
    // game->cell_map[row * GRID_SIZE + col] = !(game->cell_map[row * GRID_SIZE + col]);
    // GRID_SIZE should be CELL_AMOUNT!!!
}

// Function for setting a cell to alive state
// Also updates the states of neighbouting cells
// Adapted from https://github.com/armytricks/GameOfLife/blob/master/GameOfLifeSimulation/main.cpp
/*
void setCell(game_t *game, unsigned int x, unsigned int y){
    unsigned int w = CELL_AMOUNT;
    unsigned int h = CELL_AMOUNT;
    int x_left, x_right, y_left, y_right;
    unsigned char *cell_ptr = game->cell_map[(y * w) + x];

    if (foo)   then              else
    (condition) ? expression true : expression false

    x_left = (x == 0) ? w - 1 : -1;
}

*/

void clickOnCell(game_t *game, unsigned int row, unsigned int col){
    toggleCell(game, row, col);
}

