/**
* @file     result.c
* @brief    输赢判断文件
* @details  得到棋盘上输赢情况
*/

#include "result.h"

/**
 * @brief 得到棋盘的输赢结果
 * @param[in] state    棋盘二级指针
 * @param[in] x_row    落子的行坐标指针
 * @param[in] y_column 落子的列坐标指针
 * @param[in] order    下棋方
 * @retval none 没有结果
 * @retval black 黑方赢
 * @retval white 白方赢
 */
CHESSSTATE GetResult(CHESSSTATE **state, char x_row, char y_column, CHESSSTATE order) {
    int i, j, x, y, flag;

    //'-'横着方向赢
    x = x_row ;            //获取刚下棋坐标的开始循环坐标
    y = y_column - 4;      //x是行; y是列;
    flag = 0;
    for(i = 0; i < 9; y++, i++){
        if(y < 0 || y >= COLUMN) //超出棋盘则跳出
            continue;
        if(state[x][y] == order){
            flag++;
        }
        else if(flag >= 5){
            break;
        }
        else{
            flag = 0;
        }
    }
    if((white == order && flag >= 5) || (black == order && flag == 5))
        return order;

    //'|'竖着方向赢
    x = x_row - 4;     //获取刚下棋坐标的开始循环坐标
    y = y_column;      //x是行; y是列;
    flag = 0;
    for(i = 0; i < 9; x++, i++){
        if(x < 0 || x >= ROW) //超出棋盘则跳出
            continue;
        if(state[x][y] == order){
            flag++;
        }
        else if(flag >= 5){
            break;
        }
        else{
            flag = 0;
        }
    }
    if((white == order && flag >= 5) || (black == order && flag == 5))
        return order;

    //'/'斜杠方向赢
    x = x_row - 4;     //获取刚下棋坐标的开始循环坐标
    y = y_column + 4;  //x是行; y是列;
    flag = 0;
    for(i = 0; i < 9; x++, y--, i++){
        if(x < 0 || x >= ROW || y < 0 || y >= COLUMN) //超出棋盘则跳出
            continue;
        if(state[x][y] == order){
            flag++;
        }
        else if(flag >= 5){
            break;
        }
        else{
            flag = 0;
        }
    }
    if((white == order && flag >= 5) || (black == order && flag == 5))
        return order;

    //'\'斜杠方向赢
    x = x_row - 4;     //获取刚下棋坐标的开始循环坐标
    y = y_column - 4;  //x是行; y是列;
    flag = 0;
    for(i = 0; i < 9; x++, y++, i++){
        if(x < 0 || x >= ROW || y < 0 || y >= COLUMN) //超出棋盘则跳出
            continue;
        if(state[x][y] == order){
            flag++;
        }
        else if(flag >= 5){
            break;
        }
        else{
            flag = 0;
        }
    }
    if((white == order && flag >= 5) || (black == order && flag == 5))
        return order;

    return none;
}
