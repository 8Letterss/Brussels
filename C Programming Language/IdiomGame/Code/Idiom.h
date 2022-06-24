#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<mmsystem.h>
#include<graphics.h>

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define SUCCESS 1
#define FAIL 0
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

typedef struct idioms {      //成语数据+释义
    char word[9];
    char str[200];
}idiom;

typedef struct maxidioms {   //成语接龙
    char word[10];
}max;

typedef struct users {       //用户登录信息
    char name[6];
    char password[21];
}user;

typedef struct records {        //记录成绩
    char name[6];
    int fre;
    int score1;
    int score2;
    int nums;
    char date[28];
}record;

//数据处理
int GetData(idiom* ptr);//读取成语数据
int SeekWord(idiom* input, idiom* wptr, int num);//查找成语
int SuperGet(max* maxptr);//成语接龙数据读取
int SuperSearch(max* maxptr, char str[]);//成语接龙检索
int MatchingIdioms(max* maxptr, char str[]);//匹配成语接龙
int MyRand(int num);

//登录系统
void OutMenu(user* member);//登录菜单
int SingIn(user* member);//登录
int IsRegister(user* member);//注册

//游戏系统
int StartGame(record* player, idiom* wptr, int num, max* mptr, int num2, record* rptr);//游戏开始控制
int OpenDictionary(idiom* wptr, int num);//成语词典
int PlayTest(idiom* wptr, int num);//成语测试
int ManMachineWar(max* mptr, int num);//人机大战
int PlayTest2(idiom* wptr, int num);//成语测试2

//排行榜
int RankingList(record* player);//读取排行榜数据
void InList(record* player, int num);//显示排行榜
void WriteList(record* player, record* rptr, int num);//向排行榜写数据

//界面
void begin_menu();//开始界面
void RightAns();//正确界面
void Gameover(wchar_t rightAns[21][9], int rightCnt, wchar_t wrongAns[200][9], int wrongCnt);//结束界面
void CharToWCharT(char* putQuestion, wchar_t* wp);//字符转换
void number_write(int number_size, int x, int y, int number, COLORREF color);//屏幕上显示数字
void plays_hard();//游戏界面
int getQuestion_hard(idiom* wptr, int num, char question[9], int rNum[])


// 实现文本框控件
;
class EasyTextBox{
private:
	int left = 0, top = 0, right = 0, bottom = 0;	// 控件坐标
	wchar_t* text = NULL;							// 控件内容
	size_t maxlen = 0;								// 文本框最大内容长度

public:
	void Create(int x1, int y1, int x2, int y2, int max){
		maxlen = max;
		text = new wchar_t[maxlen];
		text[0] = 0;
		left = x1, top = y1, right = x2, bottom = y2;

		// 绘制用户界面
		Show();
	}

	~EasyTextBox(){
		if (text != NULL)
			delete[] text;
	}

	wchar_t Text(){
		return text[0];
	}

	bool Check(int x, int y){
		return (left <= x && x <= right && top <= y && y <= bottom);
	}

	// 绘制界面
	void Show(){
		// 备份环境值
		int oldlinecolor = getlinecolor();
		int oldbkcolor = getbkcolor();
		int oldfillcolor = getfillcolor();

		setlinecolor(LIGHTGRAY);		// 设置画线颜色
		setbkcolor(0xeeeeee);			// 设置背景颜色
		setfillcolor(0xeeeeee);			// 设置填充颜色
		fillrectangle(left, top, right, bottom);
		outtextxy(left + 10, top + 5, text);

		// 恢复环境值
		setlinecolor(oldlinecolor);
		setbkcolor(oldbkcolor);
		setfillcolor(oldfillcolor);
	}

	void OnMessage(clock_t start, clock_t pauTime){
		// 备份环境值
		int oldlinecolor = getlinecolor();
		int oldbkcolor = getbkcolor();
		int oldfillcolor = getfillcolor();

		setlinecolor(BLACK);			// 设置画线颜色
		setbkcolor(WHITE);				// 设置背景颜色
		setfillcolor(WHITE);			// 设置填充颜色

		fillrectangle(left, top, right, bottom);
		outtextxy(left + 10, top + 5, text);

		int width = textwidth(text);	// 字符串总宽度
		int counter = 0;				// 光标闪烁计数器
		bool binput = true;				// 是否输入中

		ExMessage msg;
		while (binput)
		{
			clock_t end = clock();

			int stime = (int)((end - start - pauTime) / CLK_TCK);
			setbkcolor(WHITE);
			number_write(35, 1060, 275, stime, BLACK);
			settextstyle(90, 0, _T("楷体"));
			settextcolor(YELLOW);
			while (binput && peekmessage(&msg, EM_MOUSE | EM_CHAR, false))	// 获取消息，但不从消息队列拿出
			{
				if (msg.message == WM_LBUTTONDOWN)
				{

					// 如果鼠标点击文本框外面，结束文本输入
					if (msg.x < left || msg.x > right || msg.y < top || msg.y > bottom)
					{
						binput = false;
						break;
					}
				}
				else if (msg.message == WM_CHAR)
				{
					size_t len = wcslen(text);
					switch (msg.ch)
					{
					case '\b':				// 用户按退格键，删掉一个字符
						if (len > 0)
						{
							text[len - 1] = 0;
							width = textwidth(text);
							counter = 0;
							clearrectangle(left + 10 + width, top + 1, right - 1, bottom - 1);
						}
						break;
					case '\r':				// 用户按回车键，结束文本输入
					case '\n':
						binput = false;
						break;
					default:				// 用户按其它键，接受文本输入
						if (len < maxlen - 1)
						{
							text[len++] = msg.ch;
							text[len] = 0;

							clearrectangle(left + 10 + width + 1, top + 3, left + 10 + width + 1, bottom - 3);	// 清除画的光标
							width = textwidth(text);				// 重新计算文本框宽度
							counter = 0;
							outtextxy(left + 1, top + 1, text);		// 输出新的字符串
						}
					}
				}
				peekmessage(NULL, EM_MOUSE | EM_CHAR);				// 从消息队列抛弃刚刚处理过的一个消息
			}

			// 绘制光标（光标闪烁周期为 20ms * 32）
			counter = (counter + 1) % 32;
			if (counter < 16)
				line(left + 10 + width + 1, top + 3, left + 10 + width + 1, bottom - 3);				// 画光标
			else
				clearrectangle(left + 10 + width + 1, top + 3, left + 10 + width + 1, bottom - 3);		// 擦光标

			// 延时 20ms
			Sleep(20);
		}

		clearrectangle(left + 10 + width + 1, top + 3, left + 10 + width + 1, bottom - 3);	// 擦光标

		// 恢复环境值
		setlinecolor(oldlinecolor);
		setbkcolor(oldbkcolor);
		setfillcolor(oldfillcolor);

		Show();
	}
};