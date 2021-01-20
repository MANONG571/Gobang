#ifndef __DISPLAY_H
#define __DISPLAY_H

#include <stdio.h>
#include "chess.h"

void draw(CHESSSTATE **state, int row, int column);
void StaticDraw(CHESSSTATE (*state)[COLUMN], int row, int column);

#endif // __DISPLAY_H
