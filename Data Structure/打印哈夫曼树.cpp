#include<bits/stdc++.h>
using namespace std;
#define n 5  					//�����ַ����� 
#define m (n*2-1)			    // ������ 
#define maxweight 10000

typedef struct {
	char ch;
	int weight;
	int parent,lchild,rchild;
	int flag;
}HuffmanTree;

void CreateHuffman();//���������ĳ�ʼ�� 
void printTree(HuffmanTree);//��ӡ������ 

HuffmanTree HT[m];//������������ 

int main(){
	
	CreateHuffman();
	printTree(HT[m-1]);//��ӡ������ 
	return 0;
}

void CreateHuffman(){
	int p1,p2,s1,s2,i,j,w;
	int a=n;
	char c;
	//�����Ϣ��ʼ��
	for(i=0;i<m;i++){       
		HT[i].parent=0;HT[i].lchild=-1;
		HT[i].rchild=-1;HT[i].weight=0;
		HT[i].flag=0;
	}
	//�����ַ���Ϣ 
	for(i=0;i<a;i++){
//		if(scanf("%c %d",&c,&w)!=2){
//			printf("�������\n");
//			fflush(stdin);
//			continue;
//		}
		scanf("%c %d",&c,&w);
		fflush(stdin);
		HT[i].weight=w;
		HT[i].ch=c;
		printf("          ��%d���ַ�Ϊ%c����ȨֵΪ%d\n",i+1,HT[i].ch,HT[i].weight);
	}
	
	//���䱣�����ĵ��� 
	FILE *fpWrite=fopen("hfm Tree.txt","w");
	for(i=0;i<n;i++){
		fprintf(fpWrite, "��%d���ַ�Ϊ��%c����ȨֵΪ��%d\n",i+1,HT[i].ch,HT[i].weight);
	}  
    fclose(fpWrite);
    printf("\n�ַ�����Ȩֵ�ѱ������ļ�hfm Tree.txt��\n");
	
	//������������ 
	for(i=n;i<m;i++){
		p1=0;p2=0;
		s1=maxweight;s2=maxweight;
		//�ҳ�Ȩֵ��С�������ַ� 
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
	static int level = -1; //��¼�ǵڼ����
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

