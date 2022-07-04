#include<bits/stdc++.h>
using namespace std;
#define n 5  					//定义字符个数 
#define m (n*2-1)			    // 结点个数 
#define maxweight 10000

typedef struct {
	char ch;
	int weight;
	int parent,lchild,rchild;
	int flag;
}HuffmanTree;

void CreateHuffman();//哈夫曼树的初始化 
void printTree(HuffmanTree);//打印二叉树 

HuffmanTree HT[m];//创建哈夫曼树 

int main(){
	
	CreateHuffman();
	printTree(HT[m-1]);//打印二叉树 
	return 0;
}

void CreateHuffman(){
	int p1,p2,s1,s2,i,j,w;
	int a=n;
	char c;
	//结点信息初始化
	for(i=0;i<m;i++){       
		HT[i].parent=0;HT[i].lchild=-1;
		HT[i].rchild=-1;HT[i].weight=0;
		HT[i].flag=0;
	}
	//读入字符信息 
	for(i=0;i<a;i++){
//		if(scanf("%c %d",&c,&w)!=2){
//			printf("输入错误\n");
//			fflush(stdin);
//			continue;
//		}
		scanf("%c %d",&c,&w);
		fflush(stdin);
		HT[i].weight=w;
		HT[i].ch=c;
		printf("          第%d个字符为%c，其权值为%d\n",i+1,HT[i].ch,HT[i].weight);
	}
	
	//将其保存在文档里 
	FILE *fpWrite=fopen("hfm Tree.txt","w");
	for(i=0;i<n;i++){
		fprintf(fpWrite, "第%d个字符为：%c，其权值为：%d\n",i+1,HT[i].ch,HT[i].weight);
	}  
    fclose(fpWrite);
    printf("\n字符及其权值已保存在文件hfm Tree.txt中\n");
	
	//建立哈夫曼树 
	for(i=n;i<m;i++){
		p1=0;p2=0;
		s1=maxweight;s2=maxweight;
		//找出权值最小的两个字符 
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
	}
	
//	for(i=0;i<m;i++){
//		printf("i=%d p=%d l=%d r=%d w=%d\n",i,HT[i].parent,HT[i].lchild,HT[i].rchild,HT[i].weight);
//	}
} 

void printTree(HuffmanTree ht)
{
	static int level = -1; //记录是第几层次
	int i;
	
	if(ht.weight==0) return;
	
	level++;
	printTree(HT[ht.rchild]);
	level--;

	level++;
	for (i = 0;i<level; i++)
		printf("\t");
	printf("%2d\n",ht.weight);
	printTree(HT[ht.lchild]);
	level--;
}

