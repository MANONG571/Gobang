#ifndef __CHESS_H
#define __CHESS_H

#define ROW 15
#define COLUMN 15
//�����ַ�
#define LEFT_TOP "�� "
#define LEFT_BOTTOM "�� "
#define LEFT_CENTER "�� "
#define RIGHT_TOP "��"
#define RIGHT_BOTTOM "��"
#define RIGHT_CENTER "��"
#define TOP_CENTER "�� "
#define BOTTOM_CENTER "�� "
#define INTERNAL "�� "
//�����ַ�
#define BLACK "��"
#define WHITE "��"

//���ӵ�״̬
//û��:0; ����:1; ����:2;
typedef enum {
    none = 0, black = 1, white = 2
}CHESSSTATE;

#endif // __CHESS_H

