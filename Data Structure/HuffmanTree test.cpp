#include<bits/stdc++.h>
using namespace std;
#define n 5  					//�����ַ����� 
#define m (n*2-1)			    // ������ 
#define maxweight 10000

//��������������ṹ�� 
typedef struct {
	char ch;
	int weight;
	int parent,lchild,rchild;
}HuffmanTree;
//�������ṹ�� 
typedef struct{
	char bits[n];
	int start;
	char ch;
}Code;

HuffmanTree HT[m];//������������ 
Code HC[n];

void SmallWelcome();//�˵� 
void CreateHuffman();//���������ĳ�ʼ�� 
void HuffmanCoding();//��ÿ���ַ��ı��� 
void HuffmanCode();//���ı����б���  
void deCode();//���ı��������� 
void printTree(HuffmanTree);//��ӡ�������� 

int main(){ 
	SmallWelcome();
	CreateHuffman();
	HuffmanCoding();
	HuffmanCode(); 
	deCode();
	printTree(HT[m-1]);
}

//���������Ĵ��� 
void CreateHuffman(){
	int p1,p2,s1,s2,i,j,w;
	int flag=0;
	char c;
	//�����Ϣ��ʼ��
	for(i=0;i<m;i++){       
		HT[i].parent=0;HT[i].lchild=-1;
		HT[i].rchild=-1;HT[i].weight=0;
	}
	//�����ַ���Ϣ 
	for(i=0;i<n;i++){
//		if(scanf("%c %d",&c,&w)!=2){
//			printf("�������\n");
//			fflush(stdin);
//			i--;
//			continue;
//		}
		scanf("%c %d",&c,&w);
		fflush(stdin);
		for(j=0;j<i;j++){
			if(HT[j].ch==c){
				printf("���ַ����Ѵ���\n");
				flag=1;
				break;
			}
		}
		
		if(flag==0){
			HT[i].weight=w;
			HT[i].ch=c;
			printf("          ��%d���ַ�Ϊ%c����ȨֵΪ%d\n",i+1,HT[i].ch,HT[i].weight);
		}
		else {
			i--;
			flag=0;
		}
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
//		printf("i=%d l=%d r=%d\t",i,HT[i].lchild,HT[i].rchild);
	}
}


//�Թ����������б��� 
void HuffmanCoding(){
	int i,j,p,c;
	Code cd; 
	for(i=0;i<n;i++){
		cd.start=n;
		cd.ch=HT[i].ch;
		c=i;
		p=HT[i].parent;
		while(p!=0){//�����ڵ�ֹͣ 
			cd.start--;
			if(HT[p].lchild==c){		//���i�������ӣ���0��1�� 
				cd.bits[cd.start]='0';
			}
			else{
				cd.bits[cd.start]='1';
			}
			c=p;
			p=HT[p].parent;
		}
		HC[i]=cd;
	} 
	
	//���ÿ���ַ��Ĺ���������
	printf("\n          ÿ���ַ��Ĺ���������ֱ��ǣ�\n");
	char num;
	for(i=0;i<n;i++){
		printf("          %c: ",HC[i].ch);
		for(j=HC[i].start;j<=n;j++){
			printf("%c ",HC[i].bits[j]);
		}
		printf("\n");
	}
	
	//����������������뱣�����ļ��� 
	FILE *fpWrite=fopen("hfm Tree.txt","a");
	for(i=0;i<n;i++){
		fprintf(fpWrite, "��%d���ַ�Ϊ��%c�������������Ϊ��",i+1,HC[i].ch);
		for(j=HC[i].start;j<=n;j++){
			fprintf(fpWrite,"%c ",HC[i].bits[j]);
		}
		fprintf(fpWrite,"\n");
	}  
    fclose(fpWrite);
    printf("\n�ַ���������������ѱ������ļ�hfm Tree.txt��\n");
}

void HuffmanCode(){
	char ch[1000],c[n];
	int i=0,j,k,flag=1,count=0;

	FILE *fpRead=fopen("ToBeTran.txt","r");  
    if(fpRead==NULL)  exit(-1); 
    fscanf(fpRead,"%s ",ch);  
    printf("\n��Ҫ������ı��ǣ�%s \n",ch);
    
    printf("\n�������ǣ�"); 
    FILE *fpWrite=fopen("CodeFile.txt","w");

	while(ch[i]!='\0'){
		for(k=0;k<n;k++){
			if(HC[k].ch==ch[i]){
				for(j=HC[k].start;j<n;j++){
					flag=0;
					count++;
					printf("%c",HC[k].bits[j]);
					fprintf(fpWrite,"%c",HC[k].bits[j]);
				}
				printf(" ");
			}//if
		}//for
		i++;
	}//while 
	
	if(flag==1){
		printf("�������ı����������ַ����������\n");
		exit(-1);
	}	
	fclose(fpWrite);
	printf("\n"); 
	printf("\n�������ѱ������ļ�CodeFile.txt��\n");

}


void deCode(){
	int i=m-1,j=0,k=0,count=0;
	char cd[10000],ch[100];
	FILE *fpRead=fopen("CodeFile.txt","r");  
    if(fpRead==NULL)  exit(-1); 
    fscanf(fpRead,"%s",cd);
    printf("\n��Ҫ������ַ���Ϊ:\n");
	while(cd[count]!='\0'){
		printf("%c",cd[count++]);
		if(count%50==0) printf("\n");
	}
//    printf("\n��Ҫ������ַ���Ϊ%s\n",cd);
	printf("\n�������ַ�Ϊ��"); 
	while(cd[j]!='\0'){
		if(cd[j]=='0'){
			i=HT[i].lchild;
		}
		else if(cd[j]=='1'){
			i=HT[i].rchild;
		}
		if(HT[i].lchild==-1){
			printf("%c",HT[i].ch);
			ch[k++]=HT[i].ch;
			i=m-1;
		}
		j++;
	}//while
	printf("\n");
//	if(HT[i].lchild!=-1 && cd[j]=='\0') {
//		printf("�������\n");
//	}
	
	FILE *fpWrite=fopen("TextFile.txt","w");
	fprintf(fpWrite, "�������Ϊ��%s\n",ch);
    fclose(fpWrite);
    printf("\n��������ѱ������ļ�TextFile.txt��\n");
}

void printTree(HuffmanTree ht){
	FILE *fpWrite=fopen("TreePrint.txt","a");
	static int level = -1; //��¼�ǵڼ����
	int i;
	
	if(ht.weight==0) return;
	
	level++;
	printTree(HT[ht.rchild]);
	level--;

	level++;
	for (i = 0;i<level; i++){
		printf("\t");
		fprintf(fpWrite,"\t");
	}
	printf("%2d\n",ht.weight);
	fprintf(fpWrite, "%2d\n",ht.weight);
	fclose(fpWrite);
	printTree(HT[ht.lchild]);
	level--;
}

void SmallWelcome(){
	printf("          ****************����������****************\n");
	printf("          ******************************************\n");
	printf("          ****************����5���ַ�***************\n"); 
	printf("          *        1.��ֱ������ַ�����Ȩֵ        *\n");
	printf("          *        2.���ĵ����б���                *\n");
	printf("          *        3.�Ա����ļ�����                *\n");
	printf("          *        4.��ӡ��������                  *\n");
	printf("          *        (Ȩֵ���ܳ���10000��            *\n");
	printf("          ******************************************\n");
	
}



