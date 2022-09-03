using namespace std;
#include<bits/stdc++.h>
#define Initial_State 1
#define End_State 2
const int NM=1e2+10;//���dfa����
const int MM=1e3+10;//�ַ��������
const int N=1e3+10;//��󶥵���
const int M=1e3+10;//������
int num=0;//ͳ��nfa/dfa����
int gnum=0;//�ķ��ܸ��� 
char s1[30]=" #+-*/%&|!^<>=()[]{},;_.'\"";//len=26��ת���ַ� 
char s2[30]=" #+-*/%&|!^<>=()[]{},;_.'";//len=25����ת���ַ� 
struct GRAMMAR//�ķ��ṹ�� 
{
	char left[MM];//�ķ��� 
	char val[NM][MM];//�ķ��Ҳ� 
	bool is_terminator[NM];//�Ƿ�Ϊ�ս��
	int cnt;//�ķ����� 
	void init()//��ʼ�� 
	{
		cnt=0;
		memset(left,0,sizeof left);
		for(int i=0;i<NM;i++)
		{
			memset(val[i],0,sizeof val[i]);
			is_terminator[i]=0;
		}
	}
	void push_left(char _left[MM])//ƴ���� 
	{
		strcpy(left,_left);
	}
	void push_right(char _right[MM])//���ս��ʱƴ���Ҳ� 
	{
		cnt++;
		strcpy(val[cnt],_right);
		is_terminator[cnt]=false;
	}
	void push_right(char _right)//�ս��ʱƴ���Ҳ� 
	{
		cnt++;
		val[cnt][0]=_right;
		is_terminator[cnt]=true;
	}
}grammar[N];


struct Edge//ǰ��߽ṹ�� 
{
	int to,nxt;//Ŀ�ĵأ���һ��Ŀ�ĵص�ַ 
	char val;//��ֵ 
}; 
//��ʽǰ���Ǵ洢 
struct NFA//NFA�ṹ��(����ͼ) 
{
	int head[N];//ͷ��㣬Edge������±꣬����λ��
	int n;//������ 
	int cnt;//���� 
	Edge E[M];//����� 
	char name[N][MM];//�洢������� 
	int type[N];//��ʾ������ͣ�1Ϊ��ʼ��㣬2λ�ս�� 
	map<string,int> mp;//�����ֵ�ԣ��ڵ����������ְ� 
	set<char> st;//ĳһnfa�������������ս�����������֡���Сд��ĸ��(������ĸ��) 
	void init()//��ʼ�� 
	{
		cnt=0;
		n=0;
		for(int i=0;i<N;i++) 
			head[i]=-1;
	}
	void add(int s,int t,char v)
	{//�ӱ�
		E[++cnt].val=v;
		E[cnt].to=t;
		E[cnt].nxt=head[s];
		head[s]=cnt;
	}
	void add_edge(char A[MM],int lenA,char B[MM],int lenB,char x)//����add�����ӱ� A-�󲿽������ lenA-�󲿽�㳤�� B-�Ҳ�������� lenB-�Ҳ���㳤�� 
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
	void setType(char A[MM],int lenA,int ty)//���ý������ 
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
	set<int> closure(int x)//���ʼclosure�հ� 
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
	set<int> move_closure(set<int> st,char x)//��x��ת�� 
	{
		set<int> ans;
		bool vis[N];
		memset(vis,0,sizeof vis);
		for(auto it1:st)
		{
			int now=it1;
			for(int i=head[now];~i;i=E[i].nxt)
			{
				if(E[i].val!=x) 
					continue;
				if(vis[E[i].to]) 
					continue;
				vis[E[i].to]=1;
				set<int> tmp=closure(E[i].to);
				for(auto it2:tmp) ans.insert(it2);
			}
		}
		return ans;
	}
}nfa[NM];

struct DFA//DFA�ṹ��(����ͼ) 
{
	int head[N];//ͷ��� 
	int n;//������ 
	int cnt;//���� 
	Edge E[M];//����� 
	map<int,set<int>>name;//�洢�������(set<int>����nfa�еĽ����������nfa����Ϊһ�����) 
	int type[N];//��ʾ������ͣ�1Ϊͷ��㣬2λ�ս�� 
	map<set<int>,int>mp;//�����ֵ�ԣ��ڵ����������ְ�
	void init()//��ʼ�� 
	{
		cnt=0;
		n=0;
		for(int i=0;i<N;i++) head[i]=-1;
	}
	void add(int s,int t,char v)
	{//�ӱ�
		E[++cnt].val=v;
		E[cnt].to=t;
		E[cnt].nxt=head[s];
		head[s]=cnt;
	}
	void add_edge(set<int> A,set<int> B,char x)
	{
		int s=-1,t=-1;
		if(mp[A]==0)//�㲻���� 
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
	void setType(set<int> st,int ty)//���ý������ 
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
	int run(char A[MM])//ƥ�䣬ƥ�����Ϊ���ַ���ƥ�������ȣ������ķ��ڶ���ʱ���ȶ�������ȼ��ߣ����������ȼ��� 
	{
		int now=1;
		int ans=0;
		int mx=0;
		int lenA=strlen(A);
		for(int i=0;i<lenA;i++)//��ͷ�������ַ���ƥ�䣬����ƥ�䳤�� 
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
}dfa[NM];

void solve(char x,bool flag,bool f,int l1,int r1,int l2,int r2,char A[MM],int lenA,char B[MM],int lenB)//����ʡ�Ա�ʾ�ķ��� 
{
	gnum++;
	grammar[gnum].push_left(A);
	if(flag)
	{
		num++;
		nfa[num].init();
		flag=false;
		nfa[num].setType(A,lenA,Initial_State);
	}
	if(f)//A->@�� 
	{
		nfa[num].setType(A,lenA,End_State);
		grammar[gnum].push_right('@');
	}
	else if(l1==l2||r1==r2)//A->a��
	{
		nfa[num].add_edge(A,lenA,"Final",5,x);
		nfa[num].setType("Final",5,End_State);
		grammar[gnum].push_right(x);
	}
	else//A->aB��
	{
		nfa[num].add_edge(A,lenA,B,lenB,x);
		grammar[gnum].push_right(x);
		grammar[gnum].push_right(B);
	}
}

void read_lexer_source()//��ȡԴ���룬�������ԪʽToken��� 
{
	char s[MM];
	int row=0;//��Ǵ������� 
	bool flag=false; 
	bool bflag=false;
	while(scanf("%[^\n]",&s)!=EOF)
	{
		row++;
		getchar();
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
			while(i<len&&(s[i]==' '||s[i]=='\n'))//ȥ���ո��뻻�з� 
				i++;
			int mxlen=0;//���ĳһtoken���ݳ��� 
			char str[MM];
			memset(str,0,sizeof str);
			for(int j=1;j<=num;j++)
			{
				int tmp=dfa[j].run(s+i);
			//	cout<<row<<' '<<j<<' '<<num<<' '<<i<<' '<<s+i<<' '<<tmp<<endl;
				if(mxlen<tmp)
				{
					mxlen=tmp;
					strcpy(str,nfa[j].name[1]);//ĳһnfa�׽�����֣������ 
				}
			}
			printf("(line %d,%s,",row,str);//��������кš���� 

			for(int j=0;j<mxlen;j++)
			{
				if(s[i+j]=='\n') 
					continue;
				printf("%c",s[i+j]);//���Token 
			}
			printf(")\n");
			if(strcmp(str,"error")==0)
			{
				cout<<"���ִʷ��������ֲ�����Ϊ��ʶ��������ĸ"<<endl; 
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
}

set<char> fir[N];
map<string,int> nonterminal_to_num;
char num_to_nonterminal[N][MM];
int tt=0;

set<char> get_first()//��ȡÿ�����ս����first�� 
{
	set<char> ans;
	for(int i=1;i<=gnum;i++)
	{
		if(strcmp(grammar[i].left,grammar[1].left)!=0) 
			continue;
		ans.insert(grammar[i].val[1][0]);
	}
	return ans;
}

void read_lexer_grammar()//��ȡ�ķ� 
{
	char s[MM];
	bool flag=true;//�ж϶�����Ƿ���ÿ���ķ��ĵ�һ��
	while(scanf("%[^\n]",&s)!=EOF)
	{
		getchar();
		int len=strlen(s);
		if(s[0]=='*')//����һ���ķ�
		{
		//	nfa[num].debug();
			set<char> tmp=get_first();
			if(nonterminal_to_num[grammar[1].left]!=0)
			{
				fir[nonterminal_to_num[grammar[1].left]].insert(tmp.begin(),tmp.end());
			}
			else
			{
				tt++;
				strcpy(num_to_nonterminal[tt],grammar[1].left);
				nonterminal_to_num[grammar[1].left]=tt;
				fir[tt]=tmp;
			}
			
			for(int i=1;i<=gnum;i++)
			{
				cout<<grammar[i].left<<endl;
				for(int j=1;j<=grammar[i].cnt;j++)
					cout<<grammar[i].val[j]<<" ";
				cout<<endl;
				cout<<grammar[i].cnt<<endl;
				
			}
			cout<<"------------"<<endl;
		//	cout<<"~~~"<<tt<<' '<<fir[tt].size()<<endl;
			for(int i=0;i<N;i++) 
			grammar[i].init();//�ķ��ṹ���ʼ�� 
			gnum=0;
			flag=true;
			continue;
		}
		int l1=-1,r1=-1,l2=-1,r2=-1,bj=-1;
		bool f=false;//�ж��Ƿ�Ϊ@ 
		for(int i=0;i<len;i++)//��ʶ��<>λ�� 
		{
			if(s[i]=='@') f=true;
			if(s[i]=='<'&&l1==-1) l1=i;
			if(s[i]=='>'&&r1==-1) r1=i;
			if(i<len-1&&s[i]=='-'&&s[i+1]=='>'&&bj==-1) bj=i+1;
		}
		for(int i=len-1;i>=0;i--)//��ʶ�Ҳ�<>λ�� 
		{
			if(s[i]=='>'&&r2==-1) r2=i;
			if(s[i]=='<'&&l2==-1) l2=i;
		}
		char A[MM],B[MM],x;
		memset(A,0,sizeof A);
		memset(B,0,sizeof B);
		int lenA=r1-l1-1;//�󲿳��� 
		int lenB=r2-l2-1;//�Ҳ����� 
		for(int i=0;i<lenA;i++)//��ȡ���ַ������� 
		{
			A[i]=s[l1+i+1];
		}
		for(int i=0;i<lenB;i++)//��ȡ�Ҳ��ַ������� 
		{
			B[i]=s[l2+i+1];
		}
		bool fflag=false;//����Ƿ����账���ʡ�Ա�ʾ�ַ� 
		for(int i=bj+1;i<len;i++)
		{
			if(s[i]!=' ')
			{
				x=s[i];
				if(i<len+1&&s[i]=='\\'&&s[i+1]=='n') x='\n';
				if(i<len+1&&s[i]=='^'&&s[i+1]=='c')//^c��ʾСд�ַ����� 
				{
					fflag=true;
					for(char j='a';j<='z';j++)
					{
						solve(j,flag,f,l1,r1,l2,r2,A,lenA,B,lenB);
					}
				}
				if(i<len+1&&s[i]=='^'&&s[i+1]=='C')//^C��ʾ��д�ַ����� 
				{
					fflag=true;
					for(char j='A';j<='Z';j++)
					{
						solve(j,flag,f,l1,r1,l2,r2,A,lenA,B,lenB);
					}
				}
				if(i<len+1&&s[i]=='^'&&s[i+1]=='d')//^d��ʾ���ּ��� 
				{
					fflag=true;
					for(char j='0';j<='9';j++)
					{
						solve(j,flag,f,l1,r1,l2,r2,A,lenA,B,lenB);
					}
				}
				if(i<len+1&&s[i]=='^'&&s[i+1]=='s')//��ת���ַ��ַ��� 
				{
					fflag=true;
					for(int j=0;j<26;j++)
					{
						solve(s1[j],flag,f,l1,r1,l2,r2,A,lenA,B,lenB);
					}
				}
				if(i<len+1&&s[i]=='^'&&s[i+1]=='S')//��ת���ַ��ַ��� 
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
		
		if(fflag) continue;//��fflag=true��ʾ��ǰ���Ϊʡ���ͣ���ִ�з�ʡ���ʹ�������ִ�з�ʡ���ʹ��� 
		//��ʡ���ͽ�㴦�� 
		if(flag)
		{
			num++;
			nfa[num].init();
			flag=false;
			nfa[num].setType(A,lenA,Initial_State);
		}
		gnum++;
		grammar[gnum].push_left(A);
		if(f)
		{//A->@��
			nfa[num].setType(A,lenA,End_State);
			grammar[gnum].push_right('@');
		}
		else if(l1==l2||r1==r2)
		{//A->a��
			nfa[num].add_edge(A,lenA,"Final",5,x);
			nfa[num].setType("Final",5,End_State);
			grammar[gnum].push_right(x);
		}
		else
		{//A->aB��
			nfa[num].add_edge(A,lenA,B,lenB,x);
			grammar[gnum].push_right(x);
			grammar[gnum].push_right(B);
		}
	}
}

void nfa_to_dfa()//nfaȷ����Ϊdfa 
{
	for(int i=1;i<=num;i++)
	{
		dfa[i].init();
		set<int> st0=nfa[i].closure(1);//��closure�հ� 
		dfa[i].setType(st0,Initial_State);//���ÿ�ʼ��� 
		queue< set<int> > que;
		que.push(st0);
		while(!que.empty())
		{
			set<int> now=que.front();
			que.pop();
			for(auto it:nfa[i].st)
			{
				set<int> tmp=nfa[i].move_closure(now,it);//��"it"��ת�� 
				if(dfa[i].mp[tmp]==0)
				{
					que.push(tmp);
					for(auto itt:tmp)
					{
						if(nfa[i].type[itt]==2){
							dfa[i].setType(tmp,End_State);
							break;
						}
					}
				}
				dfa[i].add_edge(now,tmp,it);
			}
		}
	//	dfa[i].debug();
	}
}

void out_first()//���first�� 
{
	cout<<"----------"<<endl;
	for(int i=1;i<=tt;i++)
	{
		cout<<num_to_nonterminal[i]<<"::";
		for(auto it:fir[i])
		{
			cout<<it<<" ";
		}
		cout<<endl;
	}
}

int main(){

	freopen("lexer_grammar.txt","r",stdin);
	read_lexer_grammar();//���������ķ�������nfa
	nfa_to_dfa();//nfaתdfa
	fclose(stdin);
	freopen("lexer_source.txt","r",stdin);
	freopen("lexer_out.txt","w",stdout);
	read_lexer_source();//����Դ���� �����token������Ԫ��
	out_first(); 
	//test_nfa();
	//test();
	fclose(stdout);
	fclose(stdin);

	return 0;
}



