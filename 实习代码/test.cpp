/*
 * @Descripttion: 
 * @Author: DLCT
 * @Date: 2022-07-11 10:27:55
 * @e-mail: 18109232165@163.com
 * @LastEditors: DLCT
 * @LastEditTime: 2022-07-12 17:45:56
 */
#include <iostream>
#include <fstream>
#include <malloc.h>
#include "HuffmanTree.h"
#include "function.h"
using namespace std;

LL a[256]={0};
vector<int> b[256];
unsigned char *buf;
HuffmanTree tree;

LL openfile(char *filename);
void output(char *filename);
char nu_to_char(int *nu);
LL inputLength;

int main()
{
    char filename[] = "input.txt";
    inputLength = openfile(filename);
    cout<<inputLength<<endl;
    for(int i = 0;i < inputLength;i++){
        a[buf[i]]++;
    }
    tree.createTree(a);
    vector<int>::iterator j;
    cout<<tree.Nodes.size()<<endl;
    for(int i = 0;i < tree.Nodes.size();i++){
        b[tree.Nodes[i]->data] = tree.Nodes[i]->code;
        cout<<tree.Nodes[i]->data<<" "<<tree.Nodes[i]->frequency<<endl;
        for(j = tree.Nodes[i]->code.begin();j != tree.Nodes[i]->code.end();j++){
            cout<<*j<<" ";
        }
        cout<<endl;
    }
    output("output.txt");
    free(buf);
    inputLength =  openfile("output.txt");
    cout<<endl<<inputLength<<endl;
    cout<<"----------------------------------------------"<<endl;
    tree.Decode("jm.txt", buf, inputLength);
    free(buf);
    return 0;
}

void output(char *filename){
    ofstream output;
    output.open(filename, ios::out);
    int nu[8] = {0};
    int count = 0;
    int x;
    for(int i = 0;i < inputLength;i++){
        x = buf[i];
        cout<<buf[i];
        for(int j = 0;j < b[x].size();j++){
            if(count == 8){
                output<<nu_to_char(nu);
                count = 0;
            }
            nu[count++] = b[x][j];
        }
    }
    cout<<count<<endl;
    if(count != 0){
        output<<nu_to_char(nu);
    }
    char ch = count;
    output<<ch;
    output.close();
}

LL openfile(char *filename){
    FILE *input = NULL;
    input = fopen(filename, "rb");
    fseek(input, 0, SEEK_END);
    LL inputLength = ftell(input);
    rewind(input);
    buf = (unsigned char *)malloc(inputLength);
    memset(buf, 0, inputLength);
    fread(buf, 1, inputLength, input);
    fclose(input);
    return inputLength;
}


