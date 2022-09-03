using namespace std;
#include<bits/stdc++.h>
int line=100;//统计行数 
int tempnum=0;//统计临时变量号
int max_line;//最大行号 

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

void read_lexer_out()
{
	freopen("lexer_out.txt","r",stdin);
	char s[100];
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
	fclose(stdin);
}

void write_line(int x)//根据行数输出这一行的源代码 
{
	//cout<<"line "<<x<<": ";
	for(int i=1;i<token_cnt;i++)
	{
		if(token[i]._line==x)
		{
			if(!strcmp(token[i].type,"type"))
			{
				cout<<token[i].val<<" ";
			}
			else
			{
				cout<<token[i].val;
			}	
		} 
			
	}
	cout<<endl;
}

void out_source()
{
	freopen("input_source.txt","w",stdout);
	for(int i=1;i<=max_line;i++)
	{
		write_line(i);	
	}	
	fclose(stdout);
}

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

void solve_expression(string s)//分析一般赋值语句 
{
	if((s[0]=='-'&&s[1]=='-')||(s[0]=='+'&&s[1]=='+'))//分析形如++a、--a的语句 
	{
		string tempname=s.substr(2,s.length()-2);
		char code=s[0];
		cout<<line<<":"<<"temp"<<tempnum<<"="<<tempname<<code<<"1"<<endl;
		line++;
		cout<<line<<":"<<tempname<<"="<<"temp"<<tempnum<<endl;
		line++;
		tempnum++; 
	}
	else if((s[s.length()-1]=='-'&&s[s.length()-2]=='-')||(s[s.length()-1]=='+'&&s[s.length()-2]=='+'))//分析形如a++、a--的语句 
	{
		string tempname=s.substr(0,s.length()-2);
		char code=s[s.length()-1];
		cout<<line<<":"<<"temp"<<tempnum<<"="<<tempname<<code<<"1"<<endl;
		line++;
		cout<<line<<":"<<tempname<<"="<<"temp"<<tempnum<<endl;
		line++;
		tempnum++; 
	}
	else//分析一般赋值语句 
	{
		int ans=get_num(s);
		if(ans==1)
		{
			cout<<line<<":"<<s<<endl;
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
			cout<<line<<":"<<"temp"<<tempnum<<"="<<temp2<<endl;
			line++;
			cout<<line<<":"<<temp1<<"="<<"temp"<<tempnum<<endl;
			line++;
			tempnum++; 
		}
	}
}

void solve_other(string s)//分析除if、while、for行之外的行 
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

void solve_if(string s)//分析if行语句 
{
	int len=s.length();
	int i;
	cout<<line<<":"<<"if not ";
	for(i=3;i<len;i++)
	{
		if(s[i]==')')
		break; 
		cout<<s[i];	 
	}
	string temp;
	i=i+2;
	for(;i<len;i++)
	{
		if(s[i]=='}')
		break;
		temp=temp+s[i];
		
	} 
	cout<<" goto "<<line+get_num(temp)+1<<endl;
	line++;
	solve_other(temp);
}
void solve_while(string s)//分析while行语句 
{
	int len=s.length();
	int i;
	cout<<line<<":"<<"if not ";
	for(i=6;i<len;i++)
	{
		if(s[i]==')')
		break; 
		cout<<s[i];	 
	}
	string temp;
	i=i+2;
	for(;i<len;i++)
	{
		if(s[i]=='}')
		break;
		temp=temp+s[i];
		
	} 
	cout<<" goto "<<line+get_num(temp)+2<<endl;
	int templine=line;
	line++;
	solve_other(temp);
	cout<<line<<":"<<"goto "<<templine<<endl;
	line++;
}
void solve_for(string s)//分析for行语句 
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
	cout<<line<<":"<<"if not "<<temp2<<" goto "<<line+get_num(temp)+4<<endl;
	int templine=line;
	line++;
	solve_other(temp);
	solve_expression(temp3);
	cout<<line<<":"<<"goto "<<templine<<endl;
	line++;
}

void read_source_analyze()//一边读入、一边分析、一边输出 
{
	freopen("input_source.txt","r",stdin);
	string s;
	while(getline(cin,s))
	{
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
	cout<<line<<":"<<endl;
	fclose(stdin); 
}


int main()
{
	//read_lexer_out();
	//out_source();
	freopen("out.txt","w",stdout);
	read_source_analyze();
	fclose(stdout); 

} 
