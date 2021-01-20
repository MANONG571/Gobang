/**
* @file     display.c
* @brief    ��ʾ�����ļ�
* @details  ���ն���ʾ������Ϣ
*/

#include "display.h"

/**
 * @brief   ��̬���������������ʾ
 * @param[in] state    ���̶���ָ��
 * @param[in] row      ���̵���
 * @param[in] column   ���̵���
 */
void draw(CHESSSTATE **state, int row, int column){
	system("cls"); //����
	int i,j;
	printf("  ");
	for (i = 0; i < column; i++)      //�������
		printf("%c ", (char)(i+65));
    printf("\n");
	for (i = 0; i < row; i++) {
		printf("%c ", (char)(i+65));  //�������
		for (j = 0; j < column; j++) {
			switch(state[i][j]){
				case 0:               //������
					if (j > 0 && j < column-1)
						printf("%s", (i == 0 ? TOP_CENTER : i == row-1? BOTTOM_CENTER : INTERNAL));
					else if (j == 0)
						printf("%s", (i == 0 ? LEFT_TOP : i == row-1 ? LEFT_BOTTOM : LEFT_CENTER));
					else if(j == column-1)
						printf("%s", (i == 0 ? RIGHT_TOP : i == row-1 ? RIGHT_BOTTOM : RIGHT_CENTER));
					break;
				case 1:               //������
					printf("%s", BLACK);
					break;
				case 2:               //������
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
 * @brief   ��̬���������������ʾ
 * @param[in] state    ���̶���ָ��
 * @param[in] row      ���̵���
 * @param[in] column   ���̵���
 */
void StaticDraw(CHESSSTATE (*state)[COLUMN], int row, int column){
	int i,j;
	printf("  ");
	for (i = 0; i < column; i++)      //�������
		printf("%c ", (char)(i+'0'));
    printf("\n");
	for (i = 0; i < row; i++) {
		printf("%c ", (char)(i+'0'));  //�������
		for (j = 0; j < column; j++) {
			switch(state[i][j]){
				case 0:               //������
					if (j > 0 && j < column-1)
						printf("%s", (i == 0 ? TOP_CENTER : i == row-1? BOTTOM_CENTER : INTERNAL));
					else if (j == 0)
						printf("%s", (i == 0 ? LEFT_TOP : i == row-1 ? LEFT_BOTTOM : LEFT_CENTER));
					else if(j == column-1)
						printf("%s", (i == 0 ? RIGHT_TOP : i == row-1 ? RIGHT_BOTTOM : RIGHT_CENTER));
					break;
				case 1:               //������
					printf("%s", BLACK);
					break;
				case 2:               //������
					printf("%s", WHITE);
					break;
				default:
					break;
			}
		}
		printf("\n");
	}
}
