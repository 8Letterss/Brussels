#include<bits/stdc++.h>
using namespace std;

#define STACKSIZE 100
#define STACKADD 10

typedef struct {
	int stacksize;
	int* top;
	int* base;
}Sqstack;

void initstack(Sqstack* sq);//ջ�ĳ�ʼ�� 
void push(Sqstack* ,int );//ѹջ 
int pop(Sqstack*);//��ջ 


int main()
{
	Sqstack sq1,sq2;
	initstack(&sq1);initstack(&sq2);
	int nums[]={1,2,3,4,5,6};
	for(int i=0;i<6;i++)//��Ԫ��ѹ��ջ1 
	{
		push(&sq1,*(nums+i));
	}
	printf("���ӵ�˳��Ϊ:\n");
	while(sq1.base != sq1.top)
	{
		while(sq1.top - sq1.base >1)
			push(&sq2,pop(&sq1));//��ջ1Ԫ��ѹ��ջ2 
		printf("%d \t",pop(&sq1));//���ջ��Ԫ�� 
		while(sq2.top - sq2.base > 0)//��ջ2Ԫ��ѹ��ջ1 
			push(&sq1,pop(&sq2));
	}
	printf("\n");
	
	
	return 0;
}


void initstack(Sqstack* sq)//ջ�ĳ�ʼ�� 
{
	sq->base=(int*)malloc(STACKSIZE*sizeof(int));
	if(!sq->base)  exit(-1);
	sq->top=sq->base;
	sq->stacksize=STACKSIZE;
}

void push(Sqstack* sq,int n)//ѹջ 
{
	if((sq->top-sq->base)==sq->stacksize)
	{
		sq->base=(int*)realloc(sq->base,(sq->stacksize+STACKADD)*sizeof(int));
		if(!sq->base)  exit(-1);
		sq->top=sq->base+sq->stacksize;
		sq->stacksize+=STACKADD; 
	}
	*sq->top++=n;
}

int pop(Sqstack* sq)//��ջ 
{
	if(sq->top==sq->base) exit(-1);
	return *--sq->top;
}
