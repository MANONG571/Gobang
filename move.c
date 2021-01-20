/**
* @file     move.c
* @brief    �����ļ�
* @details  ���������������
*/

#include "move.h"

/**
 * @brief �������
 * @param[in]  state     ���̶���ָ��
 * @param[out] *x_row    ���ӵ�������ָ��
 * @param[out] *y_column ���ӵ�������ָ��
 * @param[in]  order     ���巽
 * @retval ��
 */
void playermove(CHESSSTATE **state, char *x_row, char *y_column, CHESSSTATE order){
	char x, y;
	printf("���%d-%s�ߣ���H��A��,������HA:", order, order==black ? "�ڷ�" : "�׷�");
	while (1) {
		fflush(stdin);
		scanf("%c%c", x_row, y_column);
		*x_row -= 'A';
		*y_column -= 'A';
		if(*x_row >=0 && *x_row <= ROW-1 && *y_column >= 0 && *y_column <= COLUMN-1){
			if (state[*x_row][*y_column]) {
				printf("��λ���Ѿ��������ˣ����±��λ��:");
				continue;
            }
			else{
				state[*x_row][*y_column] = order;
				break;
            }
		}
		else{
			printf("�Ƿ����룬����������:");
			continue;
		}
	}
}
