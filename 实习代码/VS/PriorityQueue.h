#pragma once
/*
 * @Descripttion: 优先队列的头文件
 * @Author: DLCT
 * @Date: 2022-07-11 10:06:29
 * @e-mail: 18109232165@163.com
 * @LastEditors: DLCT
 * @LastEditTime: 2022-07-18 10:09:03
 */
#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include <string.h>
#include "HuffmanTree.h"
using namespace std;


class PriorityQueue
{
private:
	HuffmanTreeNode** pArray;		  //存放数组
	int arrayLength;  //已存放个数
	int arraySize;	  //数组大小
	void swim(int k); //上浮
	void sink(int k); //下沉
	void exSize();	  //扩充数组大小
public:
	PriorityQueue(int N); //构造函数
	void push(HuffmanTreeNode* v);		  //插入结点
	HuffmanTreeNode* pop();			  //删除队首
	HuffmanTreeNode* top();			  //获取队首
	bool isEmpty();		  //是否为空
	int size();			  //队列大小
};

#endif