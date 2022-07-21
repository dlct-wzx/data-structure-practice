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
  * @description: ʹ�û��ݷ������н����б���
  * @param {HuffmanTreeNode} *node   ������Ľ��
  * @return {*}
  */
vector<int> V;  //����ʱ�õ��Ŀɱ�����
void HuffmanTree::createCode(HuffmanTreeNode* node)
{
    //Ҷ�ӽڵ㣬���б��벢�˳�
    if (node->lchild == NULL && node->rchild == NULL)
    {
        node->code = V;
        Nodes.push_back(node);
        return;
    }
    //����������
    if (node->lchild != NULL)
    {
        V.push_back(0);
        createCode(node->lchild);
        V.pop_back();
    }
    //����������
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
 * @description: ��ʼ����������
 * @param {int} datafrequency   �������Ƶ�ε�����
 * @return {*}
 */
void HuffmanTree::createTree(int datafrequency[])
{
    //�������ȶ���
    // priority_queue<HuffmanTreeNode *, vector<HuffmanTreeNode *>, cmp> Q;
    PriorityQueue Q(10000);
    //ÿ���ֽ�8λ������0~255
    for (int i = 0; i < 256; i++)
    {
        //���ֹ����������ȶ�����
        if (datafrequency[i] != 0)
        {
            HuffmanTreeNode* newNode = new HuffmanTreeNode(i, datafrequency[i]);
            Q.push(newNode);
        }
    }
    //������������
    HuffmanTreeNode* left, * right;
    while (Q.size() > 1)
    {
        //���ף�Ϊ����
        left = Q.top();
        Q.pop();
        //���ף�Ϊ�ҽڵ�
        right = Q.top();
        Q.pop();
        //�����½��
        HuffmanTreeNode* newNode = new HuffmanTreeNode;
        newNode->frequency = left->frequency + right->frequency;
        newNode->lchild = left;
        newNode->rchild = right;
        //�����½ڵ�
        Q.push(newNode);
    }
    //root��Ϊ���ڵ�
    root = Q.top();
    //���б���
    createCode(root);
}

/**
 * @description: ���벢�����filename�ļ���
 * @param {char} *filename      Ҫ������ļ���
 * @param {unsigned char} *str  ��Ŵ������ֽڵ�����
 * @param {int} fileLength      ���鳤��
 * @return {*}
 */
void HuffmanTree::Decode(char* filename, unsigned char* str, int fileLength)
{
    //��д��ʽ���ļ�
    ofstream output(filename);
    //nu��Ϊ��������
    int nu[8] = { 0 };
    //���һ����ŵ����ڶ����ֽڽ�����λ��
    int count_lock = str[fileLength - 1];
    //��¼nuλ��
    int count_nu = 0;
    //��¼���뵽��һ���ֽ�
    int count_str = 0;
    int count_char = 0;
    //����ָ��
    HuffmanTreeNode* p = root;

    //����
    //����һ���ֽ�ת��Ϊ��������
    char_to_nu(nu, str[count_str++]);
    while (true)
    {
        //��Ҷ�ӽڵ�
        if (p->lchild == NULL && p->rchild == NULL)
        {
            //�������з�����
            if (p->data != 13)
                output.put(p->data);
            p = root;
            count_char++;
            //���������һ���ַ������һ��λ���˳�
            if (count_str == fileLength - 1 && count_lock == count_nu) break;
        }
        //�������������û�����
        if (count_nu == 8)
        {
            char_to_nu(nu, str[count_str++]);
            count_nu = 0;
        }
        //���ݶ������룬������/������
        p = nu[count_nu++] == 1 ? p->rchild : p->lchild;
    }
    cout << "�ļ���ѹ���СΪ��" << (1.0 * count_char) / 1048576 << "MB" << endl;
}

/**
 * @description: ���ù�������
 * @return {*}
 */
void HuffmanTree::clear()
{
    Nodes.clear();
    root = NULL;
}