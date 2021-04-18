#ifndef LOGIC_H_
#define LOGIC_H_

void clickOnCell(game_t *game, unsigned int row, unsigned int col); // handle clicking on cell
void nextGen(game_t *game);
void printCellMap(game_t *game); // Print cellmap, on any KEYDOWN for now

#endif // LOGIC_H_