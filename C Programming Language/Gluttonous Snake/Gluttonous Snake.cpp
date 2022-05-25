#include<stdio.h>
#include<Windows.h>//要用到用户界面函数，Kernel函数，还有系统休眠，清屏
#include<conio.h>
#include<time.h>
#include<string.h>
#define MAP_HEIGHT 80  //地图的高度
#define MAP_WIDHT 40 //地图的宽度
#define UP 'w'          //定义控制蛇走向的方向键
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
typedef struct//定义食物和单个蛇身的结构体
{
	int x;
	int y;//用坐标来表示
}Food,Snakenode,Barrier;
typedef struct //定义蛇的结构体
{
	Snakenode snakeNode[1000];//限制蛇的最长长度
	int length; //蛇目前的长度
	int speed; //蛇目前的速度
}Snake;
typedef struct
{
	char name[50];		//记录姓名
	int grade;			//成绩
	int m;//定义用户个数
}Data;
Snake snake;   //定义蛇的结构体变量
Food food;     //定义食物的结构体变量
Barrier barrier[100];//定义障碍物的结构体变量
Data data[100];
int n;//定义障碍物
int Cfood=0;//定义随机食物的种类
int Efood = 0;//定义
int r = 0;
int flag = 0;
char now_Dir = RIGHT;  //定义当前蛇头的方向
char direction = RIGHT;  //期待蛇头的方向
void GotoXY(int x, int y); //光标定位函数
void Hide();			   //隐藏光标函数
int Menu();			   //主菜单函数
void Help();			   //帮助信息函数
void About();			   //关于信息函数
void InitMap();			   //地图初始化
void PrintFood();		   //生成食物
int MoveSnake();		   //蛇移动函数
int Correct();			   //自撞或撞墙函数
void SpeedControl();	   //速度控制函数
int IsCorrect();		   //判断是否撞墙或自撞，返回值为0，否则为1
void Read();			   //读取记录
void List();			   //排行榜
void Name();			   //记录用户名
void Rank();			   //记录成绩
void Write();			   //将记录保存到记事本
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
	printf("欢迎来到贪吃蛇小游戏");
	GotoXY(48, 14);
	printf("1.开始游戏");
	GotoXY(48, 16);
	printf("2.帮助");
	GotoXY(48, 18);
	printf("3.关于");
	GotoXY(48, 20);
	printf("4.排行榜");
	GotoXY(48, 22);
	printf("其他任意键退出游戏");
	Hide();
	char ch;
	int result = 0;
	ch = _getch();//getch()函数所需头文件：conio.h
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
	system("cls");  //调用系统命令cls完成清屏操作
	return result;
}
void GotoXY(int x,int y)
{
	HANDLE hout;//句柄
	COORD cor; //Window.h中定义的坐标结构体，用来表示第一个字符在控制台屏幕上的坐标
	hout = GetStdHandle(STD_OUTPUT_HANDLE);//GetStdHandle（）是一个Windows API函数。它用于从一个特定的标准设备（标准输入、标准输出或标准错误）中取得一个句柄（用来标识不同设备的数值）
	cor.X = x;
	cor.Y = y;
	SetConsoleCursorPosition(hout, cor);//SetConsoleCursorPosition是API中定位光标位置的函数。
}
void Hide()
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);//GetStdHandle返回一个指向标准输入，输出或错误处理的句柄. STD_OUTPUT_HANDLE : 通常为标准输出的屏幕。
	CONSOLE_CURSOR_INFO cor_info = { 1,0 };//定义光标的参数，
	SetConsoleCursorInfo(hout, &cor_info);
}
void About()
{
	GotoXY(45, 12);
	printf("杭州电子科技大学--程序设计综合实践");
	GotoXY(48, 14);
	printf("贪吃蛇游戏");
	GotoXY(48, 16);
	printf("按任意键返回上级菜单");
	Hide();
	char ch = _getch();
	system("cls");
}
void Help()
{
	GotoXY(48, 12);
	printf("w上");
	GotoXY(48,14);
	printf("s下");
	GotoXY(48, 16);
	printf("a左");
	GotoXY(48, 18);
	printf("d右");
	GotoXY(48, 20);
	printf("当蛇撞墙和障碍物时游戏结束");
	GotoXY(48, 22);
	printf("按任意键返回上级菜单");
	Hide();
	char ch = _getch();
	system("cls");
}
void InitMap()
{
	
	Hide();
	snake.snakeNode[0].x = MAP_HEIGHT / 2 - 1;//使蛇头的位置出现在地图中间
	snake.snakeNode[0].y = MAP_WIDHT / 2 - 1;
	GotoXY(snake.snakeNode[0].x, snake.snakeNode[0].y);//将光标移至蛇头位置
	printf("@");//打印蛇头
	snake.length = 3;	//设置蛇的初始长度为3
	snake.speed = 250;	//设置蛇的初始移动速度250
	now_Dir = LEFT;//当前蛇头的方向
	for (int i = 1; i < snake.length; i++) //打印蛇身
	{
		snake.snakeNode[i].y = snake.snakeNode[i - 1].y; //蛇身的纵坐标位置和蛇头的位置相同
		snake.snakeNode[i].x = snake.snakeNode[i - 1].x+1; //设置蛇身的横坐标位置，蛇身在蛇头的左边，所以横坐标依次减1
		GotoXY(snake.snakeNode[i].x, snake.snakeNode[i].y);//光标移动到蛇身的位置
		printf("o");//打印蛇身

	}
	for (int i = 0; i < MAP_WIDHT; i++)//生成地图上下边界
	{
		GotoXY(0, i);
		printf("|");
		GotoXY(MAP_HEIGHT, i);
		printf("|");
	}
	for (int i = 0; i < MAP_HEIGHT; i++)//生成地图左右边界
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
	printf("当前得分：%d", snake.length - 3);
	GotoXY(MAP_HEIGHT + 1, 7);
	printf("$ ------ 1分");
	GotoXY(MAP_HEIGHT + 1, 9);
	printf("* ------ 2分");
	GotoXY(MAP_HEIGHT + 1, 11);
	printf("+ ------ 3分");
	GotoXY(MAP_HEIGHT + 1, 13);
	printf("！ ----- 4分");
	GotoXY(MAP_HEIGHT + 1, 15);
	printf("碰到自己身体减一分");
	GotoXY(MAP_HEIGHT + 1, 17);
	printf("当蛇撞墙和障碍物时游戏结束");
	PrintFood();
}
int IsCorrect()
{
	if (snake.snakeNode[0].x == 0 || snake.snakeNode[0].y == 0 || snake.snakeNode[0].x == MAP_HEIGHT||
		snake.snakeNode[0].y == MAP_WIDHT)//判断蛇头是否撞墙
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
	for (int i = 1; i < snake.length; i++)//判断蛇头是否与自身重叠
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
	temp = snake.snakeNode[snake.length - 1];//记录蛇尾
	for (int i = snake.length - 1; i >= 1; i--)
	{
		snake.snakeNode[i] = snake.snakeNode[i - 1];
	}
		GotoXY(snake.snakeNode[1].x, snake.snakeNode[1].y);
		printf("o");
		if (_kbhit())//检查当前是否有键盘输入，若有，则返回一个非0的值，否则返回0
		{
			direction = _getch();
			switch (direction)
			{
			case UP:
				if (now_Dir != DOWN)//若输入的方向与当前方向相反，则不会起作用
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
			flag+=Efood;  //flag=1表示吃到食物，flag=0表示没有吃到食物
			snake.length++;
			snake.snakeNode[snake.length - 1] = temp; //吃到食物，蛇身加1
			r = 1;//用来判断是否重复加分
		}
		if (!flag)
		{
			GotoXY(temp.x, temp.y);
			printf(" ");
		}
		else
		{
			if (flag != 0)//给蛇加上对应分数的的长度
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
			printf("当前得分：%d", snake.length - 3);
			GotoXY(MAP_HEIGHT + 1, 7);
			printf("$ ------ 1分");
			GotoXY(MAP_HEIGHT + 1, 9);
			printf("* ------ 2分");
			GotoXY(MAP_HEIGHT + 1, 11);
			printf("+ ------ 3分");
			GotoXY(MAP_HEIGHT + 1, 13);
			printf("！ ----- 4分");
			GotoXY(MAP_HEIGHT + 1, 15);
			printf("碰到自己身体减一分");
			GotoXY(MAP_HEIGHT + 1, 17);
			printf("当蛇撞墙和障碍物时游戏结束");
		}
		r = 0;
		a = IsCorrect();
		if (!a)
		{
			system("cls");
			data[data[0].m-1].grade = snake.length - 3;
			GotoXY(45, 14);
			printf("最终得分：%d", snake.length - 3);
			GotoXY(45, 16);
			printf("你输了！");
			GotoXY(45, 18);
			printf("按任意键查看排名");
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
			printf("当前得分：%d", snake.length - 3);
		}
		SpeedControl();
		Sleep(snake.speed);//将进程挂起一段时间，用于控制蛇的移动速度
		
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
			if (snake.snakeNode[k].x == food.x && snake.snakeNode[k].y == food.y)//判断食物的位置是否和蛇的位置重合，若重合，重新随机一个位置
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
	printf("用户名");
	GotoXY(58, 12);
	printf("成绩");
	for (i = 0; i <data[0].m; i++)
	{
		GotoXY(48, 12+(i+1)*2);
		printf("%s",data[i].name);
		GotoXY(58, 12+ (i + 1)*2);
		printf("%d",data[i].grade);
	}
	GotoXY(48, 12 + (i + 1) * 2);
	printf("按任意键返回菜单");
	Hide();
	char ch = _getch();
	system("cls");
}
void Name()
{
	GotoXY(48, 12);
	printf("请输入用户名：");
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
