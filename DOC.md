# Documentation

## Rules of the game

**Conway's Game of Life's** ruleset is fairly basic at its core. A "cellular map" of a certain width and height exists, in which there are either alive or dead cells. The state of the cells is determined by the state of their neighbouring cells. The rules for determining a cell's state are as follows:

 * If the cell is **alive** and has **2 or 3** alive neighbours, the cell will remain alive.
 * If the cell is **alive** and has either **less than 2** or **more than 3** alive neighbours, the cell will die.
 * If the cell is **dead** and has **exactly 3** alive neighbours, the cell will turn alive.

## Features

For this assignment I was asked to implement the following features:

 1. "Board" in which the cells would exist. The board would be sized N * N and the user/player could adjust this.
 2. The game could be progressed automatically, or in steps.
 3. The game should run on a Linux operating system.

Of the three main features I was able to implement numbers **2** and **3**. As for **1**, the board size can be adjusted in [game.h](./src/game.h), by changing the **CELL_AMOUNT** value. More on that in the **comments**.

For the generation iteration logic, and cell setting logic I used **JaffaCoder's** [excellent video](https://www.youtube.com/watch?v=ndAfWKmKF34) and the [project's source code](https://github.com/armytricks/GameOfLife/blob/master/GameOfLifeSimulation/main.cpp) as a reference.

When the game looks at cell states, the offsets to other cells are calculated in a way, which "wraps" around the screen. This allows for the game to run indefinitely in theory. Main bulk of the game's logic can be found [here.](./src/logic.cpp)

For rendering the game I used [**SDL2**](https://www.libsdl.org/). For reference I used [Tsoding's video](https://www.youtube.com/watch?v=gCVMkKgs3uQ). Even though the video implements a tic-tac-toe game, the rendering logic is pretty similiar.

The screen height and width are determined by the amount of cells, and the size of the cells in pixels. These parameters are **CELL_AMOUNT** and **GRID_SIZE**. The rendering logic can be found [here.](./src/rendering.cpp)

These two critical elements are brought together at [main.cpp](./src/main.cpp). The screen is drawn, the cell map and renderer are initialized, and the main event loop rolls if these are successful.

The event loop either runs the game automatically, or waits for the user's input to progress to a next generation of cells.

## Comments

I was very pleased on how the game turned out. I hadn't previously made anything with **C++** using a graphics library, since 98% of my experience with **C++** is with Arduino programming.

Things I would've like to achieve, but didn't have the time:

 * Pointers to **cell_map2** at **logic.cpp** for determining neighvbour alive count. I'm really not confident with pointers. Pointers would make the code alot more readable.
 * Getting user input to determine **board size**. This could've been done just reading user's input through **std::cin** and comparing that to min and max values for the **board** size. I would have to refactor the code to be able to create a dynamic **cell_map2[]** array at runtime.
 * Creating a PROPER timer for the automatic generation iteration. The current one will probably suffice for 99.999% of use cases. However, the value of **SDL_GetTicks()** wraps around at roughly 49 days of continuous running. Small chance to crash, but it's still a chance.

This I learned from this project:

 * Using an array as a "game board", by calculating offsets according to board height and width.
 * Rendering graphics. This I hadn't done before and it was fairly simple with **SDL2**
 * Reading user input (keyboard)

I've been wanting to try game programming without the use of a fancy 3D-engine for a while. Now I know got to do that, and can continue doing that.