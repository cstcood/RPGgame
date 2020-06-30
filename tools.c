#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#pragma warning(disable:4996)
void setxy(int x, int y);//移动光标位置
void hidecursor();//隐藏光标
void setcolour(int c);//设置文字颜色
void fileencrypt(char* str, char key, int isencrypt);
int StringTOnumber(char* str);

void setcolour(int c)
{ //3.蓝色 4红色 5紫色 6黄色 7白色
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);


}
void hidecursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);

}
void setxy(int x, int y)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void fileencrypt(char* str, char key, int isencrypt){
	FILE* fpr=NULL, * fpw=NULL;
	char ch;
	fpw=fopen(str, "rb+");
	fpr= fopen(str, "rb");
	while ((ch = fgetc(fpr)) != EOF)
	{
		fputc(ch ^ key, fpw);
		key = (isencrypt == 1) ? ch : ch ^ key;

	}
	fclose(fpr);
	fclose(fpw);

}
int StringTOnumber(char* str)
{
	int len = strlen(str), k = 0, aws = 0;
	for (int i = 0; i < len; i++)
	{

		if (str[i] != ' ') k++;
		else
		{
			break;
		}

	}
	int j = (int)pow(10, (double)(k - (double)1));
	for (int i = 0; i < k; i++)
	{
		aws = aws + (str[i] - '0') * j;
		j /= 10;
	}
	return aws;

}

