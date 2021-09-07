#include<bits/stdc++.h>
using namespace std;

char K[43][15]={ "include", "using", "namespace", "define", "main", "break", "case", "char",
    "const", "continue", "default", "do", "double", "else", "enum", "extern",
    "float", "for", "cin", "cout", "int", "long", "string",
    "register", "return", "if", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void",
    "bool", "while", "scanf", "printf", "EOF", "NULL","std"};
char P[38][5]={ "*", "/", ";", "(", ")", "^", ",", "\"", "\'", "%", "~", "[", "]", "{",
    "}", "\\", ".", "\?", ":", "!", "&", "|", "<", ">", "=", "#",
    "!=", "<=", ">=", "==", "&&", "||", "<<", ">>", "+", "-", "++", "--"};
char C[100][100];
char STR[100][100];
char FC[100][100];
char I[100][100];
char sss[10000];
int checkK(char str[])
{
    int i=0;
    while(i<43)
    {
        if(strcmp(K[i],str)==0)
        {
            return i+1;
        }
        i++;
    }
    return 0;
}
int checkP(char str[])
{
    int i=0;
    while(i<38)
    {
        if(strcmp(P[i],str)==0)
        {
            return i+1;
        }
        i++;
    }
    return 0;
}
int outK(char str[])
{
    int k;
    k=checkK(str);
    if(k!=0)
    {
        cout<<"(K "<<k<<")";
        return k;
    }
    else
    return 0;
}
int outP(char str[])
{
     int k;
    k=checkP(str);
    if(k!=0)
    {
        cout<<"(P "<<k<<")";
        return k;
    }
    else
    return 0;
}
int checkC(char str)
{
    if(str>='0'&&str<='9')
    {
        return true;
    }
    return false;
}
int checkI(char str)
{
     if ((str == '_' )|| (str >= 'a' && str <= 'z') || (str >= 'A' && str <= 'Z'))
    {
        return true;
    }
    return false;
}
int checkCH(char* s,int& l,int len,int& v)
{
    int i,j;
    j=0;
    char zg[100];
    memset(zg,0,100);
    for(i=l;i<len;i++)
    {
        if(s[i]=='\"')
        {
            break;
        }
        j++;
        zg[i-l]=s[i];
    }
    if(i==len)//不会有代码到最后还是字符串
    {
        return 0;
    }
    else
    {
        strcpy(STR[v],zg);
        v++;
        l+=j+1;
        return 1;
    }
}
void zg_process()
{
    char s[10000];
    memset(s,0,10000);
    strcpy(s,sss);
    char s1[10];
    int i,j,k,l;
    int tag;
    int x,y,z,v,m,n,o;
    int x1,y1,z1;
    x=0;y=0;z=0;v=0;
    l=0;

    cout<<"Token序列：";
    while(l<strlen(s))
    {
        memset(s1,0,10);
        if(s[l]==' ')
        {
            l++;
        }
        if(s[l]>='a'&&s[l]<='z')//识别K和标识符
        {
            for(i=2;i<10;i++)
            {
                m=0;
               for(k=l;k<l+i;k++)
               {
                   if((s[k]>=' '&&s[k]<'0')||(s[k]>'9'&&s[k]<'A')||(s[k]>'Z'&&s[k]<'a')||(s[k]>='z'&&s[k]<='}')||(checkC(s[k])))
                   {
                       m=1;
                       break;
                   }
                   s1[k-l]=s[k];
               }
               if(m==1)
               {
                   break;
               }
                j=outK(s1);
                if(j!=0)
                {
                    l+=i;
                    break;
                }
                else
                {
                    m=1;
                }
            }
            if(m==1)
            {
                m=0;
                y1=0;
                 for(i=l;;i++)
                {
                    if(checkI(s[i])||(s[i]>='0'&&s[i]<='9'))
                    {
                        j=i-l;
                        I[y][j]=s[i];
                    }
                    else
                    {
                        break;
                    }
                }
                for(i=0;i<y;i++)
                {
                    if(strcmp(I[i],I[y])==0)
                    {
                        y1=i+1;
                        memset(I[y],0,100);
                        cout<<"(I "<<y1<<")";
                        break;
                    }
                }
                if(y1==0)
                {
                     cout<<"(I "<<y+1<<")";
                     y++;
                }

                l+=j+1;
            }
        }
        else if((s[l]>=' '&&s[l]<'0')||(s[l]>'9'&&s[l]<'A')||(s[l]>'Z'&&s[l]<'a')||(s[l]>'z'&&s[l]<='}'))//识别界符和标识符，还有字符串
        {
            for(i=1;i<3;i++)
            {
                n=0;
                tag=0;
               for(k=l;k<l+i;k++)
               {
                   s1[k-l]=s[k];
                   if(s[k]=='\"')
                   {
                       l+=1;
                         if(checkCH(s,l,strlen(s),v)!=0)
                        {
                            tag=1;
                            break;
                        }
                   }

               }
               if(tag==1)
               {
                   break;
               }
                j=outP(s1);
                if(j!=0)
                {
                    l+=i;
                    break;
                }
                else
                {
                     n=1;
                }
            }
            if(n==1)
            {
                n=0;
                if(checkI(s[l]))
                {
                    for(i=l;;i++)
                    {
                        if(checkI(s[i])||(s[i]>='0'&&s[i]<='9'))
                        {
                            j=i-l;
                            I[y][j]=s[i];
                        }
                        else
                        {
                            break;
                        }
                    }
                for(i=0;i<y;i++)
                {
                    if(strcmp(I[i],I[y])==0)
                    {
                        y1=i+1;
                        memset(I[y],0,100);
                        cout<<"(I "<<y1<<")";
                        break;
                    }
                }
                if(y1==0)
                {
                     cout<<"(I "<<y+1<<")";
                     y++;
                }
                l+=j+1;
               }
            }
        }
        else if(checkC(s[l]))//识别浮点数和整数
        {
            for(i=l;;i++)
            {
                o=0;
                if(checkC(s[i]))
                {
                    j=i-l;
                    C[x][j]=s[i];
                     if((s[i+1]=='.')&&(checkC(s[i+2])==1))
                    {
                        strcpy(FC[z],C[x]);
                        memset(C[x],0,100);
                        j++;
                        FC[z][j]=s[j];
                        for(k=i+2;;k++)
                        {
                            o=0;
                            j=k-l;
                            if(checkC(s[k]))
                            {
                                FC[z][j]=s[k];
                            }
                            else
                            {
                                o=1;
                                break;
                            }
                        }
                        if(o=1)
                        {
                            break;
                        }
                    }
                }
                else
                {
                    break;
                }
            }
            x1=0;
            z1=0;
            if(o==0)
            {
                for(i=0;i<x;i++)
                {
                    if(strcmp(C[i],C[x])==0)
                    {
                        x1=i+1;
                        memset(C[x],0,100);
                       cout<<"(C "<<x1<<")";
                       break;
                    }
                }
                if(x1==0)
                {
                     cout<<"(C "<<x+1<<")";
                    x++;
                }
                l+=j+1;
            }
           else
           {
                for(i=0;i<z;i++)
                {
                    if(strcmp(FC[i],FC[x])==0)
                    {
                        z1=i+1;
                        memset(FC[x],0,100);
                       cout<<"(FC "<<x1<<")";
                       break;
                    }
                }
                if(z1==0)
                {
                     cout<<"(FC "<<x+1<<")";
                    z++;
                }
                l+=j;
           }

        }
    }
    cout<<endl;
    cout<<"标识符表：";
    for(i=0;i<y;i++)
    {
        cout<<I[i]<<" ";
    }
    cout<<endl;
     cout<<"常数表：";
    for(i=0;i<x;i++)
    {
        cout<<C[i]<<" ";
    }
    cout<<endl;
     cout<<"实数表：";
    for(i=0;i<z;i++)
    {
        cout<<FC[i]<<" ";
    }
    cout<<endl;
    cout<<"字符(串）表：";
     for(i=0;i<v;i++)
    {
        cout<<STR[i]<<" ";
    }
    cout<<endl;
    system("pause");
}


void Format(char r[],int flag)
{
    int i;
    int Count = 0;
    for (i = 0; i <= flag; i++)
    {
        //删除注释
        if (r[i] == '/' && r[i + 1] == '*')
        {
            i = i + 2;
            while (r[i] != '*' && r[i + 1] != '/')
            {
                i++;
                if (r[i] == '@') //删除注释到文件末尾，提示错误
                {
                    cout << "ERROR:1" << endl;
                    exit(0);
                }
            }
            i = i + 2;
        }
        if (r[i] == '/' && r[i + 1] == '/')
            while (r[i] != '\n')
                i++;
        //删除换行符、制表符、回车
        if (r[i] != '\n' && r[i] != '\t' && r[i] != '\r')
            sss[Count++] = r[i];
        else
            sss[Count++] = ' ';
    }
    sss[Count] = '\0';
}
int main()
{
    int flag=0;
    FILE* fp;
    char fs[10000];
    char infile;
     if ((fp = fopen("D:\\Code\\zzg\\in.txt", "r")) == NULL)
    {
        cout << "Error01" << endl;
        exit(0);
    }
    fs[flag]=fgetc(fp);
    while(1)
    {
        flag++;
        infile = fgetc(fp);
        if (feof(fp))
            break;
        fs[flag] = infile;
    }
    fclose(fp);
    fs[flag] = '\0';
    Format(fs, flag);
    zg_process();
    return 0;
}
