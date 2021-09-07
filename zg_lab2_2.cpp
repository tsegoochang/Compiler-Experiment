//递归下降(
#include<bits/stdc++.h>
using namespace std;
int Length;          //句子长度
string Sentence;     //存储句子
char word[20]; //当前字符
int tag = 0;

void funE(char word[]);
void funT(char word[]);
void funF(char word[]);

//判断是否为数字
bool checkNum(char Num)
{
    if (Num >= '0' && Num <= '9')
        return true;
    return false;
}
//判断是否为标识符
bool checkLetter(char l)
{
    if (l == '_' || (l >= 'a' && l <= 'z') || (l >= 'A' && l <= 'Z'))
        return true;
    return false;
}
//读入字符
void read(char word[])
{
    int i;
    int temp = 0;
    for (i = 0; i < 20; i++)
        word[i] = '\0';
    if (tag > Length)
    {
        cout << "Error:End of the sentence." << endl;
        system("pause");
        exit(0);
    }
    word[temp++] = Sentence[tag++];
    if (checkLetter(word[temp - 1]))
        while (checkLetter(Sentence[tag]) || checkNum(Sentence[tag])) //输入标识符
            word[temp++] = Sentence[tag++];
    else
        while (checkNum(Sentence[tag]) && checkNum(Sentence[tag - 1])) //输入多位数
            word[temp++] = Sentence[tag++];
    return;
}

void funF(char word[])
{
    if (checkNum(word[0]) || checkLetter(word[0]))
    {
        read(word);
        return;
    }
    else if (strcmp(word, "(") == 0)
    {
        read(word);
        funE(word);
        if (strcmp(word, ")") == 0)
        {
            read(word);
            return;
        }
        else
        {
            cout << "Error:2" << endl;
            cout << "Wrong!" << endl;
            system("pause");
            exit(0);
        }
    }
    else
    {
        cout << "Error:1" << endl;
        cout << "Wrong!" << endl;
        system("pause");
        exit(0);
    }
}
void funT(char word[])
{
    funF(word);
    while (1)
    {
        if (strcmp(word, "*") == 0 || strcmp(word, "/") == 0)
        {
            read(word);
            funF(word);
        }
        else
            return;
    }
}
void funE(char word[])
{
    funT(word);
    while (1)
    {
        if (strcmp(word, "-") == 0 || strcmp(word, "+") == 0)
        {
            read(word);
            funT(word);
        }
        else
            return;
    }
}

int main()
{
    memset(word,0,20);
    //读入句子
    cout << "输入算数表达式(数字、标识符及+、-、*、/、英文括号)：" << endl;
    cin >> Sentence;
    Sentence = Sentence + "#";
    Length = Sentence.length();
    //语法分析
    read(word);
    funE(word);
    if (strcmp(word, "#") == 0)
    {
        cout << "Right!" << endl;
    }
    else
    {
        cout << "Error:0" << endl;
        cout << "Wrong!" << endl;
        system("pause");
        exit(0);
    }
    system("pause");
    return 0;
}