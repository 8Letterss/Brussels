/* Լɪ�����⣨Joseph���ֳƶ��־����⣺��֪ m ����Χ����һȦ����ĳ����ͷ����һ���˿�ʼ�� 1 ����������
�������� n ���Ǹ��˳��У�������һ�����ִ� 1 ��ʼ���������� n ���Ǹ����ֳ��У�
���˹����ظ���ȥ��ֱ�� m ����ȫ������Լɪ�򻷽���������� 0 ~ (m-1) ���� m ���˱�ţ�������� m ���˵ĳ���˳��
*/

#include<bits/stdc++.h>
using namespace std;
struct node
{
	int data,password;
	struct node *next;	
}*head,*exm,*last,*pre;


int main()
{
	int m,n,x;
	printf("������m�ĳ�ʼֵ��\n");
	scanf("%d",&m);
	printf("�����������Ϸ��������n��\n");
	scanf("%d",&n);
	printf("������������Ϸ�����ߵ����룺\n");
	
	head=new node;
	last=head;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		exm=new node;
		exm->data=i;
		exm->password=x;
		last->next=exm;
		last=exm;
	}
	exm->next=head->next;
	pre=exm;
	exm=exm->next;
	x=0;
	printf("����˳��Ϊ��\n");
	while(exm->next!=exm)
	{
		x++;
		if(x==m)
		{
			printf("%d",exm->data);
			m=exm->password;
			pre->next=exm->next;
			exm=exm->next;
			x=0;
			continue;
		}
		pre=exm;
		exm=exm->next;
	}
	printf("%d\n",exm->data);
	
	return 0;
}
