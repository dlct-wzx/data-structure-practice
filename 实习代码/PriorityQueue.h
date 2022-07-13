/*
 * @Descripttion: 优先队列的头文件
 * @Author: DLCT
 * @Date: 2022-07-11 10:06:29
 * @e-mail: 18109232165@163.com
 * @LastEditors: DLCT
 * @LastEditTime: 2022-07-13 15:24:26
 */
#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include <string.h>
using namespace std;
#define LL long long

template <class T>
class PriorityQueue
{
private:
	T *pArray;		 //存放数组
	LL arrayLength;	 //已存放个数
	LL arraySize;	 //数组大小
	void swim(LL k); //上浮
	void sink(LL k); //下沉
	void exSize();	 //扩充数组大小
public:
	PriorityQueue(LL N); //构造函数
	void push(T v);		 //插入结点
	T pop();			 //删除结点
	T top();			 //获取队首
	bool isEmpty();		 //是否为空
	int size();			 //队列大小
};

template <class T>
PriorityQueue<T>::PriorityQueue(LL N)
{
	pArray = new T[N + 1];
	arraySize = N;
	arrayLength = 0;
}

template <class T>
void PriorityQueue<T>::swim(LL k)
{
	while (k > 1 && pArray[k]->frequency < pArray[k / 2]->frequency)
	{
		//交换父子位置
		T p = pArray[k];
		pArray[k] = pArray[k / 2];
		pArray[k / 2] = p;
		k /= 2;							//数值对应id改变
	}
}

template <class T>
void PriorityQueue<T>::sink(LL k)
{
	while (k * 2 <= arrayLength)
	{ //循环至最后一个节点截止
		int j = 2 * k;
		if (j < arrayLength && (pArray[j]->frequency > pArray[j + 1]->frequency))
			j++; // 这里先比较左子树和右子树的大小，将最大的那个键记录下来再和父节点比较
		if (pArray[k]->frequency < pArray[j]->frequency)
			break;					// 和父节点比较如果父节点比最大的子节点还要大，则直接退出循环
		// 如果父节点比子节点小则交换
		T p = pArray[k];
		pArray[k] = pArray[j];
		pArray[j] = p;
		k = j;
	}
}

template <class T>
void PriorityQueue<T>::exSize()
{
	//扩充大小
	T *newarray = new T[arraySize * 2 + 1];
	memcpy(newarray, pArray, arraySize * sizeof(T));
	delete pArray;
	pArray = newarray;
	arraySize *= 2;
}

template <class T>
void PriorityQueue<T>::push(T v)
{
	if (arrayLength == arraySize - 1)
	{
		exSize();
	}
	pArray[++arrayLength] = v;
	swim(arrayLength);
}

template <class T>
T PriorityQueue<T>::pop()
{
	T maxt = pArray[1];
	T p = pArray[1];
	pArray[1] = pArray[arrayLength];
	pArray[arrayLength--] = p;
	sink(1);
	return maxt;
}

template <class T>
T PriorityQueue<T>::top()
{
	return pArray[1];
}

template <class T>
bool PriorityQueue<T>::isEmpty()
{
	return arrayLength == 0;
}

template <class T>
int PriorityQueue<T>::size()
{
	return arrayLength;
}
#endif