/**
* @file     rules.c
* @brief    ���ֹ������ļ�
* @details  �����Ͻ��ֹ�����
*/

#include "rules.h"

/**
 * @brief ���ֹ�����
 * @param[in] state    ���̶���ָ��
 * @param[in] x_row    Ҫ�����������
 * @param[in] y_column Ҫ�����������
 * @retval 0 �޽���
 * @retval 1 ��������
 * @retval 2 ���Ľ���
 * @retval 3 ��������
 */
int BanMove(CHESSSTATE **state, int x_row, int y_column)
{
    if(1 == LongBan(state, x_row, y_column)) //�жϳ�������
        return 3;

    if(1 == FourBan(state, x_row, y_column)) //�ж����Ľ���
        return 2;

    if(1 == ThreeBan(state, x_row, y_column)) //�ж���������
        return 1;

    return 0;  //û�н���
}

/**
 * @brief �������ּ��
 * @param[in] state    ���̶���ָ��
 * @param[in] x_row    Ҫ�����������
 * @param[in] y_column Ҫ�����������
 * @retval 0 �޽���
 * @retval 1 ����������
 */
int ThreeBan(CHESSSTATE **state, int x_row, int y_column)
{
    char chess[10]; //������Χ���, '0':������; '1':����; '2':����; '4':������;
    int i, x, y, addr, count = 0, fakeflag; //x:������; y:������; addr:����ַ�����Ե�ַ;
                                                //count:����/��������,��Χ:0~4; fakeflag:�ٻ�����־λ

    //'-'���ŷ�����ֹ���
    x = x_row;          //��ȡ����������Ŀ�ʼѭ������
    y = y_column - 4;   //x����; y����;
    strcpy(chess, "444444444");//��ʼ��������Χ����״̬
    for(i = 0; i < 9; y++, i++){
        if(y < 0 || y >= COLUMN) //��������������
            continue;
        chess[i] = state[x][y] + 48;
    }
    //���"����"�����
    addr = strstr(chess, "01110") - chess; //����ַ�����ԭ�ַ������±�
    fakeflag = 0;                          //�ٻ�����־λ
    if(addr >= 0 && addr <= 9){
        //���"01110"��"0"�Ƿ���� && "01110"��ǰ���Ƿ��и�Ϊ��,�Ҳ��ǽ���
        state[x_row][y_column - 4 + addr] = black;   //"01110"�ĵ�һ��"0"�ź���
        if(0 != BanMove(state, x_row, y_column - 4 + addr)){
            fakeflag = 1;
        }
        state[x_row][y_column - 4 + addr] = none;   //�ָ�"01110"�ĵ�һ��"0"
        state[x_row][y_column + addr] = black;      //"01110"�ĵڶ���"0"�ź���
        if(0 != BanMove(state, x_row, y_column + addr)){
            fakeflag = 1;
        }
        state[x_row][y_column + addr] = none;       //�ָ�"01110"�ĵڶ���"0"
        if(0 == fakeflag && y_column - 5 + addr >= 0 && 0 == state[x_row][y_column - 5 + addr] ){ //"01110"��ǰΪ��
            state[x_row][y_column - 5 + addr] = black;
            if(0 == BanMove(state, x_row, y_column - 5 + addr)){ //���˵��Ƿ�Ϊ����
                count++;
            }
            state[x_row][y_column - 5 + addr] = none;
        }else if(0 == fakeflag && y_column + 1 + addr < COLUMN && 0 == state[x_row][y_column + 1 + addr]){//"01110"�ĺ�Ϊ��
            state[x_row][y_column + 1 + addr] = black;
            if(0 == BanMove(state, x_row, y_column + 1 + addr)){ //���˵��Ƿ�Ϊ����
                count++;
            }
            state[x_row][y_column + 1 + addr] = none;
        }
    }
    //���"����"�����1
    addr = strstr(chess, "010110") - chess;
    if(addr >= 0 && addr <= 9){
        state[x_row][y_column - 2 + addr] = black;           //"010110"�м��"0"�ź���
        if(0 == BanMove(state, x_row, y_column - 2 + addr)){ //���˵��Ƿ�Ϊ����
            count++;
        }
        state[x_row][y_column - 2 + addr] = none;            //�ָ�"010110"�м��"0"
    }
    //���"����"�����2
    addr = strstr(chess, "011010") - chess;
    if(addr >= 0 && addr <= 9){
        state[x_row][y_column - 1 + addr] = black;           //"011010"�м��"0"�ź���
        if(0 == BanMove(state, x_row, y_column - 1 + addr)){ //���˵��Ƿ�Ϊ����
            count++;
        }
        state[x_row][y_column - 1 + addr] = none;            //�ָ�"011010"�м��"0"
    }

    //'|'���ŷ�����ֹ���
    x = x_row - 4;        //��ȡ����������Ŀ�ʼѭ������
    y = y_column;         //x����; y����;
    strcpy(chess, "444444444");
    for(i = 0; i < 9; x++, i++){
        if(x < 0 || x >= ROW) //��������������
            continue;
        chess[i] = state[x][y] + 48;
    }
    //���"����"�����
    addr = strstr(chess, "01110") - chess; //����ַ�����ԭ�ַ������±�
    fakeflag = 0;                          //�ٻ�����־λ
    if(addr >= 0 && addr <= 9){
        //���"01110"��"0"�Ƿ���� && "01110"��ǰ���Ƿ��и�Ϊ��,�Ҳ��ǽ���
        state[x_row - 4 + addr][y_column] = black;   //"01110"�ĵ�һ��"0"�ź���
        if(0 != BanMove(state, x_row - 4 + addr, y_column)){
            fakeflag = 1;
        }
        state[x_row - 4 + addr][y_column] = none;   //�ָ�"01110"�ĵ�һ��"0"
        state[x_row + addr][y_column] = black;      //"01110"�ĵڶ���"0"�ź���
        if(0 != BanMove(state, x_row + addr, y_column)){
            fakeflag = 1;
        }
        state[x_row + addr][y_column] = none;       //�ָ�"01110"�ĵڶ���"0"
        if(0 == fakeflag && x_row - 5 + addr >= 0 && 0 == state[x_row - 5 + addr][y_column] ){ //"01110"��ǰΪ��
            state[x_row - 5 + addr][y_column] = black;
            if(0 == BanMove(state, x_row - 5 + addr, y_column)){ //���˵��Ƿ�Ϊ����
                count++;
            }
            state[x_row - 5 + addr][y_column] = none;
        }else if(0 == fakeflag && x_row + 1 + addr < ROW && 0 == state[x_row + 1 + addr][y_column]){//"01110"�ĺ�Ϊ��
            state[x_row + 1 + addr][y_column] = black;
            if(0 == BanMove(state, x_row + 1 + addr, y_column)){ //���˵��Ƿ�Ϊ����
                count++;
            }
            state[x_row + 1 + addr][y_column] = none;
        }
    }
    //���"����"�����1
    addr = strstr(chess, "010110") - chess;
    if(addr >= 0 && addr <= 9){
        state[x_row - 2 + addr][y_column] = black;           //"010110"�м��"0"�ź���
        if(0 == BanMove(state, x_row - 2 + addr, y_column)){ //���˵��Ƿ�Ϊ����
            count++;
        }
        state[x_row - 2 + addr][y_column] = none;            //�ָ�"010110"�м��"0"
    }
    //���"����"�����2
    addr = strstr(chess, "011010") - chess;
    if(addr >= 0 && addr <= 9){
        state[x_row - 1 + addr][y_column] = black;           //"011010"�м��"0"�ź���
        if(0 == BanMove(state, x_row - 1 + addr, y_column)){ //���˵��Ƿ�Ϊ����
            count++;
        }
        state[x_row - 1 + addr][y_column] = none;            //�ָ�"011010"�м��"0"
    }

    //'/'б�ܷ�����ֹ���
    x = x_row - 4;          //��ȡ����������Ŀ�ʼѭ������
    y = y_column + 4;       //x����; y����;
    strcpy(chess, "444444444");
    for(i = 0; i < 9; x++, y--, i++){
        if(x < 0 || x >= ROW || y < 0 || y >= COLUMN) //��������������
            continue;
        chess[i] = state[x][y] + 48;
    }
    //���"����"�����
    addr = strstr(chess, "01110") - chess; //����ַ�����ԭ�ַ������±�
    fakeflag = 0;                          //�ٻ�����־λ
    if(addr >= 0 && addr <= 9){
        //���"01110"��"0"�Ƿ���� && "01110"��ǰ���Ƿ��и�Ϊ��,�Ҳ��ǽ���
        state[x_row - 4 + addr][y_column + 4 - addr] = black;   //"01110"�ĵ�һ��"0"�ź���
        if(0 != BanMove(state, x_row - 4 + addr, y_column + 4 - addr)){
            fakeflag = 1;
        }
        state[x_row - 4 + addr][y_column + 4 - addr] = none;   //�ָ�"01110"�ĵ�һ��"0"
        state[x_row + addr][y_column - addr] = black;      //"01110"�ĵڶ���"0"�ź���
        if(0 != BanMove(state, x_row + addr, y_column - addr)){
            fakeflag = 1;
        }
        state[x_row + addr][y_column - addr] = none;       //�ָ�"01110"�ĵڶ���"0"
        if(0 == fakeflag && x_row-5+addr >= 0 && y_column+5-addr < COLUMN && 0 == state[x_row-5+addr][y_column+5-addr] ){ //"01110"��ǰΪ��
            state[x_row - 5 + addr][y_column + 5 - addr] = black;
            if(0 == BanMove(state, x_row - 5 + addr, y_column + 5 - addr)){ //���˵��Ƿ�Ϊ����
                count++;
            }
            state[x_row - 5 + addr][y_column + 5 - addr] = none;
        }else if(0 == fakeflag && x_row+1+addr < ROW && y_column-1-addr >= 0 && 0 == state[x_row+1+addr][y_column-1-addr]){//"01110"�ĺ�Ϊ��
            state[x_row + 1 + addr][y_column - 1 - addr] = black;
            if(0 == BanMove(state, x_row + 1 + addr, y_column - 1 - addr)){ //���˵��Ƿ�Ϊ����
                count++;
            }
            state[x_row + 1 + addr][y_column - 1 - addr] = none;
        }
    }
    //���"����"�����1
    addr = strstr(chess, "010110") - chess;
    if(addr >= 0 && addr <= 9){
        state[x_row - 2 + addr][y_column + 2 - addr] = black;           //"010110"�м��"0"�ź���
        if(0 == BanMove(state, x_row - 2 + addr, y_column + 2 - addr)){ //���˵��Ƿ�Ϊ����
            count++;
        }
        state[x_row - 2 + addr][y_column + 2 - addr] = none;            //�ָ�"010110"�м��"0"
    }
    //���"����"�����2
    addr = strstr(chess, "011010") - chess;
    if(addr >= 0 && addr <= 9){
        state[x_row - 1 + addr][y_column + 1 -addr] = black;           //"011010"�м��"0"�ź���
        if(0 == BanMove(state, x_row - 1 + addr, y_column + 1 -addr)){ //���˵��Ƿ�Ϊ����
            count++;
        }
        state[x_row - 1 + addr][y_column + 1 -addr] = none;            //�ָ�"011010"�м��"0"
    }

    //'\'��б�ܷ�����ֹ���
    x = x_row - 4;          //��ȡ����������Ŀ�ʼѭ������
    y = y_column - 4;       //x����; y����;
    strcpy(chess, "444444444");
    for(i = 0; i < 9; x++, y++, i++){
        if(x < 0 || x >= ROW || y < 0 || y >= COLUMN) //��������������
            continue;
        chess[i] = state[x][y] + 48;
    }
    //���"����"�����
    addr = strstr(chess, "01110") - chess; //����ַ�����ԭ�ַ������±�
    fakeflag = 0;                          //�ٻ�����־λ
    if(addr >= 0 && addr <= 9){
        //���"01110"��"0"�Ƿ���� && "01110"��ǰ���Ƿ��и�Ϊ��,�Ҳ��ǽ���
        state[x_row - 4 + addr][y_column - 4 + addr] = black;   //"01110"�ĵ�һ��"0"�ź���
        if(0 != BanMove(state, x_row - 4 + addr, y_column - 4 + addr)){
            fakeflag = 1;
        }
        state[x_row - 4 + addr][y_column - 4 + addr] = none;   //�ָ�"01110"�ĵ�һ��"0"
        state[x_row + addr][y_column + addr] = black;      //"01110"�ĵڶ���"0"�ź���
        if(0 != BanMove(state, x_row + addr, y_column + addr)){
            fakeflag = 1;
        }
        state[x_row + addr][y_column + addr] = none;       //�ָ�"01110"�ĵڶ���"0"
        if(0 == fakeflag && x_row-5+addr >= 0 && y_column-5+addr >= 0 && 0 == state[x_row-5+addr][y_column-5+addr] ){ //"01110"��ǰΪ��
            state[x_row - 5 + addr][y_column - 5 + addr] = black;
            if(0 == BanMove(state, x_row - 5 + addr, y_column - 5 + addr)){ //���˵��Ƿ�Ϊ����
                count++;
            }
            state[x_row - 5 + addr][y_column - 5 + addr] = none;
        }else if(0 == fakeflag && x_row+1+addr < ROW && y_column+1+addr < COLUMN && 0 == state[x_row+1+addr][y_column+1+addr]){//"01110"�ĺ�Ϊ��
            state[x_row + 1 + addr][y_column + 1 + addr] = black;
            if(0 == BanMove(state, x_row + 1 + addr, y_column + 1 + addr)){ //���˵��Ƿ�Ϊ����
                count++;
            }
            state[x_row + 1 + addr][y_column + 1 + addr] = none;
        }
    }
    //���"����"�����1
    addr = strstr(chess, "010110") - chess;
    if(addr >= 0 && addr <= 9){
        state[x_row - 2 + addr][y_column - 2 + addr] = black;           //"010110"�м��"0"�ź���
        if(0 == BanMove(state, x_row - 2 + addr, y_column - 2 + addr)){ //���˵��Ƿ�Ϊ����
            count++;
        }
        state[x_row - 2 + addr][y_column - 2 + addr] = none;            //�ָ�"010110"�м��"0"
    }
    //���"����"�����2
    addr = strstr(chess, "011010") - chess;
    if(addr >= 0 && addr <= 9){
        state[x_row - 1 + addr][y_column - 1 + addr] = black;           //"011010"�м��"0"�ź���
        if(0 == BanMove(state, x_row - 1 + addr, y_column + 1 -addr)){ //���˵��Ƿ�Ϊ����
            count++;
        }
        state[x_row - 1 + addr][y_column - 1 + addr] = none;            //�ָ�"011010"�м��"0"
    }

    return count > 1 ? 1 : 0;  //������1������/����, ����1; ���򷵻�0

}

/**
 * @brief ���Ľ��ּ��
 * @param[in] state    ���̶���ָ��
 * @param[in] x_row    Ҫ�����������
 * @param[in] y_column Ҫ�����������
 * @retval 0 �޽���
 * @retval 1 �����Ľ���
 */
int FourBan(CHESSSTATE **state, int x_row, int y_column)
{
    char chess[10]; //������Χ���, 0:������; 1:����; 2:����; 4:������;
    int i, x, y, count = 0; //countΪ����/��������, ��Χ: 0~4

    //'-'���ŷ�����ֹ���
    x = x_row;          //��ȡ����������Ŀ�ʼѭ������
    y = y_column - 4;   //x����; y����;
    strcpy(chess, "444444444");//��ʼ��������Χ����״̬
    for(i = 0; i < 9; y++, i++){
        if(y < 0 || y >= COLUMN) //��������������
            continue;
        chess[i] = state[x][y] + 48;
    }
    if(NULL != strstr(chess, "011110") || NULL != strstr(chess, "10111") || NULL != strstr(chess, "11011") || \
       NULL != strstr(chess, "11101") || NULL != strstr(chess, "011112") || NULL != strstr(chess, "011114") || \
       NULL != strstr(chess, "211110") || NULL != strstr(chess, "411110")) {
        count++;
    }

    //'|'���ŷ�����ֹ���
    x = x_row - 4;        //��ȡ����������Ŀ�ʼѭ������
    y = y_column;         //x����; y����;
    strcpy(chess, "444444444");
    for(i = 0; i < 9; x++, i++){
        if(x < 0 || x >= ROW) //��������������
            continue;
        chess[i] = state[x][y] + 48;
    }
    if(NULL != strstr(chess, "011110") || NULL != strstr(chess, "10111") || NULL != strstr(chess, "11011") || \
       NULL != strstr(chess, "11101") || NULL != strstr(chess, "011112") || NULL != strstr(chess, "011114") || \
       NULL != strstr(chess, "211110") || NULL != strstr(chess, "411110")) {
        count++;
    }

    //'/'б�ܷ�����ֹ���
    x = x_row- 4;          //��ȡ����������Ŀ�ʼѭ������
    y = y_column+ 4;       //x����; y����;
    strcpy(chess, "444444444");
    for(i = 0; i < 9; x++, y--, i++){
        if(x < 0 || x >= ROW || y < 0 || y >= COLUMN) //��������������
            continue;
        chess[i] = state[x][y] + 48;
    }
    if(NULL != strstr(chess, "011110") || NULL != strstr(chess, "10111") || NULL != strstr(chess, "11011") || \
       NULL != strstr(chess, "11101") || NULL != strstr(chess, "011112") || NULL != strstr(chess, "011114") || \
       NULL != strstr(chess, "211110") || NULL != strstr(chess, "411110")) {
        count++;
    }

    //'\'��б�ܷ�����ֹ���
    x = x_row- 4;          //��ȡ����������Ŀ�ʼѭ������
    y = y_column- 4;       //x����; y����;
    strcpy(chess, "444444444");
    for(i = 0; i < 9; x++, y++, i++){
        if(x < 0 || x >= ROW || y < 0 || y >= COLUMN) //��������������
            continue;
        chess[i] = state[x][y] + 48;
    }
    if(NULL != strstr(chess, "011110") || NULL != strstr(chess, "10111") || NULL != strstr(chess, "11011") || \
       NULL != strstr(chess, "11101") || NULL != strstr(chess, "011112") || NULL != strstr(chess, "011114") || \
       NULL != strstr(chess, "211110") || NULL != strstr(chess, "411110")) {
        count++;
    }

     return count > 1 ? 1 : 0;  //������1������/����/����, ����1; ���򷵻�0
}

/**
 * @brief �������ּ��
 * @param[in] state    ���̶���ָ��
 * @param[in] x_row    Ҫ�����������
 * @param[in] y_column Ҫ�����������
 * @retval 0 �޽���
 * @retval 1 �г�������
 */
int LongBan(CHESSSTATE **state, int x_row, int y_column)
{
    int x, y, i, flag;

    //'-'���ŷ�����ֹ���
    x = x_row;          //��ȡ����������Ŀ�ʼѭ������
    y = y_column - 4;   //x����; y����;
    flag = 0;
    for(i = 0; i < 9; y++, i++){
        if(y < 0 || y >= COLUMN) //��������������
            continue;
        if(state[x][y] == black){
            flag++;
        }
        else{
            flag = 0;
        }
        if(6 == flag){
            return 1;
        }
    }

    //'|'���ŷ�����ֹ���
    x = x_row - 4;     //��ȡ����������Ŀ�ʼѭ������
    y = y_column;      //x����; y����;
    flag = 0;
    for(i = 0; i < 9; x++, i++){
        if(x < 0 || x >= ROW) //��������������
            continue;
        if(state[x][y] == black){
            flag++;
        }
        else{
            flag = 0;
        }
        if(6 == flag){
            return 1;
        }
    }

    //'/'б�ܷ�����ֹ���
    x = x_row - 4;       //��ȡ����������Ŀ�ʼѭ������
    y = y_column + 4;    //x����; y����;
    flag = 0;
    for(i = 0; i < 9; x++, y--, i++){
        if(x < 0 || x >= ROW || y < 0 || y >= COLUMN) //��������������
            continue;
        if(state[x][y] == black){
            flag++;
        }
        else{
            flag = 0;
        }
        if(6 == flag){
            return 1;
        }
    }

    //'\'��б�ܷ�����ֹ���
    x = x_row - 4;       //��ȡ����������Ŀ�ʼѭ������
    y = y_column - 4;    //x����; y����;
    flag = 0;
    for(i = 0; i < 9; x++, y++, i++){
        if(x < 0 || x >= ROW || y < 0 || y >= COLUMN) //��������������
            continue;
        if(state[x][y] == black){
            flag++;
        }
        else{
            flag = 0;
        }
        if(6 == flag){
            return 1;
        }
    }
    return 0;
}
