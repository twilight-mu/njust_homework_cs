#include "analyzer.h"
#include "ui_analyzer.h"
#include <QFile>
#include <QFileDialog>
using namespace std;
#include<bits/stdc++.h>
int line=100;//统计行数
int tempnum=0;//统计临时变量号
int max_line;

struct TOKEN//存储token三元式结构体
{
    int _line;//所在行数
    char type[100];//类型
    char val[100];//具体值
    void set_token(int __line,char _type[100],char _val[100])
    {
        _line=__line;
        strcpy(type,_type);
        strcpy(val,_val);
    }
}token[1000];
int token_cnt=0;//统计token个数

int get_num(string s)//获取需要增加的行数
{
    int ans=0;
    for(int i=0;i<s.length();i++)
    {
        if(s[i]=='='||s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/')
        ans++;
    }
    return ans;
}

Analyzer::Analyzer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Analyzer)
{


    ui->setupUi(this);
    setWindowTitle("语义分析器");
    this->setFixedSize(this->width(),this->height());
    connect(ui->fanhui,&QPushButton::clicked,this,&Analyzer::Sendslot3);

    connect(ui->token,&QPushButton::clicked,
            [=]()
    {
        QString filename=QFileDialog::getOpenFileName(this,"open","../","TXT(*.txt)");
        if(filename.isEmpty()==false)
        {
            QFile file(filename);
            bool isOK =file.open(QIODevice::ReadOnly);
            if(isOK==true)
            {
                QByteArray array;
                array=file.readAll();
                QString temp=array;
                char* s;
                QStringList list = temp.split("\n");
                    for(auto it:list)//输入三元组token
                    {
                        QByteArray ba = it.toLatin1(); // must
                        s=ba.data();
                        if(s[0]=='-')//"----"为分界符
                            break;
                        int len=strlen(s)-1;
                        int bj1=-1,bj2=-1,bj3=-1;
                        for(int i=0;i<len;i++)
                        {
                            if(s[i]==','&&bj1==-1)//定位行号
                            {
                                bj1=i;
                            }
                            else if(s[i]==','&&bj2==-1)//定位类别
                            {
                                bj2=i;
                            }
                            else if(s[i]==','&&bj1!=-1&&bj2!=-1) //定位Token内容
                                break;
                        }
                        bj3=bj1-1;
                        while(s[bj3-1]>='0'&&s[bj3-1]<='9')
                            bj3--;
                        int tmp=0;
                        char str1[100];
                        char str2[100];
                        memset(str1,0,sizeof str1);
                        memset(str2,0,sizeof str2);
                        for(int i=bj3;i<bj1;i++)//获取行号
                        {
                            tmp=tmp*10+s[i]-'0';
                        }
                        max_line=max(max_line,tmp);
                        for(int i=bj1+1;i<bj2;i++)//获取类别
                        {
                            str1[i-bj1-1]=s[i];
                        }
                        for(int i=bj2+1;i<len-1;i++)//获取Token内容
                        {
                            str2[i-bj2-1]=s[i];
                        }
                        token[++token_cnt].set_token(tmp,str1,str2);
                        memset(s,0,sizeof s);
                    }
                    token[++token_cnt].set_token(max_line,(char*)"END",(char*)"\1");
            }
            file.close();
        }
        for(int x=1;x<=max_line;x++)
        {
            QString temp="";
            for(int i=1;i<token_cnt;i++)
            {
                if(token[i]._line==x)
                {
                    if(!strcmp(token[i].type,"type"))
                    {
                        //cout<<token[i].val<<" ";
                        temp=temp+token[i].val;
                        temp=temp+" ";
                    }
                    else
                    {
                        //cout<<token[i].val;
                        temp=temp+token[i].val;
                    }
                }

            }
            ui->source->append(temp);
        }
    }
            );

    connect(ui->fenxi_2,&QPushButton::clicked,
            [=]()
    {
        line=100;
        tempnum=0;
        QStringList list = ui->source->toPlainText().split("\n");
        ui->out->setText("");
        string s;
        for(auto it:list)
        {
            s=it.toStdString();
            int len=s.length();
            //cout<<s<<endl;
            if(s[0]=='i'&&s[1]=='f')
            {
                solve_if(s);
            }
            else if(s[0]=='f'&&s[1]=='o'&&s[2]=='r')
            {
                solve_for(s);
            }
            else if(s[0]=='w'&&s[1]=='h'&&s[2]=='i'&&s[3]=='l'&&s[4]=='e')
            {
                solve_while(s);
            }
            else
            {
                solve_other(s);
            }
        }
        ui->out->append(QString::number(line)+":\n");
    }
            );

    connect(ui->baocun_2,&QPushButton::clicked,
            [=]()
    {
        QString filename=QFileDialog::getSaveFileName(this,"save","../","TXT(*.txt)");
        if(filename.isEmpty()==false)
        {
            QFile file;
            file.setFileName(filename);
            bool isOK =file.open(QIODevice::WriteOnly);
            if(isOK==true)
            {
                QString temp=ui->out->toPlainText();
                file.write(temp.toUtf8());
            }
            file.close();
        }
    }
            );
}

void Analyzer::solve_expression(string s)//分析一般赋值语句
{
    if((s[0]=='-'&&s[1]=='-')||(s[0]=='+'&&s[1]=='+'))//分析形如++a、--a的语句
    {
        string tempname=s.substr(2,s.length()-2);
        char code=s[0];
        QString tempout1;
        tempout1=QString::number(line)+":temp";
        tempout1+=QString::number(tempnum);
        tempout1+="=";
        tempout1+=QString::fromStdString(tempname);
        tempout1+=code;
        tempout1+="1";
        ui->out->append(tempout1);
        //cout<<line<<":"<<"temp"<<tempnum<<"="<<tempname<<code<<"1"<<endl;
        line++;
        QString tempout2;
        tempout2=QString::number(line)+":";
        tempout2+= QString::fromStdString(tempname);
        tempout2+="=temp";
        tempout2+=QString::number(tempnum);
        ui->out->append(tempout2);
        //cout<<line<<":"<<tempname<<"="<<"temp"<<tempnum<<endl;
        line++;
        tempnum++;
    }
    else if((s[s.length()-1]=='-'&&s[s.length()-2]=='-')||(s[s.length()-1]=='+'&&s[s.length()-2]=='+'))//分析形如a++、a--的语句
    {
        string tempname=s.substr(0,s.length()-2);
        char code=s[s.length()-1];
        QString tempout1;
        tempout1=QString::number(line)+":temp";
        tempout1+=QString::number(tempnum);
        tempout1+="=";
        tempout1+=QString::fromStdString(tempname);
        tempout1+=code;
        tempout1+="1";
        ui->out->append(tempout1);
        //cout<<line<<":"<<"temp"<<tempnum<<"="<<tempname<<code<<"1"<<endl;
        line++;
        QString tempout2;
        tempout2=QString::number(line)+":";
        tempout2+=QString::fromStdString(tempname);
        tempout2+="=temp";
        tempout2+=QString::number(tempnum);
        ui->out->append(tempout2);
        //cout<<line<<":"<<tempname<<"="<<"temp"<<tempnum<<endl;
        line++;
        tempnum++;
    }
    else//分析一般赋值语句
    {
        int ans=get_num(s);
        if(ans==1)
        {
            QString tempout;
            tempout=QString::number(line)+":";
            tempout+= QString::fromStdString(s);
            ui->out->append(tempout);
            //cout<<line<<":"<<s<<endl;
            line++;
        }
        else
        {
            string temp1="";
            string temp2="";
            int i=0;
            for(;i<s.length();i++)
            {
                if(s[i]=='=')
                break;
                temp1=temp1+s[i];
            }
            i++;
            for(;i<s.length();i++)
            {
                temp2=temp2+s[i];
            }
            QString tempout1;
            tempout1=QString::number(line)+":temp";
            tempout1+=QString::number(tempnum);
            tempout1+="=";
            tempout1+=QString::fromStdString(temp2);
            ui->out->append(tempout1);
            //cout<<line<<":"<<"temp"<<tempnum<<"="<<temp2<<endl;
            line++;
            QString tempout2;
            tempout2=QString::number(line)+":";
            tempout2+=QString::fromStdString(temp1);
            tempout2+="=temp";
            tempout2+=QString::number(tempnum);
            ui->out->append(tempout2);
            //cout<<line<<":"<<temp1<<"="<<"temp"<<tempnum<<endl;
            line++;
            tempnum++;
        }
    }
}

void Analyzer::solve_other(string s)//分析除if、while、for行之外的行
{

    int p1,p2;
    for(int i=0;i<s.length();i++)
    {
        string temp="";
        p1=i;
        for(int j=p1;j<s.length();j++)
        {
            if(s[j]==';')
            {
                p2=j;
                break;
            }
        }
        for(int j=p1;j<p2;j++)
        {
            if(s.substr(j,3)=="int")
            {
                j=j+3;
            }
            else if(s.substr(j,6)=="double")
            {
                j=j+6;
            }
            else if(s.substr(j,5)=="float")
            {
                j=j+5;
            }
            else
            {
                temp=temp+s[j];
            }

        }
        i=p2;
        solve_expression(temp);
        //cout<<"temp="<<temp<<endl;
    }
}


void Analyzer::solve_while(string s)//分析while行语句
{
    int len=s.length();
    int i;
    QString tempout1;
    tempout1=QString::number(line)+":";
    tempout1+="if not ";
    //cout<<line<<":"<<"if not ";
    for(i=6;i<len;i++)
    {
        if(s[i]==')')
        break;
        //cout<<s[i];
        tempout1+=s[i];
    }
    string temp;
    i=i+2;
    for(;i<len;i++)
    {
        if(s[i]=='}')
        break;
        temp=temp+s[i];

    }
    tempout1+=" goto ";
    tempout1+=QString::number(line+get_num(temp)+2);
    ui->out->append(tempout1);
    //cout<<" goto "<<line+get_num(temp)+2<<endl;
    int templine=line;
    line++;
    solve_other(temp);
    QString tempout2;
    tempout2=QString::number(line)+":goto ";
    tempout2+=QString::number(templine);
    ui->out->append(tempout2);
    //cout<<line<<":"<<"goto "<<templine<<endl;
    line++;
}

void Analyzer::solve_if(string s)//分析if行语句
{
    int len=s.length();
    int i;
    QString tempout1;
    tempout1=QString::number(line)+":if not ";
    //cout<<line<<":"<<"if not ";
    for(i=3;i<len;i++)
    {
        if(s[i]==')')
        break;
        //cout<<s[i];
        tempout1+=s[i];
    }
    string temp;
    i=i+2;
    for(;i<len;i++)
    {
        if(s[i]=='}')
        break;
        temp=temp+s[i];

    }
    tempout1+=" goto ";
    tempout1+=QString::number(line+get_num(temp)+1);
    ui->out->append(tempout1);
    //cout<<" goto "<<line+get_num(temp)+1<<endl;
    line++;
    solve_other(temp);
}

void Analyzer::solve_for(string s)//分析for行语句
{
    string temp1="";
    string temp2="";
    string temp3="";
    int len=s.length();
    int i;
    for(i=4;i<len;i++)
    {
        if(s[i]==';')
        break;
        temp1+=s[i];
    }
    i++;
    for(;i<len;i++)
    {
        if(s[i]==';')
        break;
        temp2+=s[i];
    }
    i++;
    for(;i<len;i++)
    {
        if(s[i]==')')
        break;
        temp3+=s[i];
    }
    solve_other(temp1+";");
    string temp;
    i=i+2;
    for(;i<len;i++)
    {
        if(s[i]=='}')
        break;
        temp=temp+s[i];

    }
    QString tempout1;
    //tempout1.sprintf("%d:if not ",line);
    tempout1=QString::number(line)+":";
    tempout1+="if not ";
    tempout1+=QString::fromStdString(temp2);
    tempout1+=" goto ";
    tempout1+=QString::number(line+get_num(temp)+4);
    ui->out->append(tempout1);
    //cout<<line<<":"<<"if not "<<temp2<<" goto "<<line+get_num(temp)+4<<endl;
    int templine=line;
    line++;
    solve_other(temp);
    solve_expression(temp3);
    QString tempout2;
    tempout2=QString::number(line)+":goto ";
    tempout2+=QString::number(templine);
    ui->out->append(tempout2);
    //cout<<line<<":"<<"goto "<<templine<<endl;
    line++;
}



Analyzer::~Analyzer()
{
    delete ui;
}

void Analyzer::Sendslot3()
{
    emit Mysignal3();
}
