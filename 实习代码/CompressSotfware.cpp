/*
 * @Descripttion:
 * @Author: DLCT
 * @Date: 2022-07-11 10:27:55
 * @e-mail: 18109232165@163.com
 * @LastEditors: DLCT
 * @LastEditTime: 2022-07-15 16:59:24
 */
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <malloc.h>
#include "HuffmanTree.h"
#include "function.h"
using namespace std;

HuffmanTreeNode *b[256] = {NULL};   //用于存放不同字节对的结点指针
HuffmanTree tree;                   //存放哈夫曼树

int openFile(char *filename, unsigned char **str);                      //
double compressFile(unsigned char *str, int filelength, char *filname);
double decompressFile(char *filename);
void changeFileName(char *filename, char *newextension);

void outputHuffmanCode();
void output(char *filename, unsigned char *str);
char nu_to_char(int *nu);



int main()
{
    clock_t start, finish;
    double totaltime;
    char oper;
    char filename[100];
    unsigned char *buf;
    int fileLength;
    while (1)
    {
        system("cls");
        printf("\n\n\t\t*********************************************\t\t\n");
        printf("\t\t\t\t使用Haffman 编码压缩文件\n");
        printf("\t\t*********************************************\t\t\n");
        printf("\n\n\n\t\t\t1.压缩文件.");
        printf("\n\t\t\t2.解压文件.");
        printf("\n\t\t\t0.退出程序.");
        printf("\n\n\t\t\t\t请选择所要操作:");
        cin >> oper;
        if (oper == '1')
        {
            system("cls");
            printf("\n\n\t\t*********************************************\t\t\n");
            printf("\t\t\t\t使用Haffman压缩文件\n");
            printf("\t\t*********************************************\t\t\n");
            while (1)
            {
                printf("请输入要压缩的文件：");
                scanf("%s", filename);
                fileLength = openFile(filename, &buf);
                if (fileLength == -1)
                    printf("文件打开失败，请重新输入!\n");
                else
                    break;
            }
            start = clock();
            double bl = compressFile(buf, fileLength, filename) * 100;
            finish = clock();
            totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
            printf("压缩成功！压缩时间为：%.3fs\n压缩比率为：%.2f%\n", totaltime, bl);
            cout << "是否输出哈夫曼编码(y/n)：";
            char ch;
            cin >> ch;
            if (ch == 'y')
            {
                outputHuffmanCode();
                getchar();
                getchar();
            }
            tree.clear();
            memset(filename, 0, sizeof(filename));
            // free(buf);
            for (int i = 0; i < 256; i++)
                b[i] = NULL;
        }
        else if (oper == '2')
        {
            system("cls");
            printf("\n\n\t\t*********************************************\t\t\n");
            printf("\t\t\t\t使用Haffman解压文件\n");
            printf("\t\t*********************************************\t\t\n");
            while (1)
            {
                printf("请输入要解压的文件：");
                scanf("%s", filename);
                FILE *file1 = NULL;
                file1 = fopen(filename, "rb"); //只读方式打开文件
                if (file1 == NULL)
                    cout << "error:文件打开失败！\n";
                else
                    break;
            }
            start = clock();
            totaltime = decompressFile(filename);
            finish = clock();
            printf("解压成功！解压时间为：%.3fs\n", (double)(finish - start) / CLOCKS_PER_SEC - totaltime);
            cout << "是否输出哈夫曼编码(y/n)：";
            char ch;
            cin >> ch;
            if (ch == 'y')
            {
                outputHuffmanCode();
                getchar();
                getchar();
            }
            tree.clear();
            memset(filename, 0, sizeof(filename));
            for (int i = 0; i < 256; i++)
                b[i] = NULL;
        }
        else if (oper == '0')
        {
            break;
        }
        else
        {
            printf("\n\n\t\t\t\terror:操作码错误，请重新输入\n");
            getchar();
            getchar();
        }
    }
}

int openFile(char *filename, unsigned char **str)
{
    FILE *input = NULL;
    input = fopen(filename, "rb");
    fseek(input, 0, SEEK_END);
    int inputLength = ftell(input);
    rewind(input);
    *str = (unsigned char *)malloc(inputLength);
    memset((*str), 0, inputLength);
    fread((*str), 1, inputLength, input);
    fclose(input);
    return inputLength;
}


double compressFile(unsigned char *str, int filelength, char *filename)
{
    int count[256] = {0};
    changeFileName(filename, "dlct");
    ofstream output(filename, ios::binary);
    for (int i = 0; i < filelength; i++)
        count[str[i]]++;
    tree.createTree(count);
    output << tree.Nodes.size();
    output << " ";
    for (int i = 0; i < tree.Nodes.size(); i++)
    {
        b[tree.Nodes[i]->data] = tree.Nodes[i];
        output << int(tree.Nodes[i]->data);
        output << " ";
        output << tree.Nodes[i]->frequency;
        output << " ";
    }
    int nu[8] = {0};
    int count_nu = 0;
    int x;
    int s = 0;
    for (int i = 0; i < filelength; i++)
    {
        x = str[i];
        for (int j = 0; j < b[x]->code.size(); j++)
        {
            if (count_nu == 8)
            {
                output.put(nu_to_char(nu));
                count_nu = 0;
                s++;
            }
            nu[count_nu++] = b[x]->code[j];
        }
    }
    if (count != 0)
    {
        output << nu_to_char(nu);
    }
    char ch = count_nu;
    output << ch;
    output.close();
    return (1.0 * s) / (1.0 * filelength);
}

double decompressFile(char *filename)
{
    int inputLength;
    int count[256] = {0};
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
    inputLength = openFile(filename, &str);
    int digit = getOffset(count, len);
    inputLength -= digit;
    str = str + digit;
    char newfilename[100];
    clock_t start, finish;
    start = clock();
    printf("请输入解压后文件名：:");
    scanf("%s", newfilename);
    finish = clock();
    tree.Decode(newfilename, str, inputLength);
    return (double)(finish - start) / CLOCKS_PER_SEC;
    ;
}

void outputHuffmanCode()
{
    cout << "字符\t\t出现频次\t\t\t\t哈夫曼编码\n";
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

void changeFileName(char *filename, char *newextension)
{
    int len = strlen(filename);
    char *ch = strchr(filename, '.');
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
}
