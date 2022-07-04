//(22) 23 24 25 (27) 28 36 

#include<bits/stdc++.h>
using namespace std;
#define maxsize 100
 
typedef struct VNode{
    int data;
    struct VNode *firstarc;
}VNode;
typedef struct{
    VNode AdjList[maxsize];
    int vexnum,arcnum;
}AGraph;//图结构体 

AGraph *G;
void CreatGraph();

int main(){
	CreatGraph();
	return 0;
}

void CreatGraph(){
	G=(AGraph*)malloc(sizeof(AGraph));
	printf("请输入顶点数目：");
    scanf("%d", &(G->vexnum));
    printf("请输入弧的数目：");
    scanf("%d", &(G->arcnum));
	
	int i,j,v1,v2,a,b;
	for(i=0;i<G->vexnum;i++){
		printf("请输入顶点编号：\n");
		scanf("%d",&G->AdjList[i].data);
		G->AdjList[i].firstarc=NULL;
	}
	
	for(i=0;i<G->arcnum;i++){
		printf("请输入弧的两个顶点编号：\n");
		scanf("%d %d",&v1,&v2);
		
		for(j=0;j<G->vexnum;j++)
			if(G->AdjList[i].data==v1)
				a=j;
		for(j=0;j<G->vexnum;j++)
			if(G->AdjList[i].data==v2)
				b=j;
				
		VNode *p=(VNode*)malloc(sizeof(VNode));
		p->data=b;
		p->firstarc=G->AdjList[a].firstarc;
		G->AdjList[i].firstarc=p;
	}
}


