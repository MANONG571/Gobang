/**
* @file     main.c
* @brief    项目主函数文件
* @details  主要包含协议应用栈程序框架，main函数入口
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chess.h"
#include "display.h"
#include "move.h"
#include "result.h"
#include "rules.h"
#include "machine.h"

void Display(void);
void HumanMode(CHESSSTATE **board, char *x_row, char *y_column);
void MachineMode(CHESSSTATE **board, char *x_row, char *y_column, char option);

int main() {
	int i, j;                   //check:禁手检查; count:落子数
	char x_chess = 0, y_chess = 0, option;        //x_chess:落子的行坐标; y_chess:落子的列坐标; option:玩家输入选择选项
	char *x_row = &x_chess, *y_column = &y_chess; //*x_row:指向落子的行坐标; *y_column:指向落子的列坐标;
	CHESSSTATE **board;               //棋盘二级指针

	board = malloc(sizeof(CHESSSTATE*)*ROW); //分配第一列内存
	for(i = 0; i < ROW; i++)                 //分配第一列的每行内存
		board[i] = malloc(sizeof(CHESSSTATE)*COLUMN);
	for(i = 0; i < ROW; i++)                //初始化为0
        for(j = 0;j < COLUMN; j++)
            board[i][j] = none;

    Display(); //显示开头界面
    while(1){  //选择模式
        fflush(stdin);
        scanf("%c",&option);
        if(option == 'A' || option == 'B'){
            break;
        }
        printf("输入选项错误，请重新输入:");
    }

    if(option == 'A'){ //人人模式
        HumanMode(board, x_row, y_column);
    }
    else{              //人机模式
        printf("人机模式已选择，请选择下棋方: \n");
        printf("A:先手黑棋(有禁手限制) B:后手白棋 \n");
        while(1){  //选择人机模式中的先后手
            fflush(stdin);
            scanf("%c",&option);
            if(option == 'A' || option == 'B'){
                break;
            }
            printf("输入选项错误，请重新输入:");
        }
        MachineMode(board, x_row, y_column, option);
    }

	system("pause");

	for(i = 0; i < ROW; i++)  //释放内存
		free(board[i]);
	free(board);

	return 0;
}

/**
 * @brief      开头规则显示
 * @retval     无
 */
void Display(void){
    printf("五子棋(Gobang)，游戏规则：\n");
    printf("1. 黑方先下，白方后下 \n");
    printf("2. 黑方有三三禁手、四四禁手、长连禁手规则 \n");
    printf("3. 五连的优先级大于禁手规则 \n");
    printf("4. 三三禁手不包括假活三的情况 \n");
    printf("输入选择模式：A:人人模式 B:人机模式 \n");
}

/**
 * @brief      人人模式
 * @param[in]  **board    棋盘二级指针
 * @param[in]  *x_row     行坐标指针地址
 * @param[in]  *y_column  列坐标指针地址
 * @retval     无
 */
void HumanMode(CHESSSTATE **board, char *x_row, char *y_column){
    CHESSSTATE result, order = black;
    int check, count = 0;
    draw(board, ROW, COLUMN);              //重新画棋盘
    while(1)
	{
	    playermove(board, x_row, y_column, order); //下棋方下棋
        draw(board, ROW, COLUMN);              //重新画棋盘
        //printf("刚下的棋:%c%c\n", *x_row, *y_column);

        result = GetResult(board, *x_row, *y_column, order); //获取结果
        if(black == result) {
            printf("游戏结束，黑方获胜！\n");
            break;
        }else if(white == result) {
            printf("游戏结束，白方获胜！\n");
            break;
        }

        check = BanMove(board, *x_row, *y_column);   //获取禁手规则结果
        if(3 == check) {
            printf("长连禁手, 白方获胜！\n");
            break;
        }else if(1 == check) {
            printf("三三禁手, 白方获胜！\n");
            break;
        }else if(2 == check) {
            printf("四四禁手, 白方获胜！\n");
            break;
        }

        count++;          //落子数加1
        if(225 == count){ //若落子数等于棋盘子数, 平局
            printf("游戏结束，平局！\n");
            break;
        }
        order = (order==black ? white : black); //更换下棋方
	}
}

/**
 * @brief      人机模式
 * @param[in]  **board    棋盘二级指针
 * @param[in]  *x_row     行坐标指针地址
 * @param[in]  *y_column  列坐标指针地址
 * @param[in]  option     输入选项， A:玩家先下 B:电脑先下
 * @retval     无
 */
void MachineMode(CHESSSTATE **board, char *x_row, char *y_column, char option){
    int check, count = 0;

    if(option == 'A'){ //玩家黑棋, 电脑白棋
        draw(board, ROW, COLUMN);               //画棋盘
        while(1){
            playermove(board, x_row, y_column, black); //玩家下黑棋
            draw(board, ROW, COLUMN);                  //重新画棋盘
            if(black == GetResult(board, *x_row, *y_column, black)) { //获取结果
                printf("游戏结束，黑方获胜！\n");
                break;
            }
            check = BanMove(board, *x_row, *y_column);   //获取禁手规则结果
            if(3 == check) {
                printf("长连禁手, 白方获胜！\n");
                break;
            }else if(1 == check) {
                printf("三三禁手, 白方获胜！\n");
                break;
            }else if(2 == check) {
                printf("四四禁手, 白方获胜！\n");
                break;
            }

            count++;          //落子数加1
            if(225 == count){ //若落子数等于棋盘子数, 平局
                printf("游戏结束，平局！\n");
                break;
            }

            MachinePlay(board, x_row, y_column, white); //电脑下白棋
            draw(board, ROW, COLUMN);                //重新画棋盘
            printf("电脑下棋:%c%c \n", *x_row + 'A', *y_column + 'A');

            if(white == GetResult(board, *x_row, *y_column, white)) {//获取结果
                printf("游戏结束，白方获胜！\n");
                break;
            }
            count++;          //落子数加1
        }
    }
    else{              //玩家白棋, 电脑黑棋
        board[6][6] = black;  //电脑第一次下,直接下中间
        count++;          //落子数加1
        draw(board, ROW, COLUMN);                  //重新画棋盘
        while(1){
            playermove(board, x_row, y_column, white); //玩家下白棋
            draw(board, ROW, COLUMN);                  //重新画棋盘
            if(white == GetResult(board, *x_row, *y_column, white)) { //获取结果
                printf("游戏结束，白方获胜！\n");
                break;
            }
            count++;          //落子数加1

            MachinePlay(board, x_row, y_column, black); //电脑下黑棋
            draw(board, ROW, COLUMN);                   //重新画棋盘
            printf("电脑下棋:%c%c \n", *x_row + 'A', *y_column + 'A');
            if(black == GetResult(board, *x_row, *y_column, black)) { //获取结果
                printf("游戏结束，黑方获胜！\n");
                break;
            }
            count++;          //落子数加1
            if(225 == count){ //若落子数等于棋盘子数, 平局
                printf("游戏结束，平局！\n");
                break;
            }
        }
    }
}
