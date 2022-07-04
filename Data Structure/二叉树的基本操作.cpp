#include<bits/stdc++.h>
using namespace std;

typedef struct Node{
	char data;
	struct Node* Lchild,* Rchild;
}BTNode,*BTree;

void CreatBTree(BTree T);//���������� 
void DestroyBTree(BTree T);//���ٶ����� 
void PreOrderTraverse(BTree T);//������� 
void InOrderTraverse(BTree T);//������� 
void PostOrderTraverse(BTree T);//������� 
void DestroyLeftChild(BTree T);//ɾ�������� 
void DestroyRigthChild(BTree T);//ɾ�������� 
int MaxDepth(BTree T);//��������� 
int NodeCount(BTree T);//���Ľ���� 

int main(){
	BTree T;
	CreatBTree(T);
	return 0;
}

void CreatBTree(BTree T){
	char ch;
	printf("\n��������Ԫ��\n");
	scanf("%c",&ch);
	fflush(stdin);
	if(ch=='#') T=NULL;
	else{
		T=(BTree)malloc(sizeof(BTNode));
		if(T==NULL){
			printf("\n�����ڴ�ʧ��\n");
			exit(-1);
		}
		T->data=ch;
		CreatBTree(T->Lchild);
		CreatBTree(T->Rchild);
	}
}

void DestroyBTree(BTree T){
	if(T){
		if(T->Lchild)
			DestroyBTree(T->Lchild);
		if(T->Rchild)
			DestroyBTree(T->Rchild);
		free(T);
		T=NULL;
	}
}

void PreOrderTraverse(BTree T){
	if(T){
		printf("%-5c",T->data);
		PreOrderTraverse(T->Lchild);
		PreOrderTraverse(T->Rchild);
	}
}

void InOrderTraverse(BTree T){
	if(T){
		InOrderTraverse(T->Lchild);
		printf("%-5c",T->data);
		InOrderTraverse(T->Rchild);
	}
}

void PostOrderTraverse(BTree T){
	if(T){
		PostOrderTraverse(T->Lchild);
		PostOrderTraverse(T->Rchild);
		printf("%-5c",T->data);
	}
}

void DestroyLeftChild(BTree T){
	if(T){
		DestroyBTree(T->Lchild);
	} 
}

void DestroyRigthChild(BTree T){
	if(T){
		DestroyBTree(T->Rchild);
	}
} 

int MaxDepth(BTree T){
	if(T==NULL) return 0;
	else{
		int maxLeft=MaxDepth(T->Lchild);
		int maxRigth=MaxDepth(T->Rchild);
		int max=maxLeft>maxRigth ? maxLeft:maxRigth;
		return max+1;
	} 
}

int NodeCount(BTree T){
	if(T==NULL) return 0;
	else{
		return NodeCount(T->Lchild)+NodeCount(T->Rchild)+1; 
	} 
}
