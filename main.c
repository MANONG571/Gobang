/**
* @file     main.c
* @brief    ��Ŀ�������ļ�
* @details  ��Ҫ����Э��Ӧ��ջ�����ܣ�main�������
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
	int i, j;                   //check:���ּ��; count:������
	char x_chess = 0, y_chess = 0, option;        //x_chess:���ӵ�������; y_chess:���ӵ�������; option:�������ѡ��ѡ��
	char *x_row = &x_chess, *y_column = &y_chess; //*x_row:ָ�����ӵ�������; *y_column:ָ�����ӵ�������;
	CHESSSTATE **board;               //���̶���ָ��

	board = malloc(sizeof(CHESSSTATE*)*ROW); //�����һ���ڴ�
	for(i = 0; i < ROW; i++)                 //�����һ�е�ÿ���ڴ�
		board[i] = malloc(sizeof(CHESSSTATE)*COLUMN);
	for(i = 0; i < ROW; i++)                //��ʼ��Ϊ0
        for(j = 0;j < COLUMN; j++)
            board[i][j] = none;

    Display(); //��ʾ��ͷ����
    while(1){  //ѡ��ģʽ
        fflush(stdin);
        scanf("%c",&option);
        if(option == 'A' || option == 'B'){
            break;
        }
        printf("����ѡ���������������:");
    }

    if(option == 'A'){ //����ģʽ
        HumanMode(board, x_row, y_column);
    }
    else{              //�˻�ģʽ
        printf("�˻�ģʽ��ѡ����ѡ�����巽: \n");
        printf("A:���ֺ���(�н�������) B:���ְ��� \n");
        while(1){  //ѡ���˻�ģʽ�е��Ⱥ���
            fflush(stdin);
            scanf("%c",&option);
            if(option == 'A' || option == 'B'){
                break;
            }
            printf("����ѡ���������������:");
        }
        MachineMode(board, x_row, y_column, option);
    }

	system("pause");

	for(i = 0; i < ROW; i++)  //�ͷ��ڴ�
		free(board[i]);
	free(board);

	return 0;
}

/**
 * @brief      ��ͷ������ʾ
 * @retval     ��
 */
void Display(void){
    printf("������(Gobang)����Ϸ����\n");
    printf("1. �ڷ����£��׷����� \n");
    printf("2. �ڷ����������֡����Ľ��֡��������ֹ��� \n");
    printf("3. ���������ȼ����ڽ��ֹ��� \n");
    printf("4. �������ֲ������ٻ�������� \n");
    printf("����ѡ��ģʽ��A:����ģʽ B:�˻�ģʽ \n");
}

/**
 * @brief      ����ģʽ
 * @param[in]  **board    ���̶���ָ��
 * @param[in]  *x_row     ������ָ���ַ
 * @param[in]  *y_column  ������ָ���ַ
 * @retval     ��
 */
void HumanMode(CHESSSTATE **board, char *x_row, char *y_column){
    CHESSSTATE result, order = black;
    int check, count = 0;
    draw(board, ROW, COLUMN);              //���»�����
    while(1)
	{
	    playermove(board, x_row, y_column, order); //���巽����
        draw(board, ROW, COLUMN);              //���»�����
        //printf("���µ���:%c%c\n", *x_row, *y_column);

        result = GetResult(board, *x_row, *y_column, order); //��ȡ���
        if(black == result) {
            printf("��Ϸ�������ڷ���ʤ��\n");
            break;
        }else if(white == result) {
            printf("��Ϸ�������׷���ʤ��\n");
            break;
        }

        check = BanMove(board, *x_row, *y_column);   //��ȡ���ֹ�����
        if(3 == check) {
            printf("��������, �׷���ʤ��\n");
            break;
        }else if(1 == check) {
            printf("��������, �׷���ʤ��\n");
            break;
        }else if(2 == check) {
            printf("���Ľ���, �׷���ʤ��\n");
            break;
        }

        count++;          //��������1
        if(225 == count){ //��������������������, ƽ��
            printf("��Ϸ������ƽ�֣�\n");
            break;
        }
        order = (order==black ? white : black); //�������巽
	}
}

/**
 * @brief      �˻�ģʽ
 * @param[in]  **board    ���̶���ָ��
 * @param[in]  *x_row     ������ָ���ַ
 * @param[in]  *y_column  ������ָ���ַ
 * @param[in]  option     ����ѡ� A:������� B:��������
 * @retval     ��
 */
void MachineMode(CHESSSTATE **board, char *x_row, char *y_column, char option){
    int check, count = 0;

    if(option == 'A'){ //��Һ���, ���԰���
        draw(board, ROW, COLUMN);               //������
        while(1){
            playermove(board, x_row, y_column, black); //����º���
            draw(board, ROW, COLUMN);                  //���»�����
            if(black == GetResult(board, *x_row, *y_column, black)) { //��ȡ���
                printf("��Ϸ�������ڷ���ʤ��\n");
                break;
            }
            check = BanMove(board, *x_row, *y_column);   //��ȡ���ֹ�����
            if(3 == check) {
                printf("��������, �׷���ʤ��\n");
                break;
            }else if(1 == check) {
                printf("��������, �׷���ʤ��\n");
                break;
            }else if(2 == check) {
                printf("���Ľ���, �׷���ʤ��\n");
                break;
            }

            count++;          //��������1
            if(225 == count){ //��������������������, ƽ��
                printf("��Ϸ������ƽ�֣�\n");
                break;
            }

            MachinePlay(board, x_row, y_column, white); //�����°���
            draw(board, ROW, COLUMN);                //���»�����
            printf("��������:%c%c \n", *x_row + 'A', *y_column + 'A');

            if(white == GetResult(board, *x_row, *y_column, white)) {//��ȡ���
                printf("��Ϸ�������׷���ʤ��\n");
                break;
            }
            count++;          //��������1
        }
    }
    else{              //��Ұ���, ���Ժ���
        board[6][6] = black;  //���Ե�һ����,ֱ�����м�
        count++;          //��������1
        draw(board, ROW, COLUMN);                  //���»�����
        while(1){
            playermove(board, x_row, y_column, white); //����°���
            draw(board, ROW, COLUMN);                  //���»�����
            if(white == GetResult(board, *x_row, *y_column, white)) { //��ȡ���
                printf("��Ϸ�������׷���ʤ��\n");
                break;
            }
            count++;          //��������1

            MachinePlay(board, x_row, y_column, black); //�����º���
            draw(board, ROW, COLUMN);                   //���»�����
            printf("��������:%c%c \n", *x_row + 'A', *y_column + 'A');
            if(black == GetResult(board, *x_row, *y_column, black)) { //��ȡ���
                printf("��Ϸ�������ڷ���ʤ��\n");
                break;
            }
            count++;          //��������1
            if(225 == count){ //��������������������, ƽ��
                printf("��Ϸ������ƽ�֣�\n");
                break;
            }
        }
    }
}
