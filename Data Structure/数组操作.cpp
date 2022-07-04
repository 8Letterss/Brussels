#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<stdbool.sh>

struct Arr
{
	int *pBase;
	int cnt;
	int len;
};

void init_arr(struct Arr * pArr,int length);
int get(int pos);
bool is_full(struct Arr * pArr);
bool is_empty(struct Arr * pArr);
void show_arr(struct Arr * pArr);
void append_arr(struct Arr * pArr);
void insert_arr(struct Arr *pArr);
void sort_arr(struct Arr * pArr);

int main()
{
	struct Arr arr;
	init_arr(&arr,6);
	
	return 0;
}


void init_arr(struct Arr * pArr,int length)
{
	pArr->pBase=(int *)malloc(sizeof(struct Arr)*length);
	if (NULL == pArr->pBase)
	{
		printf("动态内存分配失败\n");
		exit(-1);
	}
	else
	{
		pArr->len=length;
		pArr->cnt=0;
	}
	return;
}


bool is_empty(struct Arr * pArr)
{
	if (0 == pArr->cnt)
		return 1;
	else
		return 0; 
}


bool is_full(struct Arr * pArr)
{
	if (pArr->cnt == pArr->len)
		return 1;
	else
		return 0;
}


void show_arr(struct Arr * pArr)
{
	if (is_empty(pArr))
		printf("数组为空"\n);
	else
	{
		for(int i=1;i<pArr->cnt;i++)
		{
			printf("%d",pArr->pBase[i]);
		}
		printf("\n");
	} 
	return;
}


void append_arr(struct Arr * pArr,int val)
{
	if(is_full(pArr))
		printf("数组已满"\n);
	else
	{
		pArr->pBase[pArr->cnt]=val;
		++pArr->cnt;
	} 
	return;
}


void insert_arr(struct Arr * pArr,int pos,int val)
{
	if(is_full(pArr))
	{
		printf("数组已满"\n);
		return;
	}
	
	if (pos<1 || pos > pArr->cnt)
	{
		printf("错误"\n);
		return;
	}
	
	for (int i=pArr->cnt;i<pos-1;--i)
	{
		pArr->pBase[i+1]=pArr->pBase[i];
	}
	pArr->pBase[pos-1]=val;
	pArr->cnt ++;
	return;
}


void inversion_arr (struct Arr * pArr)
{
	int i=0;
	int j=pArr->cnt-1;
	int t;
	
	while (i<j){
		t=pArr->pBase[i];
		pArr->pBase[i]=pArr->pBase[j];
		pArr->pBase[j]=t;
		++i;
		--j;
	}
	return;
}

void sort_arr (struct Arr * pArr)
{
	int i,j,t;
	for (i=0;i<pArr->cnt-1;++i)
	{
		for (j=i+1;j<pArr->cnt;++j)
		{
			if (pArr->pBase[i]>pArr->pBase[j])
			{
				t=pArr->pBase[i];
				pArr->pBase[i]=pArr->pBase[j];
				pArr->pBase[j]=t;
			}
		}
	}
	return;
}



















