/*
 * @Descripttion: 哈夫曼树头文件
 * @Author: DLCT
 * @Date: 2022-07-11 08:43:57
 * @e-mail: 18109232165@163.com
 * @LastEditors: DLCT
 * @LastEditTime: 2022-07-12 17:55:32
 */
#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H
#include "PriorityQueue.h"
#include "function.h"
#include <vector>
#include <map>
#define LL unsigned long long
using namespace std;

vector<int> v;

struct HuffmanTreeNode
{
    char data;    //待编码数据
    LL frequency; //出现频率
    vector<int> code;
    bool isdata; //
    HuffmanTreeNode *lchild, *rchild;
    HuffmanTreeNode() {}
    HuffmanTreeNode(char in_data, LL in_frequency)
    {
        data = in_data;
        frequency = in_frequency;
        isdata = true;
        lchild = NULL;
        rchild = NULL;
    }
};

//重载运算符，用于优先队列
bool operator<(const HuffmanTreeNode &n1, const HuffmanTreeNode &n2)
{
    return n1.frequency > n2.frequency;
}

bool operator>(const HuffmanTreeNode &n1, const HuffmanTreeNode &n2)
{
    return n1.frequency < n2.frequency;
}

class HuffmanTree
{
private:
    LL n; //字符个数
    HuffmanTreeNode *root;
    void createCode(HuffmanTreeNode *node); //编码
public:
    void createTree(LL datafrequency[]); //根据出现频数创建哈夫曼树
    vector<HuffmanTreeNode *> Nodes;     //存放结点
    void Decode(char *filename, unsigned char *str, LL fileLength);
};

void HuffmanTree::createCode(HuffmanTreeNode *node)
{
    if (node->isdata == true)
    {
        node->code = v;
        Nodes.push_back(node);
        return ;
    }
    if (node->lchild != NULL)
    {
        v.push_back(0);
        createCode(node->lchild);
        v.pop_back();
    }
    if (node->rchild != NULL)
    {
        v.push_back(1);
        createCode(node->rchild);
        v.pop_back();
    }
}

void HuffmanTree::createTree(LL datafrequency[])
{
    PriorityQueue<HuffmanTreeNode *> Q(10000);
    for (int i = 0; i < 256; i++)
    {
        if (datafrequency[i] != 0)
        {
            HuffmanTreeNode *newNode = new HuffmanTreeNode(int_to_char(i), datafrequency[i]);
            Q.insert(newNode);
        }
    }
    HuffmanTreeNode *left, *right;
    while (Q.length() > 1)
    {
        left = Q.del();
        right = Q.del();
        HuffmanTreeNode *newNode = new HuffmanTreeNode();
        newNode->frequency = left->frequency + right->frequency;
        newNode->isdata = false;
        newNode->lchild = left;
        newNode->rchild = right;
        Q.insert(newNode);
    }
    root = Q.del();
    createCode(root);
}

void HuffmanTree::Decode(char *filename, unsigned char *str, LL fileLength)
{
   
    ofstream output;
    output.open(filename, ios::binary);
    int nu[8] = {0};
    int count_lock = str[fileLength-1];
    int count_nu = 0;
    int count_str = 0;
    HuffmanTreeNode *p = root;
    cout<<fileLength<<endl;
    char_to_nu(nu, str[count_str++]);
    cout<<endl;
    int count = 0;
    while (true)
    {
        if (count_nu == 8)
        {
            if (count_str == fileLength - 1){
                if(count_lock == count_nu)
                    output<<p->data;
                break;
            }
            char_to_nu(nu, str[count_str++]);
            count_nu = 0;
        }
        if (p->lchild == NULL && p->rchild == NULL)
        {
            //消除换行符错误
            if(str[count_str-1] == 13 && str[count_str] == 10) continue;
            output.put(p->data);
            cout<<p->data;
            cout<<endl;
            count++;
            p = root;
        }
        cout<<nu[count];
        p = nu[count_nu++] == 1 ? p->rchild : p->lchild;
    }
}
#endif