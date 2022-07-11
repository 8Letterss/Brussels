#include<bits/stdc++.h>
using namespace std; 

#define STACKSIZE 100   //栈的内存空间分配量 
#define STACKADD 10

typedef struct LNode{
	int data;
	struct LNode* next;	
}Node,*pNode; //创建链表结构体 

typedef struct {
	int size;
	int * top;
	int * base;
}Sqstack;// 创建栈结构体 



pNode createlist(void);//创建链表 
void traverselist(pNode);//输出链表 
void initstack(Sqstack * sq);//初始化栈 
void push(Sqstack * sq,int a);//压栈 
void pop(Sqstack * sq,int* e);//出栈 
int key1(pNode pHead,Sqstack * sq);//用顺序栈判断单链表在元素正反序是否相同 
void key2(pNode pHead,pNode pstack);

int main()
{
	pNode pHead=NULL;
	pHead=createlist() ;
	traverselist(pHead);//创建一个链表并输出验证
	 
	Sqstack sq;
	initstack(&sq);//创建栈
	 
	int flag=key1(pHead,&sq);//用顺序栈判断单链表在元素正反序是否相同 
	if(flag)  printf("链表中所有元素正反序相同\n");
	else  printf("正反序不同\n"); 
	
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
		printf("分配内存失败，程序结束");
		exit(-1) ;
	}
	
	printf("请输入链表的长度：");
	scanf("%d",&len);
	pNode pTail=pls;
	
	for(int i=0;i<len;i++)
	{
		pNode pNew=(pNode)malloc(sizeof(Node));
		if(!pNew)
		{
			printf("分配内存失败，程序结束");
			exit(-1);
		}
		
		printf("请输入链表的值：");
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
		printf("分配内存失败，程序结束");
		exit(-1);
	}
	
	sq->top=sq->base;
	sq->size=STACKSIZE;
}

void push(Sqstack * sq,int a)//入栈 
{
	if((sq->top-sq->base)==sq->size)//判断栈是否已满，若满则重新分配内存 
	{
		sq->base=(int *)realloc(sq->base,(sq->size+STACKADD)*sizeof(int));
		if(!sq->base) exit(-1);
		sq->top=sq->base+sq->size;
		sq->size+=STACKADD;
	}
	*sq->top++=a;
}

void pop(Sqstack *sq,int* e)//出栈 
{
	if(sq->top==sq->base) exit(-1);
	*e =*--sq->top;
}

int key1(pNode pHead,Sqstack * sq)
{
	int flag=1,e;
	pNode p1=pHead->next,p2=pHead->next;
	while(p1!=NULL)//将单链表中的元素压入栈中 
	{
		push(sq,p1->data);
		p1=p1->next;
	}
	while(sq->top!=sq->base)//将栈中元素依次输出，并与单链表中元素判断 是否相等 
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
	while(pl!=NULL)//用头插入法，在链栈的头部插入元素 
	{
		pNode p=(pNode)malloc(sizeof(Node));
		p->data=pl->data;
		p->next=pstack->next;
		pstack->next=p;
		pl=pl->next; 
	}
	pls=pstack->next;
	while(pls!=NULL)//将元素输出 
	{
		printf("%d\t",pls->data);
		pls=pls->next;
	}
}
