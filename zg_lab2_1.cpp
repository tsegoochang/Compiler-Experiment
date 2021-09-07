//�������
#include <bits/stdc++.h>
using namespace std;
/*
    ������Ⱦ���:
    -1����<��
    0����=
    1����>
    9�����
*/
const int Priority[6][6] = {
        1, -1, -1, -1, 1, 1,
        1, 1, -1, -1, 1, 1,
        1, 1, 9, 9, 1, 1,
        -1, -1, -1, -1, 0, 9,
        1, 1, 9, 9, 1, 1,
        -1, -1, -1, -1, 9, 0};

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
//�ж��Ƿ�Ϊ�����
bool checkOp(char Op)
{
    if (Op == '+' || Op == '-' || Op == '*' || Op == '/')
        return true;
    return false;
}
//�жϱ��ʽ�Ƿ����
bool finderror(char *instring, char *curword)
{

    if (!(instring[0] == 'i' || instring[0] == '('||instring[0]=='-')) //�Գ�����������������ͷ
    {
        cout << "����" << endl;
        return false;
    }
    else if (checkOp(*curword) && checkOp(*(curword + 1))) //�������������
    {
        cout << "����" << endl;
        return false;
    }
    else if ((*curword == '#' || *curword == ')') && checkOp(*(curword - 1))) //�������û������
    {
        cout << "����" << endl;
        return false;
    }
    else if (*curword == '(' && checkOp(*(curword + 1))) //���ź�������
    {
        cout <<"����" << endl;
        return false;
    }
    return true;
}
//�����ս�������Ⱦ����е�λ�ã���Ϊ�ս��ʱ����0
int Loacte(char word)
{
    if (word == '+' || word == '-') //+��-�ȼ�
        return 1;
    else if (word == '*' || word == '/') //*��/�ȼ�
        return 2;
    else if (word == 'i')
        return 3;
    else if (word == '(')
        return 4;
    else if (word == ')')
        return 5;
    else if (word == '#')
        return 6;
    else
        return 0;
}

int main()
{
    //ջ
    char instack[50];
    int _stackp = 1;
    //����
    string Sentence;
    char instring[50];
    memset(instack,0,50);
    memset(instring,0,50);
    char *curword; //��ǰ�ַ�
    int key, Relation;

    instack[_stackp] = '#';
    //�����������ʽ����������
    //cout << "�����������ʽ(���֡���ʶ����+��-��*��/��Ӣ������)��" << endl;
    cin >> Sentence;
    Sentence = Sentence + "#";
    int Len = Sentence.length();
    int j = 0;
    for (int i = 0; i < Len; i++)
    {
        if (checkNum(Sentence[i]))
        {
            while (checkNum(Sentence[i + 1])) //�������滻Ϊi
                i++;
            instring[j++] = 'i';
        }
        else if (checkLetter(Sentence[i]))
        {
            while (checkLetter(Sentence[i + 1]) || checkNum(Sentence[i + 1])) //����ʶ���滻Ϊi
            {
                i++;
            }

            instring[j++] = 'i';
        }
        else
            instring[j++] = Sentence[i];
    }
    curword = instring;

    while (1)
    {
        if (!finderror(instring, curword)) //�жϱ��ʽ�Ƿ����
        {
            cout << "����" << endl;
            break;
        }
        if (Loacte(instack[_stackp])) //��ջ��Ϊ�ս����#������ջ���Ƚ����ȼ���������ջ��-1���ս���Ƚ�
            key = _stackp;
        else
            key = _stackp - 1;
        Relation = Priority[Loacte(instack[key]) - 1][Loacte(*curword) - 1]; //������ȹ�ϵ
        if (Relation == -1) //��ǰ�ַ����ȶȸߣ��ƽ�
        {
            instack[++_stackp] = *curword;
            instack[_stackp + 1] = '\0';
            curword++; //������һ���ַ�
        }
        else if (Relation == 0) //��ǰ�ַ����ȶ����
        {
            if (instack[key] == '#') //��ջ���ַ�Ϊ#�������
            {
                cout << "��ȷ" << endl;
                break;
            }
            else //���ǣ����ƽ�
            {
                instack[++_stackp] = *curword;
                instack[_stackp + 1] = '\0';
                curword++; //������һ���ַ�
            }
        }
        else if (Relation == 1) //��ǰ�ַ����ȶȵ���ջ���ַ�����Լ
        {
            char temp;
            while (1) //ѭ����ǰ����ǰһ���ַ�instack[key-1]<��instack[key]��λ��
            {
                temp = instack[key];
                if (Loacte(instack[key - 1]))
                    key--;
                else
                    key = key - 2;
                if (Priority[Loacte(instack[key]) - 1][Loacte(temp) - 1] == -1)
                    break;
            }
            _stackp = key + 1;
            instack[_stackp] = 'E';
            instack[_stackp + 1] = '\0'; //��Լ
        }
        else //��Relation��Ϊ�������������ʽ����
        {
            cout << "����" << endl;
            //cout << "Wrong!" << endl;
            break;
        }
    }
    system("pause");
    return 0;
}
