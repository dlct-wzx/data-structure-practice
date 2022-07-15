/*
 * @Descripttion: 哈夫曼树头文件
 * @Author: DLCT
 * @Date: 2022-07-11 08:43:57
 * @e-mail: 18109232165@163.com
 * @LastEditors: DLCT
 * @LastEditTime: 2022-07-14 16:16:32
 */
#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H
#include "PriorityQueue.h"
#include "function.h"
#include <queue>
#include <vector>
#include <map>
using namespace std;

vector<int> v;

struct HuffmanTreeNode
{
    int data;    //待编码数据
    int frequency; //出现频率
    vector<int> code;
    bool isdata; //
    HuffmanTreeNode *lchild, *rchild;
    HuffmanTreeNode() {
        isdata = false;
        lchild = NULL;
        rchild = NULL;
    }
    HuffmanTreeNode(int in_data, int in_frequency)
    {
        data = in_data;
        frequency = in_frequency;
        isdata = true;
        lchild = NULL;
        rchild = NULL;
    }
};

class HuffmanTree
{
private:
    char n; //字符个数
    HuffmanTreeNode *root;
    void createCode(HuffmanTreeNode *node); //编码
    void nodeRemove(HuffmanTreeNode*);
public:
    void createTree(int datafrequency[]); //根据出现频数创建哈夫曼树
    vector<HuffmanTreeNode *> Nodes;     //存放结点
    void Decode(char *filename, unsigned char *str, int fileLength);
    void clear();
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

struct cmp{
   bool operator()(HuffmanTreeNode* a, HuffmanTreeNode* b){
       return a->frequency >= b->frequency;
   }
};

void HuffmanTree::createTree(int datafrequency[])
{
    priority_queue<HuffmanTreeNode *, vector<HuffmanTreeNode *>, cmp> Q;
    // PriorityQueue<HuffmanTreeNode *> Q(10000);
    for (int i = 0; i < 256; i++)
    {
        if (datafrequency[i] != 0)
        {
            HuffmanTreeNode *newNode = new HuffmanTreeNode(i, datafrequency[i]);
            Q.push(newNode);
        }
    }
    HuffmanTreeNode *left, *right;
    while(Q.size() != 1)
    {
        left = Q.top();
        Q.pop();
        right = Q.top();
        Q.pop();
        HuffmanTreeNode *newNode = new HuffmanTreeNode;
        newNode->frequency = left->frequency + right->frequency;
        newNode->isdata = false;
        newNode->lchild = left;
        newNode->rchild = right;
        Q.push(newNode);
    }
    root = Q.top();
    createCode(root);
}

void HuffmanTree::Decode(char *filename, unsigned char *str, int fileLength)
{
   
    ofstream output(filename);
    int nu[8] = {0};
    int count_lock = str[fileLength-1];
    int count_nu = 0;
    int count_str = 0;
    HuffmanTreeNode *p = root;
    char_to_nu(nu, str[count_str++]);
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
            // cout<<endl;
            // for(int i = 0;i < 8;i++)
            //     cout<<nu[i];
            // cout<<endl;
            count_nu = 0;
        }
        if (p->lchild == NULL && p->rchild == NULL)
        {
            //消除换行符错误
            if(p->data != 13)
                output.put(p->data);
            count++;
            p = root;
        }
        p = nu[count_nu++] == 1 ? p->rchild : p->lchild;
    }
}

void HuffmanTree::clear(){
    n = 0;
    Nodes.clear();
    root = NULL;
    //nodeRemove(root);
}
void HuffmanTree::nodeRemove(HuffmanTreeNode *p){
    if(p->lchild == NULL && p->rchild ==NULL)
        delete p;
    nodeRemove(p->lchild);
    nodeRemove(p->rchild);
    delete p;
}
#endif