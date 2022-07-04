#include<bits/stdc++.h>
using namespace std; 
#define maxSite 100
#define infinite 10000

//������·��Ȩֵ�Ľṹ��
typedef struct{
	int path;
}ArcCell,AdjMatrix[maxSite][maxSite];


//���徰��ṹ��
typedef struct {
	char placeName[15];//��������
	int placeNo;//������
	char placeInfo[100];//��ž�����Ϣ
}place;

//����У԰��ͼ
typedef struct{
	place placeArray[maxSite];//��������
	AdjMatrix pathArray;//·������
	int placeNum;//��������
	int pathNum;//·��������
}Graph;

//��ʼ��У԰��ͼ
Graph InitGraph(){
	Graph G;
	int i,j;
	G.placeNum = 10;
	G.pathNum = 12;
	for(i=0;i<G.placeNum;i++)
		G.placeArray[i].placeNo = i;//�Ծ�����б��;
	strcpy(G.placeArray[0].placeName,"����������");
	strcpy(G.placeArray[0].placeInfo,"aaaaaaaaaaaaaaaaaaaaaaaaa");
	strcpy(G.placeArray[1].placeName,"�����ѧԺ");
	strcpy(G.placeArray[1].placeInfo,"bbbbbbbbbbbbbbbbbbbbbbbbb");
	strcpy(G.placeArray[2].placeName,"�ʶ��㳡");
	strcpy(G.placeArray[2].placeInfo,"ccccccccccccccccccccccccc");
	strcpy(G.placeArray[3].placeName,"ͼ���");
	strcpy(G.placeArray[3].placeInfo,"ddddddddddddddddddddddddd");
	strcpy(G.placeArray[4].placeName,"ѧ�������");
	strcpy(G.placeArray[4].placeInfo,"eeeeeeeeeeeeeeeeeeeeeeeee");
	strcpy(G.placeArray[5].placeName,"�Ų�¥��7�̣�");
	strcpy(G.placeArray[5].placeInfo,"fffffffffffffffffffffffff");
	strcpy(G.placeArray[6].placeName,"�ų�¥��6�̣�");
	strcpy(G.placeArray[6].placeInfo,"ggggggggggggggggggggggggg");
	strcpy(G.placeArray[7].placeName,"�����ﾶ��");
	strcpy(G.placeArray[7].placeInfo,"hhhhhhhhhhhhhhhhhhhhhhhhh");
	strcpy(G.placeArray[8].placeName,"ʳ��");
	strcpy(G.placeArray[8].placeInfo,"iiiiiiiiiiiiiiiiiiiiiiiii");
	strcpy(G.placeArray[9].placeName,"����");
	strcpy(G.placeArray[9].placeInfo,"kkkkkkkkkkkkkkkkkkkkkkkkk");

	for(i=0;i<G.placeNum;i++)
		for(j=0;j<G.pathNum;j++){
			G.pathArray[i][j].path = infinite;//�Ƚ�ÿ�������·����ʼ��Ϊ�����
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

	for(i=0;i<G.placeNum;i++)//����ͼ�෴����·��������ͬ
		for(j=0;j<G.placeNum;j++)
			G.pathArray[j][i].path=G.pathArray[i][j].path;
	
	printf("          ������֮����ڽӾ���Ϊ\n");
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

//���·����ѯ
void Floyd(Graph *G){
	int v,u,w,k,i,j,t;
	int flag = 1;//���ڱ�����������Ƿ���ȷ�����������ݷ���Ҫ����flag��Ϊ0

    int D[10][10],S[10][10];//D[10][10]��Ŷ����붥��֮���ֱ��·��

	for(v=0;v<G->placeNum;v++){
		for(w=0;w<G->placeNum;w++){
			D[v][w]=G->pathArray[v][w].path;//����ʼ·�����ݴ��������D[v][w]��
			S[v][w]=w;//��ʼ���м䶥��
		}
	}

	//uΪ�м��
	for(u=0;u<G->placeNum;++u){
		//vΪ���
		for(v=0;v<G->placeNum;++v)
			//wΪ�յ�
			for(w=0;w<G->placeNum;w++){
				if(D[v][u]+D[u][w]<D[v][w]){
					D[v][w]=D[v][u]+D[u][w];//������С·��
					S[v][w]=S[v][u];//������С·���м䶥�㣬��һ���м��
				}
			}
		
	}
	while(flag){
		printf("����������صı��:\n");
		scanf("%d",&k);
		printf("������Ŀ�ĵصı��:\n");
		scanf("%d",&j);
		if(k<0||k>=G->placeNum||j<0||j>=G->placeNum){
			printf("������ĵص����ڱ���ͼ��û����ؼ�¼,����������!\n");
		}
		else if(k==j){
			printf("�����غ�Ŀ�ĵ���ͬ,����������!\n");
		}else{
			flag=0;//�������ݺϷ�
			printf("�ӳ����ص�Ŀ�ĵص����(��)·��Ϊ:\n%s",G->placeArray[k].placeName);
			t=S[k][j];
			while(t!=j){
				printf("-->%s",G->placeArray[t].placeName);
				t=S[t][j];
			}
			printf("-->%s\n",G->placeArray[j].placeName);
			printf("��·�߳�Ϊ:%dm\n",D[k][j]);
		}
	}
}


//ѭ����������
void Interface(Graph *G)
{
	int i;
	printf("          ************���ݵ��ӿƼ���ѧУ԰����ϵͳ************\n");
	printf("\n          У԰������Ϣ����\n");
	for(i=0;i<G->placeNum;i++){
		printf("          ���:%2d ����:%s\n",G->placeArray[i].placeNo,G->placeArray[i].placeName);
	}
}

void Interface2(){
	printf("\n          *********************����ѡ��***********************\n");
	printf("\n          �鿴���������Ϣ������1\n");
	printf("\n          ���������������·��������2\n");
	printf("\n          �˳�����ϵͳ������3\n");
	printf("\n          ****************************************************\n");
}

//��ѯ������Ϣ
void SearchInfo(Graph *G){
	int k,flag=1;
	printf("������Ҫ��ѯ�ľ�����\n");
	while(flag){
		scanf("%d",&k);
		if(k<0||k>=G->placeNum){
			printf("�����Ų�����!���������뾰����:\n");
		}else{
			flag=0;
		}
	}
	printf("�þ���������Ϣ����:\n");
	printf("���:%4d  ����:%s   ���:%s\n",G->placeArray[k].placeNo,G->placeArray[k].placeName,G->placeArray[k].placeInfo);
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
		default:printf("�����������������\n");break;
		}
		scanf("%d",&c);
	}
	return 0;
}
