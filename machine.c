/**
* @file     machine.c
* @brief    ���˶�ս�ļ�
* @details  ��������Сֵ�����㷨, ��-�¼�֦�Ż��㷨
*/
#include "machine.h"

int x, y; //x:��������������; y:��������������;

/**
 * @brief      ��������
 * @param[in]  **state   ���̶���ָ��
 * @param[out] *x_row    ���������������ָ��
 * @param[out] *y_column ���������������ָ��
 * @param[in]  order     �������巽
 * @retval     ��
 */
void MachinePlay(CHESSSTATE **state, char *x_row, char *y_column, CHESSSTATE order){
    int i, j;
    CHESSSTATE MachState[ROW][COLUMN];

    for(i = 0; i < ROW; i++){  //��ԭ�������̿���һ��, ���������㷨ʹ��
        for(j = 0; j < COLUMN; j++){
            MachState[i][j] = state[i][j];
        }
     }

    MaxMinSearch(MachState, MACHINEDEEP, white, 1, 1, 1); //�����°���

    *x_row = (char) x;
    *y_column = (char) y;
    printf("��������: x:%d y:%d \n", *x_row, *y_column);
    state[x][y] = order;
 }

 /**
 * @brief      ����Сֵ��������
 * @param[in]  (*state)[COLUMN]    ���̶���ָ��
 * @param[out] deep                �������
 * @param[in]  order               �������巽
 * @param[in]  MaxOrMin           1:Ҫ���ֵ; 0:Ҫ��Сֵ
 * @param[in]  FirstOne            1:�ǵ�һ֦; 0:���ǵ�һ֦
 * @param[in]  AlphaBeta           AlphaBetaֵ(��֦����ֵ)
 * @retval     ���ط�������һ��
 */
int MaxMinSearch(CHESSSTATE (*state)[COLUMN], int deep, CHESSSTATE order, int MaxOrMin,int FirstOne, int AlphaBeta){
    int i, j, Score, MaxMinScore, first_score = 1; //i,j:ѭ������; xy:��16Ϊx,��16λΪy; Score:ÿ�����; first_in:��һ����ĵ÷�;

     CHESSSTATE MachState[ROW][COLUMN]; //����ʹ�õ�����

     for(i = 0; i < ROW; i++){  //��ԭ�������̿���һ��, ���������㷨ʹ��
        for(j = 0; j < COLUMN; j++){
            MachState[i][j] = state[i][j];
        }
     }

     //����ʱ��ʾ����
     //StaticDraw(MachState, ROW, COLUMN);
     //printf("------------------------------------\n");

     if(deep > 0){   //����ȴ���0
        for(i = 0; i < ROW; i++){          //������������
            for(j = 0; j < COLUMN; j++){
                if(1 == JudgeChess(MachState, i, j, order)){ //����õ��ʺϷ���

                    MachState[i][j] = order;          //����
                    Score = MaxMinSearch(MachState, deep-1, order==black?white:black, MaxOrMin==1?0:1, first_score, MaxMinScore);

                    MachState[i][j] = none;

                    if(1 == first_score){ //�����һ�ν���
                        MaxMinScore = Score;
                        first_score = 0;
                        if(deep == MACHINEDEEP){ //����ǵ�һ�����, ��¼(x,y)
                            x = i;
                            y = j;
                        }
                    }

                    if(1 == MaxOrMin && MaxMinScore < Score){    //�жϷ������ֵ������Сֵ
                        MaxMinScore = Score;
                        if(deep == MACHINEDEEP){ //����ǵ�һ�����, ��¼(x,y)
                            x = i;
                            y = j;
                        }
                    }
                    else if(0 == MaxOrMin && MaxMinScore > Score){
                        MaxMinScore = Score;
                    }

                    //��-�¼�֦�㷨
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
     else{           //����Ȳ�����0, ��������, ���ص÷�ֵ
        if(order%2 == 1){ //�����������,orderȡ��
            order = order == white ? black : white;
        }
        return GetScore(MachState, order);
     }
 }

/**
 * @brief      �жϸõ��Ƿ���ʷ���
 * @param[in]   (*MachState)[COLUMN]  ���̶���ָ��
 * @param[in]  x_row                  �õ��������
 * @param[in]  y_column               �õ��������
 * @param[in]  order                  ���巽
 * @retval     1  ���ʷ���
 * @retval     0  �����ʷ���
 * @note       ֻ����Χ2Ȧ�����ӲŻᱻѡ��
 */
int JudgeChess(CHESSSTATE (*MachState)[COLUMN], int x_row, int y_column, CHESSSTATE order){
    int i, j;

    if(none != MachState[x_row][y_column]){ //����˵��Ѿ�����, ����0
        return 0;
    }

    if(black == order){ //���巽���ֲ�����, ����0
        //����һ����̬�ڴ�����,��ΪBanMonve()������CHESSSTATE**
        CHESSSTATE **JudBoa;
        int check, result;

        JudBoa = malloc(sizeof(CHESSSTATE*)*ROW);
        for(i = 0; i < ROW; i++)
            JudBoa[i] = malloc(sizeof(CHESSSTATE)*COLUMN);
        for(i = 0; i < ROW; i++)
            for(j = 0;j < COLUMN; j++)
                JudBoa[i][j] = MachState[i][j];
        JudBoa[x_row][y_column] = black;                    //�˵��º���
        result = GetResult(JudBoa, x_row, y_column, black); //��ȡ�˵��º�����
        check = BanMove(JudBoa, x_row, y_column);

        for(i = 0; i < ROW; i++) //�ͷ��ڴ�
                free(JudBoa[i]);
        free(JudBoa);

        if(black == result){ //����˵���ֱ�ӻ�ʤ, ����1
            return 1;
        }
        if(0 != check){ //�������,����0
            return 0;
        }
    }

    for(i = x_row - 1; i < x_row + 2; i++){
        for(j = y_column - 1; j < y_column + 2; j++){
            if(i >= 0 && i < ROW && j >= 0 && j < COLUMN && MachState[i][j] != none ){ //�����Χ������, ����1
                return 1;
            }
        }
    }

    return 0; //û���򷵻�0
 }

 /**
 * @brief      ��������
 * @param[in]  **MachState   ���̶���ָ��
 * @param[in]  order         �������巽
 * @retval     ���ط���ֵ
 * @note       ��Ҫ�����������̵ĵ÷�, ��Ϊ������ȴ�, ���˶������
 */
int GetScore(CHESSSTATE (*MachState)[COLUMN], CHESSSTATE order){
     int i, j, m, n, BlackScore = 0, WhiteScore = 0;
     int TempMax = ROW > COLUMN ? ROW : COLUMN;
     char temp[TempMax + 3]; //��ʱ��ŵ���������,�����СΪROW��COLUMN���ֵ+3

     //����÷� ����÷�
     //"-"���ŷ���
     for(i = 0; i < ROW; i++){
        for(j = 0; j < COLUMN + 2; j++){        //����ʱ����ȫ��'4', ��ʾ��������
            temp[j] = '4';                      //1~COLUMN������������, 0��COLUMN+1����������
        }
        temp[COLUMN + 2] = '\0';                //COLUMN+2�����ַ���������
        for(j = 0; j < COLUMN; j++){            //ÿһ�����ݴ洢��temp������
            temp[j + 1] = MachState[i][j] + 48; //temp[0]='4'�������̱߽�
        }
        BlackScore += StrBlackScore(temp);
        WhiteScore += StrWhiteScore(temp);
     }
     //"|"���ŷ���
     for(j = 0; j < COLUMN; j++){
        for(i = 0; i < ROW + 2; i++){           //����ʱ����ȫ��'4', ��ʾ��������
            temp[i] = '4';                      //1~ROW������������, 0��ROW+1����������
        }
        temp[ROW + 2] = '\0';                   //ROW+2�����ַ���������
        for(i = 0; i < ROW; i++){ //ÿһ�����ݴ洢��temp������
            temp[i + 1] = MachState[i][j] + 48;
        }
        BlackScore += StrBlackScore(temp);
        WhiteScore += StrWhiteScore(temp);
     }
     //"/"б�˷���
     for(m = 4; m < COLUMN + ROW - 4; m++){
        i = m < COLUMN ? 0 : m - (COLUMN - 1); //m<COLUMN,���ϲ���; m>=COLUMN,���²���;
        j = m < COLUMN ? m : COLUMN - 1;

        for(n = 0; n < TempMax + 2; n++){ //����ʱ����ȫ��'4', ��ʾ��������
            temp[n] = '4';                //1~TempMax������������, 0��TempMax+1����������
         }
         temp[TempMax + 2] = '\0';        //TempMax+2�����ַ���������
        for(; j >= 0 && i < ROW; i++, j--){     //ÿһб�ܷ������ݴ洢��temp������
            temp[i + 1] = MachState[i][j] + 48;
        }
        BlackScore += StrBlackScore(temp);
        WhiteScore += StrWhiteScore(temp);
     }
     //"\"��б�ܷ���
     for(m = 0; m < COLUMN + ROW - 9; m++){
        i = m < ROW - 4 ? m : 0; //m<ROW-6,���²���; m>=ROW-6,���ϲ���;
        j = m < ROW - 4 ? 0 : m - (ROW - 5);

        for(n = 0; n < TempMax + 2; n++){ //����ʱ����ȫ��'4', ��ʾ��������
            temp[n] = '4';                //1~TempMax������������, 0��TempMax+1����������
         }
         temp[TempMax + 2] = '\0';        //TempMax+2�����ַ���������
        for(; i < ROW && j < COLUMN; i++, j++){     //ÿһ��б�ܷ������ݴ洢��temp������
            temp[i + 1] = MachState[i][j] + 48;
        }
        BlackScore += StrBlackScore(temp);
        WhiteScore += StrWhiteScore(temp);
     }

     return (order == black) ? BlackScore - WhiteScore : WhiteScore - BlackScore;
 }

/**
 * @brief      ���������еĺ���÷�
 * @param[in]  *temp   ����һ������
 * @retval     ���ظô�����ķ���ֵ
 */
 int StrBlackScore(char *temp){
     int BlackScore = 0;
     char *jumpstr = temp;

     //��ֵ��
     //*****************
     //* ���� * 100000 *
     //* ���� * 10000  *
     //* ���� * 1000   *
     //* ���� * 1000   *
     //* ��� * 100    *
     //* ���� * 100    *
     //* ��һ * 10     *
     //* ��� * 10     *
     //*****************
     BlackScore += StrTime(temp, "11111") * 100000 + StrTime(temp, "011110") * 10000 + (StrTime(temp, "01110") + \
                    StrTime(temp, "211110") + StrTime(temp, "411110") + StrTime(temp, "011112") + StrTime(temp, "011114")) * 1000 + \
                    (StrTime(temp, "0110") + StrTime(temp, "21110") + StrTime(temp, "41110") + StrTime(temp, "01112") + \
                    StrTime(temp, "01114")) * 100 + (StrTime(temp, "010") + StrTime(temp, "2110") + StrTime(temp, "4110") + \
                    StrTime(temp, "0112") + StrTime(temp, "0114")) * 10;

     //*****************
     //* ���� * 1000   *
     //* ���� * 100    *
     //* ���� * 10     *
     //*****************
     jumpstr = strstr(jumpstr, "101");
     if(NULL != jumpstr){
        if(jumpstr - temp + 4 < strlen(temp) && NULL != strstr(jumpstr, "10111")){ //����
                BlackScore += 1000;
        }else if(jumpstr - temp - 1 >= 0 && jumpstr - temp + 1 < strlen(temp) && NULL != strstr(jumpstr, "11011")){
                BlackScore += 1000;
        }else if(jumpstr - temp - 2 >= 0 && NULL != strstr(jumpstr, "11101")){
                BlackScore += 1000;
        }else if(jumpstr - temp + 3 < strlen(temp) && NULL != strstr(jumpstr, "1011")){ //����
                BlackScore += 100;
        }else if(jumpstr - temp  -1 >= 0 && NULL != strstr(jumpstr, "1101")){
                BlackScore += 100;
        }else{  //����
                BlackScore += 10;
        }
        jumpstr = strstr(jumpstr, "101") + 3;
     }

     return BlackScore;
}

/**
 * @brief      ���������еİ���÷�
 * @param[in]  *temp   ����һ������
 * @retval     ���ظô�����ķ���ֵ
 */
 int StrWhiteScore(char *temp){
     int WhiteScore = 0;
     char *jumpstr = temp;

     //��ֵ��
     //*****************
     //* ���� * 100000 *
     //* ���� * 10000  *
     //* ���� * 1000   *
     //* ���� * 1000   *
     //* ��� * 100    *
     //* ���� * 100    *
     //* ��һ * 10     *
     //* ��� * 10     *
     //*****************
     WhiteScore += StrTime(temp, "22222") * 100000 + StrTime(temp, "022220") * 10000 + (StrTime(temp, "02220") + \
                    StrTime(temp, "122220") + StrTime(temp, "422220") + StrTime(temp, "022221") + StrTime(temp, "022224")) * 1000 + \
                    (StrTime(temp, "0220") + StrTime(temp, "12220") + StrTime(temp, "42220") + StrTime(temp, "02221") + \
                    StrTime(temp, "02224")) * 100 + (StrTime(temp, "020") + StrTime(temp, "1220") + StrTime(temp, "4220") + \
                    StrTime(temp, "0221") + StrTime(temp, "0224")) * 10;

     //*****************
     //* ���� * 1000   *
     //* ���� * 100    *
     //* ���� * 10     *
     //*****************
     jumpstr = strstr(jumpstr, "202");
     if(NULL != jumpstr){
        if(jumpstr - temp + 4 < strlen(temp) && NULL != strstr(jumpstr, "20222")){ //����
                WhiteScore += 1000;
        }else if(jumpstr - temp - 1 >= 0 && jumpstr - temp + 1 < strlen(temp) && NULL != strstr(jumpstr, "22022")){
                WhiteScore += 1000;
        }else if(jumpstr - temp - 2 >= 0 && NULL != strstr(jumpstr, "22202")){
                WhiteScore += 1000;
        }else if(jumpstr - temp + 3 < strlen(temp) && NULL != strstr(jumpstr, "2022")){ //����
                WhiteScore += 100;
        }else if(jumpstr - temp  -1 >= 0 && NULL != strstr(jumpstr, "2202")){
                WhiteScore += 100;
        }else{  //����
                WhiteScore += 10;
        }
        jumpstr = strstr(jumpstr, "202") + 3;
     }

     return WhiteScore;
}

/**
 * @brief      ����ĸ�ַ��������ַ����г��ֵĴ���
 * @param[in]  mother   ĸ�ַ���
 * @param[in]  son      ���ַ���
 * @retval     ���س��ִ���
 */
int StrTime(char *mother, char *son){
    int count = 0;
    char *temp = mother;

     while(NULL != strstr(temp, son)){          //��ƥ�䵽���ַ���
        temp = strstr(temp, son) + strlen(son); //�����˶�, ����ƥ�����Ĳ���
        count++;
     }

     return count;
}


