#include<bits/stdc++.h>
using namespace std;

#define STACKSIZE 100//����ջ�ڴ�ռ��С 
#define STACKADD 10

typedef struct Node{
	char data[10];
	struct Node* next;
}Node,*pNode;//��������Ľṹ�� 

typedef struct DelStu{//����ɾ��ѧ����Ϣ
        int bottom;//�ײ�λ��
        int top;//����λ��
        char data[100][100];//��ά����洢ѧ����Ϣ
}Sqstack;//����ջ�Ľṹ�� 

pNode createlist(pNode );
void travelist(pNode );
void deletelist(pNode ,char*,char name2[],Sqstack* sq);
Sqstack* InitStack();//ջ�ĳ�ʼ�� 
void Push(Sqstack*,char e[]);//ѹջ 
void pop(Sqstack* ,char []);//��ջ
void showDel(Sqstack *stu);//�鿴ɾ������Ϣ
void undo(Sqstack *sq,pNode L);//��ջ����������


int main()
{
	pNode stu;
	char name1[10],name2[10],name3[10];
	stu=createlist(stu);
	Sqstack* sq=InitStack();
	travelist(stu);
	
	printf("������Ҫɾ��ѧ��������");
	scanf("%s",name1);
  	deletelist(stu,name1,name2,sq);
	printf("ʣ�µ�ѧ���У�"); 
	travelist(stu);
	
	showDel(sq);
	undo(sq,stu);
	travelist(stu);
	
	return 0;
}


pNode createlist(pNode stu)//����������������ѧ������ 
{
	stu=(pNode)malloc(sizeof(Node));
	if(!stu) exit(-1);
	
	int n;
	pNode pTail=stu;
	printf("������ѧ��������");
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		pNode pNew=(pNode)malloc(sizeof(Node));
		if(!pNew)  exit(-1);
		printf("�������%dΪѧ��������",i+1);
		scanf("%s",pNew->data);
		pTail->next=pNew;
		pNew->next=NULL;
		pTail=pTail->next;	
	}
	return stu;
}

void travelist(pNode stu)//����������� 
{	if(!stu) exit(-1);

	pNode pls=stu->next;
	while(pls!=NULL)
	{
		printf("%s\t",pls->data);
		pls=pls->next; 
	}
	printf("\n");
}

void deletelist(pNode stu,char* name1,char name2[10],Sqstack* sq)//ɾ��ָ��Ԫ�� 
{
	pNode pls=stu,q;
	int flag=0;
 
	while(pls->next!=NULL)
	{
		if(*pls->next->data==*name1)
		{
			q=pls->next;
			strcpy(name2,q->data);
			printf("��ɾ����ѧ������Ϊ��%s\n",name2);
			Push(sq,name2);
			pls->next=q->next;
			flag++;
		}
		else
		{
			pls=pls->next; 
		}
	} 
	if(flag==0) printf("�����ڴ�ѧ������"); 
}


Sqstack* InitStack()//��ʼ��
{
    Sqstack* s=(Sqstack*)malloc(sizeof(Sqstack));//���ٿռ�
    if(s==NULL) return 0;
    s->bottom=s->top=0;
    return s;
}


void Push(Sqstack*s,char e[]){//����ɾ����ѧ����Ϣѹ��ջ
       strcpy(s->data[s->top],e);
       s->top++;
}

void showDel(Sqstack *sq)//�鿴ɾ������Ϣ
{
    printf("������ʾ��ɾ��ѧ����Ϣ��");
    Sqstack* p=sq;
    int a = p->top;//��¼����
    //p->bottom=p->top=0;

    while(p->top!=p->bottom){//����ջ
            printf("%s\n",p->data[p->top-1]);
            p->top--;
    }
    p->top=a;//��top�Ż�ԭ���Ķ���
    return;
}

void undo(Sqstack *sq,pNode stu)//��ջ����������
{
    char *e;
    pNode p=stu;
    if(sq->top!=sq->bottom){//ջ�ǿ�
        e=sq->data[sq->top-1];
        sq->top--;
        printf("������ѧ����Ϣ��%s\n",e);

		while(p->next!=NULL) p=p->next;
        p->next=(pNode)malloc(sizeof(Node)); // �����½�㲢���뵽��β
        strcpy(p->next->data,e);//��������
        p->next->next = NULL;
    }
    return ;
}





