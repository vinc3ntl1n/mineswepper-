#ifndef MINESWEEPER_MINESWEEPER_H
#define MINESWEEPER_MINESWEEPER_H

#include "Toolbox.h"
#include "GameState.h" // Include the GameState header file

// Update the instance reference to match the instance in your code
extern Toolbox& tools;

int launch();
void restart();
void render();
void toggleDebugMode();
bool getDebugMode();

#endif //MINESWEEPER_MINESWEEPER_H
