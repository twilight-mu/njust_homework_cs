using namespace std;
#include<bits/stdc++.h>
int n;
int a[100][100];
int visit[100];
int getadj(int x) 
{
    for(int i=1;i<=n;i++)
    {
        if(a[x][i]==1&&visit[i]==0)
            return i;
    }
    return 0;
}
void dfs(int v)
{
    cout<<v<<" ";
    visit[v]=1;
    int k=getadj(v);
    while(k!=0)
    {
        if(visit[k]==0)   
            dfs(k);     
        k=getadj(v);
    }
}
void bfs(int v)
{
    queue<int>q;
    int k,temp;
    cout<<v<<" ";
    visit[v]=1;
    q.push(v);
    while(!q.empty())    
    {
        temp=q.front();  
        q.pop();
        k=getadj(temp);
        while(k!=0)
        {
            if(visit[k]==0)
            {
                cout<<k<<" ";
                visit[k]=1;
                q.push(k);   
            }
            k=getadj(temp);
		}
	}
}
int main()
{

	cin>>n;
	memset(a,0,sizeof(a));
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		cin>>a[i][j];
	}
	
	cout<<"dfs遍历结果为:"<<endl; 
	memset(visit,0,sizeof(visit));
	for(int i=1;i<=n;i++)
	{
		if(visit[i]==0)
            dfs(i);
	}
	cout<<endl;
	
	cout<<"bfs遍历结果为:"<<endl; 
    memset(visit,0,sizeof(visit));
	for(int i=1;i<=n;i++)
	{
		if(visit[i]==0)
            bfs(i);
	}
	cout<<endl;     
}
