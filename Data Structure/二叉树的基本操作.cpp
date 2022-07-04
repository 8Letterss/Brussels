#include<bits/stdc++.h>
using namespace std;

typedef struct Node{
	char data;
	struct Node* Lchild,* Rchild;
}BTNode,*BTree;

void CreatBTree(BTree T);//创建二叉树 
void DestroyBTree(BTree T);//销毁二叉树 
void PreOrderTraverse(BTree T);//先序遍历 
void InOrderTraverse(BTree T);//中序遍历 
void PostOrderTraverse(BTree T);//后序遍历 
void DestroyLeftChild(BTree T);//删除左子树 
void DestroyRigthChild(BTree T);//删除右子树 
int MaxDepth(BTree T);//求树的深度 
int NodeCount(BTree T);//数的结点数 

int main(){
	BTree T;
	CreatBTree(T);
	return 0;
}

void CreatBTree(BTree T){
	char ch;
	printf("\n请输入结点元素\n");
	scanf("%c",&ch);
	fflush(stdin);
	if(ch=='#') T=NULL;
	else{
		T=(BTree)malloc(sizeof(BTNode));
		if(T==NULL){
			printf("\n申请内存失败\n");
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
