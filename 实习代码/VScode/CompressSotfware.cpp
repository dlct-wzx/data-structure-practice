/*
 * @Descripttion:
 * @Author: DLCT
 * @Date: 2022-07-11 10:27:55
 * @e-mail: 18109232165@163.com
 * @LastEditors: DLCT
 * @LastEditTime: 2022-07-21 10:44:17
 */
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <malloc.h>
#include "HuffmanTree.h"
#include "function.h"
using namespace std;

HuffmanTreeNode *b[256] = {NULL}; //用于存放不同字节对的结点指针
HuffmanTree tree;                 //存放哈夫曼树

int openFile(char *filename, unsigned char **str);       //打开文件
double compressFile(char *filname);                      //压缩文件
double decompressFile(char *filename);                   //解压文件
char* changeFileName(char *filename, char *newextension); //改变文件扩展名
void outputHuffmanCode();                                //输出哈夫曼编码

int main()
{
    clock_t start, finish; //用于计时
    double totaltime;      //总共用时
    char oper;             //选择的操作方式
    char filename[100];    //文件名称
    while (1)
    {
        memset(filename, 0, sizeof(filename));
        system("cls");
        printf("\n\n\t\t*********************************************\t\t\n");
        printf("\t\t\t\t基于Haffman编码压缩文件\n");
        printf("\t\t*********************************************\t\t\n");
        printf("\n\n\n\t\t\t1.压缩文件.");
        printf("\n\t\t\t2.解压文件.");
        printf("\n\t\t\t0.退出程序.");
        printf("\n\n\t\t\t\t请选择所要操作:");
        cin >> oper;
        if (oper == '1') //压缩文件
        {
            system("cls");
            printf("\n\n\t\t*********************************************\t\t\n");
            printf("\t\t\t\t使用Haffman编码压缩文件\n");
            printf("\t\t*********************************************\t\t\n");
            while (1)
            {
                //输入文件名称
                printf("请输入要压缩的文件：");
                scanf("%s", filename);
                FILE *file = NULL;
                //打开文件
                file = fopen(filename, "rb"); //只读方式打开文件
                //打开文件失败
                if (file == NULL)
                    cout << "error:文件打开失败！\n";
                else
                    break;
                fclose(file);
            }
            //记录开始时间
            start = clock();
            //压缩文件，并返回压缩率
            double bl = compressFile(filename) * 100;
            finish = clock();
            //计算压缩时间
            totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
            printf("压缩成功！压缩时间为：%.3fs\n压缩比率为：%.2f%\n", totaltime, bl);
            cout << "是否输出哈夫曼编码(y/n)：";

            //输出哈夫曼编码
            char ch;
            cin >> ch;
            if (ch == 'y')
            {

                outputHuffmanCode();
                getchar();
                getchar();
            }

            //清理哈夫曼树，文件名称，结点数组
            tree.clear();
            memset(filename, 0, sizeof(filename));
            for (int i = 0; i < 256; i++)
                b[i] = NULL;
        }
        else if (oper == '2') //解压
        {
            system("cls");
            printf("\n\n\t\t*********************************************\t\t\n");
            printf("\t\t\t\t使用Haffman编码解压文件\n");
            printf("\t\t*********************************************\t\t\n");
            while (1)
            {
                //输入文件名称
                printf("请输入要解压的文件：");
                scanf("%s", filename);
                FILE *file = NULL;
                //打开文件
                file = fopen(filename, "rb"); //只读方式打开文件
                //打开文件失败
                if (file == NULL)
                    cout << "error:文件打开失败！\n";
                else
                    break;
                fclose(file);
            }
            //记录解压开始时间
            start = clock();
            //解压文件，并返回中间等待的时间
            totaltime = decompressFile(filename);
            //记录解压结束时间
            finish = clock();
            printf("解压成功！解压时间为：%.3fs\n", (double)(finish - start) / CLOCKS_PER_SEC - totaltime);

            //输出哈夫曼树
            cout << "是否输出哈夫曼编码(y/n)：";
            char ch;
            cin >> ch;
            if (ch == 'y')
            {
                outputHuffmanCode();
                getchar();
                getchar();
            }

            //清理哈夫曼树，文件名称，结点数组
            tree.clear();
            memset(filename, 0, sizeof(filename));
            for (int i = 0; i < 256; i++)
                b[i] = NULL;
        }
        else if (oper == '0') //退出
        {
            break;
        }
        else //输错
        {
            printf("\n\n\t\t\t\terror:操作码错误，请重新输入\n");
            getchar();
            getchar();
        }
    }
}

/**
 * @description: 打开文件，并将文件写入str数组中
 * @param {char} *filename  待打开文件名称
 * @param {unsigned char} * 存放文件内容的数组
 * @return {int} 文件字节长度即数组长度
 */
int openFile(char *filename, unsigned char **str)
{

    FILE *input = NULL;
    //以只读打开文件
    input = fopen(filename, "rb");
    //将文件指针移到文件末尾
    fseek(input, 0, SEEK_END);
    //获得文件长度
    int filelength = ftell(input);
    //将文件指针移到文件头
    rewind(input);
    //为数组分配内存
    *str = (unsigned char *)malloc(filelength);
    //初始化数组
    memset((*str), 0, filelength);
    //将文件所有内容写入str
    fread((*str), 1, filelength, input);
    fclose(input);
    return filelength;
}

/**
 * @description: 压缩文件
 * @param {char} *filename  待压缩文件名称
 * @return {double}         文件压缩率
 */
double compressFile(char *filename)
{
    //初始化参数
    unsigned char *str;                    //存放文件内容的数组
    int filelength;                        //数组长度
    int count[256] = {0};                  //每种字节出现频次
    int nu[8] = {0};                       //字节缓冲数组
    int count_nu = 0;                      //缓冲数组的所在位置
    int count_ac = 0;                      //压缩后字节长度
    int x;                                 //字节转为int
    filelength = openFile(filename, &str); //打开文件
    cout<<"文件大小为："<<(1.0 * filelength)/1048576<<"MB"<<endl;
    char *old = changeFileName(filename, "dlct");      //修改文件后缀，并获得文件原始后缀名
    ofstream output(filename, ios::binary); //打开输出文件
    //构建哈夫曼树，获得哈夫曼编码
    for (int i = 0; i < filelength; i++) //统计每种字节频次
        count[str[i]]++;
    tree.createTree(count); //构建哈夫曼树，获得哈夫曼编码

    output << tree.Nodes.size(); //写入结点个数
    output << " ";
    for (int i = 0; i < tree.Nodes.size(); i++) //写入出现过的每种字节及其出现次数
    {
        b[tree.Nodes[i]->data] = tree.Nodes[i];
        output << int(tree.Nodes[i]->data); //转换为int型，否则会出错
        output << " ";
        output << tree.Nodes[i]->frequency;
        output << " ";
    }
    //文件主体内容写入
    for (int i = 0; i < filelength; i++) //遍历所有字符
    {
        x = str[i];                                 // char转为int
        for (int j = 0; j < b[x]->code.size(); j++) //处理第i个字符
        {
            if (count_nu == 8) //缓冲数组满，写入文件
            {
                output.put(nu_to_char(nu)); //将缓冲数组转换为char类型
                count_nu = 0;
                count_ac++;
            }
            nu[count_nu++] = b[x]->code[j];
        }
    }

    //文件最后一个字节处理
    if (count != 0)
    {
        output << nu_to_char(nu);
    }
    char ch = count_nu; // int转char
    output << ch;       //输出最后一个字符，编码时停止位置
    output.close();
    //返回压缩率
    cout<<"压缩后文件大小为："<<(1.0 * (count_ac + getOffset(count, tree.Nodes.size()) + 2))/1048576<<"MB"<<endl;
    return (1.0 * count_ac) / (1.0 * filelength);
}

/**
 * @description: 解压文件
 * @param {char} *filename 待解压文件名称
 * @return {double}        压缩率
 */
double decompressFile(char *filename)
{
    int filelength;
    int count[256] = {0};
    char newfilename[100];
    clock_t start, finish;
    unsigned char *str;
    int len, nu;
    int ch;
    ifstream input(filename);
    input >> len;
    input.get();
    for (int i = 0; i < len; i++)
    {
        input >> ch;
        input >> nu;
        count[ch] = nu;
    }
    tree.createTree(count);
    for (int i = 0; i < tree.Nodes.size(); i++)
        b[tree.Nodes[i]->data] = tree.Nodes[i];
    filelength = openFile(filename, &str);
    int digit = getOffset(count, len);
    start = clock();
    printf("请输入解压后文件名：");
    scanf("%s", newfilename);
    cout<<"解压成功!"<<endl;
    cout<<"解压前文件大小为："<<(1.0 * filelength)/1048576<<"MB"<<endl;
    filelength -= digit;
    str = str + digit;
    finish = clock();
    tree.Decode(newfilename, str, filelength);
    
    return (double)(finish - start) / CLOCKS_PER_SEC;
    
}

/**
 * @description:
 * @return {*}
 */
void outputHuffmanCode()
{
    cout << "字符ASCII码\t\t出现频次\t\t\t\t哈夫曼编码\n";
    for (int i = 0; i < 256; i++)
    {
        if (b[i] != NULL)
        {
            cout << b[i]->data << "\t\t" << b[i]->frequency << "\t\t\t\t\t";
            for (int j = 0; j < b[i]->code.size(); j++)
            {
                if (j != 0)
                    cout << " ";
                cout << b[i]->code[j];
            }
            cout << endl;
        }
    }
}

/**
 * @description: 改变文件后缀名
 * @param {char} *filename
 * @param {char} *newextension
 * @return {char*}  文件原始后缀名
 */
char* changeFileName(char *filename, char *newextension)
{
    int len = strlen(filename);
    char *ch = strchr(filename, '.');
    int ol = filename + len - ch;
    char *old = new char[ol];
    for(int i = 0;i < ol;i++){
        old[i] = *(ch + 1 + i);
    }
    if (ch != NULL)
    {
        for (int i = 0; i < strlen(newextension); i++)
            *(ch + i + 1) = newextension[i];
    }
    else
    {
        for (int i = 0; i < strlen(newextension); i++)
            filename[len + i] = newextension[i];
    }
    return old;
}
