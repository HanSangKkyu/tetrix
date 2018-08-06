#include "Header.h"
bool Variables::reverse = 0;
unsigned long Variables::blockCounter = 2;
int main(int argc, char* argv[])
{
	PlaySound(TEXT("C:\\tetrix\\BGM.wav"), NULL, SND_FILENAME | SND_ASYNC);
	Variables tet;
	tet.start();
	return 0;
}