#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ROW 8
#define COL 8
#define MAX_STEPS (ROW*COL)
//�������̴�С 
 
typedef struct stact{
    int x;
    int y;
    int direction;
}HorseStact; 

//���� 
int chess[ROW+1][COL+1];
//��һ�����巽�� 
int dir[8][2]={{2,-1},{-2,-1},{-2,1},{2,1},{1,-2},{-1,-2},{-1,2},{1,2}};

int TopStact;//ջ�� 
int OutStact;//��ջ 
int t=1;
HorseStact horse[MAX_STEPS]; 

//��ʼ��
void init(){
    int n=MAX_STEPS-1;
    //��ʼ��horse 
    while(n!=-1){
        horse[n].x=0;
        horse[n].y=0;
        horse[n].direction=-1;
        n--;
    }
	//��ʼ������ 
    for(int i=1;i<=ROW;i++){
        for(int j=1;j<=COL;j++){
            chess[i][j]=0;
        }
    } 
    TopStact=-1;
    OutStact=0;
}

//��ջ
void PushStact(int xx,int yy){
    TopStact++;
    horse[TopStact].x=xx;
    horse[TopStact].y=yy;
    horse[TopStact].direction=-1;
}

//��ջ
void PopStact(){
    horse[TopStact].x=0;
    horse[TopStact].y=0;
    horse[TopStact].direction=-1;
    TopStact--;
}

//���λ��
void MarkChess(int xx,int yy){
    chess[xx][yy]=TopStact+1;
}

//��ӡÿһ��λ��
void PrintSteps(){
    printf("(%d,%d)",horse[TopStact].x,horse[TopStact].y);
    t++;
    if(t==ROW){
        printf("\n");
        t=0;
    }
}

void TheHorseStepBoard(){
    int xnow,ynow;
    while(1){
    	
        if(TopStact>=MAX_STEPS-1){
            break;
        }

        xnow=horse[TopStact].x;
        ynow=horse[TopStact].y;

        //�Է����������
        int nextstep[ROW]={};
        for(int i=0;i<ROW;i++){
            int xnext=xnow+dir[i][0];//������һ��λ������ 
            int ynext=ynow+dir[i][1];

            if((xnext>0 && xnext<=ROW)&&(ynext>0 &&ynext<=COL)&&(chess[xnext][ynext]==0)){//ȷ����һ������ 
                for(int j=0;j<ROW;j++){
                    int xnextnext=xnext+dir[j][0];//��������һ��λ������ 
                    int ynextnext=ynext+dir[j][1];

                    if((xnextnext>0 && xnextnext<=ROW)&&(ynextnext>0 &&ynextnext<=COL)&&(chess[xnextnext][ynextnext]==0)){//ȷ������һ������ 
                        nextstep[i]++; 
                    }
                }//for(j)
            }
        }//for(i)

        int realnext[ROW]={0};
        int k=0,tt=ROW+1;
        //�ҳ���С��nextstep�����丳��realnext������ԭ������󻯣��ҳ�realnext
        for(int i=0;i<ROW;i++){
            tt=ROW+1;
            for(int j=0;j<8;j++){
                if(nextstep[j]<tt){
                    realnext[i]=j;
                    tt=nextstep[j];
                    k=j;
                }
            }
            nextstep[k]=ROW+1;
        }

        int dirnow=0;
        for(dirnow=horse[TopStact].direction+1;dirnow<ROW;dirnow++){
            int xx=xnow+dir[realnext[dirnow]][0];
            int yy=ynow+dir[realnext[dirnow]][1];

            horse[TopStact].direction+=1;

            if((xx<=ROW &&xx>0) &&(yy<=COL && yy>0)&&(chess[xx][yy]==0)){
                PushStact(xx,yy);
                MarkChess(xx,yy);
                break;//������ѹ��ջ�в���� 
            }
        }
		
		//����һ���߲��ˣ����ջ���� 
        if(horse[TopStact].direction>=7){
            printf("\n out:(%d,%d)\n",horse[TopStact].x,horse[TopStact].y);
            chess[horse[TopStact].x][horse[TopStact].y]=0;
            OutStact++;
            PopStact();
        }
        PrintSteps();
    }//when
}

int main()
{
    int xx,yy;

    printf("Please Input: x y\n");//��ʼλ�� 
    scanf("%d %d",&xx,&yy);

    init();
    PushStact(xx,yy);//����ѹ��ջ�� 
    MarkChess(xx,yy);//����� 

    printf("\n route address:\n");
    printf("(%d,%d)",xx,yy);

    TheHorseStepBoard();

    return 0;
}
