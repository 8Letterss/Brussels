#include<bits/stdc++.h>
using namespace std;

#define MAX 3
#define PRICE 2 

typedef struct{
	char flag;
	int id;
	int time;
}CarData;//定义车辆信息  
typedef struct{
	CarData data[MAX];
	int top;
}StopCar;//顺序栈模拟停车场 
typedef struct WaitCar{
	CarData data; 
	struct WaitCar *next;
}WaitCar;//链队模拟便道 
typedef struct{
	WaitCar *front;
	WaitCar *rear;
}WaitCarLink;

void Come_Car();//车辆到达 
void Leave_Car();//车辆离开 
void EnterStop();//车辆进入停车场 
void EnterWait();//车辆进入便道 
int Instop();//判断车辆是否存在 
void SmallWelcome();//菜单 
void traverse();//输出停车场，便道停车情况 

StopCar sc,tc;//停车栈，让路栈 
WaitCarLink wcl;//便道 
char ch=' ';//车辆信息 
int id,cartime,j=0,lasttime=0;

int main(){
	sc.top=-1;
	tc.top=-1;
	wcl.rear=wcl.front=(WaitCar*)malloc(sizeof(WaitCar));//停车场、让路栈、便道初始化
	wcl.front->next=wcl.rear; 
	SmallWelcome();
	while(ch!='E'){
		fflush(stdin);//清除缓存区回车
		printf("请分别输入车辆信息（A表示到底，D表示离开），车牌号，达到离开时间：\n"); 
		if(scanf("%c %d %d",&ch,&id,&cartime)!=3){
			printf("输入不合法\n");
			continue;
		}
		if(ch=='A'){
			Come_Car();//车辆到达 
			traverse();
		}
		else if(ch=='D'){
			Leave_Car();//车辆离开 
			traverse();
		}
		else if(ch=='E'){
			printf("\n信息录入完毕，程序结束\n");
			break;
		}
		else{
			printf("\n输入不合法，请重新输入\n");
			continue;
		}
	}
	
	return 0;
}

void Come_Car(){
	if(Instop()){
		printf("\n车辆已存在\n");
	}
	else{
		if(sc.top>=MAX-1){//车辆进入停车场 
			printf("\n停车场已满，请在便道上等待\n");
			EnterWait();
		}
		else{//车辆进入便道 
			EnterStop();
		}
	}
}

void EnterStop(){//车辆进入停车场 
	if(lasttime>cartime){
		printf("输入时间错误\n");
		return;
	} 
	sc.data[++sc.top].flag=ch;
	sc.data[sc.top].id=id;
	sc.data[sc.top].time=cartime; 
	printf("\n车牌号为%d的车辆已停入停车场第%d位\n",id,sc.top+1);
	lasttime=cartime;
}

void EnterWait(){//车辆进入便道 
	if(lasttime>cartime){
		printf("输入时间错误\n");
		return;
	} 
	WaitCar* wc;
	wc=(WaitCar*)malloc(sizeof(WaitCar));
	wc->data.flag=ch;
	wc->data.id=id;
	wc->data.time=cartime;
	
	wc->next=wcl.front;
	wcl.rear->next=wc;
	wcl.rear=wc;
	printf("\n车牌号为%d的车辆已停入停车场第%d位\n",id,++j);
	lasttime=cartime;
}

void Leave_Car(){
	int i=sc.top;
	if(lasttime>cartime){
		printf("输入时间错误\n");
		return;
	} 

	for(i;i>0;i--){
		if(sc.data[i].id==id){//找到目标车辆 
			break;
		}
		else{//将目标车辆之前的车辆存入让路栈 
			tc.data[++tc.top].flag=sc.data[sc.top].flag;
			tc.data[tc.top].id=sc.data[sc.top].id;
			tc.data[tc.top].time=sc.data[sc.top].time;
			sc.top--;
		}
	} 
	if(sc.data[i].id==id){
		if((cartime-sc.data[i].time)<0){
			printf("\n输入时间错误\n");
			while(tc.top>=0){//将让路栈的车辆存入停车场 
				sc.data[++sc.top].flag=tc.data[tc.top].flag;
				sc.data[sc.top].id=tc.data[tc.top].id;
				sc.data[sc.top].time=tc.data[tc.top].time;
				tc.top--;
				return;
			}
		}
		printf("\n车牌号为%d的车辆离开停车场，共停了%d小时,每小时%d元，应支付%d元\n",sc.data[i].id,cartime-sc.data[i].time,PRICE,(cartime-sc.data[i].time)*PRICE);
		sc.top--;
		lasttime=cartime;
	
		while(tc.top>=0){//将让路栈的车辆存入停车场 
			sc.data[++sc.top].flag=tc.data[tc.top].flag;
			sc.data[sc.top].id=tc.data[tc.top].id;
			sc.data[sc.top].time=tc.data[tc.top].time;
			tc.top--;
		}
	
		//将便道上第一辆车停入停车场 
		if(wcl.front->next!=wcl.front){ 
			sc.data[++sc.top].flag=wcl.front->next->data.flag;
			sc.data[sc.top].id=wcl.front->next->data.id;
			sc.data[sc.top].time=cartime;
			wcl.front->next=wcl.front->next->next;
			j--; 
			printf("\n车牌号为%d的车辆从便道进入停车场第%d位\n",sc.data[sc.top].id,sc.top+1);
		}
		else{
			return;
		}
	}
	else{
		printf("车辆不在停车场\n");
		while(tc.top>=0){//将让路栈的车辆存入停车场 
			sc.data[++sc.top].flag=tc.data[tc.top].flag;
			sc.data[sc.top].id=tc.data[tc.top].id;
			sc.data[sc.top].time=tc.data[tc.top].time;
			tc.top--;
		}
	}
}

int Instop(){//判断车辆是否存在
	int i=sc.top,flag=1;
	for(i;i>=0;i--){
		if(sc.data[i].id==id){
			flag=0;
			break;
		}
	}
	
	int k=j;
	WaitCar* wc=wcl.front->next;
	for(k;k>0;k--){
		if(wc->data.id==id){
			flag=0;
			break;
		}
		wc=wc->next;
	}
	
	if(flag==0) return 1;
	else return 0;
}

void SmallWelcome(){//菜单 
	printf ("\t*******************目前停车场状况***********************\n");
    printf ("\t停车场共有%d个车位,当前停车场共有%d辆车,等候区共有%d辆车\n",MAX, sc.top+1,j);
    printf ("\t********************************************************\n");
    printf ("\t---------Welcome to Ep's Car Parking next time----------\n");
    printf ("\t*                                                      *\n");
    printf ("\t*                   A.汽车到达                         *\n");
    printf ("\t*                   D.汽车离开                         *\n");
    printf ("\t*                   E.退出管理系统                     *\n");
    printf ("\t*请注意：从停车场内驶离的汽车按照%d元/小时计费          *\n",PRICE);
    printf ("\t*望周知：从便道上驶离的汽车不收取费用                  *\n");
    printf ("\t*                                                      *\n");
    printf ("\t*------------------------------------------------------*\n");
}

void traverse(){//输出停车场，便道停车情况 
	printf ("\t*******************目前停车场状况***********************\n");
	int i=sc.top,flag=1;
	printf("\t停车场上共%d停车位，已停了%d辆,  车牌号    停入时间\n",MAX,sc.top+1); 
	for(i;i>=0;i--){
		printf("\t                                 %d          %d\n",sc.data[i].id,sc.data[i].time);
	}
	printf("\n");
	
	if(wcl.front!=wcl.rear)  printf("\t便道上已停了%d辆,分别是：",j);
	WaitCar* wc=wcl.front->next;
	int k=j;
	for(k;k>0;k--){
		int t=wc->data.id;
		printf("\t%d\t",t);
		wc=wc->next;
	}
	printf("\n");
	printf ("\t*------------------------------------------------------*\n");
} 
