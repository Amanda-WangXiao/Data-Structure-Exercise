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
    int count=0;//���㱻�˳�������(n-1)
    int num=0;
	int a[10000];
    for(i=0;i<n;i++)
        a[i]=i+1;
    i=s-1;
    while(count<n-1)//ֻʣ��һ��ʱ�˳�ѭ��
    {
        if(a[i]!=0)
            num++;
        if(num==m)
        {
            num=0;
            cout<<a[i]<<' ';
            a[i]=0;
            count++;//�˳�������1    
        }
        i++;
        if(i==n)
            i=0;//������ĩβ��i�ָ�Ϊ0
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
		cout<<"����������n:"<<endl;
		cin>>n;
		if(n<=0)
			cout<<"�������"<<endl;	
		cout<<"�����뱨��������:"<<endl;
    	cin>>m;
		if(m<=0)
			cout<<"�������"<<endl;
		cout<<"������ӵڼ����˿�ʼ����:"<<endl;
		cin>>s;
		if(s<=0)
			cout<<"�������"<<endl;
	}
	l.Josephus(n,m,s);
	return 0;
}

��ʽ�ṹ��
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
		q=p;//qָ��i=1
		else
		r->next=p;
		r=p;
	}
	p->next=q;//����ѭ������
	p=q;

	for(i=1;i<s;i++)
	{
		r=p;
		p=p->next;
	}//pָ���1���������
	while(p->next!=p)
	{
		for(i=1;i<m;i++)
		{
			r=p;
			p=p->next;
		}//pָ���m�����,rָ���m-1�����
		r->next=p->next;//ɾ����m�����
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
		cout<<"����������n:"<<endl;
		cin>>n;
		if(n<=0)
			cout<<"�������"<<endl;	
		cout<<"�����뱨��������:"<<endl;
    	cin>>m;
		if(m<=0)
			cout<<"�������"<<endl;
		cout<<"������ӵڼ����˿�ʼ����:"<<endl;
		cin>>s;
		if(s<=0)
			cout<<"�������"<<endl;
	}
	l.Josephus(n,m,s);
	return 0;
}

