#include "lexer.h"
#include "ui_lexer.h"
#include "widget.h"
#include <qstring.h>
#include <QFile>
#include <QFileDialog>
using namespace std;
#include<bits/stdc++.h>
#define Initial_State 1
#define End_State 2
const int NM=1e2+10;//最大dfa个数
const int MM=1e3+10;//字符串最长长度
const int N=1e3+10;//最大顶点数
const int M=1e3+10;//最大边数
int num1=0;//统计nfa/dfa个数
int gnum=0;//文法总个数
char s1[30]=" #+-*/%&|!^<>=()[]{},;_.'\"";//len=26，转义字符
char s2[30]=" #+-*/%&|!^<>=()[]{},;_.'";//len=25，无转义字符
struct GRAMMAR//文法结构体
{
    char left[MM];//文法左部
    char val[NM][MM];
    bool is_terminator[NM];//是否为终结符
    int cnt;//文法长度
    void init()//初始化
    {
        cnt=0;
        memset(left,0,sizeof left);
        for(int i=0;i<NM;i++)
        {
            memset(val[i],0,sizeof val[i]);
            is_terminator[i]=0;
        }
    }
    void push_left(char _left[MM])//拼接左部
    {
        strcpy(left,_left);
    }
    void push_right(char _right[MM])//拼接右部
    {
        cnt++;
        strcpy(val[cnt],_right);
        is_terminator[cnt]=false;
    }
    void push_right(char _right)//拼接右部
    {
        cnt++;
        val[cnt][0]=_right;
        is_terminator[cnt]=true;
    }
}grammar1[N];

struct Edge//前向边结构体
{
    int to,nxt;
    char val;
};

struct NFA//NFA结构体(有向图)
{
    int head[N];//头结点
    int n;//顶点数
    int cnt;//边数
    Edge E[M];//有向边
    char name[N][MM];//存储结点名称
    int type[N];//表示结点类型，1为头结点，2位终结点
    map<string,int> mp;//创造键值对，节点名称与数字绑定
    set<char> st;//某一nfa所包含的所有终结符，比如数字、大小写字母等
    void init()//初始化
    {
        cnt=0;
        n=0;
        for(int i=0;i<N;i++)
            head[i]=-1;
    }
    void add(int s,int t,char v)
    {//加边
        E[++cnt].val=v;
        E[cnt].to=t;
        E[cnt].nxt=head[s];
        head[s]=cnt;
    }
    void add_edge(char A[MM],int lenA,char B[MM],int lenB,char x)//调用add函数加边 A-左部结点名称 lenA-左部结点长度 B-右部结点名称 lenB-右部结点长度
    {
        int s=-1,t=-1;
        st.insert(x);
        if(mp[A]==0)
        {
            s=++n;
            mp[A]=s;
            strcpy(name[s],A);
        }
        else s=mp[A];
        if(mp[B]==0)
        {
            t=++n;
            mp[B]=t;
            strcpy(name[t],B);
        }
        else t=mp[B];
        add(s,t,x);
    }
    void setType(char A[MM],int lenA,int ty)//设置结点类型
    {
        int s=-1;
        if(mp[A]==0){
            s=++n;
            mp[A]=s;
            strcpy(name[s],A);
        }
        else s=mp[A];
        type[s]=ty;
    }
    set<int> closure(int x)//求初始closure闭包
    {
        set<int> ans;
        queue<int> que;
        que.push(x);
        bool vis[N];
        memset(vis,0,sizeof vis);
        while(!que.empty())
        {
            int now=que.front();
            que.pop();
            vis[now]=1;
            ans.insert(now);
            for(int j=head[now];~j;j=E[j].nxt)
            {
                if(E[j].val=='@'&&vis[E[j].to]==0)
                {
                    que.push(E[j].to);
                }
            }
        }
        return ans;
    }
    set<int> move_closure(set<int> st,char x)//求后续closure闭包
    {
        set<int> ans;
        bool vis[N];
        memset(vis,0,sizeof vis);
        for(auto it1:st){
            int now=it1;
            for(int i=head[now];~i;i=E[i].nxt){
                if(E[i].val!=x) continue;
                if(vis[E[i].to]) continue;
                vis[E[i].to]=1;
                set<int> tmp=closure(E[i].to);
                for(auto it2:tmp) ans.insert(it2);
            }

        }
        return ans;
    }
}nfa[NM];

struct DFA//DFA结构体(有向图)
{
    int head[N];//头结点
    int n;//顶点数
    int cnt;//边数
    Edge E[M];//有向边
    map<int,set<int>>name;//存储结点名称(set<int>类似nfa中的结点名，几个nfa结点和为一个结点)
    int type[N];//表示结点类型，1为头结点，2位终结点
    map<set<int>,int>mp;//创造键值对，节点名称与数字绑定
    void init()//初始化
    {
        cnt=0;
        n=0;
        for(int i=0;i<N;i++) head[i]=-1;
    }
    void add(int s,int t,char v)
    {//加边
        E[++cnt].val=v;
        E[cnt].to=t;
        E[cnt].nxt=head[s];
        head[s]=cnt;
    }
    void add_edge(set<int> A,set<int> B,char x)
    {
        int s=-1,t=-1;
        if(mp[A]==0)
        {
            s=++n;
            mp[A]=s;
            name[s]=A;
        }
        else s=mp[A];
        if(mp[B]==0)
        {
            t=++n;
            mp[B]=t;
            name[t]=B;
        }
        else t=mp[B];
        add(s,t,x);
    }
    void setType(set<int> st,int ty)//设置结点类型
    {
        int s=-1;
        if(mp[st]==0)
        {
            s=++n;
            mp[st]=s;
            name[s]=st;
        }
        else
            s=mp[st];
        type[s]=ty;
    }
    int run(char A[MM])//匹配，匹配机制为，字符串匹配多的优先，并且文法在读入时，先读入的优先级高，后读入的优先级低
    {
        int now=1;
        int ans=0;
        int mx=0;
        int lenA=strlen(A);
        for(int i=0;i<lenA;i++)//从头结点进行字符串匹配，返回匹配长度
        {
            bool flag=false;
            for(int j=head[now];~j;j=E[j].nxt)
            {
                if(E[j].val==A[i])
                {
                    flag=true;
                    ans++;
                    if(type[E[j].to]==2)
                    {
                        mx=max(mx,ans);
                    }
                    now=E[j].to;
                    break;
                }
            }
            if(!flag)
             break;
        }
        return mx;
    }
}dfa1[NM];

void solve(char x,bool flag,bool f,int l1,int r1,int l2,int r2,char A[MM],int lenA,char B[MM],int lenB)//处理省略表示的符号
{
    gnum++;
    grammar1[gnum].push_left(A);
    if(flag)
    {
        num1++;
        nfa[num1].init();
        flag=false;
        nfa[num1].setType(A,lenA,Initial_State);
    }
    if(f)//A->@型
    {
        nfa[num1].setType(A,lenA,End_State);
        grammar1[gnum].push_right('@');
    }
    else if(l1==l2||r1==r2)//A->a型
    {
        nfa[num1].add_edge(A,lenA,"Final",5,x);
        nfa[num1].setType("Final",5,End_State);
        grammar1[gnum].push_right(x);
    }
    else//A->aB型
    {
        nfa[num1].add_edge(A,lenA,B,lenB,x);
        grammar1[gnum].push_right(x);
        grammar1[gnum].push_right(B);
    }
}
//set<char> fir[N];//存储first集合
//map<string,int> nonterminal_to_num;//非终结符to数字
//char num_to_nonterminal[N][MM];//数字to非终结符
//int tt=0;

/*set<char> get_first()//获取文法first集
{
    set<char> ans;
    for(int i=1;i<=gnum;i++){
        if(strcmp(grammar[i].left,grammar[1].left)!=0) continue;
        if(grammar[i].cnt==1&&grammar[i].is_terminator[1]==true&&grammar[i].val[1][0]=='@'){
            ans.insert('@');
            continue;
        }
        ans.insert(grammar[i].val[1][0]);
    }
    return ans;
}*/

set<char> fir[N];
map<string,int> nonterminal_to_num1;
char num_to_nonterminal1[N][MM];
int tt=0;

set<char> get_first()//获取每个非终结符的first集
{
    set<char> ans;
    for(int i=1;i<=gnum;i++)
    {
        if(strcmp(grammar1[i].left,grammar1[1].left)!=0)
            continue;
        if(grammar1[i].cnt==1&&grammar1[i].is_terminator[1]==true&&grammar1[i].val[1][0]=='@')
        {
            ans.insert('@');
            continue;
        }
        ans.insert(grammar1[i].val[1][0]);
    }
    return ans;
}

void nfa_to_dfa()//nfa确定化为dfa
{
    for(int i=1;i<=num1;i++)
    {
        dfa1[i].init();
        set<int> st0=nfa[i].closure(1);//求closure闭包
        dfa1[i].setType(st0,Initial_State);//设置开始结点
        queue< set<int> > que;
        que.push(st0);
        while(!que.empty())
        {
            set<int> now=que.front();
            que.pop();
            for(auto it:nfa[i].st)
            {
                set<int> tmp=nfa[i].move_closure(now,it);
                if(dfa1[i].mp[tmp]==0)
                {
                    que.push(tmp);
                    for(auto itt:tmp)
                    {
                        if(nfa[i].type[itt]==2){
                            dfa1[i].setType(tmp,End_State);
                            break;
                        }
                    }
                }
                dfa1[i].add_edge(now,tmp,it);
            }
        }
    //	dfa[i].debug();
    }
}

Lexer::Lexer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Lexer)
{
    ui->setupUi(this);
    setWindowTitle("词法分析器");
    this->setFixedSize(this->width(),this->height());
    connect(ui->fanhui,&QPushButton::clicked,this,&Lexer::Sendslot1);
    connect(ui->duru,&QPushButton::clicked,
            [=]()
    {
        QString filename=QFileDialog::getOpenFileName(this,"open","../","TXT(*.txt)");
        ui->out->setText("");
        ui->out->append("开始读入文法！\n");
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
                bool flag=true;//判断读入的是否是每组文法的第一行
                //while(scanf("%[^\n]",&s)!=EOF)
                for(auto it:list)
                {
                    QByteArray ba = it.toLatin1(); // must
                    s=ba.data();
                    int len=strlen(s);
                    if(s[0]=='*')//读完一组文法
                    {
                    //	nfa[num].debug();
                        set<char> tmp=get_first();
                        if(nonterminal_to_num1[grammar1[1].left]!=0)
                        {
                            fir[nonterminal_to_num1[grammar1[1].left]].insert(tmp.begin(),tmp.end());
                        }
                        else
                        {
                            tt++;
                            strcpy(num_to_nonterminal1[tt],grammar1[1].left);
                            nonterminal_to_num1[grammar1[1].left]=tt;
                            fir[tt]=tmp;
                        }
                    //	cout<<"~~~"<<tt<<' '<<fir[tt].size()<<endl;
                        for(int i=0;i<N;i++)
                        grammar1[i].init();//文法结构体初始化
                        gnum=0;
                        flag=true;
                        continue;
                    }
                    int l1=-1,r1=-1,l2=-1,r2=-1,bj=-1;
                    bool f=false;//判断是否为@
                    for(int i=0;i<len;i++)//标识左部<>位置
                    {
                        if(s[i]=='@') f=true;
                        if(s[i]=='<'&&l1==-1) l1=i;
                        if(s[i]=='>'&&r1==-1) r1=i;
                        if(i<len-1&&s[i]=='-'&&s[i+1]=='>'&&bj==-1) bj=i+1;
                    }
                    for(int i=len-1;i>=0;i--)//标识右部<>位置
                    {
                        if(s[i]=='>'&&r2==-1) r2=i;
                        if(s[i]=='<'&&l2==-1) l2=i;
                    }
                    char A[MM],B[MM],x;
                    memset(A,0,sizeof A);
                    memset(B,0,sizeof B);
                    int lenA=r1-l1-1;//左部长度
                    int lenB=r2-l2-1;//右部长度
                    for(int i=0;i<lenA;i++)//获取左部字符串内容
                    {
                        A[i]=s[l1+i+1];
                    }
                    for(int i=0;i<lenB;i++)//获取右部字符串内容
                    {
                        B[i]=s[l2+i+1];
                    }
                    bool fflag=false;//标记是否有需处理的省略表示字符
                    for(int i=bj+1;i<len;i++)
                    {
                        if(s[i]!=' ')
                        {
                            x=s[i];
                            if(i<len+1&&s[i]=='\\'&&s[i+1]=='n') x='\n';
                            if(i<len+1&&s[i]=='^'&&s[i+1]=='c')//^c表示小写字符集合
                            {
                                fflag=true;
                                for(char j='a';j<='z';j++)
                                {
                                    solve(j,flag,f,l1,r1,l2,r2,A,lenA,B,lenB);
                                }
                            }
                            if(i<len+1&&s[i]=='^'&&s[i+1]=='C')//^C表示大写字符集合
                            {
                                fflag=true;
                                for(char j='A';j<='Z';j++)
                                {
                                    solve(j,flag,f,l1,r1,l2,r2,A,lenA,B,lenB);
                                }
                            }
                            if(i<len+1&&s[i]=='^'&&s[i+1]=='d')//^d表示数字集合
                            {
                                fflag=true;
                                for(char j='0';j<='9';j++)
                                {
                                    solve(j,flag,f,l1,r1,l2,r2,A,lenA,B,lenB);
                                }
                            }
                            if(i<len+1&&s[i]=='^'&&s[i+1]=='s')//有转义字符字符串
                            {
                                fflag=true;
                                for(int j=0;j<26;j++)
                                {
                                    solve(s1[j],flag,f,l1,r1,l2,r2,A,lenA,B,lenB);
                                }
                            }
                            if(i<len+1&&s[i]=='^'&&s[i+1]=='S')//无转义字符字符串
                            {
                                fflag=true;
                                for(int j=0;j<25;j++)
                                {
                                    solve(s2[j],flag,f,l1,r1,l2,r2,A,lenA,B,lenB);
                                }
                            }
                            break;
                        }
                    }
                    memset(s,0,sizeof s);

                    if(fflag) continue;//若fflag=true表示当前结点为省略型，则不执行非省略型处理，否则执行非省略型处理
                    //非省略型结点处理
                    if(flag)
                    {
                        num1++;
                        nfa[num1].init();
                        flag=false;
                        nfa[num1].setType(A,lenA,Initial_State);
                    }
                    gnum++;
                    grammar1[gnum].push_left(A);
                    if(f)
                    {//A->@型
                        nfa[num1].setType(A,lenA,End_State);
                        grammar1[gnum].push_right('@');
                    }
                    else if(l1==l2||r1==r2)
                    {//A->a型
                        nfa[num1].add_edge(A,lenA,"Final",5,x);
                        nfa[num1].setType("Final",5,End_State);
                        grammar1[gnum].push_right(x);
                    }
                    else
                    {//A->aB型
                        nfa[num1].add_edge(A,lenA,B,lenB,x);
                        grammar1[gnum].push_right(x);
                        grammar1[gnum].push_right(B);
                    }
                }
            }
            file.close();
        }
        ui->out->append("读入完成！");
    }
            );

    connect(ui->baocun,&QPushButton::clicked,
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

    connect(ui->fenxi,&QPushButton::clicked,
            [=]()
    {
        //freopen("lexer_grammar.txt","r",stdin);
        //read_lexer_grammar();//读入正规文法并生成nfa
        nfa_to_dfa();//nfa转dfa
        //fclose(stdin);
        //freopen("lexer_source.txt","r",stdin);
        freopen("lexer_out.txt","w",stdout);
         //读入源代码 并输出token分析三元组
        QStringList list = ui->source->toPlainText().split("\n");
        ui->out->setText("");
        //char s[MM];
        char* s;
        int row=0;//标记代码行数
        bool flag=false;
        bool bflag=false;
        //while(scanf("%[^\n]",&s)!=EOF)
        for(auto it:list)
        {
            QByteArray ba = it.toLatin1(); // must
            s=ba.data();
            row++;
            int len=strlen(s);
            s[len]='\n';
            len++;
            if(s[0]=='/'&&s[1]=='/')
                continue;
            if(s[0]=='/'&&s[1]=='*')
            {
                flag=true;
            }
            if(flag==true)
            {
                for(int i=0;i<len-1;i++)
                {
                    if(s[i]=='*'&&s[i+1]=='/')
                    {
                        flag=false;
                        break;
                    }
                }
                continue;
            }
            for(int i=0;i<len;)
            {
                while(i<len&&(s[i]==' '||s[i]=='\n'))//去除空格与换行符
                    i++;
                int mxlen=0;//标记某一token内容长度
                char str[MM];
                memset(str,0,sizeof str);
                for(int j=1;j<=num1;j++)
                {
                    int tmp=dfa1[j].run(s+i);
                    if(mxlen<tmp)
                    {
                        mxlen=tmp;
                        strcpy(str,nfa[j].name[1]);
                    }
                }
                QString token;
                printf("(line %d,%s,",row,str);//输出所在行号、类别
                token.sprintf("(line %d,%s,",row,str);
                for(int j=0;j<mxlen;j++)
                {
                    if(s[i+j]=='\n')
                        continue;
                    printf("%c",s[i+j]);//输出Token
                    token=token+s[i+j];
                }
                printf(")\n");
                token=token+")";
                ui->out->append(token);
                if(strcmp(str,"error")==0)
                {
                    cout<<"发现词法错误！数字不能作为标识符的首字母"<<endl;
                    ui->out->append("发现词法错误！数字不能作为标识符的首字母");
                    bflag=true;
                    break;
                }
                i+=mxlen;
                while(i<len&&(s[i]==' '||s[i]=='\n'))
                    i++;
            }
            memset(s,0,sizeof s);
            if(bflag)
                break;
        }
        //输出first集
        ui->out->append("----------");
        for(int i=1;i<=tt;i++)
        {
            QString temp=num_to_nonterminal1[i];
            temp=temp+"::";
            for(auto it:fir[i])
            {
              temp=temp+QString(it)+" ";
            }
            ui->out->append(temp);
        }
        cout<<"----------"<<endl;
        for(int i=1;i<=tt;i++)
        {
            cout<<num_to_nonterminal1[i]<<"::";
            for(auto it:fir[i])
            {
                cout<<it<<" ";
            }
            cout<<endl;
        }

        fclose(stdout);
        fclose(stdin);
    }
            );
}

Lexer::~Lexer()
{
    delete ui;
}

void Lexer::Sendslot1()
{
    emit Mysignal1();
}
