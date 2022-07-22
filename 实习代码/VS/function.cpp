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
  * @description:    将二进制码转换为char
  * @param {int} *nu 存放二进制码的数组
  * @return {char}   char结果
  */
char nu_to_char(int* nu) {
    char x;
    x = nu[0] * 128 + nu[1] * 64 + nu[2] * 32 + nu[3] * 16 + nu[4] * 8 + nu[5] * 4 + nu[6] * 2 + nu[7] * 1;
    return x;
}

/**
 * @description:    将char转为二进制码
 * @param {int} *nu 存放结果的数组
 * @param {int} ch  待转换的字符
 * @return {*}
 */
void char_to_nu(int* nu, int ch) {
    for (int i = 7; i >= 0; i--) {
        //判断最低位是0/1
        nu[i] = ch & 1 == 1 ? 1 : 0;
        //右移一位
        ch >>= 1;
    }
}

/**
 * @description:    获取数字的位数
 * @param {int} n   待统计的数字
 * @return {int}    n的位数
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
 * @description:        获取整个数组和数组个数的位数之和
 * @param {int} *count  待处理位数
 * @param {int} nu      有效数个数
 * @return {int}        位数之和
 */
int getOffset(int* count, int nu) {
    int sum = 0;
    //统计个数的位数，+1为空格
    sum += getDigit(nu) + 1;
    for (int i = 0; i < 256; i++) {
        if (count[i] != 0) {
            //统计每个有效数的字节值和个数的位数
            sum += getDigit(i) + getDigit(count[i]) + 2;
        }
    }
    return sum;
}

