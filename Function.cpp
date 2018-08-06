#include "Header.h"
void Stage::initStage(const int &sp, const int &ra, const int &li) {
	speed = sp;
	stick_rate = ra;
	clear_line = li;
}
int Stage::speedCheck(const int &i) const {
	return speed - i;
}
bool Stage::rateCheck(const int i) const {
	if (i <= stick_rate)
		return true;
	else
		return false;
}
int Stage::lineCheck(const int i) const {
	return clear_line - i;
}

int Variables::gotoxy(const int x, const int y) const {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.Y = y;
	pos.X = x;
	SetConsoleCursorPosition(hConsole, pos);
	return 0;
}
void Variables::SetColor(const int color) const {
	static HANDLE std_output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(std_output_handle, color);

}

void Variables::CursorView(char visible) {
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursor.bVisible = visible;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void Variables::init()
{
	srand((unsigned)time(NULL));

	if (reverse == 0)
	{
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 14; j++)
			{
				if ((j == 0) || (j == 13))
				{
					totalBlock[i][j] = 1;
				}
				else
				{
					totalBlock[i][j] = 0;
				}
			}
		}


		for (int j = 0; j < 14; j++)         //화면의 제일 밑의 줄은 1로 채운다.
			totalBlock[20][j] = 1;
	}

	if (reverse == 1)
	{
		for (int i = 1; i < 21; i++)
		{
			for (int j = 0; j < 14; j++)
			{
				if ((j == 0) || (j == 13))
				{
					totalBlock[i][j] = 1;
				}
				else
				{
					totalBlock[i][j] = 0;
				}
			}
		}

		for (int j = 0; j < 14; j++)         //화면의 제일 밑의 줄은 1로 채운다.
			totalBlock[0][j] = 1;
	}

	level = 0;
	lines = 0;
	score = 0;   //수정: score 초기화
	abX = 5;
	abY = 1;

	stageData[0].initStage(40, 20, 3);
	stageData[1].initStage(38, 18, 3);
	stageData[2].initStage(35, 18, 3);
	stageData[3].initStage(30, 17, 3);
	stageData[4].initStage(25, 16, 3);
	stageData[5].initStage(20, 14, 3);
	stageData[6].initStage(15, 14, 3);
	stageData[7].initStage(10, 13, 3);
	stageData[8].initStage(6, 12, 3);
	stageData[9].initStage(4, 11, 99999);
	ifstream fin("blockInfo.txt");
	if (fin.is_open()) {
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					for (int l = 0; l < 4; l++)
					{
						fin >> block[i][j][k][l];
					}
				}
			}
		}
	}
	else {
		cout << "파일 오류";
	}
}
void Variables::initLevel() {
	level++;
}
void Variables::initLine(const int i) {
	lines = i;
}

void Variables::showLogo()
{
	int i, j;
	setRandColor();
	gotoxy(9, 3);
	cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓";
	Sleep(100);
	setRandColor();
	gotoxy(9, 4);
	cout << "┃  ◆◆◆◆  ◆◆◆      ◆  ◆      ◆ ◆ ◆◆◆◆ ◆    ◆ ┃";
	Sleep(100);
	setRandColor();
	gotoxy(9, 5);
	cout << "┃  ◆        ◆   ◆    ◆◆  ◆    ◆  ◆    ◆     ◆  ◆  ┃";
	Sleep(100);
	setRandColor();
	gotoxy(9, 6);
	cout << "┃  ◆  ◆◆  ◆◆◆    ◆◆◆  ◆  ◆   ◆    ◆       ◆    ┃";
	Sleep(100);
	setRandColor();
	gotoxy(9, 7);
	cout << "┃  ◆    ◆  ◆  ◆   ◆    ◆  ◆◆    ◆    ◆       ◆    ┃";
	Sleep(100);
	setRandColor();
	gotoxy(9, 8);
	cout << "┃  ◆◆◆◆  ◆    ◆◆      ◆  ◆     ◆    ◆       ◆    ┃";
	Sleep(100);
	setRandColor();
	gotoxy(9, 9);
	cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛";

	SetColor(WHITE);
	gotoxy(28, 20);
	cout << "Please Press Any Key~!";

	for (i = 0; i >= 0; i++)
	{
		if (i % 2 == 0)
		{


			for (j = 0; j < 5; j++)
			{
				gotoxy(18, 14 + j);
				cout << "                                                          ";
			}
			showCurBlock(rand() % 7, rand() % 4, 6, 14);
			showCurBlock(rand() % 7, rand() % 4, 12, 14);
			showCurBlock(rand() % 7, rand() % 4, 19, 14);
			showCurBlock(rand() % 7, rand() % 4, 24, 14);
		}

		if (_kbhit())
			break;
		Sleep(30);
	}
	//@
	_getch();
	system("cls");
}

void Variables::inputData()
{
	int i = 0;
	SetColor(GRAY);
	gotoxy(45, 7);
	cout << "┏━━━━<GAME KEY>━━━━━┓";
	Sleep(10);
	gotoxy(45, 8);
	cout << "┃ UP   : Rotate Block        ┃";
	Sleep(10);
	gotoxy(45, 9);
	cout << "┃ DOWN : Move One-Step Down  ┃";
	Sleep(10);
	gotoxy(45, 10);
	cout << "┃ SPACE: Move Bottom Down    ┃";
	Sleep(10);
	gotoxy(45, 11);
	cout << "┃ LEFT : Move Left           ┃";
	Sleep(10);
	gotoxy(45, 12);
	cout << "┃ RIGHT: Move Right          ┃";
	Sleep(10);
	gotoxy(45, 13);
	cout << "┗━━━━━━━━━━━━━━┛";

	gotoxy(10, 3);
	cout << "♡  Select Start level[1-10]  ♡     \b\b\b\b\b\b\b";
	gotoxy(21, 6);
	cout << "Level 1";
	gotoxy(21, 7);
	cout << "Level 2";
	gotoxy(21, 8);
	cout << "Level 3";
	gotoxy(21, 9);
	cout << "Level 4";
	gotoxy(21, 10);
	cout << "Level 5";
	gotoxy(21, 11);
	cout << "Level 6";
	gotoxy(21, 12);
	cout << "Level 7";
	gotoxy(21, 13);
	cout << "Level 8";
	gotoxy(21, 14);
	cout << "Level 9";
	gotoxy(21, 15);
	cout << "Level 10";

	int x = 17;
	int y = 6;

	while (1)
	{
		gotoxy(x, y);
		cout << "☞";
		char ch = _getch();
		if (ch == 224)
			ch = _getch();

		switch (ch)
		{
		case 72: //up
			if (y == 6)
				y = y;
			else
			{
				cout << "\b\b";
				cout << "   ";
				y--;
			}
			break;
		case 80: //down
			if (y == 15)
				y = y;
			else
			{
				cout << "\b\b";
				cout << "   ";
				y++;
			}
			break;
		}

		if (ch == 13)//enter
		{
			/*for (k = 6; k <= 13; k++)
			{
			if (y == k)
			level = k - 6;
			break;
			}*/
			if (y == 6)
				i = 0;
			if (y == 7)
				i = 1;
			if (y == 8)
				i = 2;
			if (y == 9)
				i = 3;
			if (y == 10)
				i = 4;
			if (y == 11)
				i = 5;
			if (y == 12)
				i = 6;
			if (y == 13)
				i = 7;
			if (y == 14)
				i = 8;
			if (y == 15)
				i = 9;
			break;
		}
	}
	level = i;
	system("cls");
}

void Variables::showTotalBlock() const {
	int i, j;
	if (reverse == 0)
	{
		SetColor(DARK_GRAY);
		for (i = 0; i < 21; i++)
		{
			for (j = 0; j < 14; j++)
			{
				if (j == 0 || j == 13 || i == 20) {
					SetColor((level % 6) + 1);
				}
				else {
					SetColor(DARK_GRAY);
				}
				gotoxy((j * 2) + abX, i + abY);

				if (totalBlock[i][j] != 0) {
					cout << "■";		//임시
				}
				else {
					cout << "  ";		//임시
				}

			}
		}
		SetColor(BLACK);
		gotoxy(77, 23);
	}
	if (reverse == 1)
	{
		SetColor(DARK_GRAY);
		for (i = 0; i < 21; i++)
		{
			for (j = 0; j < 14; j++)
			{
				if (j == 0 || j == 13 || i == 0) {
					SetColor((level % 6) + 1);
				}
				else {
					SetColor(DARK_GRAY);
				}
				gotoxy((j * 2) + abX, i + abY);

				if (totalBlock[i][j] != 0) {
					cout << "■";		//임시
				}
				else {
					cout << "  ";		//임시
				}

			}
		}
		SetColor(BLACK);
		gotoxy(77, 0);
	}


}

void Variables::showCurBlock(const int &shape, const int &angle, const int &x, const int &y) const {
	int i, j;

	switch (shape)
	{
	case 0:
		SetColor(RED);
		break;
	case 1:
		SetColor(BLUE);
		break;
	case 2:
		SetColor(SKY_BLUE);
		break;
	case 3:
		SetColor(WHITE);
		break;
	case 4:
		SetColor(YELLOW);
		break;
	case 5:
		SetColor(VOILET);
		break;
	case 6:
		SetColor(GREEN);
		break;
	}

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if ((j + y) < 0)
			{
				continue;
			}

			if (block[shape][angle][j][i] == 1)
			{
				gotoxy((i + x) * 2 + abX, j + y + abY);
				cout << "■";

			}
		}
	}
	if (reverse == 0)
	{
		SetColor(BLACK);
		gotoxy(77, 23);
	}

	if (reverse == 1)
	{
		SetColor(BLACK);
		gotoxy(77, 0);
	}

}

void Variables::showPreBlock(const int &shape, const int &angle, const int &x, const int &y)
{
	if (reverse == 0)
	{
		for (int k = 0; k < 20; k++)
		{
			if (strikeCheck(shape, angle, x, y + k + 1))
			{
				switch (shape)
				{
				case 0:
					SetColor(RED);
					break;
				case 1:
					SetColor(BLUE);
					break;
				case 2:
					SetColor(SKY_BLUE);
					break;
				case 3:
					SetColor(WHITE);
					break;
				case 4:
					SetColor(YELLOW);
					break;
				case 5:
					SetColor(VOILET);
					break;
				case 6:
					SetColor(GREEN);
					break;
				}

				for (int i = 0; i < 4; i++)   //preblock 출력
				{
					for (int j = 0; j < 4; j++)
					{
						if (block[shape][angle][j][i] && totalBlock[j + y + k][i + x] == 0)
						{
							gotoxy((i + x) * 2 + abX, j + y + abY + k);
							cout << "□";
						}
					}
				}
				break;
			}
		}
	}
	if (reverse == 1)
	{
		for (int k = 0; k < 20; k++)
		{
			if (strikeCheck(shape, angle, x, y - k - 1))
			{
				switch (shape)
				{
				case 0:
					SetColor(RED);
					break;
				case 1:
					SetColor(BLUE);
					break;
				case 2:
					SetColor(SKY_BLUE);
					break;
				case 3:
					SetColor(WHITE);
					break;
				case 4:
					SetColor(YELLOW);
					break;
				case 5:
					SetColor(VOILET);
					break;
				case 6:
					SetColor(GREEN);
					break;
				}
				for (int i = 0; i < 4; i++)   //preblock 출력
				{
					for (int j = 0; j < 4; j++)
					{
						if (block[shape][angle][j][i] && totalBlock[j + y - k][i + x] == 0)
						{
							gotoxy((i + x) * 2 + abX, j + y + abY - k);
							cout << "□";
						}
					}
				}
				break;
			}
		}
	}
}

int Variables::makeNewBlock() const {
	int shape;
	int i;
	i = rand() % 100;
	if (stageData[level].rateCheck(i))      //막대기 나올확률 계산
		return 0;                     //막대기 모양으로 리턴

	shape = (rand() % 6) + 1;      //shape에는 1~6의 값이 들어감
	//showNextBlock(shape); 수정
	return shape;
}

void Variables::showNextBlock(const int &shape) const {
	int i, j;
	SetColor((level + 1) % 6 + 1);
	for (i = 1; i < 7; i++) {
		gotoxy(33, i);
		for (j = 0; j < 6; j++) {
			if (i == 1 || i == 6 || j == 0 || j == 5) {
				cout << "■";
			}
			else {
				cout << "  ";
			}

		}
	}
	showCurBlock(shape, 0, 15, 1);
}

void Variables::blockStart(int &angle, int &x, int &y) const {
	if (reverse == 0)
	{
		x = 5;
		y = -3;
		angle = 0;
	}
	if (reverse == 1)
	{
		x = 5;
		y = 21;
		angle = 0;
	}

}
//독립되어있음

int Variables::strikeCheck(const int &shape, const int &angle, const int &x, const int &y) const {
	int i, j;
	int block_dat;
	if (reverse == 0)
	{
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				if (((x + j) == 0) || ((x + j) == 13))
					block_dat = 1;
				else {
					if ((y + i) < 0)
						block_dat = 0;      //수정: y + i 값이 음수(-3, -2, -1)일 때는 totalblock[y + i][x + j]를 호출하지 않도록 했다. 
					else {
						if (totalBlock[y + i][x + j] == 0)
							block_dat = 0;
						else
							block_dat = 1;
					}
				}

				if ((block_dat == 1) && (block[shape][angle][i][j] == 1))      //좌측벽의 좌표를 빼기위함
				{
					return 1;
				}
			}
		}

	}
	if (reverse == 1)
	{
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				if (((x + j) == 0) || ((x + j) == 13))
					block_dat = 1;
				else {
					if ((y + i) > 20)
						block_dat = 0;      //수정: y + i 이 20 이상일 때는 totalBlock[y+i][x+j]를 호출하지 않도록 했다.
					else {
						if (totalBlock[y + i][x + j] == 0)
							block_dat = 0;
						else
							block_dat = 1;
					}
				}

				if ((block_dat == 1) && (block[shape][angle][i][j] == 1))      //좌측벽의 좌표를 빼기위함
				{
					return 1;
				}
			}
		}

	}
	return 0;
}

void Variables::eraseCurBlock(const int &shape, const int &angle, const int &x, const int &y) const {
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (block[shape][angle][j][i] == 1)
			{
				gotoxy((i + x) * 2 + abX, j + y + abY);
				cout << "  ";
			}
		}
	}
}

void Variables::erasePreBlock(const int &shape, const int &angle, const int &x, const int &y)
{
	if (reverse == 0) {
		for (int k = 1; k < 20; k++)
		{
			if (strikeCheck(shape, angle, x, y + k + 1))
			{
				for (int i = 0; i < 4; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						if (block[shape][angle][j][i] == 1 && totalBlock[j + y + k][i + x] == 0)
						{
							gotoxy((i + x) * 2 + abX, j + y + abY + k);
							cout << "  ";
						}
					}
				}
				break;
			}
		}
	}
	if (reverse == 1) {
		for (int k = 0; k < 20; k++)
		{
			if (strikeCheck(shape, angle, x, y - k - 1))
			{
				for (int i = 0; i < 4; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						if (block[shape][angle][j][i] == 1 && totalBlock[j + y - k][i + x] == 0)
						{
							gotoxy((i + x) * 2 + abX, j + y + abY - k);
							cout << "  ";
						}
					}
				}
				break;
			}
		}
	}
}

int Variables::moveBlock(int &shape, int &angle, int &x, int &y, int &next_shape)
{
	eraseCurBlock(shape, angle, x, y);
	if (reverse == 0)
	{
		(y)++;   //블럭을 한칸 아래로 내림
		if (strikeCheck(shape, angle, x, y) == 1)
		{
			if (y < 0)   //게임오버
			{
				return 1;
			}
			(y)--;
			mergeBlock(shape, angle, x, y);
			shape = next_shape;
			next_shape = makeNewBlock();

			blockStart(angle, x, y);   //angle,x,y는 포인터임
			showNextBlock(next_shape);
			return 2;
		}

	}
	if (reverse == 1)
	{
		(y)--;   //블럭을 한칸 아래로 내림
		if (strikeCheck(shape, angle, x, y) == 1)
		{
			if (y > 19)   //게임오버
			{
				return 1;
			}
			(y)++;
			mergeBlock(shape, angle, x, y);
			shape = next_shape;
			next_shape = makeNewBlock();

			blockStart(angle, x, y);   //angle,x,y는 포인터임
			showNextBlock(next_shape);
			return 2;
		}

	}
	return 0;
}

void Variables::mergeBlock(const int &shape, const int &angle, const int &x, const int &y)
{
	int i, j;
	int counterExit;
	if (reverse == 0)
	{
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				//if (totalBlock[y + i][x + j] > 0) {

				//} 왜 있는지 모르겠음
				if (block[shape][angle][i][j] == 1) {
					//for (int checkCounter = 2; checkCounter < blockCounter; checkCounter++)
					//{
					//	counterExit = 0;
					//	for (int a = 1; a < 20; a++)
					//	{
					//		for (int b = 1; b < 13; b++)
					//			if (totalBlock[a][b] == checkCounter)
					//			{
					//				counterExit++;
					//			}
					//	}
					//	if (counterExit == 0)
					//	{
					//		totalBlock[y + i][x + j] = checkCounter;
					//		break;
					//	}
					//	if (checkCounter == blockCounter - 1)
					//	{
					//		totalBlock[y + i][x + j] = blockCounter;
					//	}
					//}
					totalBlock[y + i][x + j] = blockCounter;
				}
			}
		}
		blockCounter++;
		checkFullLine();
		showTotalBlock();
	}
	if (reverse == 1)
	{
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				if ((block[shape][angle][i][j] == 1)) {
					totalBlock[y + i][x + j] = blockCounter;
				}
			}
		}
		blockCounter++;
		checkFullLine();
		showTotalBlock();
	}

}

void Variables::showGameover() {
	PlaySound(TEXT("C:\\tetrix\\gameover.wav"), NULL, SND_FILENAME | SND_ASYNC);
	SetColor(RED);
	gotoxy(15, 8);
	cout << "┏━━━━━━━━━━━━━┓";
	gotoxy(15, 9);
	cout << "┃**************************┃";
	gotoxy(15, 10);
	cout << "┃*        GAME OVER       *┃";
	gotoxy(15, 11);
	cout << "┃**************************┃";
	gotoxy(15, 12);
	cout << "┗━━━━━━━━━━━━━┛";
	fflush(stdin);
	Sleep(1000);

	_getch();
	system("cls");
	PlaySound(TEXT("C:\\tetrix\\BGM.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
//독립되어있음

void Variables::checkFullLine()
{
	int i, j, k;
	if (reverse == 0)
	{
		for (i = 0; i < 20; i++)
		{
			for (j = 1; j < 13; j++)
			{
				if (totalBlock[i][j] == 0)
					break;
			}
			if (j == 13)   //한줄이 다 채워졌음
			{
				lines++;
				showTotalBlock();
				SetColor(BLUE);
				gotoxy(1 * 2 + abX, i + abY);
				for (j = 1; j < 13; j++)
				{
					cout << "□";
					Sleep(10);
				}
				gotoxy(1 * 2 + abX, i + abY);
				for (j = 1; j < 13; j++)
				{
					cout << "  ";
					Sleep(10);
				}

				for (k = i; k > 0; k--)
				{
					for (j = 1; j < 13; j++)
						totalBlock[k][j] = totalBlock[k - 1][j];
				}
				for (j = 1; j < 13; j++)
					totalBlock[0][j] = 0;
				score += 100 + (level * 10) + (rand() % 10);

				if (lineCheck(0))   //클리어 스테이지
				{
					initLevel();
					initLine(0);
				}//수정 : 여기서 스테이지를 클리어 했는지 확인한다

				showGamestat();

			}
		}
	}
	if (reverse == 1)
	{
		for (i = 20; i > 0; i--)
		{
			for (j = 1; j < 13; j++)
			{
				if (totalBlock[i][j] == 0)
					break;
			}
			if (j == 13)   //한줄이 다 채워졌음
			{
				lines++;
				showTotalBlock();
				SetColor(BLUE);
				gotoxy(1 * 2 + abX, i + abY);
				for (j = 1; j < 13; j++)
				{
					cout << "□";
					Sleep(10);
				}
				gotoxy(1 * 2 + abX, i + abY);
				for (j = 1; j < 13; j++)
				{
					cout << "  ";
					Sleep(10);
				}

				for (k = i; k < 20; k++)
				{
					for (j = 1; j < 13; j++)
					{
						totalBlock[k][j] = totalBlock[k + 1][j];
					}
				}
				for (j = 1; j < 13; j++)
					totalBlock[20][j] = 0;
				score += 100 + (level * 10) + (rand() % 10);

				if (lineCheck(0))   //클리어 스테이지
				{
					initLevel();
					initLine(0);
				}//수정 : 여기서 스테이지를 클리어 했는지 확인한다

				showGamestat();

			}
		}
	}

}

void Variables::showGamestat() const
{

	SetColor(GRAY);

	gotoxy(35, 7);
	cout << "STAGE";

	gotoxy(35, 9);
	cout << "SCORE";

	gotoxy(35, 12);
	cout << "LINES";

	gotoxy(35, 15);
	cout << "TIME";

	gotoxy(41, 7);
	cout << level + 1;
	gotoxy(35, 10);
	cout << score;
	gotoxy(35, 13);
	cout << "               ";//수정//깨끗하게 지우기 위함
	gotoxy(35, 13);//수정
	cout << stageData[level].lineCheck(lines);
	gotoxy(35, 16);
	cout << "          ";
	gotoxy(35, 16);
	cout << setTime - (time2 - time1);
}

int Variables::speedCheck(const int &i) {
	return stageData[level].speedCheck(i);
}
bool Variables::lineCheck(const int &i) {
	if (stageData[level].lineCheck(lines) <= i)
		return true;
	else
		return false;
}
void Variables::frameChange() {
	if (reverse == 0)
	{
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 14; j++)
			{
				if ((j == 0) || (j == 13))
				{
					totalBlock[i][j] = 1;
				}
			}
		}
		for (int j = 1; j < 13; j++)         //화면의 제일 밑의 줄은 1로 채운다.
			totalBlock[20][j] = 1;
		for (int j = 1; j < 13; j++)         //화면의 제일 밑의 줄은 1로 채운다.
			totalBlock[0][j] = 0;
	}
	//깃발
	if (reverse == 1)
	{
		for (int i = 1; i < 21; i++)
		{
			for (int j = 0; j < 14; j++)
			{
				if ((j == 0) || (j == 13))
				{
					totalBlock[i][j] = 1;
				}
			}
		}
		for (int j = 1; j < 13; j++)         //화면의 제일 밑의 줄은 1로 채운다.
			totalBlock[0][j] = 1;
		for (int j = 1; j < 13; j++)         //화면의 제일 밑의 줄은 1로 채운다.
			totalBlock[20][j] = 0;
	}
}
int Variables::gravityChange() {
	//PlaySound(TEXT("C:\\tetrix\\gravitychange.wav"), NULL, SND_FILENAME | SND_ASYNC);
	unsigned long counter;
	int i, j;
	SetColor(RED);
	gotoxy(45, 11);
	cout << "┏━━━━━━━━━━━━━━┓";
	gotoxy(45, 12);
	cout << "┃      Gravity Change        ┃";
	gotoxy(45, 13);
	cout << "┗━━━━━━━━━━━━━━┛";

	if (reverse == 1) {		//리버스가 된 후에 변환이 시작되므로
		PlaySound(TEXT("C:\\tetrix\\gravitychange.wav"), NULL, SND_FILENAME | SND_ASYNC);
		for (i = 1; i < 20; i++) {
			for (counter = 2; counter <= blockCounter; counter++)
			{
				for (i = 1; i < 20; i++) {
					for (j = 1; j < 13; j++) {
						if (totalBlock[i][j] == counter && (totalBlock[i - 1][j] != 0 && totalBlock[i - 1][j] != counter)) {
							break;
						}
					}
					if (totalBlock[i][j] == counter && (totalBlock[i - 1][j] != 0 && totalBlock[i - 1][j] != counter)) {
						break;
					}
				}
				if (totalBlock[i][j] == counter && (totalBlock[i - 1][j] != 0 && totalBlock[i - 1][j] != counter)) {
					continue;
				}
				break;
			}
			while (counter <= blockCounter) {
				for (counter = blockCounter; counter > 1; counter--)
				{
					int i, j;
					for (i = 1; i < 20; i++) {
						for (j = 1; j < 13; j++) {
							if (totalBlock[i][j] == counter && (totalBlock[i - 1][j] != 0 && totalBlock[i - 1][j] != counter)) {
								//gotoxy(25, 25);
								//SetColor(WHITE);
								//cout << setw(2) << counter << "는 이동할 수 없습니다.(이동)";
								//gotoxy(25, 26);
								//cout << blockCounter;
								//_getch();
								break;
							}
						}
						if (totalBlock[i][j] == counter && (totalBlock[i - 1][j] != 0 && totalBlock[i - 1][j] != counter)) {
							break;
						}
					}
					if (totalBlock[i][j] == counter && (totalBlock[i - 1][j] != 0 && totalBlock[i - 1][j] != counter)) {
						continue;
					}
					//gotoxy(25, 25);
					//SetColor(WHITE);
					//cout << setw(2) << counter << "는 이동할 수 있습니다.(이동)";
					//gotoxy(25, 26);
					//cout << blockCounter;
					//_getch();
					for (i = 0; i < 20; i++) {
						for (j = 1; j < 13; j++) {
							if (totalBlock[i][j] == counter) {
								totalBlock[i - 1][j] = totalBlock[i][j];
								totalBlock[i][j] = 0;
							}
						}
					}
					showTotalBlock();
				}
				//====================== 올라갈 수 있는 블록이 있다면 해당 counter를 반환
				for (counter = 2; counter <= blockCounter; counter++)
				{
					int i, j, existance;
					for (i = 1, existance = 0; i < 20; i++) {
						for (j = 1; j < 13; j++) {
							if (totalBlock[i][j] == counter) {
								existance++;
							}
						}
					}
					if (existance == 0) {
						//gotoxy(25, 25);
						//SetColor(WHITE);
						//cout << setw(2) << counter << "는 존재하지 않습니다.(검사)";
						//gotoxy(25, 26);
						//cout << blockCounter + 1;
						//_getch();
						continue;
					}
					for (i = 1; i < 20; i++) {
						for (j = 1; j < 13; j++) {
							if (totalBlock[i][j] == counter && (totalBlock[i - 1][j] != 0 && totalBlock[i - 1][j] != counter)) {
								//gotoxy(25, 25);
								//SetColor(WHITE);
								//cout << setw(2) << counter << "는 이동할 수 없습니다.(검사)";
								//gotoxy(25, 26);
								//cout << blockCounter;
								//_getch();
								break;
							}
						}
						if (totalBlock[i][j] == counter && (totalBlock[i - 1][j] != 0 && totalBlock[i - 1][j] != counter)) {
							break;
						}
					}
					if (totalBlock[i][j] == counter && (totalBlock[i - 1][j] != 0 && totalBlock[i - 1][j] != counter)) {
						continue;
					}
					//gotoxy(25, 25);
					//SetColor(WHITE);
					//cout << setw(2) << counter << "는 이동할 수 있습니다.(검사)";
					//gotoxy(25, 26);
					//cout << blockCounter;
					//_getch();
					break;
				}
			}
		}
		PlaySound(TEXT("C:\\tetrix\\PlayGame.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}

	if (reverse == 0) {		//리버스가 된 후에 변환이 시작되므로
		PlaySound(TEXT("C:\\tetrix\\gravitychange.wav"), NULL, SND_FILENAME | SND_ASYNC);
		for (counter = 2; counter <= blockCounter; counter++)
		{
			for (i = 1; i < 20; i++) {
				for (j = 1; j < 13; j++) {
					if (totalBlock[i][j] == counter && (totalBlock[i + 1][j] != 0 && totalBlock[i + 1][j] != counter)) {
						break;
					}
				}
				if (totalBlock[i][j] == counter && (totalBlock[i + 1][j] != 0 && totalBlock[i + 1][j] != counter)) {
					break;
				}
			}
			if (totalBlock[i][j] == counter && (totalBlock[i + 1][j] != 0 && totalBlock[i + 1][j] != counter)) {
				continue;
			}
			break;
		}
		while (counter <= blockCounter) {
			for (counter = 2; counter <= blockCounter; counter++)
			{
				int i, j;
				for (i = 1; i < 20; i++) {
					for (j = 1; j < 13; j++) {
						if (totalBlock[i][j] == counter && (totalBlock[i + 1][j] != 0 && totalBlock[i + 1][j] != counter)) {
							//gotoxy(25, 25);
							//SetColor(WHITE);
							//cout << setw(2) << counter << "는 이동할 수 없습니다.(이동)";
							//gotoxy(25, 26);
							//cout << blockCounter;
							//_getch();
							break;
						}
					}
					if (totalBlock[i][j] == counter && (totalBlock[i + 1][j] != 0 && totalBlock[i + 1][j] != counter)) {
						break;
					}
				}
				if (totalBlock[i][j] == counter && (totalBlock[i + 1][j] != 0 && totalBlock[i + 1][j] != counter)) {
					continue;
				}
				//gotoxy(25, 25);
				//SetColor(WHITE);
				//cout << setw(2) << counter << "는 이동할 수 있습니다.(이동)";
				//gotoxy(25, 26);
				//cout << blockCounter;
				//_getch();
				for (i = 20; i > 0; i--) {
					for (j = 1; j < 13; j++) {
						if (totalBlock[i][j] == counter) {
							totalBlock[i + 1][j] = totalBlock[i][j];
							totalBlock[i][j] = 0;
						}
					}
				}
				showTotalBlock();
			}
			//====================== 올라갈 수 있는 블록이 있다면 해당 counter를 반환
			for (counter = 2; counter <= blockCounter; counter++)
			{
				int i, j, existance;
				for (i = 1, existance = 0; i < 20; i++) {
					for (j = 1; j < 13; j++) {
						if (totalBlock[i][j] == counter) {
							existance++;
						}
					}
				}
				if (existance == 0) {
					//gotoxy(25, 25);
					//SetColor(WHITE);
					//cout << setw(2) << counter << "는 존재하지 않습니다.(검사)";
					//gotoxy(25, 26);
					//cout << blockCounter;
					//_getch();
					continue;
				}
				for (i = 0; i < 21; i++) {
					for (j = 1; j < 13; j++) {
						if (totalBlock[i][j] == counter && (totalBlock[i + 1][j] != 0 && totalBlock[i + 1][j] != counter)) {
							/*						gotoxy(25, 25);
							SetColor(WHITE);
							cout << setw(2) << counter << "는 이동할 수 없습니다.(검사)";
							gotoxy(25, 26);
							cout << blockCounter;
							_getch();*/
							break;
						}
					}
					if (totalBlock[i][j] == counter && (totalBlock[i + 1][j] != 0 && totalBlock[i + 1][j] != counter)) {
						break;
					}
				}
				if (totalBlock[i][j] == counter && (totalBlock[i + 1][j] != 0 && totalBlock[i + 1][j] != counter)) {
					continue;
				}
				//gotoxy(25, 25);
				//SetColor(WHITE);
				//cout << setw(2) << counter << "는 이동할 수 있습니다.(검사)";
				//gotoxy(25, 26);
				//cout << blockCounter;
				//_getch();
				break;
			}
		}
		PlaySound(TEXT("C:\\tetrix\\PlayGame.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}
	gotoxy(45, 11);
	cout << "                               ";
	gotoxy(45, 12);
	cout << "                               ";
	gotoxy(45, 13);
	cout << "                               ";
	return 0;
}

int Variables::Exit() {
	CursorView(0);
	char ch;
	int x = 20, y = 11;
	SetColor(GRAY);
	gotoxy(15, 8);
	cout << "┏━━━━━━━━━━━━━┓";
	gotoxy(15, 9);
	cout << "┃**************************┃";
	gotoxy(15, 10);
	cout << "┃ 게임을 종료하시겠습니까? ┃";
	gotoxy(15, 11);
	cout << "┃       예    아니오       ┃";
	gotoxy(15, 12);
	cout << "┃**************************┃";
	gotoxy(15, 13);
	cout << "┗━━━━━━━━━━━━━┛";
	gotoxy(x, y);
	cout << "☞";
	while (1)
	{
		if (_kbhit())
		{
			ch = _getch();
			if (ch == 13) // 엔터 키 입력시
			{
				if (x == 20)
				{
					system("cls");
					return 1;
				}
				else
				{
					SetColor((level % 6) + 1);
					gotoxy(15, 8);
					cout << "                              ";
					gotoxy(15, 9);
					cout << "                              ";
					gotoxy(15, 10);
					cout << "                              ";
					gotoxy(15, 11);
					cout << "                              ";
					gotoxy(15, 12);
					cout << "                              ";
					gotoxy(15, 13);
					cout << "                              ";
					showTotalBlock();
					showCurBlock(makeNewBlock(), 0, 15, 1);
					showNextBlock(makeNewBlock());
					showGamestat();
					/*미리보기 출력 함수*/
					return 0;
				}
			}
			if (ch == EXT_KEY)
			{
				ch = _getch();
				switch (ch)
				{
				case KEY_RIGHT:
					if (x == 27)
						continue;
					else
					{
						cout << "\b\b  ";
						x = 27;
						gotoxy(x, y);
						cout << "☞";
					}
					break;
				case KEY_LEFT:
					if (x == 20)
						continue;
					else
					{
						cout << "\b\b  ";
						x = 20;
						gotoxy(x, y);
						cout << "☞";
					}
					break;
				}
			}
		}
	}
	_getch();

}

void Variables::start()
{
	CursorView(0);
	PlaySound(TEXT("C:\\tetrix\\BGM.wav"), NULL, SND_FILENAME | SND_ASYNC);

	is_gameover = 0;
	char keytemp;
	init();
	showLogo();

	while (1)
	{
		inputData();
		showTotalBlock();
		blockShape = makeNewBlock();
		nextBlockShape = makeNewBlock();
		showNextBlock(nextBlockShape);
		blockStart(blockAngle, blockX, blockY);
		PlaySound(TEXT("C:\\tetrix\\PlayGame.wav"), NULL, SND_FILENAME | SND_ASYNC);
		setTime = 20;
		time1 = time(NULL);
		timePlay();
		showGamestat();
		int i;
		for (i = 1; true; i++)
		{
			showGamestat();
			timePlay();

			if (_kbhit())
			{
				keytemp = _getch();
				if (keytemp == 27) // esc 눌렀을 시
				{
					int esc = Exit();
					CursorView(0);
					if (esc == 1) {
						PlaySound(TEXT("C:\\tetrix\\BGM.wav"), NULL, SND_FILENAME | SND_ASYNC);
						blockCounter = 2;
						break;
					}
				}
				//if (keytemp == 'z') {
				//if (Variables::reverse == 0)
				//		Variables::reverse = 1;
				//	else if (Variables::reverse == 1)
				//		Variables::reverse = 0;
				//frameChange();
				//is_gameover = gravityChange();
				//}
				if (keytemp == EXT_KEY)
				{
					keytemp = _getch();
					switch (keytemp)
					{
					case KEY_UP:      //회전하기
						if (Variables::reverse == 0)
						{
							if (strikeCheck(blockShape, (blockAngle + 1) % 4, blockX, blockY) == 0)
							{
								eraseCurBlock(blockShape, blockAngle, blockX, blockY);
								erasePreBlock(blockShape, blockAngle, blockX, blockY);
								blockAngle = (blockAngle + 1) % 4;
								showPreBlock(blockShape, blockAngle, blockX, blockY);
								showCurBlock(blockShape, blockAngle, blockX, blockY);
							}
							break;
						}
						else
						{
							is_gameover = moveBlock(blockShape, blockAngle, blockX, blockY, nextBlockShape);
							showPreBlock(blockShape, blockAngle, blockX, blockY);
							showCurBlock(blockShape, blockAngle, blockX, blockY);
							break;
						}

					case KEY_LEFT:      //왼쪽으로 이동
						if (blockX > 1)
						{
							eraseCurBlock(blockShape, blockAngle, blockX, blockY);
							erasePreBlock(blockShape, blockAngle, blockX, blockY);
							blockX--;
							if (strikeCheck(blockShape, blockAngle, blockX, blockY) == 1)
								blockX++;
							showPreBlock(blockShape, blockAngle, blockX, blockY);
							showCurBlock(blockShape, blockAngle, blockX, blockY);
						}
						break;
					case KEY_RIGHT:      //오른쪽으로 이동

						if (blockX < 14)
						{
							eraseCurBlock(blockShape, blockAngle, blockX, blockY);
							erasePreBlock(blockShape, blockAngle, blockX, blockY);
							blockX++;
							if (strikeCheck(blockShape, blockAngle, blockX, blockY) == 1)
								blockX--;
							showPreBlock(blockShape, blockAngle, blockX, blockY);
							showCurBlock(blockShape, blockAngle, blockX, blockY);
						}
						break;
					case KEY_DOWN:      //아래로 이동
						if (Variables::reverse == 0)
						{
							is_gameover = moveBlock(blockShape, blockAngle, blockX, blockY, nextBlockShape);
							showPreBlock(blockShape, blockAngle, blockX, blockY);
							showCurBlock(blockShape, blockAngle, blockX, blockY);
							break;
						}
						else
						{
							if (strikeCheck(blockShape, (blockAngle + 1) % 4, blockX, blockY) == 0)
							{
								eraseCurBlock(blockShape, blockAngle, blockX, blockY);
								erasePreBlock(blockShape, blockAngle, blockX, blockY);
								blockAngle = (blockAngle + 1) % 4;
								showPreBlock(blockShape, blockAngle, blockX, blockY);
								showCurBlock(blockShape, blockAngle, blockX, blockY);
							}
							break;
						}
					}
				}
				if (keytemp == 32)   //스페이스바를 눌렀을때
				{
					while (is_gameover == 0)
					{
						is_gameover = moveBlock(blockShape, blockAngle, blockX, blockY, nextBlockShape);
					}
					showCurBlock(blockShape, blockAngle, blockX, blockY);
				}
			}

			if ((i%speedCheck(0)) == 0)
			{
				is_gameover = moveBlock(blockShape, blockAngle, blockX, blockY, nextBlockShape);
				erasePreBlock(blockShape, blockAngle, blockX, blockY);
				showPreBlock(blockShape, blockAngle, blockX, blockY);
				showCurBlock(blockShape, blockAngle, blockX, blockY);
				i = 1;//수정//없으면 i가 오버플로우가 일어난다.
			}

			//클리어 스테이지를 checkFullLine에서 확인

			if (is_gameover == 1)
			{
				showGameover();
				SetColor(GRAY);
				is_gameover = 0;// 수정: is_gameover 초기화//
				blockCounter = 2;//수정:게임오버되면 2로 초기화해줘야 계산속도가 느려지지 않는다
				reverse = 0;//수정
				break;
			}

			gotoxy(77, 23);
			Sleep(15);
			gotoxy(77, 23);
		}
		init();
	}
}

void Variables::timePlay()
{
	time2 = time(NULL);
	if (setTime <= (time2 - time1))
	{

		if (reverse == 0)
			reverse = 1;
		else if (reverse == 1)
			reverse = 0;//깃발
		eraseCurBlock(blockShape, blockAngle, blockX, blockY);//수정//내려오고 있는 블록을 지운다
		blockStart(blockAngle, blockX, blockY);//수정//블록의 시작위치를 초기화 해준다.

		frameChange();
		is_gameover = gravityChange();
		time1 = time(NULL);

	}
}
void Variables::setRandColor()
{
	int k;
	while (1)
	{
		k = rand() % 16;
		if (k != 0)
		{
			SetColor(k);
			break;
		}			
	}
}
