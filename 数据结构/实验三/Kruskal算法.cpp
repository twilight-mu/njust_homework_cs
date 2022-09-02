using namespace std;
#include<bits/stdc++.h>
int n;
struct node
{
    int val;
    int start;
    int end;
};
node v[100];
int father[100];
int cap[100];
bool cmp(node a,node b)
{
    return a.val<b.val?true:false;
}
void make_set()
{
    for(int i=0;i<n;i++)
    {
        father[i]=i;
        cap[i]=1;
    }
}
int Find(int x)             
{
    if(x!=father[x])
     {                             
        father[x]=Find(father[x]);
    }    
    return father[x];
}                                 
void Union(int x,int y) 
{       
    x=Find(x);
    y=Find(y);
    if(x==y)
        return;
    if(cap[x]<cap[y])
        father[x]=Find(y);
    else
    {
        if(cap[x]==cap[y])
            cap[x]++;
        father[y]=Find(x);
    }
}
int Kruskal()
{
    int sum = 0;
    make_set();
    for(int i=0;i<n;i++)
    {
        if(Find(v[i].start)!=Find(v[i].end))     
        {
            Union(v[i].start,v[i].end); 
            cout<<char(v[i].start+65)<<"->"<<char(v[i].end+65)<<endl;
            sum+=v[i].val;
        }
    }
    return sum;
}
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>v[i].start>>v[i].end>>v[i].val;
	} 
    sort(v,v+n,cmp);
    cout<<Kruskal()<<endl;
}
