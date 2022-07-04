#include<bits/stdc++.h>
using namespace std; 
#define maxSite 100
#define infinite 10000

//定义存放路径权值的结构体
typedef struct{
	int path;
}ArcCell,AdjMatrix[maxSite][maxSite];


//定义景点结构体
typedef struct {
	char placeName[15];//景点名称
	int placeNo;//景点编号
	char placeInfo[100];//存放景点信息
}place;

//定义校园地图
typedef struct{
	place placeArray[maxSite];//景点数组
	AdjMatrix pathArray;//路径数组
	int placeNum;//景点数量
	int pathNum;//路径总数量
}Graph;

//初始化校园地图
Graph InitGraph(){
	Graph G;
	int i,j;
	G.placeNum = 10;
	G.pathNum = 12;
	for(i=0;i<G.placeNum;i++)
		G.placeArray[i].placeNo = i;//对景点进行编号;
	strcpy(G.placeArray[0].placeName,"杭电正大门");
	strcpy(G.placeArray[0].placeInfo,"aaaaaaaaaaaaaaaaaaaaaaaaa");
	strcpy(G.placeArray[1].placeName,"计算机学院");
	strcpy(G.placeArray[1].placeInfo,"bbbbbbbbbbbbbbbbbbbbbbbbb");
	strcpy(G.placeArray[2].placeName,"问鼎广场");
	strcpy(G.placeArray[2].placeInfo,"ccccccccccccccccccccccccc");
	strcpy(G.placeArray[3].placeName,"图书馆");
	strcpy(G.placeArray[3].placeInfo,"ddddddddddddddddddddddddd");
	strcpy(G.placeArray[4].placeName,"学生活动中心");
	strcpy(G.placeArray[4].placeInfo,"eeeeeeeeeeeeeeeeeeeeeeeee");
	strcpy(G.placeArray[5].placeName,"信博楼（7教）");
	strcpy(G.placeArray[5].placeInfo,"fffffffffffffffffffffffff");
	strcpy(G.placeArray[6].placeName,"信诚楼（6教）");
	strcpy(G.placeArray[6].placeInfo,"ggggggggggggggggggggggggg");
	strcpy(G.placeArray[7].placeName,"东边田径场");
	strcpy(G.placeArray[7].placeInfo,"hhhhhhhhhhhhhhhhhhhhhhhhh");
	strcpy(G.placeArray[8].placeName,"食堂");
	strcpy(G.placeArray[8].placeInfo,"iiiiiiiiiiiiiiiiiiiiiiiii");
	strcpy(G.placeArray[9].placeName,"寝室");
	strcpy(G.placeArray[9].placeInfo,"kkkkkkkkkkkkkkkkkkkkkkkkk");

	for(i=0;i<G.placeNum;i++)
		for(j=0;j<G.pathNum;j++){
			G.pathArray[i][j].path = infinite;//先将每个结点间的路径初始化为无穷大
		}
	G.pathArray[0][1].path = 100;
	G.pathArray[1][2].path = 150;
	G.pathArray[2][3].path = 100;
	G.pathArray[2][5].path = 150;
	G.pathArray[2][6].path = 160;
	G.pathArray[3][4].path = 90;
	G.pathArray[3][5].path = 50;
	G.pathArray[3][6].path = 50;
	G.pathArray[4][5].path = 50;
	G.pathArray[4][7].path = 50;
	G.pathArray[4][8].path = 60;
	G.pathArray[8][9].path = 50;

	for(i=0;i<G.placeNum;i++)//无向图相反方向路径长度相同
		for(j=0;j<G.placeNum;j++)
			G.pathArray[j][i].path=G.pathArray[i][j].path;
	
	printf("          各景点之间的邻接矩阵为\n");
	printf("             ");
	for(j=0;j<G.placeNum;j++) printf("%-10d",j);
	printf("\n");
	for(i=0;i<G.placeNum;i++){
		printf("          %d  ",i);
		for(j=0;j<G.placeNum;j++){
			printf("%-10d",G.pathArray[i][j].path);
		}
		printf("\n");
	}
		return G;
}

//最短路径查询
void Floyd(Graph *G){
	int v,u,w,k,i,j,t;
	int flag = 1;//用于标记输入数据是否正确，若输入数据符合要求，则将flag置为0

    int D[10][10],S[10][10];//D[10][10]存放顶点与顶点之间的直接路径

	for(v=0;v<G->placeNum;v++){
		for(w=0;w<G->placeNum;w++){
			D[v][w]=G->pathArray[v][w].path;//将初始路径数据存放在数组D[v][w]中
			S[v][w]=w;//初始化中间顶点
		}
	}

	//u为中间点
	for(u=0;u<G->placeNum;++u){
		//v为起点
		for(v=0;v<G->placeNum;++v)
			//w为终点
			for(w=0;w<G->placeNum;w++){
				if(D[v][u]+D[u][w]<D[v][w]){
					D[v][w]=D[v][u]+D[u][w];//更新最小路径
					S[v][w]=S[v][u];//更新最小路径中间顶点，第一个中间点
				}
			}
		
	}
	while(flag){
		printf("请输入出发地的编号:\n");
		scanf("%d",&k);
		printf("请输入目的地的编号:\n");
		scanf("%d",&j);
		if(k<0||k>=G->placeNum||j<0||j>=G->placeNum){
			printf("您输入的地点编号在本地图内没有相关记录,请重新输入!\n");
		}
		else if(k==j){
			printf("出发地和目的地相同,请重新输入!\n");
		}else{
			flag=0;//输入数据合法
			printf("从出发地到目的地的最佳(短)路径为:\n%s",G->placeArray[k].placeName);
			t=S[k][j];
			while(t!=j){
				printf("-->%s",G->placeArray[t].placeName);
				t=S[t][j];
			}
			printf("-->%s\n",G->placeArray[j].placeName);
			printf("总路线长为:%dm\n",D[k][j]);
		}
	}
}


//循环操作界面
void Interface(Graph *G)
{
	int i;
	printf("          ************杭州电子科技大学校园导游系统************\n");
	printf("\n          校园景点信息如下\n");
	for(i=0;i<G->placeNum;i++){
		printf("          编号:%2d 名称:%s\n",G->placeArray[i].placeNo,G->placeArray[i].placeName);
	}
}

void Interface2(){
	printf("\n          *********************功能选择***********************\n");
	printf("\n          查看景点相关信息请输入1\n");
	printf("\n          查找两景点间的最短路径请输入2\n");
	printf("\n          退出导游系统请输入3\n");
	printf("\n          ****************************************************\n");
}

//查询景点信息
void SearchInfo(Graph *G){
	int k,flag=1;
	printf("请输入要查询的景点编号\n");
	while(flag){
		scanf("%d",&k);
		if(k<0||k>=G->placeNum){
			printf("景点编号不存在!请重新输入景点编号:\n");
		}else{
			flag=0;
		}
	}
	printf("该景点的相关信息如下:\n");
	printf("编号:%4d  名称:%s   简介:%s\n",G->placeArray[k].placeNo,G->placeArray[k].placeName,G->placeArray[k].placeInfo);
	printf("\n");
}


int main(){
	int c;
	Graph G = InitGraph();
	Interface(&G);
	Interface2();
	scanf("%d",&c);
	while(c!=3){
		switch(c){
		case 1:SearchInfo(&G);Interface(&G);Interface2();break;
		case 2:Floyd(&G);Interface(&G);Interface2();break;
		case 3:exit(0);break;
		default:printf("输入错误，请重新输入\n");break;
		}
		scanf("%d",&c);
	}
	return 0;
}
