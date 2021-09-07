//�ݹ��½�(
#include<bits/stdc++.h>
using namespace std;
int Length;          //���ӳ���
string Sentence;     //�洢����
char word[20]; //��ǰ�ַ�
int tag = 0;

void funE(char word[]);
void funT(char word[]);
void funF(char word[]);

//�ж��Ƿ�Ϊ����
bool checkNum(char Num)
{
    if (Num >= '0' && Num <= '9')
        return true;
    return false;
}
//�ж��Ƿ�Ϊ��ʶ��
bool checkLetter(char l)
{
    if (l == '_' || (l >= 'a' && l <= 'z') || (l >= 'A' && l <= 'Z'))
        return true;
    return false;
}
//�����ַ�
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
        while (checkLetter(Sentence[tag]) || checkNum(Sentence[tag])) //�����ʶ��
            word[temp++] = Sentence[tag++];
    else
        while (checkNum(Sentence[tag]) && checkNum(Sentence[tag - 1])) //�����λ��
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
    //�������
    cout << "�����������ʽ(���֡���ʶ����+��-��*��/��Ӣ������)��" << endl;
    cin >> Sentence;
    Sentence = Sentence + "#";
    Length = Sentence.length();
    //�﷨����
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