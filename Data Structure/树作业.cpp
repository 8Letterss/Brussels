#include<bits/stdc++.h>
using namespace std;

//������������ǵݹ���� 
Status Potraverse(BiTree T){
	InitStack(s);
	if(T){
		Push(s,T);
		while(!Emptystack(s)){
			Pop(s,p);
			printf("%c ",p->data);
			if(p->rchild!=NULL){
				Push(s,p->rchild);
			}
			if(p->lchild!=NULL){
				Push(s,p->lchild);
			}
		}//while
	}//if
}

//�����������������滻 
void ChangeBiTree(BiTree T){
	BiTree p; 
	if(T){
		p=T->lchild;
		T->lchild=T->rchild;
		T->rchild=p;
		ChangeBiTree(T->lchild);
		ChangeBiTree(T->rchild);
	}
}

//�ö���ʵ�ֶ������İ������ 
void LayerOrder(BiTree T){
	InitQueue(q);
	BiTree p=T;
	if(T){
		PushQueue(q,p);
		while(!EmptyQueue(q)){
			printf("%c",p->data);
			if(p->lchild!=NULL){
				PushQueue(q,p->lchild);
			}
			if(p->rchild!=NULL){
				PushQueue(q,p->rchild);
			}
			PopQueue(q,p);
		}
	}
}












