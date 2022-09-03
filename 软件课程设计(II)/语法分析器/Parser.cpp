using namespace std;
#include<bits/stdc++.h> 
#pragma GCC optimize(3,"Ofast","inline") 
#define LL long long
#define MOVE_IN 1
#define STATUTE 2
#define ACC 3
#define ERR -1
const int MM=1e2+10;//字符串最长长度 
const int NN=500+10;//token个数最大值 
const int NM=1e2+10;//文法右边最大终结符/非终结符个数 
const int MN=1e2+10;//文法最大个数 
const int M=500+10;//项目最大个数
const int N=200+10;//项目集最大个数 

map<string,int> nonterminal_to_num;//非终结符与数字绑定 
char num_to_nonterminal[MN][MM];//数字与非终结符绑定 
int nonterminal_cnt=0;//非终结符个数统计 
map<char,int> terminator_to_num;//终结符与数字绑定
char num_to_terminator[MN];//数字与终结符绑定 
int terminator_cnt=0;//终结符个数统计 
map<string,bool> _is_empty;//非终结符是否能推出空 

void insert_nonterminal(char A[MM])//插入非终结符 
{
	if(nonterminal_to_num[A]==0)
	{
		nonterminal_cnt++;
		nonterminal_to_num[A]=nonterminal_cnt;
		strcpy(num_to_nonterminal[nonterminal_cnt],A);
	}
}

void insert_terminal(char A)//插入终结符 
{
	if(terminator_to_num[A]==0)
	{
		terminator_cnt++;
		terminator_to_num[A]=terminator_cnt;
		num_to_terminator[terminator_cnt]=A;
	}
}

struct TOKEN//存储token三元式结构体 
{
	int line;//所在行数 
	char type[MM];//类型 
	char val[MM];//具体值 
	void set_token(int _line,char _type[MM],char _val[MM])
	{
		line=_line;
		strcpy(type,_type);
		strcpy(val,_val);
	} 
}token[NN];
int token_cnt=0;//统计token个数 

struct GRAMMAR//文法结构体 
{
	char left[MM];//文法左部 
	char val[NM][MM];//文法右部 
	bool is_terminator[NM];//是否为终结符 
	int cnt;//文法长度 
	int id;//文法标记 
	void init()
	{
		cnt=0;
	}
	void push_left(char _left[MM],int _id)//设置文法左部 
	{
		strcpy(left,_left);
		id=_id;
	}
	void push_right(char _right[MM])//设置文法右部 
	{
		cnt++;
		strcpy(val[cnt],_right);
		is_terminator[cnt]=false;
		insert_nonterminal(_right); 
	}
	void push_right(char _right)//设置文法右部，单独char说明时终结符 
	{
		cnt++;
		val[cnt][0]=_right;
		is_terminator[cnt]=true;
		insert_terminal(_right);
	}
	int cal_right()//获取文法长度，若右部为单独终结符返回0 
	{
		if(cnt==1&&is_terminator[1]==true&&val[1][0]=='@') 
			return 0;
		return cnt;
	} 
	bool operator <(const GRAMMAR &gr)const//小于号重载，依次按照左部字符串大小-文法长度-右部字符串大小进行排序 
	{
		if(strcmp(left,gr.left)!=0) 
			return strcmp(left,gr.left)<0;
		if(cnt!=gr.cnt) 
			return cnt<gr.cnt;
		for(int i=1;i<=cnt;i++)
		{
			if(strcmp(val[i],gr.val[i])!=0) 
				return strcmp(val[i],gr.val[i])<0; 
		}
	}
	void write()//输出文法 
	{
		cout<<"<"<<left<<"> -> ";
		for(int i=1;i<=cnt;i++)
		{
			if(is_terminator[i]) 
				cout<<val[i][0];
			else 
				cout<<"<"<<val[i]<<">";
		}
		cout<<endl;
	}
}grammar[MN];

int num=0;//统计文法个数 
set<GRAMMAR> st[N];

struct SYMBOL//符号结构体，便于程序运行时建立符号栈 
{
	char x[MM];//符号内容 
	bool is;//符号是单一字符还是一串字符 
	void init(char _x[MM])
	{
		memset(x,0,sizeof x); 
		strcpy(x,_x);
		is=0;
	}
	void init(char _x)
	{
		memset(x,0,sizeof x); 
		x[0]=_x;
		is=1;
	}
};

void cal_all_grammar()//文法统一存储 
{
	for(int i=1;i<=num;i++)
	{
		st[nonterminal_to_num[grammar[i].left]].insert(grammar[i]);
	}
}

struct NONTERMINAL_FIRST//非终结符first集结构体 
{
	set<char> fir;
	bool is_cal=false;
}nonterminal_first[MN];

struct PROJECT//项目结构体 
{ 
	char left[MM];//项目集左部 
	char val1[NM][MM];//右部已规约部分 
	bool is_terminator1[NM];//右部已规约部分是否有终结符 
	int cnt1;//右部已规约部分长度 
	char val2[NM][MM];//右部待规约部分 
	bool is_terminator2[NM];//右部待规约部分是否有终结符 
	int cnt2;//右部待规约部分长度 
	char prospect;//向前搜索符 
	int id;//标识 
	void init()
	{
		cnt1=0;
		cnt2=0;
	} 
	bool operator <(const PROJECT &pj)const//小于号重载 
	{
		if(strcmp(left,pj.left)!=0) 
			return strcmp(left,pj.left)<0;
		if(cnt1+cnt2!=pj.cnt1+pj.cnt2) 
			return cnt1+cnt2<pj.cnt1+pj.cnt2;
		if(cnt1!=pj.cnt1) 
			return cnt1<pj.cnt1;
		for(int i=1;i<=cnt1;i++)
		{
			if(strcmp(val1[i],pj.val1[i])!=0) 
				return strcmp(val1[i],pj.val1[i])<0; 
		} 
		for(int i=1;i<=cnt2;i++)
		{
			if(strcmp(val2[i],pj.val2[i])!=0) 
				return strcmp(val2[i],pj.val2[i])<0;
		} 
		return prospect<pj.prospect;
	}
	void _set(GRAMMAR g,int at,char _prospect,int _id)//设置项目，通过文法设置 
	{
		prospect=_prospect;
		id=_id;
		strcpy(left,g.left);
		if(g.cnt==1&&g.is_terminator[1]==true&&g.val[1][0]=='@') 
			return;
		for(int i=1;i<at;i++)//at标识圆点位置 
		{
			cnt1++;
			strcpy(val1[cnt1],g.val[i]);
			is_terminator1[cnt1]=g.is_terminator[i]; 
		}
		for(int i=at;i<=g.cnt;i++)
		{
			cnt2++;
			strcpy(val2[cnt2],g.val[i]);
			is_terminator2[cnt2]=g.is_terminator[i]; 
		}
	}
	void _set(char _left[MM],char _val1[NM][MM],bool _is_terminator1[NM],int _cnt1,char _val2[NM][MM],bool _is_terminator2[NM],int _cnt2,char _prospect,int _id)//函数重载，设置项目，参数直接设置 
	{
		strcpy(left,_left);
		cnt1=_cnt1;
		for(int i=1;i<=cnt1;i++)
		{
			is_terminator1[i]=_is_terminator1[i];
			strcpy(val1[i],_val1[i]);
		}
		cnt2=_cnt2;
		for(int i=1;i<=cnt2;i++)
		{
			is_terminator2[i]=_is_terminator2[i];
			strcpy(val2[i],_val2[i]);
		}
		prospect=_prospect;
		id=_id;
	}
	void change_prospect(char _prospect)//更改向前搜索符 
	{
		prospect=_prospect;
	}
	void write()//项目输出 
	{
		cout<<"<"<<left<<"> -> ";
		for(int i=1;i<=cnt1;i++){
			if(is_terminator1[i]==false) cout<<"<"<<val1[i]<<">";
			else cout<<val1[i];
		}
		cout<<".";
		for(int i=1;i<=cnt2;i++){
			if(is_terminator2[i]==false) cout<<"<"<<val2[i]<<">";
			else cout<<val2[i];
		}
		cout<<"            "<<prospect<<"  "<<(int)prospect<<endl;
	}
};

struct PROJECT_SET//项目集结构体
{ 
	set<PROJECT> projects;
	void init()//初始化 
	{
		projects.clear();
	}
	void insert_project(PROJECT _pj)//项目集中插入项目 
	{
		projects.insert(_pj); 
	}
	void insert_project(set<PROJECT> _pjs)//项目集中插入多个项目 
	{
		projects.insert(_pjs.begin(),_pjs.end()); 
	}
	int cnt()//获取项目集个数 
	{
		return projects.size(); 
	}
	bool operator <(const PROJECT_SET &pjs)const//小于号重载 
	{
		return projects<pjs.projects;
	}
	void write()//输出 
	{
		cout<<"~~~~~~~~~~~~~~~~~~~~"<<endl;
		for(auto it:projects)
		{
			it.write();
		}
		cout<<"~~~~~~~~~~~~~~~~~~~~"<<endl<<endl<<endl;
	}
};

struct Edge
{
	int to,nxt;
	char val[MM];
	bool is;
}; 
//链式前向星存储 
struct DFA//DFA结构体(与词法分析器中的DFA基本相同，只不过每结点内容变成了项目集) 
{
	int head[N];//头结点 
	int n;//顶点数 
	int cnt;//边数 
	Edge E[M];//有向边 
	map<int,PROJECT_SET>name;//存储结点名称
	PROJECT_SET project_set[N];//项目集 
	map<PROJECT_SET,int>mp;//创造键值对，节点名称与数字绑定
	void init()//初始化 
	{
		cnt=0;
		n=0;
		for(int i=0;i<N;i++) 
			head[i]=-1;
	}
	void add(int s,int t,char v[MM],bool _is)
	{//加边 
		cnt++;
		strcpy(E[cnt].val,v);
		E[cnt].is=_is;
		E[cnt].to=t;
		E[cnt].nxt=head[s];
		head[s]=cnt;
	}
	bool add_edge(PROJECT_SET A,PROJECT_SET B,char x[MM],bool _is)
	{
		int s=-1,t=-1;
		bool flag=false;
		if(A.cnt()!=0&&mp[A]==0)
		{
			s=++n;
			mp[A]=s;
			name[s]=A;
		}
		else 
			s=mp[A];
		if(B.cnt()!=0&&mp[B]==0)
		{
			t=++n;
			mp[B]=t;
			name[t]=B;
			flag=true;
		}
		else 
			t=mp[B];
		if(A.cnt()==0||B.cnt()==0) 
			return false;
		add(s,t,x,_is);
		return flag;
	}
}dfa;
char sst[MM];

struct ACTION_GOTO//action-goto表结构体 
{
	int state_num;//状态总个数 
	int action[N][210];//action动作为MOVE_IN时，转入的状态号 
	int action_type[N][210];//action动作,MOVE_IN=1,STATUTE=2,ACC=3,ERR=-1
	int gt[N][MN];//goto的状态号 
	bool vis[N];//dfs遍历时标记已访问
	void dfs(int now)//dfs遍历,寻找移进的情况 
	{
		vis[now]=1;
		for(int i=dfa.head[now];~i;i=dfa.E[i].nxt)
		{
			if(dfa.E[i].is==true)
			{
				action[now][terminator_to_num[dfa.E[i].val[0]]]=dfa.E[i].to;
				action_type[now][terminator_to_num[dfa.E[i].val[0]]]=MOVE_IN;
			}
			else
			{
				gt[now][nonterminal_to_num[dfa.E[i].val]]=dfa.E[i].to;
			}
			if(vis[dfa.E[i].to]) 
				continue;
			dfs(dfa.E[i].to);
		}
	}
	void run()//制作action-goto表 
	{
		state_num=dfa.n;
		for(int i=1;i<=state_num;i++)
		{
			for(int j=1;j<=terminator_cnt;j++)
			{
				action_type[i][j]=ERR;
			}
			for(int j=1;j<=nonterminal_cnt;j++)
			{
				gt[i][j]=ERR;
			}
		}
		for(int i=1;i<=state_num;i++)
		{
			set<PROJECT> now=dfa.name[i].projects;
			for(auto it:now)
			{
				if(it.cnt2!=0) 
					continue;
				action[i][terminator_to_num[it.prospect]]=it.id;
				if(strcmp(sst,it.left)==0&&it.prospect=='\1')
				{
					action_type[i][terminator_to_num[it.prospect]]=ACC;
					continue;
				}
				action_type[i][terminator_to_num[it.prospect]]=STATUTE;
			}
		}
		memset(vis,0,sizeof vis);
		dfs(1);
	}
}ag;

void cal_empty()//计算每个非终结符是否能推出空 
{
	for(int i=1;i<=nonterminal_cnt;i++)
	{
		_is_empty[num_to_nonterminal[i]]=false; 
	}
	while(true) 
	{
		int tmp=0;
		for(int j=1;j<=num;j++)
		{
			if(_is_empty[grammar[j].left]==true) //已知能推出空，直接跳过 
				continue;
			if(grammar[j].cnt==1&&grammar[j].is_terminator[1]==true&&grammar[j].val[1][0]=='@')//右部为空，自然能推出空 
			{
				_is_empty[grammar[j].left]=true;
				tmp++;
				continue;
			}
			bool flag=true;
			for(int k=1;k<=grammar[j].cnt;k++)
			{
				if(grammar[j].is_terminator[k]||_is_empty[grammar[j].val[k]]==false)//存在终结符或右部不能推出空，则不能推出空 
				{
					flag=false;
					break;
				}
			}
			if(flag)
			{
				_is_empty[grammar[j].left]=true;
				tmp++;
			}
		}
		if(tmp==0) 
			break;
	}
}

set<char> cal_first(int now)//计算某一非终结符的first集
{ 
	set<char> ans;
	for(int i=1;i<=num;i++)
	{
		if(nonterminal_to_num[grammar[i].left]!=now)//寻找左部对应文法 
			continue;
		set<char> tmp;
		if(grammar[i].cnt==1&&grammar[i].is_terminator[1]==true&&grammar[i].val[1][0]=='@')//空产生式，插入@ 
		{
			ans.insert('@');
			continue;
		}
		for(int j=1;j<=grammar[i].cnt;j++)
		{
			if(grammar[i].is_terminator[j]==true)//右部是终结符 
			{
				tmp.insert(grammar[i].val[j][0]);
				break;
			}
			else//右部是非终结符 
			{
				int p=nonterminal_to_num[grammar[i].val[j]];
				if(nonterminal_first[p].is_cal==true)//算过了
				{ 
					tmp.insert(nonterminal_first[p].fir.begin(),nonterminal_first[p].fir.end());
					if(_is_empty[grammar[i].val[j]]==false) 
						break;
				}
				else//没算过则计算 
				{
					nonterminal_first[p].fir=cal_first(p);
					nonterminal_first[p].is_cal=true;
					tmp.insert(nonterminal_first[p].fir.begin(),nonterminal_first[p].fir.end());
					if(_is_empty[grammar[i].val[j]]==false) 
						break;
				}
			}
			if(j==grammar[i].cnt) 
				tmp.insert('@'); 
		}
		ans.insert(tmp.begin(),tmp.end());
	}
	return ans;
}

void cal_nonterminal_first()//计算所有非终结符的first集
{ 
	for(int i=1;i<=nonterminal_cnt;i++)
	{
		if(nonterminal_first[i].is_cal==true) //避免重复计算 
			continue;
		set<int>tmp;
		tmp.insert(i);
		nonterminal_first[i].fir=cal_first(i);
		nonterminal_first[i].is_cal=true;
	}
}

set<char> get_first(char val[NM][MM],bool is[NM],int _cnt)
{
	set<char> ans;
	for(int i=1;i<=_cnt;i++)
	{
		if(is[i])
		{
			ans.insert(val[i][0]);
			break;
		}
		ans.insert(nonterminal_first[nonterminal_to_num[val[i]]].fir.begin(),nonterminal_first[nonterminal_to_num[val[i]]].fir.end());
		if(_is_empty[val[i]]==false) 
			break;
	}
	return ans;
}

set<PROJECT> project_closure(PROJECT now)//获得某一项目的闭包 
{
	set<PROJECT> ans;
	if(now.cnt2==0||now.is_terminator2[1]==true)//待约部分为终结符 
	{
		ans.insert(now);
		return ans;
	}
	queue<PROJECT> que;
	que.push(now);
	while(!que.empty()) //如果待约部分不是非终结符，则加入新的产生式，直到闭包不再增大 
	{
		PROJECT x=que.front();
		que.pop();
		ans.insert(x);
		char val[NM][MM];
		bool is[NM];
		int _cnt=0;
		for(int i=2;i<=x.cnt2;i++)
		{
			_cnt++;
			strcpy(val[_cnt],x.val2[i]);
			is[_cnt]=x.is_terminator2[i];
		}
		_cnt++;
		val[_cnt][0]=x.prospect;
		is[_cnt]=true;
		set<char> pp=get_first(val,is,_cnt);
		int oo=nonterminal_to_num[x.val2[1]];
		for(auto itt:st[oo])
		{
			PROJECT tmp;
			tmp.init();
			tmp._set(itt,1,x.prospect,itt.id);
			for(auto it:pp)
			{
				if(it=='@')
					continue;
				tmp.change_prospect(it);
				if(ans.count(tmp)==0) //如果tmp不在ans集里则加入 
					que.push(tmp);
			}
		}
	}
	return ans;
}

void read_phaser_grammar()//读入文法 
{
	char s[MM];
	bool flag=true;
	while(scanf("%[^\n]",&s)!=EOF)//每次读一行 
	{
		getchar();
		int len=strlen(s);
		num++;//文法个数自增 
		int bj=-1,bj1=-1,bj2=-1;
		for(int i=0;i<len;i++)
		{
			if(s[i]=='-'&&s[i+1]=='>')
			{
				bj=i;//先定位文法左部 
				break;
			}
		}
		if(bj==-1) 
			continue;
		char str[MM];
		memset(str,0,sizeof str); 
		for(int i=0;i<bj;i++)//定位文法左部<>位置 
		{
			if(s[i]=='<') bj1=i;
			if(s[i]=='>') bj2=i;
		}
		for(int i=bj1+1;i<bj2;i++)//存储<>内的内容 
		{
			str[i-bj1-1]=s[i];
		}
		insert_nonterminal(str);//插入非终结符 
		grammar[num].push_left(str,num);//文法左部插入 
		if(flag)
		{
			flag=false;
			strcpy(sst,str);
		}
		deque<char> dq;
		int pp=bj+2;//定位右部位置 
		for(int i=bj+2;i<len;i++)
		{
			if(s[i]==' ') 
				continue;
			if(s[i]=='>')
			{
				bool flag=false;
				int bj3=-1;
				for(int j=i-1;j>=pp;j--)
				{
					if(s[j]=='<')
					{
						bj3=j;
						flag=true;//<abc>->k<ads>q<smk>
						break;    //0123456789ABCDEFGHI
								  //pp=7 bj3=8 
					}
				}
				if(flag)//flag为true,右部找到< 
				{
					for(int j=pp;j<bj3;j++)//单字符情况 
					{
						if(s[j]==' ') 
							continue;
						grammar[num].push_right(s[j]);
					}
					memset(str,0,sizeof str);
					for(int j=bj3+1;j<i;j++)//字符串情况 
					{
						str[j-bj3-1]=s[j];
					}
					grammar[num].push_right(str);
				}
				else//定位失败单字符 
				{
					for(int j=pp;j<=i;j++)
					{
						if(s[j]==' ') 
							continue;
						grammar[num].push_right(s[j]);
					}
				}
				pp=i+1;
			}
		}
		for(int j=pp;j<len;j++)//防止后置终结符遗漏 
		{
			if(s[j]==' ') 
				continue;
			grammar[num].push_right(s[j]);
		}
		memset(s,0,sizeof s);
	}
}

bool vvis[N];
int max_line=0;
void read_lexer_out()//读入词法分析器输出的三元组token和非终结符的first集 
{
	char s[MM];
	while(scanf("%[^\n]",&s)!=EOF)//输入三元组token 
	{
		getchar();
		if(s[0]=='-')//"----"为分界符 
			break;
		int len=strlen(s);
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
		char str1[MM];
		char str2[MM];
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
			insert_terminal(s[i]);
		}
		token[++token_cnt].set_token(tmp,str1,str2);
		insert_nonterminal(str1);
		memset(s,0,sizeof s);
	}
	token[++token_cnt].set_token(max_line,(char*)"END",(char*)"\1");
	insert_nonterminal((char*)"END");
	insert_terminal('\1');
	memset(s,0,sizeof s);
	while(scanf("%[^\n]",&s)!=EOF)//输入非终结符first集 
	{
		getchar();
		int len=strlen(s);
		int bj=-1;
		for(int i=0;i<len;i++)
		{
			if(s[i]==':'&&s[i+1]==':')//定位:: 
			{
				bj=i;
				break;
			}
		}
		char xx[MM];
		memset(xx,0,sizeof xx);
		for(int i=0;i<bj;i++)//读入非终结符 
		{
			xx[i]=s[i];
		}
		int pp=nonterminal_to_num[xx];
		vvis[pp]=1; 
		for(int i=bj+2;i<len;i++)//读入对应的first集 
		{
			if(s[i]==' ') 
				continue;
			nonterminal_first[pp].fir.insert(s[i]);
		}
		nonterminal_first[pp].is_cal=true;
		memset(s,0,sizeof s);
	}
}

PROJECT que[61000];
PROJECT_SET GO(PROJECT_SET pjs,char x[MM],bool is)
{
	PROJECT_SET an;
	an.init();
	set<PROJECT> ans;
	int l=0;
	int r=-1;
	for(auto it:pjs.projects)
	{
		if(it.cnt2==0||it.is_terminator2[1]!=is||strcmp(it.val2[1],x)!=0) 
			continue;
		char _left[MM];
		char _val1[NM][MM];
		bool _is_terminator1[NM];
		int _cnt1;
		char _val2[NM][MM];
		bool _is_terminator2[NM];
		int _cnt2;
		char _prospect;
		int _id;
		strcpy(_left,it.left);
		_cnt1=it.cnt1;
		_id=it.id;
		for(int i=1;i<=_cnt1;i++)
		{
			strcpy(_val1[i],it.val1[i]);
			_is_terminator1[i]=it.is_terminator1[i];
		}
		_cnt1++;
		strcpy(_val1[_cnt1],it.val2[1]);
		_is_terminator1[_cnt1]=it.is_terminator2[1];
		_cnt2=it.cnt2-1;
		for(int i=1;i<=_cnt2;i++)
		{
			strcpy(_val2[i],it.val2[i+1]);
			_is_terminator2[i]=it.is_terminator2[i+1];
		}
		_prospect=it.prospect;
		PROJECT pj;
		pj.init();
		pj._set(_left,_val1,_is_terminator1,_cnt1,_val2,_is_terminator2,_cnt2,_prospect,_id);
		r++;
		que[r]=pj;
	}
	if(l>r)
	{
		return an;
	}
	while(l<=r)
	{
		PROJECT x=que[l];
		l++;
		ans.insert(x);
		char val[NM][MM];
		bool is[NM];
		int _cnt=0;
		for(int i=2;i<=x.cnt2;i++)
		{
			_cnt++;
			strcpy(val[_cnt],x.val2[i]);
			is[_cnt]=x.is_terminator2[i];
		}
		_cnt++;
		val[_cnt][0]=x.prospect;
		is[_cnt]=true;
		set<char> pp=get_first(val,is,_cnt);
		int oo=nonterminal_to_num[x.val2[1]];
		for(auto itt:st[oo])
		{
			PROJECT tmp;
			tmp.init();
			tmp._set(itt,1,x.prospect,itt.id);
			for(auto it:pp)
			{
				if(it=='@') continue;
				tmp.change_prospect(it);
				if(ans.count(tmp)==0)
				{
					r++;
					que[r]=tmp;
				}
			}
		}
	}
	an.insert_project(ans);
	return an;
}
void make_project_set()//制作项目集 
{
	dfa.init();
	PROJECT pstart;
	PROJECT_SET ps;
	pstart.init();
	pstart._set(grammar[1],1,'\1',1);
	ps.insert_project(project_closure(pstart));//先求第一个闭包 
	queue<PROJECT_SET> que;
	que.push(ps);
	int ppn=1;
	while(!que.empty())//调用GO函数制作项目集，直到项目集不再扩大为止 
	{
		PROJECT_SET now=que.front();
		que.pop();
		for(int i=1;i<=terminator_cnt;i++)//终结符 
		{
			char x[MM];
			memset(x,0,sizeof x);
			x[0]=num_to_terminator[i];
			PROJECT_SET nxt=GO(now,x,1);
			bool flag=dfa.add_edge(now,nxt,x,1);
			if(flag)
			{
				que.push(nxt);
			}
		}
		for(int i=1;i<=nonterminal_cnt;i++)//非终结符 
		{
			char x[MM];
			memset(x,0,sizeof x);
			strcpy(x,num_to_nonterminal[i]);
			PROJECT_SET nxt=GO(now,x,0);
			bool flag=dfa.add_edge(now,nxt,x,0);
			if(flag)
			{
				que.push(nxt);	
			}
		}
	}
}

void debug_project_set()//输出项目集 
{
	freopen("project_set.txt","w",stdout);
	cout<<"Project_set num:"<<dfa.n<<endl;
	for(int i=1;i<=dfa.n;i++)
	{
		cout<<"----Project_set "<<i<<"----"<<endl;
		PROJECT_SET now=dfa.name[i];
		for(auto it:now.projects)
		{
			it.write();
		}
	} 
	fclose(stdout);
}

void make_action_goto()//制作action-goto表
{ 
	ag.run();
}

void debug_action_goto()//输出action-goto表 
{
	freopen("action_goto.txt","w",stdout);
	for(int i=1;i<=ag.state_num;i++)
	{
		cout<<"state:"<<i<<"-----------------"<<endl;
		for(int j=1;j<=terminator_cnt;j++)//终结符 
		{
			cout<<num_to_terminator[j]<<":";
			if(ag.action_type[i][j]==MOVE_IN) 
				cout<<"S"<<ag.action[i][j]<<endl;
			else if(ag.action_type[i][j]==STATUTE) 
				cout<<"r"<<ag.action[i][j]<<endl;
			else if(ag.action_type[i][j]==ACC) 
				cout<<"acc"<<endl;
			else if(ag.action_type[i][j]==ERR) 
				cout<<"err"<<endl;
			else 
				cout<<"type"<<ag.action_type[i][j]<<endl;
		}
		for(int j=1;j<=nonterminal_cnt;j++)//非终结符 
		{
			cout<<"<"<<num_to_nonterminal[j]<<">:";
			if(ag.gt[i][j]==ERR) 
				cout<<"err"<<endl;
			else 
				cout<<ag.gt[i][j]<<endl;
		}
		cout<<endl<<endl;
	}
	fclose(stdout);
}

void write_line(int x)//根据行数输出这一行的源代码 
{
	cout<<"line "<<x<<": ";
	for(int i=1;i<token_cnt;i++)
	{
		if(token[i].line==x) 
			cout<<token[i].val<<" ";
	}
	cout<<endl;
}

void post_error(TOKEN tk,int at,int x)//输出错误信息 
{
	cout<<"NO"<<endl;
	cout<<"----line information----"<<endl;//错误所发生的位置 
	if(tk.line>1) write_line(tk.line-1);
	write_line(tk.line);
	if(tk.line<max_line) write_line(tk.line+1);
	cout<<"------------------------"<<endl;//错误信息 
	cout<<"error line: "<<tk.line<<endl;
	cout<<"error value: "<<tk.val<<endl;
	cout<<"----expected symbol-----"<<endl;//错误特征 
	for(int j=1;j<=terminator_cnt;j++)
	{
		if(ag.action_type[x][j]!=ERR) 
			cout<<num_to_terminator[j]<<endl;
	}
	for(int j=1;j<=nonterminal_cnt;j++)
	{
		if(vvis[j]&&ag.gt[x][j]!=ERR) 
			cout<<"<"<<num_to_nonterminal[j]<<">"<<endl;
	}
	cout<<"-------------------------"<<endl<<endl;
}

void post_succ()//无语法错误打印成功 
{
	cout<<"YES"<<endl;
}

void solve_token()//对读入的token进行分析 
{
	freopen("parser_out.txt","w",stdout);
	stack<int> state_stack;//状态栈
	stack<SYMBOL> symbol_stack;//符号栈 
	state_stack.push(1);
	SYMBOL tmp;
	for(int i=1;i<=token_cnt;i++)
	{
		int tp=state_stack.top();
		bool flag=false;
		if(ag.gt[tp][nonterminal_to_num[token[i].type]]!=ERR)
		{
			tmp.init(token[i].type);
			symbol_stack.push(tmp);
			state_stack.push(ag.gt[tp][nonterminal_to_num[token[i].type]]);
			continue;
		}
		else
		{
			while(ag.action_type[tp][terminator_to_num[token[i].val[0]]]==STATUTE)//规约
			{
				int number=ag.action[tp][terminator_to_num[token[i].val[0]]];
				int shu=grammar[number].cal_right();
				for(int i=1;i<=shu;i++)
				{
					state_stack.pop();
					symbol_stack.pop();
				}
				tmp.init(grammar[number].left);
				symbol_stack.push(tmp);
				tp=state_stack.top();
				state_stack.push(ag.gt[tp][nonterminal_to_num[grammar[number].left]]);
				tp=state_stack.top();
			}
			tp=state_stack.top();
			if(ag.gt[tp][nonterminal_to_num[token[i].type]]!=ERR)
			{
				tmp.init(token[i].type);
				symbol_stack.push(tmp);
				state_stack.push(ag.gt[tp][nonterminal_to_num[token[i].type]]);
				continue;
			}
			int len=strlen(token[i].val);
			int poi=0;
			while(poi<len)
			{
				tp=state_stack.top();
				if(ag.action_type[tp][terminator_to_num[token[i].val[poi]]]==MOVE_IN)//移进
				{ 
					tmp.init(token[i].type[poi]);
					symbol_stack.push(tmp);
					state_stack.push(ag.action[tp][terminator_to_num[token[i].val[poi]]]);
					poi++;
				}
				else if(ag.action_type[tp][terminator_to_num[token[i].val[poi]]]==STATUTE)//规约
				{
					int number=ag.action[tp][terminator_to_num[token[i].val[poi]]];
					int shu=grammar[number].cal_right(); 
					for(int i=1;i<=shu;i++)
					{
						state_stack.pop();
						symbol_stack.pop();
					}
					tmp.init(grammar[number].left);
					symbol_stack.push(tmp);
					tp=state_stack.top();
					state_stack.push(ag.gt[tp][nonterminal_to_num[grammar[number].left]]);
				}
				else if(ag.action_type[tp][terminator_to_num[token[i].val[poi]]]==ACC)//接收
				{
					post_succ(); //输出成功信息 
					flag=true;
					break;
				}
				else
				{
					post_error(token[i],poi,tp);//输出错误信息 
					flag=true;
					break;
				}
			}
		}
		if(flag) break;
	}
	fclose(stdout);
}

int main()
{
	freopen("lexer_out.txt","r",stdin);
	read_lexer_out();//读入token列表
	fclose(stdin); 
	freopen("parser_grammar.txt","r",stdin);
	read_phaser_grammar();//读入语法程序 
	fclose(stdin);
	cal_empty();//计算每个非终结符是否能推出空
	cal_nonterminal_first();//计算每个终结符的first集 
	cal_all_grammar();//统计所有文法 
	make_project_set();//生成项目集 
	debug_project_set();//输出项目集 
	make_action_goto();//生成action goto表 
	debug_action_goto();//输出action-goto表 
	solve_token();//对读入的token序列进行语法分析 
	return 0;
} 

