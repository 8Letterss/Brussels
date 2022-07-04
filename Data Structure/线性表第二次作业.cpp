#include<bits/stdc++.h>
using namespace std; 

#define STACKSIZE 100   //ջ���ڴ�ռ������ 
#define STACKADD 10

typedef struct LNode{
	int data;
	struct LNode* next;	
}Node,*pNode; //��������ṹ�� 

typedef struct {
	int size;
	int * top;
	int * base;
}Sqstack;// ����ջ�ṹ�� 



pNode createlist(void);//�������� 
void traverselist(pNode);//������� 
void initstack(Sqstack * sq);//��ʼ��ջ 
void push(Sqstack * sq,int a);//ѹջ 
void pop(Sqstack * sq,int* e);//��ջ 
int key1(pNode pHead,Sqstack * sq);//��˳��ջ�жϵ�������Ԫ���������Ƿ���ͬ 
void key2(pNode pHead,pNode pstack);

int main()
{
	pNode pHead=NULL;
	pHead=createlist() ;
	traverselist(pHead);//����һ�����������֤
	 
	Sqstack sq;
	initstack(&sq);//����ջ
	 
	int flag=key1(pHead,&sq);//��˳��ջ�жϵ�������Ԫ���������Ƿ���ͬ 
	if(flag)  printf("����������Ԫ����������ͬ\n");
	else  printf("������ͬ\n"); 
	
	pNode pstack=NULL;
	key2(pHead,pstack);
	
	return 0;
}



pNode createlist()
{
	int val,len;
	pNode pls=(pNode)malloc(sizeof(Node));
	if(!pls)
	{
		printf("�����ڴ�ʧ�ܣ��������");
		exit(-1) ;
	}
	
	printf("����������ĳ��ȣ�");
	scanf("%d",&len);
	pNode pTail=pls;
	
	for(int i=0;i<len;i++)
	{
		pNode pNew=(pNode)malloc(sizeof(Node));
		if(!pNew)
		{
			printf("�����ڴ�ʧ�ܣ��������");
			exit(-1);
		}
		
		printf("�����������ֵ��");
		scanf("%d",&val);
		
		pNew->data=val;
		pTail->next=pNew;
		pNew->next=NULL;
		pTail=pNew;
	}
	return pls; 
}

void traverselist(pNode pHead)
{
	pNode p=pHead->next;
	while(p!=NULL)
	{
		printf("%d\t",p->data);
		p=p->next;
	}
//	printf("\n");
	return;
}

void initstack(Sqstack * sq)
{
	sq->base=(int*)malloc(STACKSIZE*sizeof(int));
	if(!sq->base)
	{
		printf("�����ڴ�ʧ�ܣ��������");
		exit(-1);
	}
	
	sq->top=sq->base;
	sq->size=STACKSIZE;
}

void push(Sqstack * sq,int a)//��ջ 
{
	if((sq->top-sq->base)==sq->size)//�ж�ջ�Ƿ����������������·����ڴ� 
	{
		sq->base=(int *)realloc(sq->base,(sq->size+STACKADD)*sizeof(int));
		if(!sq->base) exit(-1);
		sq->top=sq->base+sq->size;
		sq->size+=STACKADD;
	}
	*sq->top++=a;
}

void pop(Sqstack *sq,int* e)//��ջ 
{
	if(sq->top==sq->base) exit(-1);
	*e =*--sq->top;
}

int key1(pNode pHead,Sqstack * sq)
{
	int flag=1,e;
	pNode p1=pHead->next,p2=pHead->next;
	while(p1!=NULL)//���������е�Ԫ��ѹ��ջ�� 
	{
		push(sq,p1->data);
		p1=p1->next;
	}
	while(sq->top!=sq->base)//��ջ��Ԫ��������������뵥������Ԫ���ж� �Ƿ���� 
	{
		pop(sq,&e);
		if(e==p2->data)
		{
			p2=p2->next; 	
		}
		else
		{
			flag=0;
			break;
		}
	}
	return flag;
}

void key2(pNode pHead,pNode pstack)
{
	pNode pl=pHead->next,pls;
	pstack=(pNode)malloc(sizeof(Node));
	pstack->next=NULL;
	while(pl!=NULL)//��ͷ���뷨������ջ��ͷ������Ԫ�� 
	{
		pNode p=(pNode)malloc(sizeof(Node));
		p->data=pl->data;
		p->next=pstack->next;
		pstack->next=p;
		pl=pl->next; 
	}
	pls=pstack->next;
	while(pls!=NULL)//��Ԫ����� 
	{
		printf("%d\t",pls->data);
		pls=pls->next;
	}
}
