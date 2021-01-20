#ifndef __MACHINE_H
#define __MACHINE_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "chess.h"
#include "display.h"
#include "rules.h"
#include "result.h"

#define MACHINEDEEP  2   //电脑搜索深度
#define POSIINFI     268435455     //正无穷大
#define NEGAINFI     -268435455    //负无穷大

//博弈树结点
typedef struct {
    int score;
    int node_x;
    int node_y;
}Node;

void MachinePlay(CHESSSTATE **state, char *x_row, char *y_column, CHESSSTATE order);
int MaxMinSearch(CHESSSTATE (*state)[COLUMN], int deep, CHESSSTATE order, int MaxOrMin,int FirstOne, int AlphaBeta);
int JudgeChess(CHESSSTATE (*MachState)[COLUMN], int x_row, int y_column, CHESSSTATE order);
int GetScore(CHESSSTATE (*MachState)[COLUMN], CHESSSTATE order);
int StrBlackScore(char *temp);
int StrWhiteScore(char *temp);
int StrTime(char *mother, char *son);

#endif // __MACHINE_H
