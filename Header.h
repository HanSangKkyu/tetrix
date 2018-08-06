#include <iostream>
#include <iomanip>
#include <conio.h>
#include <cstring>
#include <ctime>
#include <Windows.h>
#include <fstream>
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib")

using namespace std;

//*********************************
//��� ����
//*********************************

#define EXT_KEY         0xffffffe0   //Ȯ��Ű �νİ� 
#define KEY_LEFT      0x4b
#define KEY_RIGHT      0x4d
#define KEY_UP         0x48
#define KEY_DOWN      0x50

enum {
	BLACK,      /*  0 : ��� */
	DARK_BLUE,    /*  1 : ��ο� �Ķ� */
	DARK_GREEN,    /*  2 : ��ο� �ʷ� */
	DARK_SKY_BLUE,  /*  3 : ��ο� �ϴ� */
	DARK_RED,    /*  4 : ��ο� ���� */
	DARK_VOILET,  /*  5 : ��ο� ���� */
	DARK_YELLOW,  /*  6 : ��ο� ��� */
	GRAY,      /*  7 : ȸ�� */
	DARK_GRAY,    /*  8 : ��ο� ȸ�� */
	BLUE,      /*  9 : �Ķ� */
	GREEN,      /* 10 : �ʷ� */
	SKY_BLUE,    /* 11 : �ϴ� */
	RED,      /* 12 : ���� */
	VOILET,      /* 13 : ���� */
	YELLOW,      /* 14 : ��� */
	WHITE,      /* 15 : �Ͼ� */
};



//*********************************
//Ŭ���� ����
//*********************************
class Stage {      //�� �������������� ���̵� ����

private:
	int speed;   //���ڰ� �������� �ӵ��� ������
	int stick_rate;      //���밡 ������ Ȯ�� 0~99 , 99�� ����⸸ ����
	int clear_line;

public:
	void initStage(const int &sp, const int &ra, const int &li);
	int speedCheck(const int &i) const;
	bool rateCheck(const int i) const;
	int lineCheck(const int i) const;

};

class Variables {
private:
	int level;
	int abX, abY;   //ȭ���� ���� ��Ÿ���� ��ǥ�� ������ġ
	int score;
	int lines;
	unsigned long totalBlock[21][14];      //ȭ�鿡 ǥ�õǴ� ����
	Stage stageData[10];
	int block[7][4][4][4];
	int blockShape, blockAngle, blockX, blockY;
	int nextBlockShape;
	int is_gameover;

	int setTime;
	time_t time1, time2;

public:
	static bool reverse;
	static unsigned long blockCounter;
	int gotoxy(const int x, const int y) const;   //Ŀ���ű��
	void SetColor(const int color) const;   //��ǥ��
	void init();               //�������� �ʱ�ȭ
	void initLevel();
	void initLine(const int i);
	void showLogo();
	void inputData();
	void showTotalBlock()const;   //�׿����ִ� ���� ȭ�鿡 ǥ���Ѵ�.
	void showCurBlock(const int &shape, const int &angle, const int &x, const int &y) const;   //�������� ���� ȭ�鿡 ǥ���Ѵ�
	void showPreBlock(const int &shape, const int &angle, const int &x, const int &y); //�� �̸����� '��'���� ���
	int makeNewBlock() const;   //return������ block�� ����ȣ�� �˷���
	void showNextBlock(const int &shape) const;
	void blockStart(int &angle, int &x, int &y) const;   //���� ó�� ���ö� ��ġ�� ����� �˷���
	int strikeCheck(const int &shape, const int &angle, const int &x, const int &y) const;   //���� ȭ�� �� �Ʒ��� �ε��ƴ��� �˻� �ε�ġ�� 1������ �ƴϸ� 0����
	void eraseCurBlock(const int &shape, const int &angle, const int &x, const int &y) const;   //�� ������ �ܻ��� ����� ���� �Լ�
	void erasePreBlock(const int &shape, const int &angle, const int &x, const int &y);    //�̸����� ���� ����� ���� �Լ�
	int moveBlock(int &shape, int &angle, int &x, int &y, int &next_shape);   //���ӿ����� 1������ �ٴڿ� ���� ������ 2�� ����
	void mergeBlock(const int &shape, const int &angle, const int &x, const int &y);   //���� �ٴڿ� ������� �������� ���� �׾��� ���� ��ħ
	void showGameover();
	void checkFullLine();
	void showGamestat() const;
	int speedCheck(const int &i);
	bool lineCheck(const int &i);
	void frameChange();
	int gravityChange();
	int Exit();
	void start();
	void CursorView(char visible);
	void timePlay();
	void setRandColor();
};

