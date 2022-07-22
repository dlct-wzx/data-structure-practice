/*
 * @Descripttion:
 * @Author: DLCT
 * @Date: 2022-07-18 10:09:50
 * @e-mail: 18109232165@163.com
 * @LastEditors: DLCT
 * @LastEditTime: 2022-07-18 10:10:33
 */
#include "function.h"

 /**
  * @description:    ����������ת��Ϊchar
  * @param {int} *nu ��Ŷ������������
  * @return {char}   char���
  */
char nu_to_char(int* nu) {
    char x;
    x = nu[0] * 128 + nu[1] * 64 + nu[2] * 32 + nu[3] * 16 + nu[4] * 8 + nu[5] * 4 + nu[6] * 2 + nu[7] * 1;
    return x;
}

/**
 * @description:    ��charתΪ��������
 * @param {int} *nu ��Ž��������
 * @param {int} ch  ��ת�����ַ�
 * @return {*}
 */
void char_to_nu(int* nu, int ch) {
    for (int i = 7; i >= 0; i--) {
        //�ж����λ��0/1
        nu[i] = ch & 1 == 1 ? 1 : 0;
        //����һλ
        ch >>= 1;
    }
}

/**
 * @description:    ��ȡ���ֵ�λ��
 * @param {int} n   ��ͳ�Ƶ�����
 * @return {int}    n��λ��
 */
int getDigit(int n) {
    int sum = 0;
    while (n > 0) {
        sum++;
        n /= 10;
    }
    return sum;
}

/**
 * @description:        ��ȡ������������������λ��֮��
 * @param {int} *count  ������λ��
 * @param {int} nu      ��Ч������
 * @return {int}        λ��֮��
 */
int getOffset(int* count, int nu) {
    int sum = 0;
    //ͳ�Ƹ�����λ����+1Ϊ�ո�
    sum += getDigit(nu) + 1;
    for (int i = 0; i < 256; i++) {
        if (count[i] != 0) {
            //ͳ��ÿ����Ч�����ֽ�ֵ�͸�����λ��
            sum += getDigit(i) + getDigit(count[i]) + 2;
        }
    }
    return sum;
}

