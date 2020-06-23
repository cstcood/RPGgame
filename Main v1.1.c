/*
	@NAME : RPGGAME
	@VERSION: 1.1
	@DATE : 2020.6
	@AUTHOR : cstdlib 
	@STATUE: DEBUG
	@LOG : FALSE
*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<Windows.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include"tools.h"
//#include <openssl/md5.h>//不用管这个库
#include<tchar.h>
#include"effect.h"
#include"struct.h"
#include"linkop.h"
#include"linkTransform.h"
#include"safe.h"
#include"draw.h"
#include"directoryjudge.h"
#include"show.h"
#include"battle.h"
#include"judge.h"
int process = 0;//游戏流程
#pragma warning(disable:4996)
/*
0 主界面
1 商店选择
2 商店购买
3 商店卖出
4 背包操作
5 怪物选择界面
6 战斗界面
7 战斗使用道具界面
*/
////////
//WARNING THIS IS THE initAllData MODE
void initAllData(char* name);
///////////////////
void userOperater();




player player1;
enemy enemy1;
struct commodityList* shophead;//商店链表头指针
struct enemyList* enemyhead;//敌人链表头头指针
struct itemList* itemhead;//物品链表头指针
struct bagList* baghaed;//背包链表头指针
const int statusbarlen;//状态栏长度
 const int blanklen;//空格大小
 const int roomx; //room.x
 const int roomy;//room.y
int roundnum;//战斗回合数
 const int roomWidth ;//room宽度
 const int roomheight;//room高度
 char RoomLine[15][30];//存储room文字 （通常）
 char RoomLine1[15][30];//存储room中每行文字（战斗系统）
 int curPostion ;//当前选中按钮
char* buttomText[5][4];//存储不同按钮文字
/* 0 主菜单
 * 1  通用 （上 下 返回 确认）
 * 2  道具使用
 * 3  卖出
 * 4  战斗
 */


void Login();//入口登录
void MainPanel();


//============================================
//=========== 基础工具模板==============
// 




//======================================


//===========用户层=================

//==================================



int validation(char*, char*);//登陆Control层
//void loadThePlayerInformation('k');//角色类



int main()
{

	//_getche();
	OutputDebugString(_T("start to thread \n"));//调试输出不用管 不参加游戏进程
	GameProtect('k');
	SetConsoleTitle(TEXT("RPGgame"));//设置窗口标题
	//Login();

	setxy(0, roomy + roomheight + 4);//结束后光标移动到最后
	return 0;
	
}

void enterInfomation(char *user,char *password)
{

	int len = 0, k = 0;
	setxy(roomx - 23 + (+roomWidth + statusbarlen) / 2, roomy + (roomheight + 4) / 2 - 3);
	len = scanf("%s", user);
	getchar();//清除缓冲区
	setxy(roomx - 25 + (+roomWidth + statusbarlen) / 2, roomy + (roomheight + 4) / 2 - 1);

	//////////////////////////////////////////////////////////

	//     密码输入+ *掩码
	while (k < 19 && (password[k] = _getch()) != 13) {

		if (password[k] == 8 && k > 0) {
			k--;
			setxy(roomx - 25 + (+roomWidth + statusbarlen) / 2 + k, roomy + (roomheight + 4) / 2 - 1);
			printf(" ");
			setxy(roomx - 25 + (+roomWidth + statusbarlen) / 2 + k, roomy + (roomheight + 4) / 2 - 1);

		}
		else
		{
			printf("*");
			k++;
		}

	}
	password[k] = '\0';//密码结束标识 len标识

}
void Login()
{
	char user[20];
	char password[20];
	drawlogin(1);
	enterInfomation(user, password);
	//            验证区域
	if (validation(user, password) == 1)//判断用户名密码是否正确 1 T 0 F
	{
		init();
		loadThePlayerInformation('k');
		MainPanel();

	}
	else {

		MessageBox(NULL, TEXT("用户名或密码错误"), TEXT("错误"), MB_OK);
		system("cls");
		Login();
	}
}
void regist()
{
	setcolour(7);
	char  user[20];
	char password[20];

	drawlogin(0);
	enterInfomation(user, password);
	setxy(roomx - 23 + (+roomWidth + statusbarlen) / 2, roomy + (roomheight + 4) / 2+1);
	char name[20];
	scanf("%s", name);

	//写入注册的用户名密码
	FILE* fp = fopen("login.txt","w+");
	//char* md5 = strtomd5(password, strlen(password));
	fprintf(fp, "%s %s", user, password);
	fclose(fp);
	initAllData(name);//初始化所有数据


	init();//读取文件
	loadThePlayerInformation('k');
	MainPanel();

}

void MainPanel()
{
	int timeRecovery = 10;
	curPostion = 1;

	//    绘制游戏窗口
	hidecursor();
	system("cls");
	drawRoom();//room区
	drawOther();
	drawthePlayInformation();
	/////////////////////

	time_t timep;
	struct tm* p;
	time(&timep);
	p = gmtime(&timep);
	//构建时间结构体

	setxy(roomx + 3, roomy + 1);
	printf("===Welcome to RPGGame（BATE 1.1v）===");

	while (1)
	{

		userOperater();
		Sleep(100);
		if (process == 0)
		{
			setxy(roomx + 3, roomy + 2);
			time(&timep);
			p = gmtime(&timep);
			printf("现在时间%d%年%d月%d日%d时%d分%d秒", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, 8 + p->tm_hour, p->tm_min, p->tm_sec);

			//     自然回血
			timeRecovery--;
			if (timeRecovery <= 0)
			{
				timeRecovery = 10;
				recoverFixHP(1);
				cleanPlayerInformation();
				drawthePlayInformation();

			}
			//////////////

		}

	}


}

void userOperater() {
	
	//1 2 3 4分别对应左上 右上 左下 右下的按钮 

	if (_kbhit())//判读是否按下按钮
	{
		char input = _getch();//获取按下的值
		switch (input) {

		case 'a':
			if (curPostion == 2) { curPostion = 1; reDrawText(2, 1); }
			if (curPostion == 4) { curPostion = 3; reDrawText(4, 3); }
			break;

		case 'w':
			if (curPostion == 3) { curPostion = 1; reDrawText(3, 1); }
			if (curPostion == 4) { curPostion = 2; reDrawText(4, 2); }
			break;
		case 'd':
			if (curPostion == 1) { curPostion = 2; reDrawText(1, 2); }
			if (curPostion == 3) { curPostion = 4; reDrawText(3, 4); }
			break;
		case 's':
			if (curPostion == 1) { curPostion = 3; reDrawText(1, 3); }
			if (curPostion == 2) { curPostion = 4; reDrawText(2, 4); }
			break;
		case 13: judgeProcess();
			break;
		}

	}


}





//读写文件判断正确性
int validation(char* user, char* password) {
	FILE* file;
	char Fileuser[20]="\0";
	char Filepassword[40]="\0";
	file = fopen("login.txt", "r");
	fscanf(file, "%s %s", Fileuser, Filepassword);
	//char* md5 = strtomd5(password, strlen(password));
	if (strcmp(Fileuser, user) != 0 || strcmp(Filepassword,password) != 0)
		return 0;



	return 1;
}

void initAllData(char* name)
{
	baghaed = (struct bagList*) malloc(sizeof(struct bagList));
	baghaed->next = NULL;
	baghaed->preview = NULL;
	strcpy(player1.name, name);
	player1.hp = 50;
	player1.MAXhp = 50;
	player1.level = 1;
	player1.attack = 8;
	player1.defence = 7;
	player1.money = 0;
	player1.exp = 0;
	Saveinfomation('k');
	Savebag('k');

}


/////////END/////////////////


/*
   未来工程：可视化
   MFC
   OpenGL 
*/