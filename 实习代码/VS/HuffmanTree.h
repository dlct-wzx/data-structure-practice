#pragma once
/*
 * @Descripttion: ��������ͷ�ļ�
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
    int data;                         //����������
    int frequency;                    //����Ƶ��
    vector<int> code;                 //����������
    HuffmanTreeNode* lchild, * rchild; //���Һ��ӵ�ָ��
    HuffmanTreeNode()
    { //�޲ι���
        lchild = NULL;
        rchild = NULL;
    }
    HuffmanTreeNode(int in_data, int in_frequency) //�вι���
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
    HuffmanTreeNode* root;                  //���������ĸ��ڵ�
    void createCode(HuffmanTreeNode* node); //�����н����б���
public:
    void createTree(int datafrequency[]);                            //���ݳ���Ƶ��������������
    vector<HuffmanTreeNode*> Nodes;                                 //�������Ҷ�ӽ��
    void Decode(char* filename, unsigned char* str, int fileLength); //���룬�������filename�ļ���
    void clear();                                                    //����
};

#endif