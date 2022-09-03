using namespace std;
#include<bits/stdc++.h> 
#pragma GCC optimize(3,"Ofast","inline") 
#define LL long long
#define MOVE_IN 1
#define STATUTE 2
#define ACC 3
#define ERR -1
const int MM=1e2+10;//�ַ�������� 
const int NN=500+10;//token�������ֵ 
const int NM=1e2+10;//�ķ��ұ�����ս��/���ս������ 
const int MN=1e2+10;//�ķ������� 
const int M=500+10;//��Ŀ������
const int N=200+10;//��Ŀ�������� 

map<string,int> nonterminal_to_num;//���ս�������ְ� 
char num_to_nonterminal[MN][MM];//��������ս���� 
int nonterminal_cnt=0;//���ս������ͳ�� 
map<char,int> terminator_to_num;//�ս�������ְ�
char num_to_terminator[MN];//�������ս���� 
int terminator_cnt=0;//�ս������ͳ�� 
map<string,bool> _is_empty;//���ս���Ƿ����Ƴ��� 

void insert_nonterminal(char A[MM])//������ս�� 
{
	if(nonterminal_to_num[A]==0)
	{
		nonterminal_cnt++;
		nonterminal_to_num[A]=nonterminal_cnt;
		strcpy(num_to_nonterminal[nonterminal_cnt],A);
	}
}

void insert_terminal(char A)//�����ս�� 
{
	if(terminator_to_num[A]==0)
	{
		terminator_cnt++;
		terminator_to_num[A]=terminator_cnt;
		num_to_terminator[terminator_cnt]=A;
	}
}

struct TOKEN//�洢token��Ԫʽ�ṹ�� 
{
	int line;//�������� 
	char type[MM];//���� 
	char val[MM];//����ֵ 
	void set_token(int _line,char _type[MM],char _val[MM])
	{
		line=_line;
		strcpy(type,_type);
		strcpy(val,_val);
	} 
}token[NN];
int token_cnt=0;//ͳ��token���� 

struct GRAMMAR//�ķ��ṹ�� 
{
	char left[MM];//�ķ��� 
	char val[NM][MM];//�ķ��Ҳ� 
	bool is_terminator[NM];//�Ƿ�Ϊ�ս�� 
	int cnt;//�ķ����� 
	int id;//�ķ���� 
	void init()
	{
		cnt=0;
	}
	void push_left(char _left[MM],int _id)//�����ķ��� 
	{
		strcpy(left,_left);
		id=_id;
	}
	void push_right(char _right[MM])//�����ķ��Ҳ� 
	{
		cnt++;
		strcpy(val[cnt],_right);
		is_terminator[cnt]=false;
		insert_nonterminal(_right); 
	}
	void push_right(char _right)//�����ķ��Ҳ�������char˵��ʱ�ս�� 
	{
		cnt++;
		val[cnt][0]=_right;
		is_terminator[cnt]=true;
		insert_terminal(_right);
	}
	int cal_right()//��ȡ�ķ����ȣ����Ҳ�Ϊ�����ս������0 
	{
		if(cnt==1&&is_terminator[1]==true&&val[1][0]=='@') 
			return 0;
		return cnt;
	} 
	bool operator <(const GRAMMAR &gr)const//С�ں����أ����ΰ������ַ�����С-�ķ�����-�Ҳ��ַ�����С�������� 
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
	void write()//����ķ� 
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

int num=0;//ͳ���ķ����� 
set<GRAMMAR> st[N];

struct SYMBOL//���Žṹ�壬���ڳ�������ʱ��������ջ 
{
	char x[MM];//�������� 
	bool is;//�����ǵ�һ�ַ�����һ���ַ� 
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

void cal_all_grammar()//�ķ�ͳһ�洢 
{
	for(int i=1;i<=num;i++)
	{
		st[nonterminal_to_num[grammar[i].left]].insert(grammar[i]);
	}
}

struct NONTERMINAL_FIRST//���ս��first���ṹ�� 
{
	set<char> fir;
	bool is_cal=false;
}nonterminal_first[MN];

struct PROJECT//��Ŀ�ṹ�� 
{ 
	char left[MM];//��Ŀ���� 
	char val1[NM][MM];//�Ҳ��ѹ�Լ���� 
	bool is_terminator1[NM];//�Ҳ��ѹ�Լ�����Ƿ����ս�� 
	int cnt1;//�Ҳ��ѹ�Լ���ֳ��� 
	char val2[NM][MM];//�Ҳ�����Լ���� 
	bool is_terminator2[NM];//�Ҳ�����Լ�����Ƿ����ս�� 
	int cnt2;//�Ҳ�����Լ���ֳ��� 
	char prospect;//��ǰ������ 
	int id;//��ʶ 
	void init()
	{
		cnt1=0;
		cnt2=0;
	} 
	bool operator <(const PROJECT &pj)const//С�ں����� 
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
	void _set(GRAMMAR g,int at,char _prospect,int _id)//������Ŀ��ͨ���ķ����� 
	{
		prospect=_prospect;
		id=_id;
		strcpy(left,g.left);
		if(g.cnt==1&&g.is_terminator[1]==true&&g.val[1][0]=='@') 
			return;
		for(int i=1;i<at;i++)//at��ʶԲ��λ�� 
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
	void _set(char _left[MM],char _val1[NM][MM],bool _is_terminator1[NM],int _cnt1,char _val2[NM][MM],bool _is_terminator2[NM],int _cnt2,char _prospect,int _id)//�������أ�������Ŀ������ֱ������ 
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
	void change_prospect(char _prospect)//������ǰ������ 
	{
		prospect=_prospect;
	}
	void write()//��Ŀ��� 
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

struct PROJECT_SET//��Ŀ���ṹ��
{ 
	set<PROJECT> projects;
	void init()//��ʼ�� 
	{
		projects.clear();
	}
	void insert_project(PROJECT _pj)//��Ŀ���в�����Ŀ 
	{
		projects.insert(_pj); 
	}
	void insert_project(set<PROJECT> _pjs)//��Ŀ���в�������Ŀ 
	{
		projects.insert(_pjs.begin(),_pjs.end()); 
	}
	int cnt()//��ȡ��Ŀ������ 
	{
		return projects.size(); 
	}
	bool operator <(const PROJECT_SET &pjs)const//С�ں����� 
	{
		return projects<pjs.projects;
	}
	void write()//��� 
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
//��ʽǰ���Ǵ洢 
struct DFA//DFA�ṹ��(��ʷ��������е�DFA������ͬ��ֻ����ÿ������ݱ������Ŀ��) 
{
	int head[N];//ͷ��� 
	int n;//������ 
	int cnt;//���� 
	Edge E[M];//����� 
	map<int,PROJECT_SET>name;//�洢�������
	PROJECT_SET project_set[N];//��Ŀ�� 
	map<PROJECT_SET,int>mp;//�����ֵ�ԣ��ڵ����������ְ�
	void init()//��ʼ�� 
	{
		cnt=0;
		n=0;
		for(int i=0;i<N;i++) 
			head[i]=-1;
	}
	void add(int s,int t,char v[MM],bool _is)
	{//�ӱ� 
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

struct ACTION_GOTO//action-goto��ṹ�� 
{
	int state_num;//״̬�ܸ��� 
	int action[N][210];//action����ΪMOVE_INʱ��ת���״̬�� 
	int action_type[N][210];//action����,MOVE_IN=1,STATUTE=2,ACC=3,ERR=-1
	int gt[N][MN];//goto��״̬�� 
	bool vis[N];//dfs����ʱ����ѷ���
	void dfs(int now)//dfs����,Ѱ���ƽ������ 
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
	void run()//����action-goto�� 
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

void cal_empty()//����ÿ�����ս���Ƿ����Ƴ��� 
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
			if(_is_empty[grammar[j].left]==true) //��֪���Ƴ��գ�ֱ������ 
				continue;
			if(grammar[j].cnt==1&&grammar[j].is_terminator[1]==true&&grammar[j].val[1][0]=='@')//�Ҳ�Ϊ�գ���Ȼ���Ƴ��� 
			{
				_is_empty[grammar[j].left]=true;
				tmp++;
				continue;
			}
			bool flag=true;
			for(int k=1;k<=grammar[j].cnt;k++)
			{
				if(grammar[j].is_terminator[k]||_is_empty[grammar[j].val[k]]==false)//�����ս�����Ҳ������Ƴ��գ������Ƴ��� 
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

set<char> cal_first(int now)//����ĳһ���ս����first��
{ 
	set<char> ans;
	for(int i=1;i<=num;i++)
	{
		if(nonterminal_to_num[grammar[i].left]!=now)//Ѱ���󲿶�Ӧ�ķ� 
			continue;
		set<char> tmp;
		if(grammar[i].cnt==1&&grammar[i].is_terminator[1]==true&&grammar[i].val[1][0]=='@')//�ղ���ʽ������@ 
		{
			ans.insert('@');
			continue;
		}
		for(int j=1;j<=grammar[i].cnt;j++)
		{
			if(grammar[i].is_terminator[j]==true)//�Ҳ����ս�� 
			{
				tmp.insert(grammar[i].val[j][0]);
				break;
			}
			else//�Ҳ��Ƿ��ս�� 
			{
				int p=nonterminal_to_num[grammar[i].val[j]];
				if(nonterminal_first[p].is_cal==true)//�����
				{ 
					tmp.insert(nonterminal_first[p].fir.begin(),nonterminal_first[p].fir.end());
					if(_is_empty[grammar[i].val[j]]==false) 
						break;
				}
				else//û�������� 
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

void cal_nonterminal_first()//�������з��ս����first��
{ 
	for(int i=1;i<=nonterminal_cnt;i++)
	{
		if(nonterminal_first[i].is_cal==true) //�����ظ����� 
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

set<PROJECT> project_closure(PROJECT now)//���ĳһ��Ŀ�ıհ� 
{
	set<PROJECT> ans;
	if(now.cnt2==0||now.is_terminator2[1]==true)//��Լ����Ϊ�ս�� 
	{
		ans.insert(now);
		return ans;
	}
	queue<PROJECT> que;
	que.push(now);
	while(!que.empty()) //�����Լ���ֲ��Ƿ��ս����������µĲ���ʽ��ֱ���հ��������� 
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
				if(ans.count(tmp)==0) //���tmp����ans��������� 
					que.push(tmp);
			}
		}
	}
	return ans;
}

void read_phaser_grammar()//�����ķ� 
{
	char s[MM];
	bool flag=true;
	while(scanf("%[^\n]",&s)!=EOF)//ÿ�ζ�һ�� 
	{
		getchar();
		int len=strlen(s);
		num++;//�ķ��������� 
		int bj=-1,bj1=-1,bj2=-1;
		for(int i=0;i<len;i++)
		{
			if(s[i]=='-'&&s[i+1]=='>')
			{
				bj=i;//�ȶ�λ�ķ��� 
				break;
			}
		}
		if(bj==-1) 
			continue;
		char str[MM];
		memset(str,0,sizeof str); 
		for(int i=0;i<bj;i++)//��λ�ķ���<>λ�� 
		{
			if(s[i]=='<') bj1=i;
			if(s[i]=='>') bj2=i;
		}
		for(int i=bj1+1;i<bj2;i++)//�洢<>�ڵ����� 
		{
			str[i-bj1-1]=s[i];
		}
		insert_nonterminal(str);//������ս�� 
		grammar[num].push_left(str,num);//�ķ��󲿲��� 
		if(flag)
		{
			flag=false;
			strcpy(sst,str);
		}
		deque<char> dq;
		int pp=bj+2;//��λ�Ҳ�λ�� 
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
				if(flag)//flagΪtrue,�Ҳ��ҵ�< 
				{
					for(int j=pp;j<bj3;j++)//���ַ���� 
					{
						if(s[j]==' ') 
							continue;
						grammar[num].push_right(s[j]);
					}
					memset(str,0,sizeof str);
					for(int j=bj3+1;j<i;j++)//�ַ������ 
					{
						str[j-bj3-1]=s[j];
					}
					grammar[num].push_right(str);
				}
				else//��λʧ�ܵ��ַ� 
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
		for(int j=pp;j<len;j++)//��ֹ�����ս����© 
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
void read_lexer_out()//����ʷ��������������Ԫ��token�ͷ��ս����first�� 
{
	char s[MM];
	while(scanf("%[^\n]",&s)!=EOF)//������Ԫ��token 
	{
		getchar();
		if(s[0]=='-')//"----"Ϊ�ֽ�� 
			break;
		int len=strlen(s);
		int bj1=-1,bj2=-1,bj3=-1;
		for(int i=0;i<len;i++)
		{
			if(s[i]==','&&bj1==-1)//��λ�к� 
			{
				bj1=i;
			}
			else if(s[i]==','&&bj2==-1)//��λ��� 
			{
				bj2=i;
			}
			else if(s[i]==','&&bj1!=-1&&bj2!=-1) //��λToken���� 
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
		for(int i=bj3;i<bj1;i++)//��ȡ�к� 
		{
			tmp=tmp*10+s[i]-'0';
		}
		max_line=max(max_line,tmp);
		for(int i=bj1+1;i<bj2;i++)//��ȡ��� 
		{
			str1[i-bj1-1]=s[i];
		}
		for(int i=bj2+1;i<len-1;i++)//��ȡToken���� 
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
	while(scanf("%[^\n]",&s)!=EOF)//������ս��first�� 
	{
		getchar();
		int len=strlen(s);
		int bj=-1;
		for(int i=0;i<len;i++)
		{
			if(s[i]==':'&&s[i+1]==':')//��λ:: 
			{
				bj=i;
				break;
			}
		}
		char xx[MM];
		memset(xx,0,sizeof xx);
		for(int i=0;i<bj;i++)//������ս�� 
		{
			xx[i]=s[i];
		}
		int pp=nonterminal_to_num[xx];
		vvis[pp]=1; 
		for(int i=bj+2;i<len;i++)//�����Ӧ��first�� 
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
void make_project_set()//������Ŀ�� 
{
	dfa.init();
	PROJECT pstart;
	PROJECT_SET ps;
	pstart.init();
	pstart._set(grammar[1],1,'\1',1);
	ps.insert_project(project_closure(pstart));//�����һ���հ� 
	queue<PROJECT_SET> que;
	que.push(ps);
	int ppn=1;
	while(!que.empty())//����GO����������Ŀ����ֱ����Ŀ����������Ϊֹ 
	{
		PROJECT_SET now=que.front();
		que.pop();
		for(int i=1;i<=terminator_cnt;i++)//�ս�� 
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
		for(int i=1;i<=nonterminal_cnt;i++)//���ս�� 
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

void debug_project_set()//�����Ŀ�� 
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

void make_action_goto()//����action-goto��
{ 
	ag.run();
}

void debug_action_goto()//���action-goto�� 
{
	freopen("action_goto.txt","w",stdout);
	for(int i=1;i<=ag.state_num;i++)
	{
		cout<<"state:"<<i<<"-----------------"<<endl;
		for(int j=1;j<=terminator_cnt;j++)//�ս�� 
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
		for(int j=1;j<=nonterminal_cnt;j++)//���ս�� 
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

void write_line(int x)//�������������һ�е�Դ���� 
{
	cout<<"line "<<x<<": ";
	for(int i=1;i<token_cnt;i++)
	{
		if(token[i].line==x) 
			cout<<token[i].val<<" ";
	}
	cout<<endl;
}

void post_error(TOKEN tk,int at,int x)//���������Ϣ 
{
	cout<<"NO"<<endl;
	cout<<"----line information----"<<endl;//������������λ�� 
	if(tk.line>1) write_line(tk.line-1);
	write_line(tk.line);
	if(tk.line<max_line) write_line(tk.line+1);
	cout<<"------------------------"<<endl;//������Ϣ 
	cout<<"error line: "<<tk.line<<endl;
	cout<<"error value: "<<tk.val<<endl;
	cout<<"----expected symbol-----"<<endl;//�������� 
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

void post_succ()//���﷨�����ӡ�ɹ� 
{
	cout<<"YES"<<endl;
}

void solve_token()//�Զ����token���з��� 
{
	freopen("parser_out.txt","w",stdout);
	stack<int> state_stack;//״̬ջ
	stack<SYMBOL> symbol_stack;//����ջ 
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
			while(ag.action_type[tp][terminator_to_num[token[i].val[0]]]==STATUTE)//��Լ
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
				if(ag.action_type[tp][terminator_to_num[token[i].val[poi]]]==MOVE_IN)//�ƽ�
				{ 
					tmp.init(token[i].type[poi]);
					symbol_stack.push(tmp);
					state_stack.push(ag.action[tp][terminator_to_num[token[i].val[poi]]]);
					poi++;
				}
				else if(ag.action_type[tp][terminator_to_num[token[i].val[poi]]]==STATUTE)//��Լ
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
				else if(ag.action_type[tp][terminator_to_num[token[i].val[poi]]]==ACC)//����
				{
					post_succ(); //����ɹ���Ϣ 
					flag=true;
					break;
				}
				else
				{
					post_error(token[i],poi,tp);//���������Ϣ 
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
	read_lexer_out();//����token�б�
	fclose(stdin); 
	freopen("parser_grammar.txt","r",stdin);
	read_phaser_grammar();//�����﷨���� 
	fclose(stdin);
	cal_empty();//����ÿ�����ս���Ƿ����Ƴ���
	cal_nonterminal_first();//����ÿ���ս����first�� 
	cal_all_grammar();//ͳ�������ķ� 
	make_project_set();//������Ŀ�� 
	debug_project_set();//�����Ŀ�� 
	make_action_goto();//����action goto�� 
	debug_action_goto();//���action-goto�� 
	solve_token();//�Զ����token���н����﷨���� 
	return 0;
} 

