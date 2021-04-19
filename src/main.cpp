#include <iostream>
#include <SDL2/SDL.h>
#include "game.h"
#include "rendering.h"
#include "logic.h"

// Automatic generation iteration delay in milliseconds
#define TICK_RATE 50

bool is_running = false;
// Free running determines is generations
// are iterated through automatically (1),
// or per user input (0)
bool free_runnning = false;
unsigned int prev_time = 0;
unsigned int current_time;


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

    // Check if window init was ok
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
    
    if (renderer == NULL){
        std::cout << "Renderer init failed." << std::endl << SDL_GetError();
        is_running = false;
    } else {
        is_running = true;
    }

    game_t game = {
        .cell_map2 = {}
    };

    SDL_Event e;

    // Main event loop
    while (is_running)
    {   
        if (free_runnning){
            // Get milliseconds since SDL was initialized
            // Quick and dirty timer, but doesn't freeze the whole
            // thing like SDL_Delay();
            current_time = SDL_GetTicks();
            if (current_time > (prev_time + TICK_RATE)) {
                nextGen(&game);
                prev_time = current_time;
            }
            
        }
        // Poll events
        if (SDL_PollEvent(&e)){
            switch (e.type)
            {
            case SDL_QUIT:
                // Quit event loop
                std::cout << "Quit event." << std::endl;
                is_running = false;
                break;
            case SDL_MOUSEBUTTONDOWN:{
                // Get mouse click coordinates & print them.
                // Later check coordinates against cell and toggle alive/dead.
                if (free_runnning){
                    break;
                }
                unsigned int click_x = e.button.x / GRID_SIZE;
                unsigned int click_y = e.button.y / GRID_SIZE;
                clickOnCell(&game, click_x, click_y);
                std::cout << "Clicked at width: " << click_x << ", height: " << click_y << std::endl;
                }
                break;
            case SDL_KEYDOWN:{
                switch (e.key.keysym.sym)
                {
                case SDLK_RIGHT:
                    // Generation++
                    if (free_runnning){
                        break;
                    }
                    nextGen(&game);
                    break;
                case SDLK_SPACE:
                    // tried free_running != free_running here,
                    // didn't work for some reason?
                    // Try to simplify the if-loop
                    if (free_runnning){
                        free_runnning = false;
                        std::cout << "Automatic iteration stopped" << std::endl;;
                    } else {
                        free_runnning = true;
                        std::cout << "Automatic iteration started" << std::endl;;
                    }
                    break;
                case SDLK_r: // Reset cell_map on R-press
                    for (int i = 0; i < CELL_AMOUNT * CELL_AMOUNT; i++){
                        game.cell_map2[i] = 0;
                    }
                    std::cout << "Cells reset" << std::endl;
                    // Stop free running on cell map clearing
                    free_runnning = false;
                    std::cout << "Automatic iteration stopped" << std::endl;;
                    break;
                default: {}
                    break;
                }
                break;
            }
            default:
                {}
                break;
            }
        }

        // Render screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        renderRunningState(renderer, &game, free_runnning);
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