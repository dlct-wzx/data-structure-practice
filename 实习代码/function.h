/*
 * @Descripttion: 
 * @Author: DLCT
 * @Date: 2022-07-11 17:18:40
 * @e-mail: 18109232165@163.com
 * @LastEditors: DLCT
 * @LastEditTime: 2022-07-14 17:43:47
 */
#ifndef FUNCITON_H
#define FUNCITON_H
#include <iostream>
#include <fstream>
#include <malloc.h>
#define LL long long

char nu_to_char(int *nu){
    char x;
    x = nu[0] * 128 + nu[1] * 64 + nu[2] * 32 + nu[3] * 16 + nu[4] * 8 + nu[5] * 4 + nu[6] * 2 + nu[7] * 1;
    return x;
}

char int_to_char(int nu){
    int i = 1;
    char ch;
    for(int j = 0;j < 8;j++){
        ch += i * (nu & 1 == 1 ? 1 : 0);
        i <<= 1;
        nu >>= 1;
    }
}

void char_to_nu(int *nu, int ch){
    for(int i = 7;i >= 0;i--){
        nu[i] = ch & 1 == 1 ? 1 : 0;
        ch>>=1;
    }
}

int getDigit(int n){
    int sum = 0;
    while(n > 0){
        sum++;
        n /= 10;
    }
    return sum;
}


int getOffset(int *count, int nu){
    int sum = 0;
    sum += getDigit(nu) + 1;
    for(int i = 0;i < 256;i++){
        if(count[i] != 0){
            sum += getDigit(i) + getDigit(count[i]) + 2;
        }
    }
    return sum;
}

int char_to_int(char ch){
    int sum = 0;
    int i = 2;
    for(int j = 0;j < 8;j++){
        sum += i * (ch & 1 == 1 ? 1 : 0);
        i <<= 1;
        ch >>= 1;
    }
}


#endif