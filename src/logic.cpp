#include <iostream>
#include "game.h"
#include "logic.h"
#include <cstring>

void printCellMap(game_t *game){
    // Is the print flipped or values assign in a wrong way?
    // Dumb dumb print function, make a better one
    // ^^ Do we even need a print function for debugging?
    // when CELL_AMOUNT >= 10 the print is absurdly long
    int print_counter = 0;
    for(int i = 0; i < (CELL_AMOUNT * CELL_AMOUNT); i++){
        std::cout << (0x01 & game->cell_map2[i]);
        print_counter++;
        if (print_counter == CELL_AMOUNT){
            print_counter = 0;
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}

void setCell(game_t *game, unsigned int row, unsigned int col){
    // Adapted from https://github.com/armytricks/GameOfLife/blob/master/GameOfLifeSimulation/main.cpp
    // Only toggle cell state for now
    //x = row, y = col

    int xoleft, xoright, yoabove, yobelow;
    // Calculate offsets to other cells

    xoleft = (row == 0) ? CELL_AMOUNT - 1 : -1;
	xoright = (row == (CELL_AMOUNT - 1)) ? -(CELL_AMOUNT - 1) : 1;
	yoabove = (col == 0) ? (CELL_AMOUNT * CELL_AMOUNT) - CELL_AMOUNT : -CELL_AMOUNT;
	yobelow = (col == (CELL_AMOUNT - 1)) ? -((CELL_AMOUNT * CELL_AMOUNT) - CELL_AMOUNT) : CELL_AMOUNT;

    game->cell_map2[col * CELL_AMOUNT + row] |= 0x01;

    // Update neighbour state count for neighbouring cells
    // Really messy looking/hard to read. Figure a way to use a pointer for
    // game->cell_map2[cell] later.
    game->cell_map2[(col * CELL_AMOUNT + row) + yoabove + xoleft] += 0x02; // numpad 1
	game->cell_map2[(col * CELL_AMOUNT + row) + yoabove] += 0x02; // numpad 2
	game->cell_map2[(col * CELL_AMOUNT + row) + yoabove + xoright] += 0x02; // numpad 3
	game->cell_map2[(col * CELL_AMOUNT + row) + xoleft] += 0x02; // numpad 4
	game->cell_map2[(col * CELL_AMOUNT + row) + xoright] += 0x02; // numpad 6
	game->cell_map2[(col * CELL_AMOUNT + row) + yobelow + xoleft] += 0x02; // numpad 7
	game->cell_map2[(col * CELL_AMOUNT + row) + yobelow] += 0x02; // numpad 8
	game->cell_map2[(col * CELL_AMOUNT + row) + yobelow + xoright] += 0x02; // numpad 9
}

void clearCell(game_t *game, unsigned int row, unsigned int col){
    // Adapted from https://github.com/armytricks/GameOfLife/blob/master/GameOfLifeSimulation/main.cpp
    // Only toggle cell state for now

    int xoleft, xoright, yoabove, yobelow;
    // Calculate offsets to other cells
    // (check the math here)
    
    xoleft = (row == 0) ? CELL_AMOUNT - 1 : -1;
	xoright = (row == (CELL_AMOUNT - 1)) ? -(CELL_AMOUNT - 1) : 1;
	yoabove = (col == 0) ? (CELL_AMOUNT * CELL_AMOUNT) - CELL_AMOUNT : -CELL_AMOUNT;
	yobelow = (col == (CELL_AMOUNT - 1)) ? -((CELL_AMOUNT * CELL_AMOUNT) - CELL_AMOUNT) : CELL_AMOUNT;
    
    game->cell_map2[col * CELL_AMOUNT + row] &= ~0x01;

    // Update neighbour state count for neighbouring cells
    game->cell_map2[(col * CELL_AMOUNT + row) + yoabove + xoleft] -= 0x02;
	game->cell_map2[(col * CELL_AMOUNT + row) + yoabove] -= 0x02;
	game->cell_map2[(col * CELL_AMOUNT + row) + yoabove + xoright] -= 0x02;
	game->cell_map2[(col * CELL_AMOUNT + row) + xoleft] -= 0x02;
	game->cell_map2[(col * CELL_AMOUNT + row) + xoright] -= 0x02;
	game->cell_map2[(col * CELL_AMOUNT + row) + yobelow + xoleft] -= 0x02;
	game->cell_map2[(col * CELL_AMOUNT + row) + yobelow] -= 0x02;
	game->cell_map2[(col * CELL_AMOUNT + row) + yobelow + xoright] -= 0x02;
}

void clickOnCell(game_t *game, unsigned int row, unsigned int col){
    // Toggle cell on if dead/toggle cell off if alive
    if (0x01 & game->cell_map2[col * CELL_AMOUNT + row]){
        clearCell(game, row, col);
    } else {
        setCell(game, row, col);
    }
}

void nextGen(game_t *game){
    unsigned int x, y, count;
    int cell_pos = 0;

    std::memcpy(game->cell_map_temp, game->cell_map2, CELL_AMOUNT * CELL_AMOUNT);

    for (int col = 0; col < CELL_AMOUNT; col++){
        // std::cout << "Col scanning for next gen" << std::endl;
        for (int row = 0; row < CELL_AMOUNT; row++){
            count = game->cell_map_temp[(col * CELL_AMOUNT) + row] >> 1;
            if((0x01 & game->cell_map_temp[(col * CELL_AMOUNT) + row]) == 1){
                if ((count != 2) && (count != 3)){
                    clearCell(game, row, col);
                } 
            } else {
                if (count == 3) {
                    setCell(game, row, col);
                }
            }
        }
    }

    /*
    for (y = 0; y < CELL_AMOUNT; y++){
        x = 0;
        do {
            while(game->cell_map_temp[cell_pos] == 0) {
                cell_pos++;
                if (x++ > CELL_AMOUNT) goto RowDone2;
            }
            count = game->cell_map_temp[cell_pos] >> 1;
            if ((0x01 & game->cell_map_temp[cell_pos]) == 1) {
                if ((count != 2) && (count != 3)) {
                    clearCell(game, x, y);
                }
            } else {
                if (count == 3) {
                    setCell(game, x, y);
                }
            }
            cell_pos++;
        } while (x++ < CELL_AMOUNT);
        RowDone2:;
    }
    */
}