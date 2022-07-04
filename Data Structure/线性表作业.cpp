#include<stdio.h>
#include<malloc.h>
#include<stdbool.h>
#include <stdlib.h>

typedef struct Node
{
	int data;
	struct Node * pNext;
}NODE,*PNODE;//����ṹ�� 


PNODE create_list(void);//�������� 
PNODE delete_list(PNODE pHead,int a,int *n);//ɾ��ָ��Ԫ�� 
void traverse_list(PNODE pHead);//��������ֵ 
PNODE delete1_list(PNODE pHead);//ɾ���ظ�Ԫ�� 
PNODE reverse_list(PNODE pHead);//����
void insert_list(PNODE pHead,int x,int y);//����x��y���ڵ�һ��x�����y������x���ڱ�β����y 


int main()
{
	int n=0;
	PNODE pHead=NULL;
	pHead=create_list();//�������� 
	traverse_list(pHead);
	pHead=delete_list(pHead,3,&n);//ɾ��ָ��Ԫ�� 
	traverse_list(pHead);
	printf("%d\n",n);
	pHead=delete1_list(pHead);//ɾ���ظ�Ԫ��
	traverse_list(pHead);
	pHead=reverse_list(pHead);//����
	traverse_list(pHead);
	insert_list(pHead,4,5);//����x��y���ڵ�һ��x�����y������x���ڱ�β����y
	traverse_list(pHead);
	
	return 0;
}


PNODE create_list()
{
	int len,val;
	PNODE pHead=(PNODE)malloc(sizeof(NODE));
	
	if (!pHead)
	{
		printf("�����ڴ�ʧ�ܣ��������");
		exit(-1); 
	}
	
	printf("�����������ȣ�");
	scanf("%d",&len);
	
	PNODE pTail=pHead;//����һ��ָ�룬��������ָ���������һ����ЧԪ�� 
	pTail->pNext=NULL;
	
	for (int i=0;i<len;i++)
	{
		PNODE pNew=(PNODE)malloc(sizeof(NODE));
		if (pNew==NULL)
		{
			printf("�����ڴ�ʧ�ܣ��������");
			exit(-1); 
		}
		
		printf("������Ҫ���������ֵ��");
		scanf("%d",&val);
		
		pNew->data=val; 
		pTail->pNext=pNew;//�������ɵĽӵ����һ����ЧԪ��ָ���β�� 
		pNew->pNext=NULL;//�����һ��Ԫ�ص�ָ������Ϊ�� 
		pTail=pTail->pNext;
		}	
	return pHead;
}



PNODE delete_list(PNODE pHead,int a,int *n)
{
	int * c=n;
	if (!pHead)//�ж������Ƿ�Ϊ�� 
		return NULL;
	PNODE p=pHead;
	while(p->pNext!=NULL)
	{
		if (p->pNext->data==a)//����ָ�����һ��Ԫ��Ϊָ��Ԫ�أ���ָ��ָ������һ��Ԫ�أ����ͷ��ڴ� 
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
	q=(PNODE)malloc(sizeof(NODE));//����һ���µ�������ͷ���뷨��ԭ�����ֵ���� 
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


void insert_list(PNODE pHead,int x,int y)//����x��y���ڵ�һ��x�����y������x���ڱ�β����y
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
















