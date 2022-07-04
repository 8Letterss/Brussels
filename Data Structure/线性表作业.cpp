#include<stdio.h>
#include<malloc.h>
#include<stdbool.h>
#include <stdlib.h>

typedef struct Node
{
	int data;
	struct Node * pNext;
}NODE,*PNODE;//定义结构体 


PNODE create_list(void);//创建链表 
PNODE delete_list(PNODE pHead,int a,int *n);//删除指定元素 
void traverse_list(PNODE pHead);//输出链表的值 
PNODE delete1_list(PNODE pHead);//删除重复元素 
PNODE reverse_list(PNODE pHead);//倒序
void insert_list(PNODE pHead,int x,int y);//输入x，y。在第一个x后插入y。若无x，在表尾插入y 


int main()
{
	int n=0;
	PNODE pHead=NULL;
	pHead=create_list();//创建链表 
	traverse_list(pHead);
	pHead=delete_list(pHead,3,&n);//删除指定元素 
	traverse_list(pHead);
	printf("%d\n",n);
	pHead=delete1_list(pHead);//删除重复元素
	traverse_list(pHead);
	pHead=reverse_list(pHead);//倒序
	traverse_list(pHead);
	insert_list(pHead,4,5);//输入x，y。在第一个x后插入y。若无x，在表尾插入y
	traverse_list(pHead);
	
	return 0;
}


PNODE create_list()
{
	int len,val;
	PNODE pHead=(PNODE)malloc(sizeof(NODE));
	
	if (!pHead)
	{
		printf("分配内存失败，程序结束");
		exit(-1); 
	}
	
	printf("请输入链表长度：");
	scanf("%d",&len);
	
	PNODE pTail=pHead;//定义一个指针，令它总是指向链表最后一个有效元素 
	pTail->pNext=NULL;
	
	for (int i=0;i<len;i++)
	{
		PNODE pNew=(PNODE)malloc(sizeof(NODE));
		if (pNew==NULL)
		{
			printf("分配内存失败，程序结束");
			exit(-1); 
		}
		
		printf("请输入要插入链表的值：");
		scanf("%d",&val);
		
		pNew->data=val; 
		pTail->pNext=pNew;//将新生成的接到最后一个有效元素指针的尾部 
		pNew->pNext=NULL;//将最后一个元素的指针域设为空 
		pTail=pTail->pNext;
		}	
	return pHead;
}



PNODE delete_list(PNODE pHead,int a,int *n)
{
	int * c=n;
	if (!pHead)//判断链表是否为空 
		return NULL;
	PNODE p=pHead;
	while(p->pNext!=NULL)
	{
		if (p->pNext->data==a)//若此指针的下一个元素为指定元素，将指针指向下下一个元素，并释放内存 
		{
			PNODE q=p->pNext;
			p->pNext=p->pNext->pNext;
			free(q);
			*c+=1;
			
		}else
			p=p->pNext;
	}
	return pHead;
}


void traverse_list(PNODE pHead)
{
	PNODE p=pHead->pNext;
	while (NULL!=p)
	{
		printf("%d\t",p->data);
		p=p->pNext;
	}
	printf("\n");
}

PNODE delete1_list(PNODE pHead)
{
	if (pHead==NULL)
		return NULL;
	PNODE p=pHead->pNext;
	PNODE q,t,pD;
	pD =pHead;
	while(p!=NULL)
	{
		q=p;
		while (q->pNext!=NULL)
		{
			if (p->data==q->pNext->data)
			{
				t=q->pNext;
				p->pNext=t->pNext;
				free(t);
			}
			else
				q=q->pNext;
		}
		p=p->pNext; 
	}
	return pD;
}


PNODE reverse_list(PNODE pHead)
{
	PNODE p,q,qNew;
	p=pHead->pNext;
	q=(PNODE)malloc(sizeof(NODE));//建立一个新的链表，用头插入法将原链表的值输入 
	q->pNext=NULL;
	while(p!=NULL)
	{
		qNew=(PNODE)malloc(sizeof(NODE));
		qNew->data=p->data;
		qNew->pNext=q->pNext;
		q->pNext=qNew;
		p=p->pNext;
	}
	return q;
}


void insert_list(PNODE pHead,int x,int y)//输入x，y。在第一个x后插入y。若无x，在表尾插入y
{
	int flag=0;
	PNODE p,pNew;
	p=pHead->pNext;
	while(p->pNext!=NULL)
	{
		if(p->data==x)
		{
			pNew=(PNODE)malloc(sizeof(NODE));
			pNew->data=y;
			pNew->pNext=p->pNext;
			p->pNext=pNew;
			flag=1;
			break;
		}
		else
		{
			p=p->pNext;
		}
	}
	
	if(flag==0)
	{
		pNew=(PNODE)malloc(sizeof(NODE));
		pNew->data=y;
		pNew->pNext=NULL;
		p->pNext=pNew;
	}
	
 } 
















