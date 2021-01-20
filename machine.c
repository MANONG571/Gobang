/**
* @file     machine.c
* @brief    人人对战文件
* @details  包含极大极小值搜索算法, α-β剪枝优化算法
*/
#include "machine.h"

int x, y; //x:电脑下棋行坐标; y:电脑下棋列坐标;

/**
 * @brief      电脑下棋
 * @param[in]  **state   棋盘二级指针
 * @param[out] *x_row    电脑下棋的行坐标指针
 * @param[out] *y_column 电脑下棋的列坐标指针
 * @param[in]  order     电脑下棋方
 * @retval     无
 */
void MachinePlay(CHESSSTATE **state, char *x_row, char *y_column, CHESSSTATE order){
    int i, j;
    CHESSSTATE MachState[ROW][COLUMN];

    for(i = 0; i < ROW; i++){  //将原来的棋盘拷贝一份, 用来电脑算法使用
        for(j = 0; j < COLUMN; j++){
            MachState[i][j] = state[i][j];
        }
     }

    MaxMinSearch(MachState, MACHINEDEEP, white, 1, 1, 1); //电脑下白棋

    *x_row = (char) x;
    *y_column = (char) y;
    printf("电脑下棋: x:%d y:%d \n", *x_row, *y_column);
    state[x][y] = order;
 }

 /**
 * @brief      极大极小值搜索函数
 * @param[in]  (*state)[COLUMN]    棋盘二级指针
 * @param[out] deep                搜索深度
 * @param[in]  order               电脑下棋方
 * @param[in]  MaxOrMin           1:要最大值; 0:要最小值
 * @param[in]  FirstOne            1:是第一枝; 0:不是第一枝
 * @param[in]  AlphaBeta           AlphaBeta值(剪枝的数值)
 * @retval     返回分数给上一级
 */
int MaxMinSearch(CHESSSTATE (*state)[COLUMN], int deep, CHESSSTATE order, int MaxOrMin,int FirstOne, int AlphaBeta){
    int i, j, Score, MaxMinScore, first_score = 1; //i,j:循环变量; xy:高16为x,低16位为y; Score:每个点分; first_in:第一下棋的得分;

     CHESSSTATE MachState[ROW][COLUMN]; //电脑使用的棋盘

     for(i = 0; i < ROW; i++){  //将原来的棋盘拷贝一份, 用来电脑算法使用
        for(j = 0; j < COLUMN; j++){
            MachState[i][j] = state[i][j];
        }
     }

     //调试时显示棋盘
     //StaticDraw(MachState, ROW, COLUMN);
     //printf("------------------------------------\n");

     if(deep > 0){   //若深度大于0
        for(i = 0; i < ROW; i++){          //遍历整个棋盘
            for(j = 0; j < COLUMN; j++){
                if(1 == JudgeChess(MachState, i, j, order)){ //如果该点适合放棋

                    MachState[i][j] = order;          //放棋
                    Score = MaxMinSearch(MachState, deep-1, order==black?white:black, MaxOrMin==1?0:1, first_score, MaxMinScore);

                    MachState[i][j] = none;

                    if(1 == first_score){ //如果第一次进入
                        MaxMinScore = Score;
                        first_score = 0;
                        if(deep == MACHINEDEEP){ //如果是第一个深度, 记录(x,y)
                            x = i;
                            y = j;
                        }
                    }

                    if(1 == MaxOrMin && MaxMinScore < Score){    //判断返回最大值还是最小值
                        MaxMinScore = Score;
                        if(deep == MACHINEDEEP){ //如果是第一个深度, 记录(x,y)
                            x = i;
                            y = j;
                        }
                    }
                    else if(0 == MaxOrMin && MaxMinScore > Score){
                        MaxMinScore = Score;
                    }

                    //α-β剪枝算法
                    if(1 != FirstOne){
                        if(1 == MaxOrMin && MaxMinScore >= AlphaBeta){
                            return POSIINFI;
                        }
                        else if(0 == MaxOrMin && MaxMinScore <= AlphaBeta){
                            return NEGAINFI;
                        }
                    }
                }
            }
        }
        return MaxMinScore;
     }
     else{           //若深度不大于0, 遍历结束, 返回得分值
        if(order%2 == 1){ //奇数搜索深度,order取反
            order = order == white ? black : white;
        }
        return GetScore(MachState, order);
     }
 }

/**
 * @brief      判断该点是否合适放棋
 * @param[in]   (*MachState)[COLUMN]  棋盘二级指针
 * @param[in]  x_row                  该点的行坐标
 * @param[in]  y_column               该点的列坐标
 * @param[in]  order                  下棋方
 * @retval     1  合适放棋
 * @retval     0  不合适放棋
 * @note       只有周围2圈有棋子才会被选中
 */
int JudgeChess(CHESSSTATE (*MachState)[COLUMN], int x_row, int y_column, CHESSSTATE order){
    int i, j;

    if(none != MachState[x_row][y_column]){ //如果此点已经有棋, 返回0
        return 0;
    }

    if(black == order){ //黑棋方禁手不能下, 返回0
        //分配一个动态内存数组,因为BanMonve()参数是CHESSSTATE**
        CHESSSTATE **JudBoa;
        int check, result;

        JudBoa = malloc(sizeof(CHESSSTATE*)*ROW);
        for(i = 0; i < ROW; i++)
            JudBoa[i] = malloc(sizeof(CHESSSTATE)*COLUMN);
        for(i = 0; i < ROW; i++)
            for(j = 0;j < COLUMN; j++)
                JudBoa[i][j] = MachState[i][j];
        JudBoa[x_row][y_column] = black;                    //此点下黑棋
        result = GetResult(JudBoa, x_row, y_column, black); //获取此点下黑棋结果
        check = BanMove(JudBoa, x_row, y_column);

        for(i = 0; i < ROW; i++) //释放内存
                free(JudBoa[i]);
        free(JudBoa);

        if(black == result){ //如果此点能直接获胜, 返回1
            return 1;
        }
        if(0 != check){ //如果禁手,返回0
            return 0;
        }
    }

    for(i = x_row - 1; i < x_row + 2; i++){
        for(j = y_column - 1; j < y_column + 2; j++){
            if(i >= 0 && i < ROW && j >= 0 && j < COLUMN && MachState[i][j] != none ){ //如果周围有棋子, 返回1
                return 1;
            }
        }
    }

    return 0; //没有则返回0
 }

 /**
 * @brief      评估函数
 * @param[in]  **MachState   棋盘二级指针
 * @param[in]  order         电脑下棋方
 * @retval     返回分数值
 * @note       需要搜索整个棋盘的得分, 因为可能深度大, 下了多个棋子
 */
int GetScore(CHESSSTATE (*MachState)[COLUMN], CHESSSTATE order){
     int i, j, m, n, BlackScore = 0, WhiteScore = 0;
     int TempMax = ROW > COLUMN ? ROW : COLUMN;
     char temp[TempMax + 3]; //临时存放的数据数组,数组大小为ROW与COLUMN最大值+3

     //黑棋得分 白棋得分
     //"-"横着方向
     for(i = 0; i < ROW; i++){
        for(j = 0; j < COLUMN + 2; j++){        //将临时数组全赋'4', 表示超出棋盘
            temp[j] = '4';                      //1~COLUMN代表棋盘内容, 0和COLUMN+1代表超出棋盘
        }
        temp[COLUMN + 2] = '\0';                //COLUMN+2代表字符串结束符
        for(j = 0; j < COLUMN; j++){            //每一行数据存储到temp数组中
            temp[j + 1] = MachState[i][j] + 48; //temp[0]='4'代表棋盘边界
        }
        BlackScore += StrBlackScore(temp);
        WhiteScore += StrWhiteScore(temp);
     }
     //"|"竖着方向
     for(j = 0; j < COLUMN; j++){
        for(i = 0; i < ROW + 2; i++){           //将临时数组全赋'4', 表示超出棋盘
            temp[i] = '4';                      //1~ROW代表棋盘内容, 0和ROW+1代表超出棋盘
        }
        temp[ROW + 2] = '\0';                   //ROW+2代表字符串结束符
        for(i = 0; i < ROW; i++){ //每一行数据存储到temp数组中
            temp[i + 1] = MachState[i][j] + 48;
        }
        BlackScore += StrBlackScore(temp);
        WhiteScore += StrWhiteScore(temp);
     }
     //"/"斜杆方向
     for(m = 4; m < COLUMN + ROW - 4; m++){
        i = m < COLUMN ? 0 : m - (COLUMN - 1); //m<COLUMN,左上部分; m>=COLUMN,右下部分;
        j = m < COLUMN ? m : COLUMN - 1;

        for(n = 0; n < TempMax + 2; n++){ //将临时数组全赋'4', 表示超出棋盘
            temp[n] = '4';                //1~TempMax代表棋盘内容, 0和TempMax+1代表超出棋盘
         }
         temp[TempMax + 2] = '\0';        //TempMax+2代表字符串结束符
        for(; j >= 0 && i < ROW; i++, j--){     //每一斜杠方向数据存储到temp数组中
            temp[i + 1] = MachState[i][j] + 48;
        }
        BlackScore += StrBlackScore(temp);
        WhiteScore += StrWhiteScore(temp);
     }
     //"\"反斜杠方向
     for(m = 0; m < COLUMN + ROW - 9; m++){
        i = m < ROW - 4 ? m : 0; //m<ROW-6,左下部分; m>=ROW-6,右上部分;
        j = m < ROW - 4 ? 0 : m - (ROW - 5);

        for(n = 0; n < TempMax + 2; n++){ //将临时数组全赋'4', 表示超出棋盘
            temp[n] = '4';                //1~TempMax代表棋盘内容, 0和TempMax+1代表超出棋盘
         }
         temp[TempMax + 2] = '\0';        //TempMax+2代表字符串结束符
        for(; i < ROW && j < COLUMN; i++, j++){     //每一反斜杠方向数据存储到temp数组中
            temp[i + 1] = MachState[i][j] + 48;
        }
        BlackScore += StrBlackScore(temp);
        WhiteScore += StrWhiteScore(temp);
     }

     return (order == black) ? BlackScore - WhiteScore : WhiteScore - BlackScore;
 }

/**
 * @brief      评估函数中的黑棋得分
 * @param[in]  *temp   棋盘一串数据
 * @retval     返回该串黑棋的分数值
 */
 int StrBlackScore(char *temp){
     int BlackScore = 0;
     char *jumpstr = temp;

     //分值表
     //*****************
     //* 五连 * 100000 *
     //* 活四 * 10000  *
     //* 活三 * 1000   *
     //* 冲四 * 1000   *
     //* 活二 * 100    *
     //* 冲三 * 100    *
     //* 活一 * 10     *
     //* 冲二 * 10     *
     //*****************
     BlackScore += StrTime(temp, "11111") * 100000 + StrTime(temp, "011110") * 10000 + (StrTime(temp, "01110") + \
                    StrTime(temp, "211110") + StrTime(temp, "411110") + StrTime(temp, "011112") + StrTime(temp, "011114")) * 1000 + \
                    (StrTime(temp, "0110") + StrTime(temp, "21110") + StrTime(temp, "41110") + StrTime(temp, "01112") + \
                    StrTime(temp, "01114")) * 100 + (StrTime(temp, "010") + StrTime(temp, "2110") + StrTime(temp, "4110") + \
                    StrTime(temp, "0112") + StrTime(temp, "0114")) * 10;

     //*****************
     //* 跳四 * 1000   *
     //* 跳三 * 100    *
     //* 跳二 * 10     *
     //*****************
     jumpstr = strstr(jumpstr, "101");
     if(NULL != jumpstr){
        if(jumpstr - temp + 4 < strlen(temp) && NULL != strstr(jumpstr, "10111")){ //跳四
                BlackScore += 1000;
        }else if(jumpstr - temp - 1 >= 0 && jumpstr - temp + 1 < strlen(temp) && NULL != strstr(jumpstr, "11011")){
                BlackScore += 1000;
        }else if(jumpstr - temp - 2 >= 0 && NULL != strstr(jumpstr, "11101")){
                BlackScore += 1000;
        }else if(jumpstr - temp + 3 < strlen(temp) && NULL != strstr(jumpstr, "1011")){ //跳三
                BlackScore += 100;
        }else if(jumpstr - temp  -1 >= 0 && NULL != strstr(jumpstr, "1101")){
                BlackScore += 100;
        }else{  //跳二
                BlackScore += 10;
        }
        jumpstr = strstr(jumpstr, "101") + 3;
     }

     return BlackScore;
}

/**
 * @brief      评估函数中的白棋得分
 * @param[in]  *temp   棋盘一串数据
 * @retval     返回该串白棋的分数值
 */
 int StrWhiteScore(char *temp){
     int WhiteScore = 0;
     char *jumpstr = temp;

     //分值表
     //*****************
     //* 五连 * 100000 *
     //* 活四 * 10000  *
     //* 活三 * 1000   *
     //* 冲四 * 1000   *
     //* 活二 * 100    *
     //* 冲三 * 100    *
     //* 活一 * 10     *
     //* 冲二 * 10     *
     //*****************
     WhiteScore += StrTime(temp, "22222") * 100000 + StrTime(temp, "022220") * 10000 + (StrTime(temp, "02220") + \
                    StrTime(temp, "122220") + StrTime(temp, "422220") + StrTime(temp, "022221") + StrTime(temp, "022224")) * 1000 + \
                    (StrTime(temp, "0220") + StrTime(temp, "12220") + StrTime(temp, "42220") + StrTime(temp, "02221") + \
                    StrTime(temp, "02224")) * 100 + (StrTime(temp, "020") + StrTime(temp, "1220") + StrTime(temp, "4220") + \
                    StrTime(temp, "0221") + StrTime(temp, "0224")) * 10;

     //*****************
     //* 跳四 * 1000   *
     //* 跳三 * 100    *
     //* 跳二 * 10     *
     //*****************
     jumpstr = strstr(jumpstr, "202");
     if(NULL != jumpstr){
        if(jumpstr - temp + 4 < strlen(temp) && NULL != strstr(jumpstr, "20222")){ //跳四
                WhiteScore += 1000;
        }else if(jumpstr - temp - 1 >= 0 && jumpstr - temp + 1 < strlen(temp) && NULL != strstr(jumpstr, "22022")){
                WhiteScore += 1000;
        }else if(jumpstr - temp - 2 >= 0 && NULL != strstr(jumpstr, "22202")){
                WhiteScore += 1000;
        }else if(jumpstr - temp + 3 < strlen(temp) && NULL != strstr(jumpstr, "2022")){ //跳三
                WhiteScore += 100;
        }else if(jumpstr - temp  -1 >= 0 && NULL != strstr(jumpstr, "2202")){
                WhiteScore += 100;
        }else{  //跳二
                WhiteScore += 10;
        }
        jumpstr = strstr(jumpstr, "202") + 3;
     }

     return WhiteScore;
}

/**
 * @brief      测量母字符串中子字符串中出现的次数
 * @param[in]  mother   母字符串
 * @param[in]  son      子字符串
 * @retval     返回出现次数
 */
int StrTime(char *mother, char *son){
    int count = 0;
    char *temp = mother;

     while(NULL != strstr(temp, son)){          //若匹配到子字符串
        temp = strstr(temp, son) + strlen(son); //跳过此段, 继续匹配后面的部分
        count++;
     }

     return count;
}


