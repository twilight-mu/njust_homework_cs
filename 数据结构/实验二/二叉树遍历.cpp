using namespace std;
#include<bits/stdc++.h>
struct TreeNode
{
	char data;
	TreeNode *right;
	TreeNode *left;
};
struct TreeNode1
{
	TreeNode *tn;
	int tag;
};
TreeNode *create()
{
   char a;
   TreeNode *T;
   cin>>a; 
   if(a=='0')
       T=NULL;
   else
   {
       T=new TreeNode; 
       T->data=a;
       T->left=create();
       T->right=create();
   }
   return T;
}  
void Preorder(TreeNode *p)
{
	stack<TreeNode *>s;
	while(p||!s.empty())
	{
		if(p)
		{
			cout<<p->data<<' ';
			s.push(p);
			p=p->left;
		}
		else
		{
			p=s.top();
			s.pop();
			p=p->right;
		}
	}
}
void Inorder(TreeNode *p)
{
	stack<TreeNode *>s;
	while(p||!s.empty())
	{
		if(p)
		{
			s.push(p);
			p=p->left;
		}
		else
		{
			p=s.top();
			s.pop();
			cout<<p->data<<' ';
			p=p->right;
		}
	}
}
void Postorder(TreeNode *p)
{
	stack<TreeNode1 *>s;
	TreeNode1 *temp;
	while(p||!s.empty())
	{
		if(p)
		{
			TreeNode1 *t=new TreeNode1;
			t->tn=p;
			t->tag=1;
			s.push(t);
			p=p->left;
		}
		else
		{
			temp=s.top();
			s.pop();
			if(temp->tag==1)
			{
				s.push(temp);
				temp->tag=2;
				p=temp->tn->right;
			}
			else
			{
				cout<<temp->tn->data<<' ';
				p=NULL;
			}
		}
	}
}
int main()
{
	TreeNode *T;
	T=create();
	
	Preorder(T);
	cout<<endl;
	
	Inorder(T);
	cout<<endl;

	Postorder(T);
	cout<<endl;
} 