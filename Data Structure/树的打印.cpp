#include<bits/stdc++.h>
using namespace std;
#define n 5 
#define m (2*n-1)

typedef struct {
	int weight;
	char ch;
	int parent,lchild,rchild;
}HuffmanTree;

HuffmanTree HT[m];

void CreateHuffman();

int main(){
	
	CreateHuffman(); 
	
	return 0;
}

void CreateHuffman(){
	int p1,p2,s1,s2,i,j,w;
	int a=n;
	char c;
	for(i=0;i<m;i++){
		HT[i].parent=0;HT[i].lchild=-1;
		HT[i].rchild=-1;HT[i].weight=0;
	}
	for(i=0;i<a;i++){
		if(scanf("%c %d",&c,&w)!=2){
			printf("输入错误\n");
			getchar();
			i--;
			continue;
		}else{
		HT[i].weight=w;
		HT[i].ch=c;
		printf("          第%d为字符是%c，权值为%d\n",i+1,HT[i].ch,HT[i].weight);
		}
	}
	
	for(i=n;i<m;i++){
		p1=0;p2=0;
		s1=HT[0].weight;s2=HT[1].weight;
		for(j=0;j<i;j++){
			if(HT[j].parent==0){
				if(HT[j].weight<s1){
					s2=s1;
					s1=HT[j].weight;
					p2=p1;p1=j;
				}
				else if(HT[j].weight<s2){
					s2=HT[j].weight;
					p2=j;
				}
			}
    	}
		HT[p1].parent=i;HT[p2].parent=i;
		HT[i].lchild=p1;HT[i].rchild=p2;
		HT[i].weight=HT[p1].weight+HT[p2].weight;
		printf("i=%d l=%d r=%d\t",i,HT[i].lchild,HT[i].rchild);
	}
}
