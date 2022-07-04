#include<bits/stdc++.h>
using namespace std;

#define MAX 3
#define PRICE 2 

typedef struct{
	char flag;
	int id;
	int time;
}CarData;//���峵����Ϣ  
typedef struct{
	CarData data[MAX];
	int top;
}StopCar;//˳��ջģ��ͣ���� 
typedef struct WaitCar{
	CarData data; 
	struct WaitCar *next;
}WaitCar;//����ģ���� 
typedef struct{
	WaitCar *front;
	WaitCar *rear;
}WaitCarLink;

void Come_Car();//�������� 
void Leave_Car();//�����뿪 
void EnterStop();//��������ͣ���� 
void EnterWait();//���������� 
int Instop();//�жϳ����Ƿ���� 
void SmallWelcome();//�˵� 
void traverse();//���ͣ���������ͣ����� 

StopCar sc,tc;//ͣ��ջ����·ջ 
WaitCarLink wcl;//��� 
char ch=' ';//������Ϣ 
int id,cartime,j=0,lasttime=0;

int main(){
	sc.top=-1;
	tc.top=-1;
	wcl.rear=wcl.front=(WaitCar*)malloc(sizeof(WaitCar));//ͣ��������·ջ�������ʼ��
	wcl.front->next=wcl.rear; 
	SmallWelcome();
	while(ch!='E'){
		fflush(stdin);//����������س�
		printf("��ֱ����복����Ϣ��A��ʾ���ף�D��ʾ�뿪�������ƺţ��ﵽ�뿪ʱ�䣺\n"); 
		if(scanf("%c %d %d",&ch,&id,&cartime)!=3){
			printf("���벻�Ϸ�\n");
			continue;
		}
		if(ch=='A'){
			Come_Car();//�������� 
			traverse();
		}
		else if(ch=='D'){
			Leave_Car();//�����뿪 
			traverse();
		}
		else if(ch=='E'){
			printf("\n��Ϣ¼����ϣ��������\n");
			break;
		}
		else{
			printf("\n���벻�Ϸ�������������\n");
			continue;
		}
	}
	
	return 0;
}

void Come_Car(){
	if(Instop()){
		printf("\n�����Ѵ���\n");
	}
	else{
		if(sc.top>=MAX-1){//��������ͣ���� 
			printf("\nͣ�������������ڱ���ϵȴ�\n");
			EnterWait();
		}
		else{//���������� 
			EnterStop();
		}
	}
}

void EnterStop(){//��������ͣ���� 
	if(lasttime>cartime){
		printf("����ʱ�����\n");
		return;
	} 
	sc.data[++sc.top].flag=ch;
	sc.data[sc.top].id=id;
	sc.data[sc.top].time=cartime; 
	printf("\n���ƺ�Ϊ%d�ĳ�����ͣ��ͣ������%dλ\n",id,sc.top+1);
	lasttime=cartime;
}

void EnterWait(){//���������� 
	if(lasttime>cartime){
		printf("����ʱ�����\n");
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
	printf("\n���ƺ�Ϊ%d�ĳ�����ͣ��ͣ������%dλ\n",id,++j);
	lasttime=cartime;
}

void Leave_Car(){
	int i=sc.top;
	if(lasttime>cartime){
		printf("����ʱ�����\n");
		return;
	} 

	for(i;i>0;i--){
		if(sc.data[i].id==id){//�ҵ�Ŀ�공�� 
			break;
		}
		else{//��Ŀ�공��֮ǰ�ĳ���������·ջ 
			tc.data[++tc.top].flag=sc.data[sc.top].flag;
			tc.data[tc.top].id=sc.data[sc.top].id;
			tc.data[tc.top].time=sc.data[sc.top].time;
			sc.top--;
		}
	} 
	if(sc.data[i].id==id){
		if((cartime-sc.data[i].time)<0){
			printf("\n����ʱ�����\n");
			while(tc.top>=0){//����·ջ�ĳ�������ͣ���� 
				sc.data[++sc.top].flag=tc.data[tc.top].flag;
				sc.data[sc.top].id=tc.data[tc.top].id;
				sc.data[sc.top].time=tc.data[tc.top].time;
				tc.top--;
				return;
			}
		}
		printf("\n���ƺ�Ϊ%d�ĳ����뿪ͣ��������ͣ��%dСʱ,ÿСʱ%dԪ��Ӧ֧��%dԪ\n",sc.data[i].id,cartime-sc.data[i].time,PRICE,(cartime-sc.data[i].time)*PRICE);
		sc.top--;
		lasttime=cartime;
	
		while(tc.top>=0){//����·ջ�ĳ�������ͣ���� 
			sc.data[++sc.top].flag=tc.data[tc.top].flag;
			sc.data[sc.top].id=tc.data[tc.top].id;
			sc.data[sc.top].time=tc.data[tc.top].time;
			tc.top--;
		}
	
		//������ϵ�һ����ͣ��ͣ���� 
		if(wcl.front->next!=wcl.front){ 
			sc.data[++sc.top].flag=wcl.front->next->data.flag;
			sc.data[sc.top].id=wcl.front->next->data.id;
			sc.data[sc.top].time=cartime;
			wcl.front->next=wcl.front->next->next;
			j--; 
			printf("\n���ƺ�Ϊ%d�ĳ����ӱ������ͣ������%dλ\n",sc.data[sc.top].id,sc.top+1);
		}
		else{
			return;
		}
	}
	else{
		printf("��������ͣ����\n");
		while(tc.top>=0){//����·ջ�ĳ�������ͣ���� 
			sc.data[++sc.top].flag=tc.data[tc.top].flag;
			sc.data[sc.top].id=tc.data[tc.top].id;
			sc.data[sc.top].time=tc.data[tc.top].time;
			tc.top--;
		}
	}
}

int Instop(){//�жϳ����Ƿ����
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

void SmallWelcome(){//�˵� 
	printf ("\t*******************Ŀǰͣ����״��***********************\n");
    printf ("\tͣ��������%d����λ,��ǰͣ��������%d����,�Ⱥ�������%d����\n",MAX, sc.top+1,j);
    printf ("\t********************************************************\n");
    printf ("\t---------Welcome to Ep's Car Parking next time----------\n");
    printf ("\t*                                                      *\n");
    printf ("\t*                   A.��������                         *\n");
    printf ("\t*                   D.�����뿪                         *\n");
    printf ("\t*                   E.�˳�����ϵͳ                     *\n");
    printf ("\t*��ע�⣺��ͣ������ʻ�����������%dԪ/Сʱ�Ʒ�          *\n",PRICE);
    printf ("\t*����֪���ӱ����ʻ�����������ȡ����                  *\n");
    printf ("\t*                                                      *\n");
    printf ("\t*------------------------------------------------------*\n");
}

void traverse(){//���ͣ���������ͣ����� 
	printf ("\t*******************Ŀǰͣ����״��***********************\n");
	int i=sc.top,flag=1;
	printf("\tͣ�����Ϲ�%dͣ��λ����ͣ��%d��,  ���ƺ�    ͣ��ʱ��\n",MAX,sc.top+1); 
	for(i;i>=0;i--){
		printf("\t                                 %d          %d\n",sc.data[i].id,sc.data[i].time);
	}
	printf("\n");
	
	if(wcl.front!=wcl.rear)  printf("\t�������ͣ��%d��,�ֱ��ǣ�",j);
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
