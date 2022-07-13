/*
 * @Descripttion:
 * @Author: DLCT
 * @Date: 2022-07-11 10:27:55
 * @e-mail: 18109232165@163.com
 * @LastEditors: DLCT
 * @LastEditTime: 2022-07-13 17:50:12
 */
#include <iostream>
#include <fstream>
#include <string>
#include <malloc.h>
#include "HuffmanTree.h"
#include "function.h"
using namespace std;

// LL a[256] = {0};
HuffmanTreeNode *b[256] = {NULL};
// unsigned char *buf;
HuffmanTree tree;

LL openFile(char *filename, unsigned char **str);
double compressFile(unsigned char *str, LL filelength, char *filname);
double decompressFile(char *filename);
void changeFileName(char *filename);

void outputHuffmanCode();
void output(char *filename);
char nu_to_char(int *nu);
LL inputLength;

// int solve()
// {
//     char filename[] = "input.txt";
//     inputLength = openFile(filename, &buf);
//     cout << inputLength << endl;
//     for (int i = 0; i < inputLength; i++)
//     {
//         a[buf[i]]++;
//     }
//     tree.createTree(a);
//     vector<int>::iterator j;
//     cout << tree.Nodes.size() << endl;

//     for (int i = 0; i < tree.Nodes.size(); i++)
//     {
//         b[tree.Nodes[i]->data] = tree.Nodes[i];
//         cout << tree.Nodes[i]->data << " " << tree.Nodes[i]->frequency << endl;
//         for (j = tree.Nodes[i]->code.begin(); j != tree.Nodes[i]->code.end(); j++)
//         {
//             cout << *j << " ";
//         }
//         cout << endl;
//     }
//     cout << "there" << endl;
//     output("output.txt");
//     free(buf);
//     inputLength = openFile("output.txt", &buf);
//     cout << endl
//          << inputLength << endl;
//     cout << "----------------------------------------------" << endl;
//     tree.Decode("jm.txt", buf, inputLength);
//     free(buf);
//     return 0;
// }

// void output(char *filename)
// {
//     ofstream output(filename, ios::binary);
//     ofstream debug("debug.txt");
//     int nu[8] = {0};
//     int count = 0;
//     int x;
//     cout << "there" << endl;
//     int s = 0;
//     for (int i = 0; i < inputLength; i++)
//     {
//         x = buf[i];
//         for (int j = 0; j < b[x]->code.size(); j++)
//         {
//             if (count == 8)
//             {

//                 output.put(nu_to_char(nu));
//                 if (i >= 341 && i <= 350)
//                 {
//                     debug.put(nu_to_char(nu));
//                     for (int i = 0; i < 8; i++)
//                         cout << nu[i];
//                 }
//                 count = 0;
//                 s++;
//             }
//             nu[count++] = b[x]->code[j];
//         }
//     }
//     cout << "there" << endl;
//     cout << count << endl;
//     if (count != 0)
//     {
//         output << nu_to_char(nu);
//     }
//     char ch = count;
//     output << ch;
//     output.close();
// }

LL openFile(char *filename, unsigned char **str)
{
    FILE *input = NULL;
    input = fopen(filename, "rb");
    if (input == NULL)
    {
        cout << "文件打开失败！";
        return -1;
    }
    fseek(input, 0, SEEK_END);
    LL inputLength = ftell(input);
    rewind(input);
    *str = (unsigned char *)malloc(inputLength);
    memset((*str), 0, inputLength);
    fread((*str), 1, inputLength, input);
    fclose(input);
    return inputLength;
}

int main()
{
    //    solve();
    char oper;
    char filename[100];
    unsigned char *buf;
    LL fileLength;
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
            printf("压缩比为：%.2f%\n", compressFile(buf, fileLength, filename) * 100);
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
            free(buf);
            for(int i = 0;i < 256;i++) b[i] = NULL;
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
                    cout << "error:文件打开失败！";
                else    break;
            }
            printf("压缩比为：%.2f%\n", decompressFile(filename) * 100);
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
            free(buf);
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

double compressFile(unsigned char *str, LL filelength, char *filename)
{
    LL count[256] = {0};
    changeFileName(filename);
    ofstream output(filename);
    for (int i = 0; i < filelength; i++)
        count[str[i]]++;
    tree.createTree(count);
    output<<tree.Nodes.size();
    output<<" ";
    cout<<tree.Nodes.size();
    for (int i = 0; i < tree.Nodes.size(); i++)
    {
        b[tree.Nodes[i]->data] = tree.Nodes[i];
        output<<int(tree.Nodes[i]->data);
        output<<" ";
        output<<tree.Nodes[i]->frequency;
        output<<" ";
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

double decompressFile(char *filename){
    LL count[256];
    int len, nu;
    int ch;
    ifstream input(filename);
    input>>len;
    input.get();
    cout<<len;
    for(int i = 0;i < len;i++)
    {
        input>>ch;
        input>>nu;
        count[ch] = nu;
        cout<<ch<<" "<<nu<<endl;
    }
    cout<<"---------"<<endl;
    tree.createTree(count);
    cout<<"---------"<<endl;
    cout<<tree.Nodes.size()<<endl;
    for (int i = 0; i < tree.Nodes.size(); i++)
    {
        b[tree.Nodes[i]->data] = tree.Nodes[i];
    }
    cout<<"---------"<<endl;
    return 1.0;
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

void changeFileName(char *filename)
{
    int len = strlen(filename);
    filename[len + 1] = '\0';
    filename[len] = 't';
    filename[len - 1] = 'c';
    filename[len - 2] = 'l';
    filename[len - 3] = 'd';
}