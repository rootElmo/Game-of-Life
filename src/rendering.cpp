#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "game.h"
#include "rendering.h"


const SDL_Color GRID_COLOR = {.r = 255, .g = 255, .b = 255};

void renderGrid(SDL_Renderer *renderer /*, const SDL_Color * color */){
    // Get color from a constant later,
    // hardcoded for now
    SDL_SetRenderDrawColor(renderer, 64, 64, 64, 255);
    // std::cout << "Render grid called" << std::endl;
    
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
    // Check the "math" here before testing

    //std::cout << "Render one cell called" << std::endl;

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

    // Compile error, since I haven't put the lib in the command
    // Investigate on how to include the sdl2_gfx primitives
    // Time to make a Makefile? Or something similiar?
    // ^^^^^ pkg-config --list-all | grep *keyword*
    // ^^^^^ to search for libraries to include.

    // Draw filled box
    boxRGBA(renderer, center_x - half_cell, // +1
                    center_y - half_cell, // +1
                    center_x + half_cell, // -1
                    center_y + half_cell, // -1
                    color, color, color, 255);
}

// Render cells from cellmap :)
// Change function name later to sometihng like "renderMap" etc.
void renderCells(SDL_Renderer *renderer, const game_t *game  /*, unsigned int x, unsigned int y */){
    // for loops for x & y
    // Render ACTUAL shapes here or do it in another function?

    // ^^^ Render in another function, where calculations for the rendered
    // cell's coordinates are made. 

    for (int i = 0; i < CELL_AMOUNT; i++){
        for (int j = 0; j < CELL_AMOUNT; j++){

            // Why use switch since it's a boolean array??
            // FIX
            // JUST CALL THE FUNCTION AND PUT game->cell_map[foo]
            // IN THE state PARAMETER OF THE renderState FUNCTION CALL
            // dumb dumb coding right here
            switch (game->cell_map[i * CELL_AMOUNT + j])
            {
            case DEAD:
                // RENDER BLACK (DEAD) CELL
                // renderDeadOrAlive(renderer, row, col, state)
                renderState(renderer, i, j, 0);
                break;
            case ALIVE:
                // RENDER WHITE (WHITE) CELL
                // renderDeadOrAlive(renderer, row, col, state)
                renderState(renderer, i, j, 1);
                break;
            default: {}
                break;
            }
        }
    }
}

void renderRunningState(SDL_Renderer *renderer, const game_t *game) {
    // Render grid on top off cells at initial state
    // Don't render grid, when state != initial state
    renderCells(renderer, game);
    renderGrid(renderer /*, &GRID_COLOR*/ );
    
}

void renderGame(SDL_Renderer *renderer, const game_t *game){
    renderRunningState(renderer, game);
}