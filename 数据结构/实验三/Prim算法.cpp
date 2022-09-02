using namespace std;
#include<bits/stdc++.h>
const int inf=1000000;
int n,m;
int a[100][100];
int lowcost[100];//表示i到距离集合最近的距离
int closest[100];//表示i与之相连边的顶点序号
int Prim(int s)
{
	for(int i=0;i<n;i++) 
	{
		if(i==s)
			lowcost[i]=0;
		else
			lowcost[i]=a[s][i];
		closest[i]=s;
	}
	int minn,pos;
	int sum=0;
	for(int i=0;i<n;i++)
	{
		minn=inf;
		for(int j=0;j<n;j++)//找到集合最小边 
		{
			if(lowcost[j]!=0&&lowcost[j]<minn)
			{
				minn=lowcost[j];
				pos=j;
			}
		}
		if(minn==inf)
			break;
		sum+=minn;
		lowcost[pos]=0;//加入点集合。
		for(int j=0;j<n;j++)//加入新点更新 
		{
			if(lowcost[j]!=0&&a[pos][j]<lowcost[j])
			{
				lowcost[j]=a[pos][j];
				closest[j]=pos;
			}
		}
	}
	return sum;
}
int main()
{
	int u,v,w;
	cin>>n>>m;
	memset(a,inf,sizeof(a));	
	for(int i=0;i<m;i++)
	{
		cin>>u>>v>>w;
		a[u][v]=a[v][u]=w;
	}
	cout<<Prim(0)<<endl;
	int temp;
	for(int i=1;i<n;i++)
	{
		temp=closest[i];
		cout<<char(temp+65)<<"->"<<char(i+65)<<endl;
	}
}





