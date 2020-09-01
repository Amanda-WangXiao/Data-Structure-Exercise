#include<iostream>
using namespace std;
class A
{
public:
    void Josephus(int n0,int m0,int s0);
private:
	int m;
	int n;
	int s;
};
void A::Josephus(int n0,int m0,int s0)
{
	m=m0;
	n=n0;
	s=s0;
    int i;
    int count=0;//计算被退出的人数(n-1)
    int num=0;
	int a[10000];
    for(i=0;i<n;i++)
        a[i]=i+1;
    i=s-1;
    while(count<n-1)//只剩下一个时退出循环
    {
        if(a[i]!=0)
            num++;
        if(num==m)
        {
            num=0;
            cout<<a[i]<<' ';
            a[i]=0;
            count++;//退出人数加1    
        }
        i++;
        if(i==n)
            i=0;//报数到末尾后i恢复为0
    }
    for(i=0;i<n;i++)
        if(a[i]!=0)
        {
            cout<<a[i]<<' ';
            return;
        }
}

int main()
{
	A l;
	int n=0,m=0,s=0;
	while(n*s*m==0)
	{
		cout<<"请输入人数n:"<<endl;
		cin>>n;
		if(n<=0)
			cout<<"输入错误"<<endl;	
		cout<<"请输入报数周期是:"<<endl;
    	cin>>m;
		if(m<=0)
			cout<<"输入错误"<<endl;
		cout<<"请输入从第几个人开始报数:"<<endl;
		cin>>s;
		if(s<=0)
			cout<<"输入错误"<<endl;
	}
	l.Josephus(n,m,s);
	return 0;
}

链式结构：
#include<iostream>
#include<stdlib.h>
using namespace std;
class A
{
	public:
		void Josephus(int n0,int m0,int s0);
	private:
		int m;
		int n;
		int s;
};
typedef struct LNode
{
	int data;
	struct LNode *next;

}LNode,*LinkList;
void A::Josephus(int n0,int m0,int s0)
{
	LinkList p,r,q=NULL;
	int i;
    m=m0;
	n=n0;
	s=s0;
	for(i=1;i<=n;i++)
	{
		p=(LinkList)malloc(sizeof(LNode));
		p->data=i;
		if(q==NULL)
		q=p;//q指向i=1
		else
		r->next=p;
		r=p;
	}
	p->next=q;//建立循环链表
	p=q;

	for(i=1;i<s;i++)
	{
		r=p;
		p=p->next;
	}//p指向第1个出发结点
	while(p->next!=p)
	{
		for(i=1;i<m;i++)
		{
			r=p;
			p=p->next;
		}//p指向第m个结点,r指向第m-1个结点
		r->next=p->next;//删除第m个结点
		cout<<p->data<<' ';
		free(p);
		p=r->next;
	}
	cout<<p->data<<endl;
}
int main()
{
	A l;
	int n=0,m=0,s=0;
	while(n*s*m==0)
	{
		cout<<"请输入人数n:"<<endl;
		cin>>n;
		if(n<=0)
			cout<<"输入错误"<<endl;	
		cout<<"请输入报数周期是:"<<endl;
    	cin>>m;
		if(m<=0)
			cout<<"输入错误"<<endl;
		cout<<"请输入从第几个人开始报数:"<<endl;
		cin>>s;
		if(s<=0)
			cout<<"输入错误"<<endl;
	}
	l.Josephus(n,m,s);
	return 0;
}

