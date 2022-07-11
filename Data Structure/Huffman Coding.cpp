#include<bits/stdc++.h>
using namespace std;
#define n 5  					//定义字符个数 
#define m (n*2-1)			    // 结点个数 
#define maxweight 10000

//定义哈夫曼树结点结构体 
typedef struct {
	char ch;
	int weight;
	int parent,lchild,rchild;
}HuffmanTree;
//定义编码结构体 
typedef struct{
	char bits[n];
	int start;
	char ch;
}Code;

HuffmanTree HT[m];//创建哈夫曼树 
Code HC[n];

void SmallWelcome();//菜单 
void CreateHuffman();//哈夫曼树的初始化 
void HuffmanCoding();//求每个字符的编码 
void HuffmanCode();//对文本进行编码  
void deCode();//对文本进行译码 
void printTree(HuffmanTree);//打印哈夫曼树 

int main(){ 
	SmallWelcome();
	CreateHuffman();
	HuffmanCoding();
	HuffmanCode(); 
	deCode();
	printTree(HT[m-1]);
}

//哈夫曼树的创建 
void CreateHuffman(){
	int p1,p2,s1,s2,i,j,w;
	int flag=0;
	char c;
	//结点信息初始化
	for(i=0;i<m;i++){       
		HT[i].parent=0;HT[i].lchild=-1;
		HT[i].rchild=-1;HT[i].weight=0;
	}
	//读入字符信息 
	for(i=0;i<n;i++){
//		if(scanf("%c %d",&c,&w)!=2){
//			printf("输入错误\n");
//			fflush(stdin);
//			i--;
//			continue;
//		}
		scanf("%c %d",&c,&w);
		fflush(stdin);
		for(j=0;j<i;j++){
			if(HT[j].ch==c){
				printf("该字符串已存在\n");
				flag=1;
				break;
			}
		}
		
		if(flag==0){
			HT[i].weight=w;
			HT[i].ch=c;
			printf("          第%d个字符为%c，其权值为%d\n",i+1,HT[i].ch,HT[i].weight);
		}
		else {
			i--;
			flag=0;
		}
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
//		printf("i=%d l=%d r=%d\t",i,HT[i].lchild,HT[i].rchild);
	}
}


//对哈夫曼树进行编码 
void HuffmanCoding(){
	int i,j,p,c;
	Code cd; 
	for(i=0;i<n;i++){
		cd.start=n;
		cd.ch=HT[i].ch;
		c=i;
		p=HT[i].parent;
		while(p!=0){//到根节点停止 
			cd.start--;
			if(HT[p].lchild==c){		//如果i是其左孩子，左0右1； 
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
	
	//输出每个字符的哈夫曼编码
	printf("\n          每个字符的哈夫曼编码分别是：\n");
	char num;
	for(i=0;i<n;i++){
		printf("          %c: ",HC[i].ch);
		for(j=HC[i].start;j<=n;j++){
			printf("%c ",HC[i].bits[j]);
		}
		printf("\n");
	}
	
	//将符及其哈夫曼编码保存在文件里 
	FILE *fpWrite=fopen("hfm Tree.txt","a");
	for(i=0;i<n;i++){
		fprintf(fpWrite, "第%d个字符为：%c，其哈夫曼编码为：",i+1,HC[i].ch);
		for(j=HC[i].start;j<=n;j++){
			fprintf(fpWrite,"%c ",HC[i].bits[j]);
		}
		fprintf(fpWrite,"\n");
	}  
    fclose(fpWrite);
    printf("\n字符及其哈夫曼编码已保存在文件hfm Tree.txt中\n");
}

void HuffmanCode(){
	char ch[1000],c[n];
	int i=0,j,k,flag=1,count=0;

	FILE *fpRead=fopen("ToBeTran.txt","r");  
    if(fpRead==NULL)  exit(-1); 
    fscanf(fpRead,"%s ",ch);  
    printf("\n需要编译的文本是：%s \n",ch);
    
    printf("\n编译结果是："); 
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
		printf("需编译的文本中无输入字符，程序结束\n");
		exit(-1);
	}	
	fclose(fpWrite);
	printf("\n"); 
	printf("\n编译结果已保存在文件CodeFile.txt中\n");

}


void deCode(){
	int i=m-1,j=0,k=0,count=0;
	char cd[10000],ch[100];
	FILE *fpRead=fopen("CodeFile.txt","r");  
    if(fpRead==NULL)  exit(-1); 
    fscanf(fpRead,"%s",cd);
    printf("\n需要译码的字符串为:\n");
	while(cd[count]!='\0'){
		printf("%c",cd[count++]);
		if(count%50==0) printf("\n");
	}
//    printf("\n需要译码的字符串为%s\n",cd);
	printf("\n译码后的字符为："); 
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
//		printf("输入错误\n");
//	}
	
	FILE *fpWrite=fopen("TextFile.txt","w");
	fprintf(fpWrite, "其编译结果为：%s\n",ch);
    fclose(fpWrite);
    printf("\n其编译结果已保存在文件TextFile.txt中\n");
}

void printTree(HuffmanTree ht){
	FILE *fpWrite=fopen("TreePrint.txt","a");
	static int level = -1; //记录是第几层次
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
	printf("          ****************哈夫曼编码****************\n");
	printf("          ******************************************\n");
	printf("          ****************共有5个字符***************\n"); 
	printf("          *        1.请分别输入字符及其权值        *\n");
	printf("          *        2.对文档进行编码                *\n");
	printf("          *        3.对编码文件译码                *\n");
	printf("          *        4.打印哈夫曼树                  *\n");
	printf("          *        (权值不能超过10000）            *\n");
	printf("          ******************************************\n");
	
}



