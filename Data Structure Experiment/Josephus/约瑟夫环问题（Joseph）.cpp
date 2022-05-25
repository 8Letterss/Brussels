/* 约瑟夫环问题（Joseph）又称丢手绢问题：已知 m 个人围坐成一圈，由某人起头，下一个人开始从 1 递增报数，
报到数字 n 的那个人出列，他的下一个人又从 1 开始报数，数到 n 的那个人又出列；
依此规律重复下去，直到 m 个人全部出列约瑟夫环结束。如果从 0 ~ (m-1) 给这 m 个人编号，请输出这 m 个人的出列顺序。
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
	printf("请输入m的初始值：\n");
	scanf("%d",&m);
	printf("请输入参与游戏的总人数n：\n");
	scanf("%d",&n);
	printf("请依次输入游戏参与者的密码：\n");
	
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
	printf("出列顺序为：\n");
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
