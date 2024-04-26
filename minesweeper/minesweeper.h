#ifndef MINESWEEPER_MINESWEEPER_H
#define MINESWEEPER_MINESWEEPER_H

#include "Toolbox.h"
extern Toolbox instance;
int launch();
void restart();
void render();
void toggleDebugMode();
bool getDebugMode();

#endif //MINESWEEPER_MINESWEEPER_H
