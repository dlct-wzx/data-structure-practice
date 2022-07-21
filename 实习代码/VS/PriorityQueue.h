#pragma once
/*
 * @Descripttion: ���ȶ��е�ͷ�ļ�
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
	HuffmanTreeNode** pArray;		  //�������
	int arrayLength;  //�Ѵ�Ÿ���
	int arraySize;	  //�����С
	void swim(int k); //�ϸ�
	void sink(int k); //�³�
	void exSize();	  //���������С
public:
	PriorityQueue(int N); //���캯��
	void push(HuffmanTreeNode* v);		  //������
	HuffmanTreeNode* pop();			  //ɾ������
	HuffmanTreeNode* top();			  //��ȡ����
	bool isEmpty();		  //�Ƿ�Ϊ��
	int size();			  //���д�С
};

#endif