#ifndef __RULES_H
#define __RULES_H

#include <stdio.h>
#include <string.h>
#include "chess.h"

int BanMove(CHESSSTATE **state, int x_row, int y_column);
int ThreeBan(CHESSSTATE **state, int x_row, int y_column);
int FourBan(CHESSSTATE **state, int x_row, int y_column);
int LongBan(CHESSSTATE **state, int x_row, int y_column);

#endif // __RULES_H
