/**
* @file     result.c
* @brief    ��Ӯ�ж��ļ�
* @details  �õ���������Ӯ���
*/

#include "result.h"

/**
 * @brief �õ����̵���Ӯ���
 * @param[in] state    ���̶���ָ��
 * @param[in] x_row    ���ӵ�������ָ��
 * @param[in] y_column ���ӵ�������ָ��
 * @param[in] order    ���巽
 * @retval none û�н��
 * @retval black �ڷ�Ӯ
 * @retval white �׷�Ӯ
 */
CHESSSTATE GetResult(CHESSSTATE **state, char x_row, char y_column, CHESSSTATE order) {
    int i, j, x, y, flag;

    //'-'���ŷ���Ӯ
    x = x_row ;            //��ȡ����������Ŀ�ʼѭ������
    y = y_column - 4;      //x����; y����;
    flag = 0;
    for(i = 0; i < 9; y++, i++){
        if(y < 0 || y >= COLUMN) //��������������
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

    //'|'���ŷ���Ӯ
    x = x_row - 4;     //��ȡ����������Ŀ�ʼѭ������
    y = y_column;      //x����; y����;
    flag = 0;
    for(i = 0; i < 9; x++, i++){
        if(x < 0 || x >= ROW) //��������������
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

    //'/'б�ܷ���Ӯ
    x = x_row - 4;     //��ȡ����������Ŀ�ʼѭ������
    y = y_column + 4;  //x����; y����;
    flag = 0;
    for(i = 0; i < 9; x++, y--, i++){
        if(x < 0 || x >= ROW || y < 0 || y >= COLUMN) //��������������
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

    //'\'б�ܷ���Ӯ
    x = x_row - 4;     //��ȡ����������Ŀ�ʼѭ������
    y = y_column - 4;  //x����; y����;
    flag = 0;
    for(i = 0; i < 9; x++, y++, i++){
        if(x < 0 || x >= ROW || y < 0 || y >= COLUMN) //��������������
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
