//24 25 (27) 28 36 
#include<bits/stdc++.h>
using namespace std;
#define maxsize 100

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
int level=1;
int visit[maxsize];

void CreatGraph();
int isExitedPathDFS(AGraph* ,int ,int);
//int DFSReachable(AGraph* ,int ,int);

int main(){
	int v1,v2,i;
	
	CreatGraph();
	
	for(i=0;i<G->vexnum;i++){
		visit[G->AdjList[i].data]=0;
	}
	printf("请输入起点和终点:\n");
	scanf("%d %d",&v1,&v2);
	if(isExitedPathDFS(G,v1,v2)){
		printf("存在");
	} 
//	if(DFSReachable(G,v1,v2)){
//		printf("存在");
//	} 
	
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


int isExitedPathDFS(AGraph* G,int v1,int v2){	
	struct VNode *p;
	int k; 
	
	if(v1==v2) return 1;
	else{
		visit[v1]=1;
		for(p=G->AdjList[v1].firstarc;p!=NULL;p=p->firstarc,level--){
			level++;
			k=p->data;
			if(!visit[k] && isExitedPathDFS[G,k,v2]) return true;
		}
	}
	
	if(level==1) return false;
}

//int DFSReachable(AGraph* G,int v1,int v2){
//	VNode *p;
//	Queue Q;
//	int i,j;
//	InitQueue(Q);
//	EnQueue(Q,v1);
//	while(!QueueEmpty(Q)){
//		DeQueue(Q,i);
//		visit[i]=1;
//		p=G->AdjList[i].firstarc;
//		for(;p!=NULL;p=p->firstarc){
//			j=p->data;
//			if(j==v2) return 1;
//			else if(!visit[j]) EnQueue(Q,j);
//		}
//	}
//	return 0;
//}


//void F24(AGraph* G,int start){
//	SqStack S;
//	int i,e,visit[maxsize];
//	
//	for(i=0;i<G->vexnum;i++){
//		visit[i]=-1;
//	}
//	
//	InitStack(&S);
//	Push(&S,start);
//	visit[stack]=1;
//	printf("%d",start);
//	
//	while(!StackEmpty(&S)){
//		GetTop(&S,&e);
//		
//		for(i=0;i<G->vexnum;i++){
//			if(G->AdjList[e][i].data && !visit[i]){
//				Push(&S,i);
//				visit[i]=1;
//				printf("%d",i);
//				break;
//			}
//		}
//		
//		if(i>G->vexnum) Pop(&S,&e);
//	}
//} 





