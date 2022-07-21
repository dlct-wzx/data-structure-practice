/*
 * @Descripttion:
 * @Author: DLCT
 * @Date: 2022-07-18 10:11:16
 * @e-mail: 18109232165@163.com
 * @LastEditors: DLCT
 * @LastEditTime: 2022-07-18 10:16:33
 */
#include "HuffmanTree.h"
#include "PriorityQueue.h"
#include "function.h"
#include <iostream>
 /**
  * @description: 使用回溯法对所有结点进行编码
  * @param {HuffmanTreeNode} *node   待编码的结点
  * @return {*}
  */
vector<int> V;  //编码时用到的可变数组
void HuffmanTree::createCode(HuffmanTreeNode* node)
{
    //叶子节点，进行编码并退出
    if (node->lchild == NULL && node->rchild == NULL)
    {
        node->code = V;
        Nodes.push_back(node);
        return;
    }
    //进入左子树
    if (node->lchild != NULL)
    {
        V.push_back(0);
        createCode(node->lchild);
        V.pop_back();
    }
    //进入右子树
    if (node->rchild != NULL)
    {
        V.push_back(1);
        createCode(node->rchild);
        V.pop_back();
    }
}

struct cmp {
    bool operator()(HuffmanTreeNode* a, HuffmanTreeNode* b) {
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
    PriorityQueue Q(10000);
    //每个字节8位，所以0~255
    for (int i = 0; i < 256; i++)
    {
        //出现过，插入优先队列中
        if (datafrequency[i] != 0)
        {
            HuffmanTreeNode* newNode = new HuffmanTreeNode(i, datafrequency[i]);
            Q.push(newNode);
        }
    }
    //构建哈夫曼树
    HuffmanTreeNode* left, * right;
    while (Q.size() > 1)
    {
        //队首，为左孩子
        left = Q.top();
        Q.pop();
        //队首，为右节点
        right = Q.top();
        Q.pop();
        //构建新结点
        HuffmanTreeNode* newNode = new HuffmanTreeNode;
        newNode->frequency = left->frequency + right->frequency;
        newNode->lchild = left;
        newNode->rchild = right;
        //插入新节点
        Q.push(newNode);
    }
    //root即为根节点
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
void HuffmanTree::Decode(char* filename, unsigned char* str, int fileLength)
{
    //以写方式打开文件
    ofstream output(filename);
    //nu作为缓冲数组
    int nu[8] = { 0 };
    //最后一个存放倒数第二个字节结束的位置
    int count_lock = str[fileLength - 1];
    //记录nu位置
    int count_nu = 0;
    //记录解码到哪一个字节
    int count_str = 0;
    int count_char = 0;
    //遍历指针
    HuffmanTreeNode* p = root;

    //解码
    //将第一个字节转换为二进制码
    char_to_nu(nu, str[count_str++]);
    while (true)
    {
        //到叶子节点
        if (p->lchild == NULL && p->rchild == NULL)
        {
            //消除换行符错误
            if (p->data != 13)
                output.put(p->data);
            p = root;
            count_char++;
            //遍历到最后一个字符的最后一个位置退出
            if (count_str == fileLength - 1 && count_lock == count_nu) break;
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
    cout << "文件解压后大小为：" << (1.0 * count_char) / 1048576 << "MB" << endl;
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