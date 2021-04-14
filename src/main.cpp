#include <iostream>
#include <SDL2/SDL.h>
#include "game.h"
#include "rendering.h"
#include "logic.h"

bool is_running = false;

int main(int argc, char *argv[]){

    // Search for a way to ask user for
    // amount of cells before everything
    // so that window's size can be determined by
    // the amount of cells (N x N)

    SDL_Init(SDL_INIT_VIDEO);
    // Create window, size determined by GRID_SIZE and CELL_AMOUNT
    SDL_Window *window = SDL_CreateWindow("Game of Life", 
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                GRID_SIZE * CELL_AMOUNT,
                                GRID_SIZE * CELL_AMOUNT,
                                SDL_WINDOW_SHOWN);

    // Check if window init was ok, set running state accordingly
    if (window == NULL){
        std::cout << "Window init failed." << std::endl << SDL_GetError();
        is_running = false;
    } else {
        is_running = true;
    }

    // Create renderer & check if init was ok
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 
                                                SDL_RENDERER_ACCELERATED /* |
                                                SDL_RENDERER_PRESENTVSYNC */);  
                                    // As with almost any game I've played,
                                    // turning Vsync off drastically improves
                                    // performance. Don't know why.
                                    // Investigate?
    
    if (renderer == NULL){
        std::cout << "Renderer init failed." << std::endl << SDL_GetError();
        is_running = false;
    } else {
        is_running = true;
    }

    game_t game = {
        .cell_map = {}
    };

    SDL_Event e;

    while (is_running)
    {
        // Poll events/main event loop
        if (SDL_PollEvent(&e)){
            switch (e.type)
            {
            case SDL_QUIT:
                // Quite event loop
                std::cout << "Quit event." << std::endl;
                is_running = false;
                break;
            case SDL_MOUSEBUTTONDOWN:{
                // Get mouse click coordinates & print them.
                // Later check coordinates against cell and toggle alive/dead.
                unsigned int click_x = e.button.x / GRID_SIZE;
                unsigned int click_y = e.button.y / GRID_SIZE;
                clickOnCell(&game, click_x, click_y);
                std::cout << "Clicked at width: " << click_x << ", height: " << click_y << std::endl;
                }
                break;
            case SDL_KEYDOWN:{
                printCellMap(&game);
                break;
            }
            default:
                {}
                break;
            }
        }
        // Function polling & rendering seem to be really slow
        // Try to find out why (it was Vsync)

        // Find out why exactly the functions,
        // apart from renderGame() need to be present in order
        // to render anything to the screen.
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        renderGame(renderer, &game);
        // SDL's render functions don't render straight to screen,
        // we need to render the scene from the backbuffer
        // using the below function
        SDL_RenderPresent(renderer);
    }
    // Free up resources allocated to window.
    SDL_DestroyWindow(window);
    SDL_Quit(); 
    return 0;
}