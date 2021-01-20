/**
* @file     display.c
* @brief    显示棋盘文件
* @details  在终端显示棋盘信息
*/

#include "display.h"

/**
 * @brief   动态分配数组的棋盘显示
 * @param[in] state    棋盘二级指针
 * @param[in] row      棋盘的行
 * @param[in] column   棋盘的列
 */
void draw(CHESSSTATE **state, int row, int column){
	system("cls"); //清屏
	int i,j;
	printf("  ");
	for (i = 0; i < column; i++)      //画列序号
		printf("%c ", (char)(i+65));
    printf("\n");
	for (i = 0; i < row; i++) {
		printf("%c ", (char)(i+65));  //画行序号
		for (j = 0; j < column; j++) {
			switch(state[i][j]){
				case 0:               //画棋盘
					if (j > 0 && j < column-1)
						printf("%s", (i == 0 ? TOP_CENTER : i == row-1? BOTTOM_CENTER : INTERNAL));
					else if (j == 0)
						printf("%s", (i == 0 ? LEFT_TOP : i == row-1 ? LEFT_BOTTOM : LEFT_CENTER));
					else if(j == column-1)
						printf("%s", (i == 0 ? RIGHT_TOP : i == row-1 ? RIGHT_BOTTOM : RIGHT_CENTER));
					break;
				case 1:               //画黑棋
					printf("%s", BLACK);
					break;
				case 2:               //画白棋
					printf("%s", WHITE);
					break;
				default:
					break;
			}
		}
		printf("\n");
	}
}

/**
 * @brief   静态分配数组的棋盘显示
 * @param[in] state    棋盘二级指针
 * @param[in] row      棋盘的行
 * @param[in] column   棋盘的列
 */
void StaticDraw(CHESSSTATE (*state)[COLUMN], int row, int column){
	int i,j;
	printf("  ");
	for (i = 0; i < column; i++)      //画列序号
		printf("%c ", (char)(i+'0'));
    printf("\n");
	for (i = 0; i < row; i++) {
		printf("%c ", (char)(i+'0'));  //画行序号
		for (j = 0; j < column; j++) {
			switch(state[i][j]){
				case 0:               //画棋盘
					if (j > 0 && j < column-1)
						printf("%s", (i == 0 ? TOP_CENTER : i == row-1? BOTTOM_CENTER : INTERNAL));
					else if (j == 0)
						printf("%s", (i == 0 ? LEFT_TOP : i == row-1 ? LEFT_BOTTOM : LEFT_CENTER));
					else if(j == column-1)
						printf("%s", (i == 0 ? RIGHT_TOP : i == row-1 ? RIGHT_BOTTOM : RIGHT_CENTER));
					break;
				case 1:               //画黑棋
					printf("%s", BLACK);
					break;
				case 2:               //画白棋
					printf("%s", WHITE);
					break;
				default:
					break;
			}
		}
		printf("\n");
	}
}
