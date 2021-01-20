#ifndef __CHESS_H
#define __CHESS_H

#define ROW 15
#define COLUMN 15
//ÆåÅÌ×Ö·û
#define LEFT_TOP "©° "
#define LEFT_BOTTOM "©¸ "
#define LEFT_CENTER "©À "
#define RIGHT_TOP "©´"
#define RIGHT_BOTTOM "©¼"
#define RIGHT_CENTER "©È"
#define TOP_CENTER "©Ð "
#define BOTTOM_CENTER "©Ø "
#define INTERNAL "©à "
//Æå×Ó×Ö·û
#define BLACK "¡ð"
#define WHITE "¡ñ"

//Æå×ÓµÄ×´Ì¬
//Ã»Æå:0; ºÚÆå:1; °×Æå:2;
typedef enum {
    none = 0, black = 1, white = 2
}CHESSSTATE;

#endif // __CHESS_H

