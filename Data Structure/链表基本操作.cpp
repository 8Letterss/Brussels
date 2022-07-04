#include<stdio.h>
#include<malloc.h>
#include<stdbool.h>
# include <stdlib.h>


typedef struct Node
{
	int data;
	struct Node * pNext;
}NODE,*PNODE;


PNODE create_list(void);
void traverse_list(PNODE pHead);
bool is_empty(PNODE pHead);
int length_list(PNODE pHead);
bool insert_list(PNODE pHead);
bool delete_list(PNODE pHead);
void sort_list(PNODE pHead);

int main()
{
	PNODE pHead=NULL;
	pHead=create_list();
	
	
	return 0;
}


PNODE create_list(void)
{
	int len;
	int i;
	int val;
	
	PNODE pHead=(PNODE)malloc(sizeof(NODE));
	if (NULL == pHead)
	{
		printf("�����ڴ�ʧ��\n");
		exit(-1);
	}
	
	printf("������������\n");
	scanf("%d",&len);
	
	PNODE pTail=pHead;
	pTail->pNext=NULL;
	
	for (i=0;i<len;i++)
	{
		PNODE pNew=(PNODE)malloc(sizeof(NODE));
		if (NULL == pNew)
		{
			printf("�����ڴ�ʧ��\n");
			exit(-1);
		}
		printf("������Ҫ���������ֵ��val=");
		scanf("%d",&val);
		
		pNew->data=val;
		pTail->pNext=pNew;
		pNew->pNext=NULL;
		pTail=pNew;
	}
	return pHead;
}


































