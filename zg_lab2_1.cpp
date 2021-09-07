//算符优先
#include <bits/stdc++.h>
using namespace std;
/*
    算符优先矩阵:
    -1代表<·
    0代表=
    1代表·>
    9代表空
*/
const int Priority[6][6] = {
        1, -1, -1, -1, 1, 1,
        1, 1, -1, -1, 1, 1,
        1, 1, 9, 9, 1, 1,
        -1, -1, -1, -1, 0, 9,
        1, 1, 9, 9, 1, 1,
        -1, -1, -1, -1, 9, 0};

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
//判断是否为运算符
bool checkOp(char Op)
{
    if (Op == '+' || Op == '-' || Op == '*' || Op == '/')
        return true;
    return false;
}
//判断表达式是否出错
bool finderror(char *instring, char *curword)
{

    if (!(instring[0] == 'i' || instring[0] == '('||instring[0]=='-')) //以除减号以外的运算符开头
    {
        cout << "错误" << endl;
        return false;
    }
    else if (checkOp(*curword) && checkOp(*(curword + 1))) //两个运算符相邻
    {
        cout << "错误" << endl;
        return false;
    }
    else if ((*curword == '#' || *curword == ')') && checkOp(*(curword - 1))) //运算符后没有数字
    {
        cout << "错误" << endl;
        return false;
    }
    else if (*curword == '(' && checkOp(*(curword + 1))) //括号后接运算符
    {
        cout <<"错误" << endl;
        return false;
    }
    return true;
}
//返回终结符在优先矩阵中的位置，不为终结符时返回0
int Loacte(char word)
{
    if (word == '+' || word == '-') //+、-等价
        return 1;
    else if (word == '*' || word == '/') //*、/等价
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
    //栈
    char instack[50];
    int _stackp = 1;
    //输入
    string Sentence;
    char instring[50];
    memset(instack,0,50);
    memset(instring,0,50);
    char *curword; //当前字符
    int key, Relation;

    instack[_stackp] = '#';
    //输入算术表达式，过滤整理
    //cout << "输入算数表达式(数字、标识符及+、-、*、/、英文括号)：" << endl;
    cin >> Sentence;
    Sentence = Sentence + "#";
    int Len = Sentence.length();
    int j = 0;
    for (int i = 0; i < Len; i++)
    {
        if (checkNum(Sentence[i]))
        {
            while (checkNum(Sentence[i + 1])) //将数字替换为i
                i++;
            instring[j++] = 'i';
        }
        else if (checkLetter(Sentence[i]))
        {
            while (checkLetter(Sentence[i + 1]) || checkNum(Sentence[i + 1])) //将标识符替换为i
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
        if (!finderror(instring, curword)) //判断表达式是否出错
        {
            cout << "错误" << endl;
            break;
        }
        if (Loacte(instack[_stackp])) //若栈顶为终结符或#，则用栈顶比较优先级，否则用栈顶-1的终结符比较
            key = _stackp;
        else
            key = _stackp - 1;
        Relation = Priority[Loacte(instack[key]) - 1][Loacte(*curword) - 1]; //获得优先关系
        if (Relation == -1) //当前字符优先度高，移进
        {
            instack[++_stackp] = *curword;
            instack[_stackp + 1] = '\0';
            curword++; //处理下一个字符
        }
        else if (Relation == 0) //当前字符优先度相等
        {
            if (instack[key] == '#') //若栈内字符为#，则接受
            {
                cout << "正确" << endl;
                break;
            }
            else //不是，则移进
            {
                instack[++_stackp] = *curword;
                instack[_stackp + 1] = '\0';
                curword++; //处理下一个字符
            }
        }
        else if (Relation == 1) //当前字符优先度低于栈中字符，归约
        {
            char temp;
            while (1) //循环向前查找前一个字符instack[key-1]<·instack[key]的位置
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
            instack[_stackp + 1] = '\0'; //归约
        }
        else //若Relation不为上述情况，则表达式错误
        {
            cout << "错误" << endl;
            //cout << "Wrong!" << endl;
            break;
        }
    }
    system("pause");
    return 0;
}
