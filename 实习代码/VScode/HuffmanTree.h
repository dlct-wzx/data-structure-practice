/*
 * @Descripttion: 哈夫曼树头文件
 * @Author: DLCT
 * @Date: 2022-07-11 08:43:57
 * @e-mail: 18109232165@163.com
 * @LastEditors: DLCT
 * @LastEditTime: 2022-07-21 10:37:18
 */
#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H
#include "PriorityQueue.h"
#include "function.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
using namespace std;

vector<int> v;  //编码时用到的可变数组

struct HuffmanTreeNode
{
    int data;                         //待编码数据
    int frequency;                    //出现频率
    vector<int> code;                 //哈夫曼编码
    HuffmanTreeNode *lchild, *rchild; //左右孩子的指针
    HuffmanTreeNode()
    { //无参构造
        lchild = NULL;
        rchild = NULL;
    }
    HuffmanTreeNode(int in_data, int in_frequency) //有参构造
    {
        data = in_data;
        frequency = in_frequency;
        lchild = NULL;
        rchild = NULL;
    }
};

class HuffmanTree
{
private:
    HuffmanTreeNode *root;                  //哈夫曼树的根节点
    void createCode(HuffmanTreeNode *node); //对所有结点进行编码
public:
    void createTree(int datafrequency[]);                            //根据出现频数创建哈夫曼树
    vector<HuffmanTreeNode *> Nodes;                                 //存放所有叶子结点
    void Decode(char *filename, unsigned char *str, int fileLength); //解码，并输出到filename文件中
    void clear();                                                    //清理
};
/**
 * @description: 使用回溯法对所有结点进行编码
 * @param {HuffmanTreeNode} *node   待编码的结点
 * @return {*}
 */
void HuffmanTree::createCode(HuffmanTreeNode *node)
{
    //叶子节点，进行编码并退出
    if (node->lchild == NULL && node->rchild == NULL)
    {
        node->code = v;
        Nodes.push_back(node);
        return;
    }
    //进入左子树
    if (node->lchild != NULL)
    {
        v.push_back(0);
        createCode(node->lchild);
        v.pop_back();
    }
    //进入右子树
    if (node->rchild != NULL)
    {
        v.push_back(1);
        createCode(node->rchild);
        v.pop_back();
    }
}

struct cmp{
   bool operator()(HuffmanTreeNode* a, HuffmanTreeNode* b){
       return a->frequency >= b->frequency;
   }
};

/**
 * @description: 初始化哈夫曼树
 * @param {int} datafrequency   存放数据频次的数组
 * @return {*}
 */
void HuffmanTree::createTree(int datafrequency[])
{
    //建立优先队列
    // priority_queue<HuffmanTreeNode *, vector<HuffmanTreeNode *>, cmp> Q;
    PriorityQueue<HuffmanTreeNode *> Q(10000);
    //每个字节8位，所以0~255
    for (int i = 0; i < 256; i++)
    {
        //出现过，插入优先队列中
        if (datafrequency[i] != 0)
        {
            HuffmanTreeNode *newNode = new HuffmanTreeNode(i, datafrequency[i]);
            Q.push(newNode);
        }
    }
    //构建哈夫曼树
    HuffmanTreeNode *left, *right;
    while (Q.size() > 1)
    {
        left = Q.top();
        Q.pop();
        right = Q.top();
        Q.pop();
        HuffmanTreeNode *newNode = new HuffmanTreeNode;
        newNode->frequency = left->frequency + right->frequency;
        newNode->lchild = left;
        newNode->rchild = right;
        //插入新节点
        Q.push(newNode);
    }
    root = Q.top();
    //进行编码
    createCode(root);
}

/**
 * @description: 解码并输出到filename文件中
 * @param {char} *filename      要输出的文件名
 * @param {unsigned char} *str  存放待解码字节的数组
 * @param {int} fileLength      数组长度
 * @return {*}
 */
void HuffmanTree::Decode(char *filename, unsigned char *str, int fileLength)
{
    //以写方式打开文件
    ofstream output(filename);
    //解压后字节大小
    int count_ac=0;
    //nu作为缓冲数组
    int nu[8] = {0};
    //最后一个存放倒数第二个字节结束的位置
    int count_lock = str[fileLength - 1];
    //记录nu位置
    int count_nu = 0;
    //记录解码到哪一个字节
    int count_str = 0;
    //遍历指针
    HuffmanTreeNode *p = root;
    //解码
    //将第一个字节转换为二进制码
    char_to_nu(nu, str[count_str++]);
    
    while (true)
    {
        //到叶子节点
        if (p->lchild == NULL && p->rchild == NULL)
        {
            //消除换行符错误
            if (p->data != 13){
                output.put(p->data);
            }
            count_ac++;
            p = root;
            if(count_str == fileLength - 1 && count_lock == count_nu) break;
            //遍历到最后一个字符的最后一个位置退出
            
        }
        //缓冲区满，重置缓冲区
        if (count_nu == 8)
        {
            char_to_nu(nu, str[count_str++]);
            count_nu = 0;
        }
        //根据二进制码，进入右/左子树
        p = nu[count_nu++] == 1 ? p->rchild : p->lchild;
    }
    cout<<"解压后文件大小为："<<(1.0 * count_ac)/1048576<<"MB"<<endl;
}

/**
 * @description: 重置哈夫曼树
 * @return {*}
 */
void HuffmanTree::clear()
{
    Nodes.clear();
    root = NULL;
}
#endif