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
  * @description: 	优先队列构造函数
  * @param {int} N	初始数组长度
  */
PriorityQueue::PriorityQueue(int N)
{
	pArray = new HuffmanTreeNode*[N + 1];
	arraySize = N;
	arrayLength = 0;
}

/**
 * @description: 	插入结点时上浮,构造最小堆
 * @param {int} K	新结点的位置
 */

void PriorityQueue::swim(int k)
{
	while (k > 1 && pArray[k]->frequency < pArray[k / 2]->frequency)
	{
		//交换父子位置
		HuffmanTreeNode* p = pArray[k];
		pArray[k] = pArray[k / 2];
		pArray[k / 2] = p;
		k /= 2; //数值对应id改变
	}
}

/**
 * @description: 	删除结点时下沉
 * @param {int} k	起始结点位置
 */

void PriorityQueue::sink(int k)
{
	while (k * 2 <= arrayLength)
	{ //循环至最后一个节点截止
		int j = 2 * k;
		if (j < arrayLength && (pArray[j]->frequency > pArray[j + 1]->frequency))
			j++; // 这里先比较左子树和右子树的大小，将最大的那个键记录下来再和父节点比较
		if (pArray[k]->frequency < pArray[j]->frequency)
			break; // 和父节点比较如果父节点比最大的子节点还要大，则直接退出循环
		// 如果父节点比子节点小则交换
		HuffmanTreeNode* p = pArray[k];
		pArray[k] = pArray[j];
		pArray[j] = p;
		k = j;
	}
}

/**
 * @description: 扩充存放结点的数组大小
 */

void PriorityQueue::exSize()
{
	//扩充大小
	HuffmanTreeNode** newarray = new HuffmanTreeNode*[arraySize * 2 + 1];
	//拷贝原数组
	memcpy(newarray, pArray, arraySize * sizeof(HuffmanTreeNode*));
	//释放
	delete pArray;
	pArray = newarray;
	arraySize *= 2;
}

/**
 * @description: 	插入新节点
 * @param {HuffmanTreeNode*} v		新结点的值
 */

void PriorityQueue::push(HuffmanTreeNode* v)
{
	//若空间过小，扩充
	if (arrayLength == arraySize - 1)
		exSize();
	pArray[++arrayLength] = v;
	//上浮
	swim(arrayLength);
}

/**
 * @description: 	删除队首
 * @return {HuffmanTreeNode*} 		队首元素
 */

HuffmanTreeNode* PriorityQueue::pop()
{
	HuffmanTreeNode* maxt = pArray[1];
	HuffmanTreeNode* p = pArray[1];
	//交换队首和队尾
	pArray[1] = pArray[arrayLength];
	pArray[arrayLength--] = p;
	//下沉
	sink(1);
	return maxt;
}

/**
 * @description: 获取队首元素
 * @return {HuffmanTreeNode*}	 队首元素
 */

HuffmanTreeNode* PriorityQueue::top()
{
	return pArray[1];
}

/**
 * @description: 	判断优先队列是否为空
 * @return {bool} 	若为空返回true，不为空返回false
 */

bool PriorityQueue::isEmpty()
{
	return arrayLength == 0;
}

/**
 * @description: 获取优先队列的大小
 * @return {int} 返回优先队列的大小
 */

int PriorityQueue::size()
{
	return arrayLength;
}