//14 (22) 23 24 25 (27) 28 36 

#include<bits/stdc++.h>
using namespace std;
#define maxsize 100

typedef struct ArcNode{
	int adjvex;
	struct ArcNode *nextarc;
}ArcNode;
typedef struct {
	int data;
	ArcNode * firstarc;
}VNode;
typedef struct {
	VNode AdjList[maxsize];
	int vexnum,arcnum;
}AGraph;//图的结构体 

int main(){
	
	
	return 0;
}
