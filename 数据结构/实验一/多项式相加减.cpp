using namespace std;
#include<bits/stdc++.h>
struct node
{
	int num;
	int exp;
	node *next;	
};
node *insert(node *head,node *p)//向链表中插入 
{
    node *q,*qa,*qb;
    q=new node;
    q->num=p->num;
    q->exp=p->exp;
    q->next=NULL;
    if(head==NULL)
    {
        head=q;
        head->next=NULL;
        return head;
    }
    qa=qb=head;
    while(qa!=NULL)
    {
        while(qa->exp<p->exp)
        {
            qb=qa;
            if(qa->next==NULL)
                break;
            qa=qa->next;
        }
        if(qa->exp==p->exp)
        {
            qa->num=qa->num+p->num;
            if(qa->num==0)
            {
                if(qa==head)
                {
                    head=head->next;
                    break;
                }
                else
                {
                    qb->next=qa->next;
                }
            }
            else
        	{
        		break;
			}
        }
        else if(qa->exp<p->exp)
        {
            qa->next=q;
            break;
        }
        else
        {
            if(qb==head&&qb->exp>q->exp)  
            {
                q->next=head;
                head=q;
                break;
            }
            else
            {
                qb->next=q;
                q->next=qa;
                break;
            }
        }
    }
    return head;
}
node *create()//创建多项式 
{
	node *p,*head;
    p=new node;
    head=NULL;
    while(cin>>p->num>>p->exp)
    {
    	if(p->num==0&&p->exp==0)
    		break;
        head=insert(head,p); 
    }
    return head;
}
node *addsub(node *pa,node *pb,char s)//多项式相加减 
{
	node *p,*q,*head;
    p=(node*)malloc(sizeof(node));
    head=q=p;
    while(pa!=NULL&&pb!=NULL)
    {
    	if(pa==NULL)
    	{
    		while(pb!=NULL)
    		{
    			q=p;                              
                p->exp=pb->exp;
                p->num=pb->num;
                p=new node;
                q->next=p;
                pb=pb->next;
			}
		}
		else if(pb==NULL)
		{
			while(pa!=NULL)
    		{
    			q=p;
    			p->exp=pa->exp;
    			p->num=pa->num;
    			p=new node;
    			q->next=p;
    			pa=pa->next;
			}
		}
		else
		{
			if(pa->exp>pb->exp)
			{
				q=p;
				p->exp=pb->exp;
				p->num=pb->num;
				p=new node;
				q->next=p;
				pb=pb->next; 
			}
			else if(pa->exp<pb->exp)
			{
				q=p;
				p->exp=pa->exp;
				p->num=pa->num;
				p=new node;
				q->next=p;
				pa=pa->next;
			}
			else
			{
				q=p;
				p->exp=pa->exp;
				if(s=='+')
					p->num=pa->num+pb->num;
				if(s=='-')
					p->num=pa->num-pb->num;
				if(p->num!=0)
				{
					p=new node;
					q->next=p;
					pa=pa->next;
					pb=pb->next;
				}
				else
				{
					pa=pa->next;
					pb=pb->next;
				}
			}
		}
	}
	q->next=NULL;
	return head;
} 
int main()
{
	node *pa,*pb,*p;
	cout<<"请输入第一个多项式:"<<endl;
	pa=create();
	cout<<"请输入第二个多项式:"<<endl;
	pb=create(); 
	p=addsub(pa,pb,'+');
	cout<<"加法结果"<<endl; 
	while(p!=NULL)
	{
		cout<<p->num<<" "<<p->exp<<endl;
		p=p->next;
	}
	cout<<endl;
	p=addsub(pa,pb,'-'); 
	cout<<"减法结果"<<endl; 
	while(p!=NULL)
	{
		cout<<p->num<<" "<<p->exp<<endl;
		p=p->next;
	}
	cout<<endl;
}
