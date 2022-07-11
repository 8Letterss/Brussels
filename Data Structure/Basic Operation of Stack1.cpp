#include<bits/stdc++.h>
using namespace std;

#define STACKSIZE 100//定义栈内存空间大小 
#define STACKADD 10

typedef struct Node{
	char data[10];
	struct Node* next;
}Node,*pNode;//定义链表的结构体 

typedef struct DelStu{//储存删除学生信息
        int bottom;//底部位置
        int top;//顶部位置
        char data[100][100];//二维数组存储学生信息
}Sqstack;//定义栈的结构体 

pNode createlist(pNode );
void travelist(pNode );
void deletelist(pNode ,char*,char name2[],Sqstack* sq);
Sqstack* InitStack();//栈的初始化 
void Push(Sqstack*,char e[]);//压栈 
void pop(Sqstack* ,char []);//出栈
void showDel(Sqstack *stu);//查看删除的信息
void undo(Sqstack *sq,pNode L);//出栈，撤销操作


int main()
{
	pNode stu;
	char name1[10],name2[10],name3[10];
	stu=createlist(stu);
	Sqstack* sq=InitStack();
	travelist(stu);
	
	printf("请输入要删除学生姓名：");
	scanf("%s",name1);
  	deletelist(stu,name1,name2,sq);
	printf("剩下的学生有："); 
	travelist(stu);
	
	showDel(sq);
	undo(sq,stu);
	travelist(stu);
	
	return 0;
}


pNode createlist(pNode stu)//创建单链表，并输入学生姓名 
{
	stu=(pNode)malloc(sizeof(Node));
	if(!stu) exit(-1);
	
	int n;
	pNode pTail=stu;
	printf("请输入学生个数：");
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		pNode pNew=(pNode)malloc(sizeof(Node));
		if(!pNew)  exit(-1);
		printf("请输入第%d为学生姓名：",i+1);
		scanf("%s",pNew->data);
		pTail->next=pNew;
		pNew->next=NULL;
		pTail=pTail->next;	
	}
	return stu;
}

void travelist(pNode stu)//将单链表输出 
{	if(!stu) exit(-1);

	pNode pls=stu->next;
	while(pls!=NULL)
	{
		printf("%s\t",pls->data);
		pls=pls->next; 
	}
	printf("\n");
}

void deletelist(pNode stu,char* name1,char name2[10],Sqstack* sq)//删除指定元素 
{
	pNode pls=stu,q;
	int flag=0;
 
	while(pls->next!=NULL)
	{
		if(*pls->next->data==*name1)
		{
			q=pls->next;
			strcpy(name2,q->data);
			printf("您删除的学生姓名为：%s\n",name2);
			Push(sq,name2);
			pls->next=q->next;
			flag++;
		}
		else
		{
			pls=pls->next; 
		}
	} 
	if(flag==0) printf("不存在此学生姓名"); 
}


Sqstack* InitStack()//初始化
{
    Sqstack* s=(Sqstack*)malloc(sizeof(Sqstack));//开辟空间
    if(s==NULL) return 0;
    s->bottom=s->top=0;
    return s;
}


void Push(Sqstack*s,char e[]){//将被删除的学生信息压入栈
       strcpy(s->data[s->top],e);
       s->top++;
}

void showDel(Sqstack *sq)//查看删除的信息
{
    printf("下面显示被删除学生信息：");
    Sqstack* p=sq;
    int a = p->top;//记录顶部
    //p->bottom=p->top=0;

    while(p->top!=p->bottom){//遍历栈
            printf("%s\n",p->data[p->top-1]);
            p->top--;
    }
    p->top=a;//将top放回原来的顶部
    return;
}

void undo(Sqstack *sq,pNode stu)//出栈，撤销操作
{
    char *e;
    pNode p=stu;
    if(sq->top!=sq->bottom){//栈非空
        e=sq->data[sq->top-1];
        sq->top--;
        printf("撤销的学生信息：%s\n",e);

		while(p->next!=NULL) p=p->next;
        p->next=(pNode)malloc(sizeof(Node)); // 生成新结点并插入到表尾
        strcpy(p->next->data,e);//撤销操作
        p->next->next = NULL;
    }
    return ;
}





