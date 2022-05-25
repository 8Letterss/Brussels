#include<stdio.h>
#include<Windows.h>//Ҫ�õ��û����溯����Kernel����������ϵͳ���ߣ�����
#include<conio.h>
#include<time.h>
#include<string.h>
#define MAP_HEIGHT 80  //��ͼ�ĸ߶�
#define MAP_WIDHT 40 //��ͼ�Ŀ��
#define UP 'w'          //�������������ķ����
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
typedef struct//����ʳ��͵�������Ľṹ��
{
	int x;
	int y;//����������ʾ
}Food,Snakenode,Barrier;
typedef struct //�����ߵĽṹ��
{
	Snakenode snakeNode[1000];//�����ߵ������
	int length; //��Ŀǰ�ĳ���
	int speed; //��Ŀǰ���ٶ�
}Snake;
typedef struct
{
	char name[50];		//��¼����
	int grade;			//�ɼ�
	int m;//�����û�����
}Data;
Snake snake;   //�����ߵĽṹ�����
Food food;     //����ʳ��Ľṹ�����
Barrier barrier[100];//�����ϰ���Ľṹ�����
Data data[100];
int n;//�����ϰ���
int Cfood=0;//�������ʳ�������
int Efood = 0;//����
int r = 0;
int flag = 0;
char now_Dir = RIGHT;  //���嵱ǰ��ͷ�ķ���
char direction = RIGHT;  //�ڴ���ͷ�ķ���
void GotoXY(int x, int y); //��궨λ����
void Hide();			   //���ع�꺯��
int Menu();			   //���˵�����
void Help();			   //������Ϣ����
void About();			   //������Ϣ����
void InitMap();			   //��ͼ��ʼ��
void PrintFood();		   //����ʳ��
int MoveSnake();		   //���ƶ�����
int Correct();			   //��ײ��ײǽ����
void SpeedControl();	   //�ٶȿ��ƺ���
int IsCorrect();		   //�ж��Ƿ�ײǽ����ײ������ֵΪ0������Ϊ1
void Read();			   //��ȡ��¼
void List();			   //���а�
void Name();			   //��¼�û���
void Rank();			   //��¼�ɼ�
void Write();			   //����¼���浽���±�
int main()
{
	srand((unsigned int)time(0));
	int end = 1, result;
	Read();
	while (end)
	{
		result = Menu();
		switch (result)
		{
		case 1:
			Name();
			InitMap();
			while (MoveSnake());
			Rank();
			break;
		case 2:
			Help();
			break;
		case 3:
			About();
			break;
		case 4:
			List();
			break;
		case 0:
			end = 0;
			Write();
			break;
		}
	}
}
int Menu()
{
	GotoXY(45,12);
	printf("��ӭ����̰����С��Ϸ");
	GotoXY(48, 14);
	printf("1.��ʼ��Ϸ");
	GotoXY(48, 16);
	printf("2.����");
	GotoXY(48, 18);
	printf("3.����");
	GotoXY(48, 20);
	printf("4.���а�");
	GotoXY(48, 22);
	printf("����������˳���Ϸ");
	Hide();
	char ch;
	int result = 0;
	ch = _getch();//getch()��������ͷ�ļ���conio.h
	switch (ch)
	{
	case'1':
		result = 1;
		break;
	case'2':
		result = 2;
		break;
	case'3':
		result = 3;
		break;
	case'4':
		result = 4;
		break;
	}
	system("cls");  //����ϵͳ����cls�����������
	return result;
}
void GotoXY(int x,int y)
{
	HANDLE hout;//���
	COORD cor; //Window.h�ж��������ṹ�壬������ʾ��һ���ַ��ڿ���̨��Ļ�ϵ�����
	hout = GetStdHandle(STD_OUTPUT_HANDLE);//GetStdHandle������һ��Windows API�����������ڴ�һ���ض��ı�׼�豸����׼���롢��׼������׼������ȡ��һ�������������ʶ��ͬ�豸����ֵ��
	cor.X = x;
	cor.Y = y;
	SetConsoleCursorPosition(hout, cor);//SetConsoleCursorPosition��API�ж�λ���λ�õĺ�����
}
void Hide()
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);//GetStdHandle����һ��ָ���׼���룬����������ľ��. STD_OUTPUT_HANDLE : ͨ��Ϊ��׼�������Ļ��
	CONSOLE_CURSOR_INFO cor_info = { 1,0 };//������Ĳ�����
	SetConsoleCursorInfo(hout, &cor_info);
}
void About()
{
	GotoXY(45, 12);
	printf("���ݵ��ӿƼ���ѧ--��������ۺ�ʵ��");
	GotoXY(48, 14);
	printf("̰������Ϸ");
	GotoXY(48, 16);
	printf("������������ϼ��˵�");
	Hide();
	char ch = _getch();
	system("cls");
}
void Help()
{
	GotoXY(48, 12);
	printf("w��");
	GotoXY(48,14);
	printf("s��");
	GotoXY(48, 16);
	printf("a��");
	GotoXY(48, 18);
	printf("d��");
	GotoXY(48, 20);
	printf("����ײǽ���ϰ���ʱ��Ϸ����");
	GotoXY(48, 22);
	printf("������������ϼ��˵�");
	Hide();
	char ch = _getch();
	system("cls");
}
void InitMap()
{
	
	Hide();
	snake.snakeNode[0].x = MAP_HEIGHT / 2 - 1;//ʹ��ͷ��λ�ó����ڵ�ͼ�м�
	snake.snakeNode[0].y = MAP_WIDHT / 2 - 1;
	GotoXY(snake.snakeNode[0].x, snake.snakeNode[0].y);//�����������ͷλ��
	printf("@");//��ӡ��ͷ
	snake.length = 3;	//�����ߵĳ�ʼ����Ϊ3
	snake.speed = 250;	//�����ߵĳ�ʼ�ƶ��ٶ�250
	now_Dir = LEFT;//��ǰ��ͷ�ķ���
	for (int i = 1; i < snake.length; i++) //��ӡ����
	{
		snake.snakeNode[i].y = snake.snakeNode[i - 1].y; //�����������λ�ú���ͷ��λ����ͬ
		snake.snakeNode[i].x = snake.snakeNode[i - 1].x+1; //��������ĺ�����λ�ã���������ͷ����ߣ����Ժ��������μ�1
		GotoXY(snake.snakeNode[i].x, snake.snakeNode[i].y);//����ƶ��������λ��
		printf("o");//��ӡ����

	}
	for (int i = 0; i < MAP_WIDHT; i++)//���ɵ�ͼ���±߽�
	{
		GotoXY(0, i);
		printf("|");
		GotoXY(MAP_HEIGHT, i);
		printf("|");
	}
	for (int i = 0; i < MAP_HEIGHT; i++)//���ɵ�ͼ���ұ߽�
	{
		GotoXY(i, 0);
		printf("-");
		GotoXY(i,MAP_WIDHT);
		printf("-");
	}
	int x, y;
	x = rand() % (MAP_HEIGHT-5) + 1;
	for (y= 1; y < 6; y++)
	{
		GotoXY(x, y);
		barrier[n].x = x;
		barrier[n].y = y;
		printf("|");
		n++;
	}
	x++;
	for (int i = 0; i < 5; i++)
	{
		GotoXY(x, y);
		barrier[n].x = x;
		barrier[n].y = y;
		printf("-");
		x++;
		n++;
	}
	GotoXY(MAP_HEIGHT + 1, 5);
	printf("��ǰ�÷֣�%d", snake.length - 3);
	GotoXY(MAP_HEIGHT + 1, 7);
	printf("$ ------ 1��");
	GotoXY(MAP_HEIGHT + 1, 9);
	printf("* ------ 2��");
	GotoXY(MAP_HEIGHT + 1, 11);
	printf("+ ------ 3��");
	GotoXY(MAP_HEIGHT + 1, 13);
	printf("�� ----- 4��");
	GotoXY(MAP_HEIGHT + 1, 15);
	printf("�����Լ������һ��");
	GotoXY(MAP_HEIGHT + 1, 17);
	printf("����ײǽ���ϰ���ʱ��Ϸ����");
	PrintFood();
}
int IsCorrect()
{
	if (snake.snakeNode[0].x == 0 || snake.snakeNode[0].y == 0 || snake.snakeNode[0].x == MAP_HEIGHT||
		snake.snakeNode[0].y == MAP_WIDHT)//�ж���ͷ�Ƿ�ײǽ
	{
		return 0;
	}
	for (int i = 0; i < n; i++)
	{
		if (snake.snakeNode[0].x == barrier[i].x && snake.snakeNode[0].y==barrier[i].y)
		{
			return 0;
		}
	}
	for (int i = 1; i < snake.length; i++)//�ж���ͷ�Ƿ��������ص�
	{
		if (snake.snakeNode[0].x == snake.snakeNode[i].x && snake.snakeNode[0].y == snake.snakeNode[i].y)
		{
			return 2;
		}
	}
	return 1;
}
int MoveSnake()
{
	int a = 0;
	Hide();
	Snakenode temp;
	temp = snake.snakeNode[snake.length - 1];//��¼��β
	for (int i = snake.length - 1; i >= 1; i--)
	{
		snake.snakeNode[i] = snake.snakeNode[i - 1];
	}
		GotoXY(snake.snakeNode[1].x, snake.snakeNode[1].y);
		printf("o");
		if (_kbhit())//��鵱ǰ�Ƿ��м������룬���У��򷵻�һ����0��ֵ�����򷵻�0
		{
			direction = _getch();
			switch (direction)
			{
			case UP:
				if (now_Dir != DOWN)//������ķ����뵱ǰ�����෴���򲻻�������
				{
					now_Dir = direction;
				}
				break;
			case DOWN:
				if (now_Dir != UP)
				{
					now_Dir = direction;
				}
				break;
			case LEFT:
				if (now_Dir != RIGHT)
				{
					now_Dir = direction;
				}
				break;
			case RIGHT:
				if (now_Dir != LEFT)
				{
					now_Dir = direction;
				}
				break;
			}
		}
		switch (now_Dir)
		{
		case UP:
			snake.snakeNode[0].y--; break;
		case DOWN:
			snake.snakeNode[0].y++; break;
		case LEFT:
			snake.snakeNode[0].x--; break;
		case RIGHT:
			snake.snakeNode[0].x++; break;
		}
		GotoXY(snake.snakeNode[0].x, snake.snakeNode[0].y);
		printf("@");
		if (snake.snakeNode[0].x == food.x && snake.snakeNode[0].y == food.y)
		{
			flag+=Efood;  //flag=1��ʾ�Ե�ʳ�flag=0��ʾû�гԵ�ʳ��
			snake.length++;
			snake.snakeNode[snake.length - 1] = temp; //�Ե�ʳ������1
			r = 1;//�����ж��Ƿ��ظ��ӷ�
		}
		if (!flag)
		{
			GotoXY(temp.x, temp.y);
			printf(" ");
		}
		else
		{
			if (flag != 0)//���߼��϶�Ӧ�����ĵĳ���
			{
				flag--;
				if (r == 0)
				{
					snake.length++;
					snake.snakeNode[snake.length - 1] = temp;
				}
			}
			if (!flag)
			{
				PrintFood();
			}
			GotoXY(MAP_HEIGHT+1, 5);
			printf("��ǰ�÷֣�%d", snake.length - 3);
			GotoXY(MAP_HEIGHT + 1, 7);
			printf("$ ------ 1��");
			GotoXY(MAP_HEIGHT + 1, 9);
			printf("* ------ 2��");
			GotoXY(MAP_HEIGHT + 1, 11);
			printf("+ ------ 3��");
			GotoXY(MAP_HEIGHT + 1, 13);
			printf("�� ----- 4��");
			GotoXY(MAP_HEIGHT + 1, 15);
			printf("�����Լ������һ��");
			GotoXY(MAP_HEIGHT + 1, 17);
			printf("����ײǽ���ϰ���ʱ��Ϸ����");
		}
		r = 0;
		a = IsCorrect();
		if (!a)
		{
			system("cls");
			data[data[0].m-1].grade = snake.length - 3;
			GotoXY(45, 14);
			printf("���յ÷֣�%d", snake.length - 3);
			GotoXY(45, 16);
			printf("�����ˣ�");
			GotoXY(45, 18);
			printf("��������鿴����");
			char c;
			c = _getch();
			system("cls");
			return 0;
		}
		if (a == 2)
		{
			GotoXY(snake.snakeNode[snake.length - 1].x, snake.snakeNode[snake.length - 1].y);
			printf(" ");
			snake.length--;
			GotoXY(MAP_HEIGHT + 1, 5);
			printf("��ǰ�÷֣�%d", snake.length - 3);
		}
		SpeedControl();
		Sleep(snake.speed);//�����̹���һ��ʱ�䣬���ڿ����ߵ��ƶ��ٶ�
		
	return 1;
}
void PrintFood()
{
	int lag = 1;
	while (lag)
	{
		lag = 0;
		food.x = rand() % (MAP_HEIGHT - 2)+1;
		food.y = rand() % (MAP_WIDHT - 2)+1;
		for (int k = 0; k < snake.length - 1; k++)
		{
			if (snake.snakeNode[k].x == food.x && snake.snakeNode[k].y == food.y)//�ж�ʳ���λ���Ƿ���ߵ�λ���غϣ����غϣ��������һ��λ��
			{
				lag = 1;
				break;
			}
		}
		if (food.x == 0 || food.y == 0 || food.x == MAP_HEIGHT || food.y == MAP_WIDHT)
		{
			lag = 1;
		}
	}
	GotoXY(food.x, food.y);
	Cfood = rand() % 4;
	Efood = Cfood+1;
	if (Cfood == 0)
	{
		printf("$");
	}
	if (Cfood == 1)
	{
		printf("*");
	}
	if (Cfood == 2)
	{
		printf("+");
	}
	if (Cfood == 3)
	{
		printf("!");
	}
}
void SpeedControl()
{
	if(snake.length>3&&snake.length<=6)
	{
		snake.speed=200;
	}
	if(snake.length>6&&snake.length<=9)
	{
		snake.speed=180;
	}
	if(snake.length>9&&snake.length<=12)
	{
		snake.speed=160;
	}
	if(snake.length>12&&snake.length<=15)
	{
		snake.speed=140;
	}
	if(snake.length>15&&snake.length<=18)
	{
		snake.speed=120;
	}
	if(snake.length>18&&snake.length<=21)
	{
		snake.speed=100;
	}
	if(snake.length>21)
	{
		snake.speed=80;
	}
}
void Read()
{
	FILE* p;
	char b[100];
	p = fopen("grade.txt", "rb");
	fscanf(p, "%d", &data[0].m);
	for(int i=0;i<data[0].m;i++)
	{
		fscanf(p, "%s", &data[i].name);
		fscanf(p, "%d", &data[i].grade);
		data[i].m = data[0].m;
	}
	fclose(p);
}
void List()
{
	int i;
	GotoXY(48, 12);
	printf("�û���");
	GotoXY(58, 12);
	printf("�ɼ�");
	for (i = 0; i <data[0].m; i++)
	{
		GotoXY(48, 12+(i+1)*2);
		printf("%s",data[i].name);
		GotoXY(58, 12+ (i + 1)*2);
		printf("%d",data[i].grade);
	}
	GotoXY(48, 12 + (i + 1) * 2);
	printf("����������ز˵�");
	Hide();
	char ch = _getch();
	system("cls");
}
void Name()
{
	GotoXY(48, 12);
	printf("�������û�����");
	GotoXY(48, 14);
	scanf("%s", &data[data[0].m].name);
	data[0].m++;
	char ch = _getch();
	system("cls");
}
void Rank()
{
	int z=0,g=0;
	char a[50];
	
	for (int i = 0; i < data[0].m; i++)
	{
		z = i;
		for (int j = i+1; j < data[0].m; j++)
		{
			if (data[j].grade > data[i].grade)
			{
				z = j;
			}
		}
		strcpy(a, data[i].name);
		strcpy(data[i].name, data[z].name);
		strcpy(data[z].name, a);
		g = data[i].grade;
		data[i].grade = data[z].grade;
		data[z].grade = g;
	
	}
	List();
}
void Write()
{
	FILE* p;
	p = fopen("grade.txt", "wb");
	fprintf(p, "%d\n", data[0].m);
	for (int i = 0; i < data[0].m; i++)
	{
		fprintf(p,"%s ", data[i].name);
		fprintf(p,"%d", data[i].grade);
		fprintf(p, "\n");
	}
	fclose(p);
}
