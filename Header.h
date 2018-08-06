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
//상수 선언
//*********************************

#define EXT_KEY         0xffffffe0   //확장키 인식값 
#define KEY_LEFT      0x4b
#define KEY_RIGHT      0x4d
#define KEY_UP         0x48
#define KEY_DOWN      0x50

enum {
	BLACK,      /*  0 : 까망 */
	DARK_BLUE,    /*  1 : 어두운 파랑 */
	DARK_GREEN,    /*  2 : 어두운 초록 */
	DARK_SKY_BLUE,  /*  3 : 어두운 하늘 */
	DARK_RED,    /*  4 : 어두운 빨강 */
	DARK_VOILET,  /*  5 : 어두운 보라 */
	DARK_YELLOW,  /*  6 : 어두운 노랑 */
	GRAY,      /*  7 : 회색 */
	DARK_GRAY,    /*  8 : 어두운 회색 */
	BLUE,      /*  9 : 파랑 */
	GREEN,      /* 10 : 초록 */
	SKY_BLUE,    /* 11 : 하늘 */
	RED,      /* 12 : 빨강 */
	VOILET,      /* 13 : 보라 */
	YELLOW,      /* 14 : 노랑 */
	WHITE,      /* 15 : 하양 */
};



//*********************************
//클래스 선언
//*********************************
class Stage {      //각 스테이지마다의 난이도 설정

private:
	int speed;   //숫자가 낮을수록 속도가 빠르다
	int stick_rate;      //막대가 나오는 확률 0~99 , 99면 막대기만 나옴
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
	int abX, abY;   //화면중 블럭이 나타나는 좌표의 절대위치
	int score;
	int lines;
	unsigned long totalBlock[21][14];      //화면에 표시되는 블럭들
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
	int gotoxy(const int x, const int y) const;   //커서옮기기
	void SetColor(const int color) const;   //색표현
	void init();               //각종변수 초기화
	void initLevel();
	void initLine(const int i);
	void showLogo();
	void inputData();
	void showTotalBlock()const;   //쌓여져있는 블럭을 화면에 표시한다.
	void showCurBlock(const int &shape, const int &angle, const int &x, const int &y) const;   //진행중인 블럭을 화면에 표시한다
	void showPreBlock(const int &shape, const int &angle, const int &x, const int &y); //블럭 미리보기 '□'으로 출력
	int makeNewBlock() const;   //return값으로 block의 모양번호를 알려줌
	void showNextBlock(const int &shape) const;
	void blockStart(int &angle, int &x, int &y) const;   //블럭이 처음 나올때 위치와 모양을 알려줌
	int strikeCheck(const int &shape, const int &angle, const int &x, const int &y) const;   //블럭이 화면 맨 아래에 부딪쳤는지 검사 부딪치면 1을리턴 아니면 0리턴
	void eraseCurBlock(const int &shape, const int &angle, const int &x, const int &y) const;   //블럭 진행의 잔상을 지우기 위한 함수
	void erasePreBlock(const int &shape, const int &angle, const int &x, const int &y);    //미리보기 블럭을 지우기 위한 함수
	int moveBlock(int &shape, int &angle, int &x, int &y, int &next_shape);   //게임오버는 1을리턴 바닥에 블럭이 닿으면 2를 리턴
	void mergeBlock(const int &shape, const int &angle, const int &x, const int &y);   //블럭이 바닥에 닿았을때 진행중인 블럭과 쌓아진 블럭을 합침
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

