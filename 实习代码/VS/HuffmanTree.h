#pragma once
/*
 * @Descripttion: 哈夫曼树头文件
 * @Author: DLCT
 * @Date: 2022-07-11 08:43:57
 * @e-mail: 18109232165@163.com
 * @LastEditors: DLCT
 * @LastEditTime: 2022-07-18 10:18:52
 */
#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H
#include <vector>
#include <fstream>
using namespace std;



struct HuffmanTreeNode
{
    int data;                         //待编码数据
    int frequency;                    //出现频率
    vector<int> code;                 //哈夫曼编码
    HuffmanTreeNode* lchild, * rchild; //左右孩子的指针
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
    HuffmanTreeNode* root;                  //哈夫曼树的根节点
    void createCode(HuffmanTreeNode* node); //对所有结点进行编码
public:
    void createTree(int datafrequency[]);                            //根据出现频数创建哈夫曼树
    vector<HuffmanTreeNode*> Nodes;                                 //存放所有叶子结点
    void Decode(char* filename, unsigned char* str, int fileLength); //解码，并输出到filename文件中
    void clear();                                                    //清理
};

#endif