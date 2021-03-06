#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "game.h"
#include "rendering.h"


const SDL_Color GRID_COLOR = {.r = 255, .g = 255, .b = 255};

void renderGrid(SDL_Renderer *renderer /*, const SDL_Color * color */){
    
    SDL_SetRenderDrawColor(renderer, 64, 64, 64, 255);
    
    // Draw vertical and horizontal lines to form the grid
    for (int i = 1; i < CELL_AMOUNT; ++i) {

        SDL_RenderDrawLine(renderer,
                           i * GRID_SIZE, 0,
                           i * GRID_SIZE, GRID_SIZE * CELL_AMOUNT);
        SDL_RenderDrawLine(renderer,
                           0,   i * GRID_SIZE,
                           GRID_SIZE * CELL_AMOUNT, i * GRID_SIZE);
    }
}

void renderState(SDL_Renderer *renderer, unsigned int x, unsigned int y, bool state){

    const float center_x = GRID_SIZE * 0.5 + y * GRID_SIZE;
    const float center_y = GRID_SIZE * 0.5 + x * GRID_SIZE;
    const float half_cell = GRID_SIZE * 0.5;
    Uint8 color;
    // White when alive, black when dead
    if (state) {
        color = 255;
    } else {
        color = 0;
    }

    // Draw filled box for a cell
    boxRGBA(renderer, center_x - half_cell, // +1
                    center_y - half_cell, // +1
                    center_x + half_cell, // -1
                    center_y + half_cell, // -1
                    color, color, color, 255);
}

// Render cells
void renderCells(SDL_Renderer *renderer, const game_t *game  /*, unsigned int x, unsigned int y */){

    for (int i = 0; i < CELL_AMOUNT; i++){
        for (int j = 0; j < CELL_AMOUNT; j++){

            // Get first bit of cell to determine cell_state (dead/alive)
            Uint8 cell_state = 0x01 & game->cell_map2[i * CELL_AMOUNT + j];
            switch(cell_state)
            {
            case DEAD:
                renderState(renderer, i, j, 0);
                break;
            case ALIVE:
                renderState(renderer, i, j, 1);
                break;
            default: {}
                break;
            }
        }
    }
}

void renderRunningState(SDL_Renderer *renderer, const game_t *game, bool state) {
    renderCells(renderer, game);
    // If game isn't free running, draw grid
    if (!state){
        renderGrid(renderer /*, &GRID_COLOR*/ );
    }
}