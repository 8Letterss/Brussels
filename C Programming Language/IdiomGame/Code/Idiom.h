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

typedef struct idioms {      //��������+����
    char word[9];
    char str[200];
}idiom;

typedef struct maxidioms {   //�������
    char word[10];
}max;

typedef struct users {       //�û���¼��Ϣ
    char name[6];
    char password[21];
}user;

typedef struct records {        //��¼�ɼ�
    char name[6];
    int fre;
    int score1;
    int score2;
    int nums;
    char date[28];
}record;

//���ݴ���
int GetData(idiom* ptr);//��ȡ��������
int SeekWord(idiom* input, idiom* wptr, int num);//���ҳ���
int SuperGet(max* maxptr);//����������ݶ�ȡ
int SuperSearch(max* maxptr, char str[]);//�����������
int MatchingIdioms(max* maxptr, char str[]);//ƥ��������
int MyRand(int num);

//��¼ϵͳ
void OutMenu(user* member);//��¼�˵�
int SingIn(user* member);//��¼
int IsRegister(user* member);//ע��

//��Ϸϵͳ
int StartGame(record* player, idiom* wptr, int num, max* mptr, int num2, record* rptr);//��Ϸ��ʼ����
int OpenDictionary(idiom* wptr, int num);//����ʵ�
int PlayTest(idiom* wptr, int num);//�������
int ManMachineWar(max* mptr, int num);//�˻���ս
int PlayTest2(idiom* wptr, int num);//�������2

//���а�
int RankingList(record* player);//��ȡ���а�����
void InList(record* player, int num);//��ʾ���а�
void WriteList(record* player, record* rptr, int num);//�����а�д����

//����
void begin_menu();//��ʼ����
void RightAns();//��ȷ����
void Gameover(wchar_t rightAns[21][9], int rightCnt, wchar_t wrongAns[200][9], int wrongCnt);//��������
void CharToWCharT(char* putQuestion, wchar_t* wp);//�ַ�ת��
void number_write(int number_size, int x, int y, int number, COLORREF color);//��Ļ����ʾ����
void plays_hard();//��Ϸ����
int getQuestion_hard(idiom* wptr, int num, char question[9], int rNum[])


// ʵ���ı���ؼ�
;
class EasyTextBox{
private:
	int left = 0, top = 0, right = 0, bottom = 0;	// �ؼ�����
	wchar_t* text = NULL;							// �ؼ�����
	size_t maxlen = 0;								// �ı���������ݳ���

public:
	void Create(int x1, int y1, int x2, int y2, int max){
		maxlen = max;
		text = new wchar_t[maxlen];
		text[0] = 0;
		left = x1, top = y1, right = x2, bottom = y2;

		// �����û�����
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

	// ���ƽ���
	void Show(){
		// ���ݻ���ֵ
		int oldlinecolor = getlinecolor();
		int oldbkcolor = getbkcolor();
		int oldfillcolor = getfillcolor();

		setlinecolor(LIGHTGRAY);		// ���û�����ɫ
		setbkcolor(0xeeeeee);			// ���ñ�����ɫ
		setfillcolor(0xeeeeee);			// ���������ɫ
		fillrectangle(left, top, right, bottom);
		outtextxy(left + 10, top + 5, text);

		// �ָ�����ֵ
		setlinecolor(oldlinecolor);
		setbkcolor(oldbkcolor);
		setfillcolor(oldfillcolor);
	}

	void OnMessage(clock_t start, clock_t pauTime){
		// ���ݻ���ֵ
		int oldlinecolor = getlinecolor();
		int oldbkcolor = getbkcolor();
		int oldfillcolor = getfillcolor();

		setlinecolor(BLACK);			// ���û�����ɫ
		setbkcolor(WHITE);				// ���ñ�����ɫ
		setfillcolor(WHITE);			// ���������ɫ

		fillrectangle(left, top, right, bottom);
		outtextxy(left + 10, top + 5, text);

		int width = textwidth(text);	// �ַ����ܿ��
		int counter = 0;				// �����˸������
		bool binput = true;				// �Ƿ�������

		ExMessage msg;
		while (binput)
		{
			clock_t end = clock();

			int stime = (int)((end - start - pauTime) / CLK_TCK);
			setbkcolor(WHITE);
			number_write(35, 1060, 275, stime, BLACK);
			settextstyle(90, 0, _T("����"));
			settextcolor(YELLOW);
			while (binput && peekmessage(&msg, EM_MOUSE | EM_CHAR, false))	// ��ȡ��Ϣ����������Ϣ�����ó�
			{
				if (msg.message == WM_LBUTTONDOWN)
				{

					// ���������ı������棬�����ı�����
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
					case '\b':				// �û����˸����ɾ��һ���ַ�
						if (len > 0)
						{
							text[len - 1] = 0;
							width = textwidth(text);
							counter = 0;
							clearrectangle(left + 10 + width, top + 1, right - 1, bottom - 1);
						}
						break;
					case '\r':				// �û����س����������ı�����
					case '\n':
						binput = false;
						break;
					default:				// �û����������������ı�����
						if (len < maxlen - 1)
						{
							text[len++] = msg.ch;
							text[len] = 0;

							clearrectangle(left + 10 + width + 1, top + 3, left + 10 + width + 1, bottom - 3);	// ������Ĺ��
							width = textwidth(text);				// ���¼����ı�����
							counter = 0;
							outtextxy(left + 1, top + 1, text);		// ����µ��ַ���
						}
					}
				}
				peekmessage(NULL, EM_MOUSE | EM_CHAR);				// ����Ϣ���������ոմ������һ����Ϣ
			}

			// ���ƹ�꣨�����˸����Ϊ 20ms * 32��
			counter = (counter + 1) % 32;
			if (counter < 16)
				line(left + 10 + width + 1, top + 3, left + 10 + width + 1, bottom - 3);				// �����
			else
				clearrectangle(left + 10 + width + 1, top + 3, left + 10 + width + 1, bottom - 3);		// �����

			// ��ʱ 20ms
			Sleep(20);
		}

		clearrectangle(left + 10 + width + 1, top + 3, left + 10 + width + 1, bottom - 3);	// �����

		// �ָ�����ֵ
		setlinecolor(oldlinecolor);
		setbkcolor(oldbkcolor);
		setfillcolor(oldfillcolor);

		Show();
	}
};