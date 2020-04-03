#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<Windows.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
//#include <openssl/md5.h>//不用管这个库
#include<tchar.h>
int process = 0;//游戏流程
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
//WARNING THIS IS THE TEST MODE
void TEST(char* name);
///////////////////


int curline = 1;
int curline1 = 1;//room区所选行
int shopnum = 0;//商店商品数量
int bagnum = 0;//背包物品数量
int enemynum = 0;//敌人数量
int isinput = 0;
int isWin = 1;//战斗的胜负 1 TRUE 0 FALSE
char key = 'k';//加密的种子
typedef struct
{
	char name[20];
	int level;
	int MAXhp;
	int hp;
	int attack;
	int defence;
	int exp;
	int money;


}player;
typedef struct
{
	int ID;
	char name[20];
	int effect;
	int range;
}item;
struct itemList
{
	item item1;
	struct itemList* next;
};
typedef struct
{
	int ID;
	int money;

}commodity;
struct  commodityList
{
	commodity commodity1;
	struct commodityList* next;
};
struct bagList
{
	int ID;
	int num;
	struct bagList* next;
	struct bagList* preview;

};
typedef struct {
	int ID;
	char name[20];
	int level;
	int MAXhp;
	int hp;
	int attack;
	int defence;
	int exp;
	int money;

}enemy;
struct enemyList
{
	struct enemyList* next;
	enemy enemy;
};

player player1;
enemy enemy1;
struct commodityList* shophead;
struct enemyList* enemyhead;
struct itemList* itemhead;
struct bagList* baghaed;
const int statusbarlen = 20;
const int blanklen = 2;
const int roomx = 28;
const int roomy = 1;
int roundnum = 0;
const int roomWidth = 40;
static const int roomheight = 15;
char RoomLine[15][30];
char RoomLine1[15][30];//存储room中每行文字
int curPostion = 1;//当前选中按钮
char* buttomText[5][4];//存储不同按钮文字
/* 0 主菜单
 * 1  通用 （上 下 返回 确认）
 * 2  道具使用
 * 3  卖出
 * 4  战斗
 */


void showLogin();//入口登录
void MainPanel();//主菜单循环
void battleThread();//战斗系统循环
void init();//读取数据

//============================================
//=========== 基础工具模板==============
// 
void fileencrypt(char* str, char key, int isencrypt);
void setxy(int x, int y);
void hidecursor();
void setcolour(int c);
void cleanroom();//清空room区
void cleanButton();//清空Buttom区
void cleanPlayerInformation();//清空角色状态区
int StringTOnumber(char *str);//去出第一个整数（ID）
void deleteItem(struct bagList* node);
void refeshmessage();
//char* strtomd5(const char* str, int length);
//======================================

//===========界面绘制模板===============
//             VIEW层      

//外边框
void drawRoom();
void drawOther();

void reDrawText(int perPostion, int curPostion);//重绘按钮文字（变色）
void drawthePlayInformation();//绘制角色信息
char* InsertButtomText(int Postion, char* text);
void drawshopButtom();
void redrawroom(int control);//room框架内变色
void drawshopinitRoom();
void drawbagButtom();
void drawbattleButtom();
void drawMainButttom();
void drawsellButtom();
void showsell();
void showbag();
void showbattlebag();
///=================================

//===========用户层=================
void userOperater();//角色控制
//==================================


int GameProtect();//安全类（不要各位组员了解）！！！！！！！！！
int validation(char*, char*);//登陆Control层
void loadThePlayerInformation();//角色类

//========== judge决策 ================
//           control层
//
void judgeProcess();//总控制
void judgebuy();
void judgeUse();
void judgesell();
//           Buttom决策
void Directoryjudgement();//主界面
void DirectoryjudgementShop();
void DirectoryjudgementShopBuy();
void Directoryjudgementbag();
void DirectoryjudgementEnemy();
void DirectoryjudgementShopsell();
void DirectoryjudgementBattle();
void DirectoryjudgementBattleBag();
//            战斗决策层
void judgehuntPlayer();
void judgehuntEnemy();
void judgeuse1();
void huntjudge();
//==================================



//===========商店模板==================
//         
void initshop();
void showshop();
//
//==================================




//==========物品模板===================
//        
void inititem();
//==================================



//========= 转换类==================
//           
struct  itemList* machItem(int ID);
char* getItemName(int ID);
int getItemRange(int ID);
int getItemEffect(int ID);
int getmoney(int ID);
//==================================



//===========背包模块=================
//          
void initbag();
//=====================================

;
//=========物品效果类===============
int recoverFixHP(int);//固定回血
int recoverRatrHP(int);//比例回血
//==================================



//===========战斗类=================
void showEnemy();
void initEnemy();
void battlePanel();
void showEnemyInfomation(enemy purpose);
void afterBattle();
void upgrade();
//==================================

//=============回写类===============
void Savebag();
void Saveinfomation();
//==================================
//=========================================

int main()
{

	//_getche();
	OutputDebugString(_T("start to thread \n"));
	GameProtect();
	SetConsoleTitle(TEXT("RPGgame"));


	setxy(0, roomy + roomheight + 4);
	return 0;
	
}
void showLogin()
{
	setcolour(7);
	char* user;
	char* password;
	int len = 0, k = 0;
	user = (char*)malloc(sizeof(char) * 20);
	password = (char*)malloc(sizeof(char) * 20);


	//             绘制登陆窗口
	/*
	 *左边框x=roomx-statusbarlen 右边框x=roomx+roomWidth
	 *上边框y=roomy 下边框y=roomy+roomheight + 4
	*/
	for (int i = 1; i < roomWidth + statusbarlen; i++) {
		setxy(roomx - statusbarlen + i, roomy);
		printf("*");
		setxy(roomx - statusbarlen + i, roomy + roomheight + 4);
		printf("*");
	}
	for (int i = 1; i < roomheight + 4; i++)
	{
		setxy(roomx - statusbarlen, roomy + i);
		printf("*");
		setxy(roomx + roomWidth, roomy + i);
		printf("*");

	}
	setxy(roomx - 22 + (+roomWidth + statusbarlen) / 2, roomy + (roomheight + 4) / 2 - 5);
	printf("登录到RPGGame");
	setxy(roomx - 30 + (+roomWidth + statusbarlen) / 2, roomy + (roomheight + 4) / 2 - 3);
	printf("用户名:");
	setxy(roomx - 30 + (+roomWidth + statusbarlen) / 2, roomy + (roomheight + 4) / 2 - 1);
	printf("密码:");
	setxy(roomx - 23 + (+roomWidth + statusbarlen) / 2, roomy + (roomheight + 4) / 2 - 3);
	OutputDebugString(_T("login pannel successed \n"));
	len = scanf("%s", user);
	getchar();//清除缓冲区
	setxy(roomx - 25 + (+roomWidth + statusbarlen) / 2, roomy + (roomheight + 4) / 2 - 1);
	//////////////////////////////////////////////////////////


	//     密码输入+ *掩码
	while ((password[k] = _getch()) != 13) {

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

	//            验证区域
	if (validation(user, password) == 1)
	{
		init();
		loadThePlayerInformation();
		MainPanel();




	}
	else {

		MessageBox(NULL, TEXT("用户名或密码错误"), TEXT("错误"), MB_OK);
		system("cls");
		showLogin();
	}


}
void regist()
{
	setcolour(7);
	char* user;
	char* password;
	int len = 0, k = 0;
	user = (char*)malloc(sizeof(char) * 20);
	password = (char*)malloc(sizeof(char) * 20);


	//             绘制登陆窗口
	/*
	 *左边框x=roomx-statusbarlen 右边框x=roomx+roomWidth
	 *上边框y=roomy 下边框y=roomy+roomheight + 4
	*/
	for (int i = 1; i < roomWidth + statusbarlen; i++) {
		setxy(roomx - statusbarlen + i, roomy);
		printf("*");
		setxy(roomx - statusbarlen + i, roomy + roomheight + 4);
		printf("*");
	}
	for (int i = 1; i < roomheight + 4; i++)
	{
		setxy(roomx - statusbarlen, roomy + i);
		printf("*");
		setxy(roomx + roomWidth, roomy + i);
		printf("*");

	}
	setxy(roomx - 22 + (+roomWidth + statusbarlen) / 2, roomy + (roomheight + 4) / 2 - 5);
	printf("注册新的RPGGame");
	setxy(roomx - 30 + (+roomWidth + statusbarlen) / 2, roomy + (roomheight + 4) / 2 - 3);
	printf("用户名:");
	setxy(roomx - 30 + (+roomWidth + statusbarlen) / 2, roomy + (roomheight + 4) / 2 - 1);
	printf("密码:");
	setxy(roomx - 30 + (+roomWidth + statusbarlen) / 2, roomy + (roomheight + 4) / 2+1);
	printf("角色名:");
	setxy(roomx - 23 + (+roomWidth + statusbarlen) / 2, roomy + (roomheight + 4) / 2-3);
	OutputDebugString(_T("login pannel successed \n"));
	len = scanf("%s", user);
	getchar();//清除缓冲区
	setxy(roomx - 25 + (+roomWidth + statusbarlen) / 2, roomy + (roomheight + 4) / 2 - 1);
	//////////////////////////////////////////////////////////


	//     密码输入+ *掩码
	while ((password[k] = _getch()) != 13) {

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

	setxy(roomx - 23 + (+roomWidth + statusbarlen) / 2, roomy + (roomheight + 4) / 2+1);
	char name[20];
	scanf("%s", name);
	password[k] = '\0';//密码结束标识 len标识
	FILE* fp = fopen("login.txt","w+");
	//char* md5 = strtomd5(password, strlen(password));
	fprintf(fp, "%s %s", user, password);
	fclose(fp);
	TEST(name);


	init();
	loadThePlayerInformation();
	MainPanel();



}
void init()
{
	
	initEnemy();
	initshop();
	inititem();
	initbag();
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
void drawOther() {
	setxy(0, 0);
	//绘制属性框
	for (int i = 1; i < statusbarlen; i++)
	{
		setxy(roomx - i, roomy);
		printf("*");
		setxy(roomx - i, roomy + roomheight);
		printf("*");
	}
	for (int i = 1; i < roomheight; i++)
	{
		setxy(roomx - statusbarlen, roomy + i);
		printf("*");
	}
	//绘制状态栏文字 起始坐标：X:roomx-13 Y:roomy+x
	setxy(roomx - statusbarlen + blanklen, roomy + 1); printf("姓名:");
	setxy(roomx - statusbarlen + blanklen, roomy + 2); printf("等级:");
	setxy(roomx - statusbarlen + blanklen, roomy + 3); printf("生命值:");
	setxy(roomx - statusbarlen + blanklen, roomy + 4); printf("攻击:");
	setxy(roomx - statusbarlen + blanklen, roomy + 5); printf("防御:");
	setxy(roomx - statusbarlen + blanklen, roomy + 6); printf("经验:");
	setxy(roomx - statusbarlen + blanklen, roomy + 7); printf("金钱:");

	//绘制按钮框 起始坐标：x:roomx - statusbarlen Y: roomy + roomheight + i
	for (int i = 1; i <= 4; i++)
	{
		setxy(roomx - statusbarlen, roomy + roomheight + i);
		printf("*");
		setxy(roomx - statusbarlen + (statusbarlen + roomWidth) / 2, roomy + roomheight + i);
		printf("*");
		setxy(roomx + roomWidth, roomy + roomheight + i);
		printf("*");
	}
	for (int i = 1; i <= roomWidth + statusbarlen; i++)
	{
		setxy(roomx - statusbarlen + i, roomy + roomheight + 2);
		printf("*");

	}
	for (int i = 1; i <= roomWidth + statusbarlen; i++)
	{
		setxy(roomx - statusbarlen + i, roomy + roomheight + 4);
		printf("*");

	}
	drawMainButttom();


}
void drawMainButttom()
{   //主菜单文字
	setcolour(4);
	buttomText[0][0] = InsertButtomText(1, "战斗");
	setcolour(7);
	buttomText[0][1] = InsertButtomText(2, "商店");

	buttomText[0][2] = InsertButtomText(3, "背包");

	buttomText[0][3] = InsertButtomText(4, "退出");
}
void drawRoom()
{
	setxy(roomx, roomy);
	for (int i = 1; i < roomheight; i++)
	{
		setxy(roomx, roomy + i);
		printf("*");
		setxy(roomx + roomWidth, roomy + i);
		printf("*");
	}
	for (int i = 1; i < roomWidth; i++)
	{
		setxy(roomx + i, roomy);
		printf("*");
		setxy(roomx + i, roomy + roomheight);
		printf("*");
	}


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
char* InsertButtomText(int Postion, char* text) {

	///按钮文字绘制
	switch (Postion) {
	case 1: setxy(roomx - statusbarlen + blanklen, roomy + roomheight + 1); break;
	case 2:setxy(roomx - statusbarlen + blanklen + (statusbarlen + roomWidth) / 2, roomy + roomheight + 1); break;
	case 3:setxy(roomx - statusbarlen + blanklen, roomy + roomheight + 3); break;
	case 4:setxy(roomx - statusbarlen + blanklen + (statusbarlen + roomWidth) / 2, roomy + roomheight + 3); break;
	}

	printf("%s", text);
	setcolour(7);
	return text;
}
void userOperater() {
	if (_kbhit())
	{
		char input = _getch();
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
void judgeProcess()
{   ///当回车按下时调用
	if (process == 0)
		Directoryjudgement();//主菜单
	else if (process == 1) {
		DirectoryjudgementShop();//商店选择
	}
	else if (process == 2)
	{

		DirectoryjudgementShopBuy();//商店买入

	}
	else if (process == 3)
	{
		DirectoryjudgementShopsell();//商店卖出

	}
	else if (process == 4)
	{
		Directoryjudgementbag();//背包

	}
	else if (process == 6)
	{
		DirectoryjudgementBattle();//战斗面板


	}
	else if (process == 5)
	{
		DirectoryjudgementEnemy();//敌人选择

	}
	else if (process == 7)
	{
		DirectoryjudgementBattleBag();//战斗道具

	}


}
void setcolour(int c)
{ //3.蓝色 4红色 5紫色 6黄色 7白色
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);


}
void reDrawText(int perPostion, int curPostion)
{   //W A S D操作重绘按钮 红字移动
	if (process == 0)
	{
		setcolour(7);
		InsertButtomText(perPostion, buttomText[0][perPostion - 1]);
		setcolour(4);
		InsertButtomText(curPostion, buttomText[0][curPostion - 1]);
	}
	if (process == 1 || process == 2 || process == 5)
	{
		setcolour(7);
		InsertButtomText(perPostion, buttomText[1][perPostion - 1]);
		setcolour(4);
		InsertButtomText(curPostion, buttomText[1][curPostion - 1]);

	}
	if (process == 3)
	{
		setcolour(7);
		InsertButtomText(perPostion, buttomText[3][perPostion - 1]);
		setcolour(4);
		InsertButtomText(curPostion, buttomText[3][curPostion - 1]);


	}
	if (process == 4 || process == 7)
	{
		setcolour(7);
		InsertButtomText(perPostion, buttomText[2][perPostion - 1]);
		setcolour(4);
		InsertButtomText(curPostion, buttomText[2][curPostion - 1]);

	}
	if (process == 6)
	{
		setcolour(7);
		InsertButtomText(perPostion, buttomText[4][perPostion - 1]);
		setcolour(4);
		InsertButtomText(curPostion, buttomText[4][curPostion - 1]);

	}

}

int GameProtect() {
	//这里不用管
	OutputDebugString(_T("start to protect……\n"));
//	EnableDebugPrivilege();
	SetFileAttributes(TEXT("bag.txt"), FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_HIDDEN 
		| FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_ARCHIVE);
	SetFileAttributes(TEXT("enemy.txt"), FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_HIDDEN 
		| FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_ARCHIVE);
	SetFileAttributes(TEXT("login.txt"), FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_HIDDEN 
		| FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_ARCHIVE);
	SetFileAttributes(TEXT("item.txt"), FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_HIDDEN 
		| FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_ARCHIVE);
	SetFileAttributes(TEXT("player.txt"), FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_HIDDEN 
		| FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_ARCHIVE);
	SetFileAttributes(TEXT("shop.txt"), FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_HIDDEN
		| FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_ARCHIVE);
	if (fopen("item.txt", "r") == NULL || fopen("enemy.txt", "r") == NULL || fopen("shop.txt", "r") == NULL)
	{
		MessageBox(0, _T("错误,游戏基础文件丢失"), _T("错误"), MB_ICONWARNING | MB_OK);
		exit(-1);

	}
	
	if (fopen("player.txt", "r") == NULL && fopen("bag.txt","r")==NULL && fopen("login.txt","r")==NULL)
	{
		if (fopen("c:\\key.txt", "r") == NULL)
		{

			system("wmic diskdrive get serialnumber >>  key1.txt");
			system("type key1.txt>key.txt");
			system("copy key.txt c:\\key.txt");
			system("del key1.txt");
			system("cls"); SetFileAttributes(TEXT("c:\\key.txt"),FILE_ATTRIBUTE_NORMAL);
			fileencrypt("c:\\key.txt", key, 1);
			SetFileAttributes(TEXT("c:\\key.txt"), FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_HIDDEN
				| FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_ARCHIVE);
			regist();
		}
		else
		{
			MessageBox(0, _T("错误,游戏核心文件丢失"), _T("错误"), MB_ICONWARNING | MB_OK);
			exit(-1);
		}
	}
	else
	{
		SetFileAttributes(TEXT("c:\\key.txt"), FILE_ATTRIBUTE_NORMAL);
		fileencrypt("c:\\key.txt", key, 0);
		FILE* fp = fopen("c:\\key.txt", "r");
		if (fp == NULL)
		{
			MessageBox(0, _T("错误，KEY文件丢失"), _T("错误"), MB_ICONWARNING | MB_OK);
			exit(-1);

		}
		else
		{
			system("del key1.txt");
			system("wmic diskdrive get serialnumber >\"key1.txt\" ");
			system("type key1.txt>key.txt");
			system("del key1.txt");
			FILE* fp2= fopen("key.txt", "r");
			system("cls");
			char source[20];
			char target[20];
				
				while (!feof(fp2))
				{
					fscanf(fp, "%s", source);
					fscanf(fp2, "%s", target);
					if (strcmp(source, target) != 0)
					{
						system("del key.txt");
						system("cls");
						MessageBox(0, _T("非法修改数据"), _T("错误"), MB_ICONWARNING | MB_OK);
						exit(-1);
					}



				}
			
			

			fclose(fp);
			fclose(fp2);
			fileencrypt("c:\\key.txt", key, 1);
			SetFileAttributes(TEXT("c:\\key.txt"), FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_HIDDEN
				| FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_ARCHIVE);
			system("del key.txt");
			system("cls");
			showLogin();
		}


	}

	//system("del key.txt");

	return 1;
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
void loadThePlayerInformation() {
	FILE* file;
	SetFileAttributes(TEXT("player.txt"), FILE_ATTRIBUTE_NORMAL);
	fileencrypt("player.txt", key, 0);
	file = fopen("player.txt", "r");
	if (file == 0) {
		MessageBox(NULL, TEXT("游戏文件破坏"), TEXT("错误"), MB_OK);
		exit(-1);
	}
	fscanf(file, "%s %d %d %d %d %d %d %d", player1.name, &player1.level, &player1.MAXhp, &player1.hp, &player1.attack, &player1.defence, &player1.exp, &player1.money);
	fclose(file);
	fileencrypt("player.txt", key, 1);
	SetFileAttributes(TEXT("player.txt"), FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_HIDDEN
		| FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_ARCHIVE);
	drawthePlayInformation();




}
void drawthePlayInformation() {
	cleanPlayerInformation();
	setxy(roomx - statusbarlen + blanklen + 5, roomy + 1);  printf("%s", player1.name);
	setxy(roomx - statusbarlen + blanklen + 5, roomy + 2);  printf("%d", player1.level);
	setxy(roomx - statusbarlen + blanklen + 7, roomy + 3);  printf("%d/%d", player1.hp, player1.MAXhp);
	setxy(roomx - statusbarlen + blanklen + 5, roomy + 4);  printf("%d", player1.attack);
	setxy(roomx - statusbarlen + blanklen + 5, roomy + 5);  printf("%d", player1.defence);
	setxy(roomx - statusbarlen + blanklen + 5, roomy + 6);  printf("%d", player1.exp);
	setxy(roomx - statusbarlen + blanklen + 5, roomy + 7);  printf("%d G", player1.money);

}
void cleanPlayerInformation()
{ //用空格覆盖已经写的内容
	int blank = statusbarlen - blanklen - 5;
	setxy(roomx - statusbarlen + blanklen + 5, roomy + 1);  for (int i = 1; i < blank; i++) printf(" ");
	setxy(roomx - statusbarlen + blanklen + 5, roomy + 2); for (int i = 1; i < blank; i++) printf(" ");
	setxy(roomx - statusbarlen + blanklen + 7, roomy + 3); for (int i = 1; i < blank - 2; i++) printf(" ");
	setxy(roomx - statusbarlen + blanklen + 5, roomy + 4); for (int i = 1; i < blank; i++) printf(" ");
	setxy(roomx - statusbarlen + blanklen + 5, roomy + 5); for (int i = 1; i < blank; i++) printf(" ");
	setxy(roomx - statusbarlen + blanklen + 5, roomy + 6);  for (int i = 1; i < blank; i++) printf(" ");
	setxy(roomx - statusbarlen + blanklen + 5, roomy + 7);  for (int i = 1; i < blank; i++) printf(" ");

}
void Directoryjudgement()//判断主目录
{

	switch (curPostion)
	{
	case 1: {process = 5; drawshopButtom(); showEnemy(); }break;
	case 2: {process = 1;  drawshopButtom(); drawshopinitRoom(); } break;
	case 3: {process = 4; drawbagButtom(); showbag(); }break;
	case 4: {setxy(0, roomy + roomheight + 4); Savebag(); Saveinfomation(); exit(-1); }  break;

	}
}
void Directoryjudgementbag() {
	switch (curPostion)
	{
	case 1: {if (curline > 1) { curline--; redrawroom(1); } } break;
	case 2: {  judgeUse(); } break;
	case 3: {if (curline < bagnum) { curline++; redrawroom(2); } }break;
	case 4: {process = 0; MainPanel();  }  break;

	}
}
void DirectoryjudgementBattle()
{
	if (isinput == 1)
	{
		switch (curPostion)
		{
		case 1: { huntjudge(); } break;
		case 2: {} break;
		case 3: {process = 7; drawbagButtom(); showbattlebag();  } break;
		case 4: { process = 5; drawshopButtom(); showEnemy(); }  break;

		}

	}
}
void judgeUse()
{
	char str[100];
	//int exist = 0;
	//int money = 0;
	strcpy(str, RoomLine[curline]);
	int ID = StringTOnumber(str);
	struct bagList* node = baghaed;
	int (*func)(int);
	func = NULL;

	switch (getItemEffect(ID))
	{
	case 1: func = recoverFixHP; break;
	case 2: func = recoverRatrHP; break;

	}
	if (func(getItemRange(ID)))
	{
		while (node != NULL)
		{
			if (node->ID == ID) {
				node->num--;
				break;
			}
			node = node->next;

		}
		if (node->num <= 0)
		{
			deleteItem(node);

		}
		cleanroom();
		setxy(roomx + 3, roomy + 1);
		printf("使用成功");
		getchar();
		showbag();
		drawbagButtom();
		drawthePlayInformation();
	}
	else
	{
		cleanroom();
		setxy(roomx + 3, roomy + 1);
		printf("使用失败");
		getchar();
		showbag();
		drawbagButtom();
		drawthePlayInformation();

	}
	Savebag();
	Saveinfomation();


}
void deleteItem(struct bagList* node)
{
	struct bagList* newNode;
	newNode = node->preview;
	newNode->next = node->next;
	free(node);

}
void DirectoryjudgementShopsell() {

	switch (curPostion)
	{
	case 1: {if (curline > 1) { curline--; redrawroom(1); } } break;
	case 2: {  judgesell();  } break;
	case 3: {if (curline < bagnum) { curline++; redrawroom(2); } }break;
	case 4: { process = 1;  drawshopButtom(); drawshopinitRoom(); }  break;

	}

}
void judgesell()
{
	char str[100];
	//int exist = 0;
	//int money = 0;
	strcpy(str, RoomLine[curline]);
	int ID = StringTOnumber(str);
	struct bagList* node = baghaed;
	while (node != NULL)
	{
		if (node->ID == ID) {
			node->num--;
			player1.money += (int)(0.8 * getmoney(node->ID));
			break;
		}
		node = node->next;

	}
	if (node->num <= 0)
	{
		deleteItem(node);

	}
	cleanroom();
	setxy(roomx + 3, roomy + 1);
	printf("售卖成功");
	getchar();
	showsell();
	drawsellButtom();
	drawthePlayInformation();

}
void DirectoryjudgementShop()//判断商店主目录
{
	switch (curPostion)
	{
	case 1: {if (curline > 1) { curline--; redrawroom(1); } } break;
	case 2: {
		if (curline == 1)
		{//买入
			process = 2;
			cleanroom();

			showshop();

		}
		if (curline == 2)
		{//卖出

			process = 3;
			cleanroom();
			showsell();
			drawsellButtom();

		}
		if (curline == 3)
		{
			process = 0;
			MainPanel();

		}
	} break;
		///此处为一级目录判断
	case 3: {if (curline < 3) { curline++; redrawroom(2); } }break;
	case 4: {process = 0; MainPanel();  }  break;

	}


}
void DirectoryjudgementEnemy() {
	switch (curPostion)
	{
	case 1: {if (curline > 1) { curline--; redrawroom(1); } } break;
	case 2: {isinput = 0; fflush(stdin); process = 6; drawbattleButtom(); battlePanel();    } break;
	case 3: {if (curline < enemynum) { curline++; redrawroom(2); } }break;
	case 4: {process = 0; MainPanel(); drawMainButttom();  }  break;

	}

}
void DirectoryjudgementShopBuy()//判断商店主购买目录
{
	switch (curPostion)
	{
	case 1: {if (curline > 1) { curline--; redrawroom(1); } } break;
	case 2: {  judgebuy(); } break;
	case 3: {if (curline < shopnum) { curline++; redrawroom(2); } }break;
	case 4: {process = 1; drawshopButtom(); drawshopinitRoom();  }  break;

	}


}
void judgebuy() {
	char str[100];
	int exist = 0;
	int money = 0;
	strcpy(str, RoomLine[curline]);
	int ID = StringTOnumber(str);
	struct bagList* node, * newNode;
	struct commodityList* shopnode;
	node = baghaed;
	shopnode = shophead;
	while (shopnode != NULL)
	{
		if (shopnode->commodity1.ID == ID)
		{
			money = shopnode->commodity1.money;
			break;

		}
		shopnode = shopnode->next;
		//node = shopnode;
	}
	if (player1.money >= money)
	{
		player1.money -= money;

		if (node->next ==NULL ||node->next->ID<=0)
		{
			newNode = (struct   bagList*)malloc(sizeof(struct   bagList));
			baghaed = newNode;
			baghaed->preview = NULL;
		newNode= newNode = (struct   bagList*)malloc(sizeof(struct   bagList));
		newNode->ID = ID;
		newNode->num = 1;
		newNode->preview = baghaed;
		baghaed->next = newNode;
		newNode->next = NULL;
		node = newNode;
		exist = 1;

		}
		else
		{



			while (node != NULL)
			{
				if (node->ID == ID)
				{
					node->num++;
					exist = 1;
					break;
				}

				node = node->next;
			}
			if (exist == 0)
			{
				newNode = (struct   bagList*)malloc(sizeof(struct   bagList));
				newNode->ID = ID;
				newNode->num = 1;
				node = baghaed;
				while (node ->next!= NULL)
				{
					node = node->next;
				}
				node->next = newNode;
				newNode->preview = node;
				newNode->next = NULL;

			}
		}
		Savebag();
		cleanroom();

		drawthePlayInformation();
		setxy(roomx + 3, roomy + 1);
		printf("购买成功，当前数量：%d", node->num);
		getchar();
		cleanroom();
		showshop();


	}
	else {

		cleanroom();
		setxy(roomx + 3, roomy + 1);
		printf("购买失败");
		getchar();
		cleanroom();
		showshop();

	}

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
	int j =(int) pow(10, (double)(k - 1));
	for (int i = 0; i < k; i++)
	{
		aws = aws + (str[i] - '0') * j;
		j /= 10;
	}
	return aws;

}
void cleanroom()
{
	for (int i = 1; i < roomWidth; i++)
		for (int j = 1; j < roomheight; j++)
		{
			setxy(roomx + i, roomy + j);
			printf(" ");

		}

}
/////以下为物品效果效果
//固定回血
int recoverFixHP(int hp)//1 
{
	if (player1.hp == player1.MAXhp) return 0;
	if (player1.hp + hp > player1.MAXhp)
		player1.hp = player1.MAXhp;
	else
		player1.hp += hp;
	return 1;

}
//比例回血
int recoverRatrHP(int rate)//2
{
	int recoverHP = (int)(player1.MAXhp * (double)rate / 100);
	if (player1.hp == player1.MAXhp) return 0;
	if (player1.hp + recoverHP > player1.MAXhp)
		player1.hp = player1.MAXhp;
	else
		player1.hp += recoverHP;
	return 1;

}
////商店模块
void initshop() {
	FILE* fp;
	fp = fopen("shop.txt", "r");
	struct commodityList* newNode, * tail;
	tail = (struct commodityList*)malloc(sizeof(struct commodityList));
	shophead = tail;
	while (!feof(fp))
	{
		newNode = (struct commodityList*)malloc(sizeof(struct commodityList));
		fscanf(fp, "%d %d", &newNode->commodity1.ID, &newNode->commodity1.money);
		//printf("%d %d", newNode->commodity1.ID, newNode->commodity1.money);
		tail->next = newNode;
		tail = newNode;

	}
	fclose(fp);
	tail->next = NULL;



}
void showshop()
{
	drawshopButtom();
	curPostion = 1;
	curline = 1;
	int num = 0;
	cleanroom();
	setxy(roomx + 3, roomy + 1);
	strcpy(RoomLine[0], "========购买系统=========");
	printf("%s", RoomLine[0]);
	struct commodityList* newNode = shophead->next;
	int line = 2;
	while (newNode != NULL)
	{
		num++;
		if (num == 1) { setcolour(4); }
		else setcolour(7);
		setxy(roomx + 3, roomy + line);
		sprintf(RoomLine[line - 1], "%d %s %d G", newNode->commodity1.ID, getItemName(newNode->commodity1.ID), newNode->commodity1.money);
		printf("%s", RoomLine[line - 1]);
		++line;
		newNode = newNode->next;
	}
	shopnum = num;
}
void drawshopButtom() {
	cleanButton();
	curPostion = 1;
	setcolour(4);
	buttomText[1][0] = InsertButtomText(1, "上");
	setcolour(7);
	buttomText[1][2] = InsertButtomText(3, "下");
	buttomText[1][1] = InsertButtomText(2, "确认");
	buttomText[1][3] = InsertButtomText(4, "返回");



}
void drawbagButtom()
{
	cleanButton();
	curPostion = 1;
	setcolour(4);
	buttomText[2][0] = InsertButtomText(1, "上");
	setcolour(7);
	buttomText[2][2] = InsertButtomText(3, "下");
	buttomText[2][1] = InsertButtomText(2, "使用");
	buttomText[2][3] = InsertButtomText(4, "返回");


}
void cleanButton()
{
	setcolour(7);
	InsertButtomText(1, "     ");
	InsertButtomText(2, "     ");
	InsertButtomText(3, "     ");
	InsertButtomText(4, "     ");
}
void drawshopinitRoom()
{
	cleanroom();
	curline = 1;
	strcpy(RoomLine[0], "======商店系统=====");
	strcpy(RoomLine[1], "1.买入");
	strcpy(RoomLine[2], "2.卖出");
	strcpy(RoomLine[3], "3.返回");
	setxy(roomx + 3, roomy + 1);
	printf("%s", RoomLine[0]);
	setcolour(4);
	setxy(roomx + 3, roomy + 2);
	printf("%s", RoomLine[1]);
	setcolour(7);
	setxy(roomx + 3, roomy + 3);
	printf("%s", RoomLine[2]);
	setxy(roomx + 3, roomy + 4);
	printf("%s", RoomLine[3]);



}
void redrawroom(int control)
{
	if (control == 1)
	{
		setcolour(4);
		setxy(roomx + 3, roomy + curline + 1);
		printf("%s", RoomLine[curline]);
		setcolour(7);
		setxy(roomx + 3, roomy + curline + 2);
		printf("%s", RoomLine[curline + 1]);

	}
	if (control == 2)
	{
		setcolour(4);
		setxy(roomx + 3, roomy + curline + 1);
		printf("%s", RoomLine[curline]);
		setcolour(7);
		setxy(roomx + 3, roomy + curline);
		printf("%s", RoomLine[curline - 1]);

	}

}
void redrawroom1(int control)
{
	if (control == 1)
	{
		setcolour(4);
		setxy(roomx + 3, roomy + curline1 + 1);
		printf("%s", RoomLine1[curline1]);
		setcolour(7);
		setxy(roomx + 3, roomy + curline1 + 2);
		printf("%s", RoomLine1[curline1 + 1]);

	}
	if (control == 2)
	{
		setcolour(4);
		setxy(roomx + 3, roomy + curline1 + 1);
		printf("%s", RoomLine1[curline1]);
		setcolour(7);
		setxy(roomx + 3, roomy + curline1);
		printf("%s", RoomLine1[curline1 - 1]);

	}

}
/////背包类
void initbag() {

	FILE* fp;
	SetFileAttributes(TEXT("bag.txt"), FILE_ATTRIBUTE_NORMAL);
	fileencrypt("bag.txt", key, 0);
	fp = fopen("bag.txt", "r");
	struct  bagList* newNode, * tail;
	tail = (struct   bagList*)malloc(sizeof(struct   bagList));
	baghaed = tail;
	baghaed->preview = NULL;
	int id=-1,pre=0;
	int num;
	while (!feof(fp))
	{
		newNode = (struct   bagList*)malloc(sizeof(struct  bagList));

	
		fscanf(fp, "%d %d", &id, &num);
		if (pre == id) break;
		pre = id;
		if (id > 0)
		{ 
			newNode->ID = id;
			newNode->num = num;
			tail->next = newNode;
			newNode->preview = tail;
			tail = newNode;
		}
		else
		{
			break;
		}

	}
	fclose(fp);
	tail->next = NULL;
	fileencrypt("bag.txt", key, 1);
	SetFileAttributes(TEXT("bag.txt"), FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_HIDDEN
		| FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_ARCHIVE);


}
void showbag()
{

	drawbagButtom();
	curPostion = 1;
	curline = 1;
	int num = 0;
	cleanroom();
	setxy(roomx + 3, roomy + 1);
	strcpy(RoomLine[0], "========背包系统========");
	printf("%s", RoomLine[0]);
	struct bagList* newNode = baghaed->next;
	int line = 2;
	while (newNode != NULL && newNode->ID > 0)
	{
		num++;
		if (num == 1) { setcolour(4); }
		else setcolour(7);
		setxy(roomx + 3, roomy + line);
		sprintf(RoomLine[line - 1], "%d %s %d", newNode->ID, getItemName(newNode->ID), newNode->num);
		printf("%s", RoomLine[line - 1]);
		++line;
		newNode = newNode->next;
	}
	bagnum = num;
}
void showbattlebag()
{
	drawbagButtom();
	curPostion = 1;
	int num = 0;

	curline1 = 1;
	cleanroom();
	setxy(roomx + 3, roomy + 1);
	strcpy(RoomLine1[0], "========道具使用系统========");
	printf("%s", RoomLine1[0]);
	struct bagList* newNode = baghaed->next;
	int line = 2;
	while (newNode != NULL && newNode->ID > 0)
	{
		num++;
		if (num == 1) { setcolour(4); }
		else setcolour(7);
		setxy(roomx + 3, roomy + line);
		sprintf(RoomLine1[line - 1], "%d %s %d", newNode->ID, getItemName(newNode->ID), newNode->num);
		printf("%s", RoomLine1[line - 1]);
		++line;
		newNode = newNode->next;
	}
	bagnum = num;
}
/////物品数据初始化
void inititem() {
	FILE* fp;
	fp = fopen("item.txt", "r");
	struct  itemList* newNode, * tail;
	tail = (struct  itemList*)malloc(sizeof(struct  itemList));
	itemhead = tail;
	while (!feof(fp))
	{
		newNode = (struct  itemList*)malloc(sizeof(struct  itemList));
		fscanf(fp, "%d %s %d %d", &newNode->item1.ID, newNode->item1.name, &newNode->item1.effect, &newNode->item1.range);
		//printf("%d %d", newNode->commodity1.ID, newNode->commodity1.money);
		tail->next = newNode;
		tail = newNode;

	}
	fclose(fp);
	tail->next = NULL;



}
////物品链表信息匹配
struct  itemList* machItem(int ID)
{
	struct  itemList* newNode = itemhead->next;
	while (newNode != NULL)
	{
		if (ID == newNode->item1.ID)
		{

			return newNode;
		}
		newNode = newNode->next;
	}
	return NULL;

}
char* getItemName(int ID)
{
	return machItem(ID)->item1.name;


}
int getItemEffect(int ID)
{
	return machItem(ID)->item1.effect;


}
int getItemRange(int ID)
{

	return machItem(ID)->item1.range;
}
int getmoney(int ID)
{
	struct  commodityList* newNode = shophead->next;
	while (newNode != NULL)
	{
		if (ID == newNode->commodity1.ID)
		{

			return newNode->commodity1.money;
		}
		newNode = newNode->next;
	}
	return 0;

}
void showsell()
{
	drawshopButtom();
	curPostion = 1;
	curline = 1;
	int num = 0;
	cleanroom();
	setxy(roomx + 3, roomy + 1);
	strcpy(RoomLine[0], "========贩卖系统========");
	printf("%s", RoomLine[0]);
	struct bagList* newNode = baghaed->next;
	int line = 2;
	while (newNode != NULL && newNode->ID > 0)
	{
		num++;
		if (num == 1) { setcolour(4); }
		else setcolour(7);
		setxy(roomx + 3, roomy + line);
		sprintf(RoomLine[line - 1], "%d %s %d %d G", newNode->ID, getItemName(newNode->ID), newNode->num, (int)(0.8 * getmoney(newNode->ID)));
		printf("%s", RoomLine[line - 1]);
		++line;
		newNode = newNode->next;
	}
	bagnum = num;

}
void drawsellButtom() {

	cleanButton();
	curPostion = 1;
	setcolour(4);
	buttomText[3][0] = InsertButtomText(1, "上");
	setcolour(7);
	buttomText[3][2] = InsertButtomText(3, "下");
	buttomText[3][1] = InsertButtomText(2, "售卖");
	buttomText[3][3] = InsertButtomText(4, "返回");

}
void drawbattleButtom() {

	cleanButton();
	curPostion = 1;
	setcolour(4);
	buttomText[4][0] = InsertButtomText(1, "攻击");
	setcolour(7);
	buttomText[4][2] = InsertButtomText(3, "物品");
	buttomText[4][1] = InsertButtomText(2, "未开启");
	buttomText[4][3] = InsertButtomText(4, "撤退");
	isinput = 0;

}
void showEnemy() {
	isWin = 0;
	curPostion = 1;
	curline = 1;
	int num = 0;
	cleanroom();
	setxy(roomx + 3, roomy + 1);
	strcpy(RoomLine[0], "========怪物列表========");
	printf("%s", RoomLine[0]);
	struct enemyList* newNode = enemyhead->next;
	int line = 2;
	while (newNode != NULL)
	{
		num++;
		if (num == 1) { setcolour(4); }
		else setcolour(7);
		setxy(roomx + 3, roomy + line);
		sprintf(RoomLine[line - 1], "%d %s LV:%d", newNode->enemy.ID, newNode->enemy.name, newNode->enemy.level);
		printf("%s", RoomLine[line - 1]);
		++line;
		newNode = newNode->next;
	}
	enemynum = num;


}
void initEnemy() {
	FILE* fp;
	fp = fopen("enemy.txt", "r");
	struct enemyList* newNode, * tail;
	tail = (struct enemyList*)malloc(sizeof(struct enemyList));
	enemyhead = tail;
	while (!feof(fp))
	{
		newNode = (struct enemyList*)malloc(sizeof(struct enemyList));
		fscanf(fp, "%d %s %d %d %d %d %d %d %d", &newNode->enemy.ID, newNode->enemy.name, &newNode->enemy.level, &newNode->enemy.MAXhp, &newNode->enemy.hp, &newNode->enemy.attack, &newNode->enemy.defence, &newNode->enemy.exp, &newNode->enemy.money);
		//printf("%d %d", newNode->commodity1.ID, newNode->commodity1.money);
		tail->next = newNode;
		tail = newNode;

	}
	fclose(fp);
	tail->next = NULL;



}
void battlePanel() {
	char str[100];
	//int exist = 0;
	//int money = 0;
	strcpy(str, RoomLine[curline]);
	int ID = StringTOnumber(str);
	struct enemyList* node = enemyhead;
	struct enemyList* purpose = NULL;
	while (node != NULL)
	{
		if (node->enemy.ID == ID) {
			purpose = node;
			break;

		}
		node = node->next;

	}

	enemy1 = purpose->enemy;
	showEnemyInfomation(enemy1);
	curline = 1;
	battleThread();



}
void showEnemyInfomation(enemy purpose)
{
	setxy(roomx - statusbarlen + blanklen, roomy + 9); printf("怪物信息");
	setxy(roomx - statusbarlen + blanklen, roomy + 10); printf("怪物名:");
	setxy(roomx - statusbarlen + blanklen + 7, roomy + 10);  printf("%s", purpose.name);
	setxy(roomx - statusbarlen + blanklen, roomy + 11); printf("血量:");
	setxy(roomx - statusbarlen + blanklen + 5, roomy + 11);  printf("%d", purpose.hp);


}
void cleanEnemyInfomation() {
	setxy(roomx - statusbarlen + blanklen, roomy + 9); for (int i = 0; i < statusbarlen - blanklen; i++) printf(" ");
	setxy(roomx - statusbarlen + blanklen, roomy + 10); for (int i = 0; i < statusbarlen - blanklen; i++) printf(" ");
	setxy(roomx - statusbarlen + blanklen, roomy + 11); for (int i = 0; i < statusbarlen - blanklen; i++) printf(" ");


}
void battleThread()
{
	roundnum++;
	if (roundnum == 1)
		cleanroom();

	setxy(roomx + 3, roomy + 1);
	strcpy(RoomLine[0], "========战斗机制========");
	printf("%s", RoomLine[0]);
	if (curline <= 13)
	{
		setxy(roomx + 3, roomy + 1 + curline);
		sprintf(RoomLine[curline], "第%d回合", roundnum);
		printf("%s", RoomLine[curline]);
		curline++;
		isinput = 1;
		fflush(stdin);






	}
	else {
		sprintf(RoomLine[curline], "第%d回合", roundnum);

		refeshmessage();
		isinput = 1;
		fflush(stdin);
	}
	Saveinfomation();


}
//////战斗伤害判定
void huntjudge()
{
	isinput = 0;
	judgehuntPlayer();
	if (isWin != 1) {
		judgehuntEnemy();
		if (isWin == 0)
			battleThread();
		else
		{
			//败北
			roundnum = 0;
			process = 0;
			MainPanel();

		}
	}
	else {

		afterBattle();
		//胜利	
	}



}
void judgehuntPlayer()
{

	int enmeyBloodDeduction = (int)((2 * player1.level + 10) / 10 + (player1.attack / enemy1.defence) * player1.attack);

	if (enemy1.hp - enmeyBloodDeduction > 0)
	{
		enemy1.hp -= enmeyBloodDeduction;
		cleanEnemyInfomation();
		showEnemyInfomation(enemy1);
		sprintf(RoomLine[curline], "向%s使用攻击，造成%d伤害", enemy1.name, enmeyBloodDeduction);
	}
	else {

		enemy1.hp = 0;
		cleanEnemyInfomation();
		showEnemyInfomation(enemy1);
		sprintf(RoomLine[curline], "向%s使用攻击，造成%d伤害,打到敌人", enemy1.name, enmeyBloodDeduction);
		isWin = 1;

	}

	if (curline <= 13)
	{
		setxy(roomx + 3, roomy + 1 + curline);
		printf("%s", RoomLine[curline]);
		curline++;
	}
	else {


		refeshmessage();

	}

}
void judgehuntEnemy()
{
	int PlayerBloodDeduction = (int)((2 * enemy1.level + 10) / 10 + (enemy1.attack / player1.defence) * enemy1.attack);

	if (player1.hp - PlayerBloodDeduction > 0)
	{
		player1.hp -= PlayerBloodDeduction;
		cleanPlayerInformation();
		drawthePlayInformation();
		sprintf(RoomLine[curline], "受到%s的%d伤害", enemy1.name, PlayerBloodDeduction);
	}
	else
	{
		player1.hp = 0;
		sprintf(RoomLine[curline], "受到%s的%d伤害,阵亡", enemy1.name, PlayerBloodDeduction);
		isWin = 2;
	}
	if (curline <= 13)
	{
		setxy(roomx + 3, roomy + 1 + curline);
		printf("%s", RoomLine[curline]);
		curline++;
	}
	else {


		refeshmessage();

	}
}
void refeshmessage()
{
	cleanroom();
	curline = 14;
	setxy(roomx + 3, roomy + 1);
	printf("%s", RoomLine[0]);
	for (int i = 1; i <= 13; i++)
	{
		setxy(roomx + 3, roomy + 1 + i);
		strcpy(RoomLine[i], RoomLine[i + 1]);
		printf("%s", RoomLine[i]);
	}


}
void afterBattle()
{
	curline1++;
	if (curline <= 13)
	{
		sprintf(RoomLine[curline], "获得 %d G", enemy1.money);
		setxy(roomx + 3, roomy + curline + 1);
		printf("%s", RoomLine[curline]);
		curline++;

	}
	else {
		sprintf(RoomLine[14], "获得 %d G", enemy1.money);
		refeshmessage();
	}
	if (curline <= 13)
	{
		sprintf(RoomLine[curline], "获得经验 %d ", enemy1.exp);
		setxy(roomx + 3, roomy + curline + 1);
		printf("%s", RoomLine[curline]);
		curline++;

	}
	else {
		sprintf(RoomLine[14], "获得经验 %d G", enemy1.exp);
		//setxy(roomx + 3, roomy + curline+1);
		refeshmessage();
	}

	player1.money += enemy1.money;
	player1.exp += enemy1.exp;
	upgrade();
	cleanPlayerInformation();
	drawthePlayInformation();
	getchar();
	Saveinfomation();
	roundnum = 0;
	process = 0;
	MainPanel();

}
void upgrade()
{
	int upgradExperience = 10 * player1.level;
	if (player1.exp >= upgradExperience)
	{
		player1.exp -= upgradExperience;
		player1.level++;
		int tempMAXhp = player1.MAXhp;
		player1.MAXhp += 30 * player1.level;
		player1.hp += (player1.MAXhp - tempMAXhp);
		player1.attack += 4 * player1.level;
		player1.defence += 5 * player1.level;
		if (player1.exp >= 10 * player1.level) upgrade();



	}



}
void DirectoryjudgementBattleBag() {
	switch (curPostion)
	{
	case 1: {if (curline1 > 1) { curline1--; redrawroom1(1); } } break;
	case 2: {  judgeuse1(); } break;
	case 3: {if (curline1 < bagnum) { curline1++; redrawroom1(2); } }break;
	case 4: {process = 6;  }  break;

	}


}
void judgeuse1()
{
	char str[100];
	//int exist = 0;
	//int money = 0;
	strcpy(str, RoomLine1[curline1]);
	int ID = StringTOnumber(str);
	int Prehp = player1.hp;
	struct bagList* node = baghaed;
	int (*func)(int);
	func = NULL;
	switch (getItemEffect(ID))
	{
	case 1: func = recoverFixHP; break;
	case 2: func = recoverRatrHP; break;

	}
	if (func(getItemRange(ID)))
	{
		while (node != NULL)
		{
			if (node->ID == ID) {
				node->num--;
				break;
			}
			node = node->next;

		}
		if (node->num <= 0)
		{
			deleteItem(node);

		}
		cleanroom();

	}
	Savebag();
	Saveinfomation();
	drawbattleButtom();
	process = 6;
	for (int i = 0; i < curline; i++)
	{
		setxy(roomx + 3, roomy + 1 + i);
		printf("%s", RoomLine[i]);

	}

	cleanPlayerInformation();
	drawthePlayInformation();
	if (ID < 3) 	sprintf(RoomLine[curline], "使用物品%s 恢复%d血量", getItemName(ID), player1.hp - Prehp);

	if (curline <= 13)
	{
		setxy(roomx + 3, roomy + 1 + curline);
		printf("%s", RoomLine[curline]);
		curline++;
	}
	else {


		refeshmessage();

	}



	judgehuntEnemy();
	if (isWin == 0)
		battleThread();
	else
	{
		Saveinfomation();
		//败北
		roundnum = 0;
		process = 0;
		MainPanel();

	}


}
void Savebag()
{
	SetFileAttributes(TEXT("bag.txt"), FILE_ATTRIBUTE_NORMAL);
	struct bagList* newnode = baghaed->next;
	FILE* fp,*fp1;
	fp = fopen("bag.txt", "w");
	//fp1 = fopen("bag1.txt", "w");
	int id=0;
	while (newnode != NULL && newnode->ID > 0)
	{
		if (id == newnode->ID) break;
		id = newnode->ID;
		
		fprintf(fp, "%d %d \n", newnode->ID, newnode->num);
		//fprintf(fp1, "%d %d \n", newnode->ID, newnode->num);
		newnode = newnode->next;
	}
	fclose(fp);
	//fclose(fp1);
	
	fileencrypt("bag.txt", key, 1);
	SetFileAttributes(TEXT("bag.txt"), FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_HIDDEN
		| FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_ARCHIVE);
}
void Saveinfomation() {
	FILE* file;
	SetFileAttributes(TEXT("player.txt"),FILE_ATTRIBUTE_NORMAL);
	file = fopen("player.txt", "w+");
	fprintf(file, "%s %d %d %d %d %d %d %d", player1.name, player1.level, player1.MAXhp, player1.hp, player1.attack, player1.defence, player1.exp, player1.money);
	fclose(file);
	fileencrypt("player.txt", key, 1);
	SetFileAttributes(TEXT("player.txt"), FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_HIDDEN
		| FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_ARCHIVE);


}

void TEST(char* name)
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
	Saveinfomation();
	Savebag();

}

void fileencrypt(char* str, char key,int isencrypt)
{
	FILE* fpr,*fpw;
	char ch;
	fpw = fopen(str, "rb+");
	fpr = fopen(str, "rb");
	while ((ch = fgetc(fpr)) != EOF)
	{
		fputc(ch ^ key, fpw);
		key = (isencrypt == 1) ? ch : ch ^ key;

	}
	fclose(fpr);
	fclose(fpw);

}
/////////END/////////////////
