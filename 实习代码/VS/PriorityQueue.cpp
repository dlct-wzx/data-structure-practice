/*
 * @Descripttion:
 * @Author: DLCT
 * @Date: 2022-07-18 10:07:23
 * @e-mail: 18109232165@163.com
 * @LastEditors: DLCT
 * @LastEditTime: 2022-07-18 10:09:10
 */
#include "PriorityQueue.h"

 /**
  * @description: 	���ȶ��й��캯��
  * @param {int} N	��ʼ���鳤��
  */
PriorityQueue::PriorityQueue(int N)
{
	pArray = new HuffmanTreeNode*[N + 1];
	arraySize = N;
	arrayLength = 0;
}

/**
 * @description: 	������ʱ�ϸ�,������С��
 * @param {int} K	�½���λ��
 */

void PriorityQueue::swim(int k)
{
	while (k > 1 && pArray[k]->frequency < pArray[k / 2]->frequency)
	{
		//��������λ��
		HuffmanTreeNode* p = pArray[k];
		pArray[k] = pArray[k / 2];
		pArray[k / 2] = p;
		k /= 2; //��ֵ��Ӧid�ı�
	}
}

/**
 * @description: 	ɾ�����ʱ�³�
 * @param {int} k	��ʼ���λ��
 */

void PriorityQueue::sink(int k)
{
	while (k * 2 <= arrayLength)
	{ //ѭ�������һ���ڵ��ֹ
		int j = 2 * k;
		if (j < arrayLength && (pArray[j]->frequency > pArray[j + 1]->frequency))
			j++; // �����ȱȽ����������������Ĵ�С���������Ǹ�����¼�����ٺ͸��ڵ�Ƚ�
		if (pArray[k]->frequency < pArray[j]->frequency)
			break; // �͸��ڵ�Ƚ�������ڵ�������ӽڵ㻹Ҫ����ֱ���˳�ѭ��
		// ������ڵ���ӽڵ�С�򽻻�
		HuffmanTreeNode* p = pArray[k];
		pArray[k] = pArray[j];
		pArray[j] = p;
		k = j;
	}
}

/**
 * @description: �����Ž��������С
 */

void PriorityQueue::exSize()
{
	//�����С
	HuffmanTreeNode** newarray = new HuffmanTreeNode*[arraySize * 2 + 1];
	//����ԭ����
	memcpy(newarray, pArray, arraySize * sizeof(HuffmanTreeNode*));
	//�ͷ�
	delete pArray;
	pArray = newarray;
	arraySize *= 2;
}

/**
 * @description: 	�����½ڵ�
 * @param {HuffmanTreeNode*} v		�½���ֵ
 */

void PriorityQueue::push(HuffmanTreeNode* v)
{
	//���ռ��С������
	if (arrayLength == arraySize - 1)
		exSize();
	pArray[++arrayLength] = v;
	//�ϸ�
	swim(arrayLength);
}

/**
 * @description: 	ɾ������
 * @return {HuffmanTreeNode*} 		����Ԫ��
 */

HuffmanTreeNode* PriorityQueue::pop()
{
	HuffmanTreeNode* maxt = pArray[1];
	HuffmanTreeNode* p = pArray[1];
	//�������׺Ͷ�β
	pArray[1] = pArray[arrayLength];
	pArray[arrayLength--] = p;
	//�³�
	sink(1);
	return maxt;
}

/**
 * @description: ��ȡ����Ԫ��
 * @return {HuffmanTreeNode*}	 ����Ԫ��
 */

HuffmanTreeNode* PriorityQueue::top()
{
	return pArray[1];
}

/**
 * @description: 	�ж����ȶ����Ƿ�Ϊ��
 * @return {bool} 	��Ϊ�շ���true����Ϊ�շ���false
 */

bool PriorityQueue::isEmpty()
{
	return arrayLength == 0;
}

/**
 * @description: ��ȡ���ȶ��еĴ�С
 * @return {int} �������ȶ��еĴ�С
 */

int PriorityQueue::size()
{
	return arrayLength;
}