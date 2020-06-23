#include"struct.h"
#include<windows.h>
#include<tchar.h>
#pragma warning(disable:4996)
extern const int statusbarlen = 20;//状态栏长度
extern const int blanklen = 2;//空格大小
extern const int roomx = 28;//room.x
extern const int roomy = 1;//room.y
extern const int roomWidth = 40;//room宽度
extern const int roomheight = 15;//room高度
extern char* buttomText[5][4];//存储不同按钮文字
extern int curPostion = 1;//当前选中按钮
extern int curline = 1;
extern int curline1 = 1;
extern int isinput = 0;
extern char RoomLine[15][30];//存储room文字 （通常）
extern char RoomLine1[15][30];//存储room中每行文字（战斗系统）
int process;
void drawOther();
void drawMainButttom();
void drawRoom();
char* InsertButtomText(int Postion, char* text);
void drawlogin(int mode);
void drawthePlayInformation();
void cleanPlayerInformation();
void drawshopButtom();
void drawsellButtom();
void drawbattleButtom();
void cleanButton();
void drawshopinitRoom();
void refeshmessage(); // 当room区满的时候刷新滚动
void cleanEnemyInfomation();
void showEnemyInfomation(enemy purpose);
void redrawroom1(int control);
void redrawroom(int control);
void cleanroom();//清空room区
void reDrawText(int perPostion, int curPostion);
player player1;
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
void drawlogin(int mode) {


	//             绘制登陆窗口
	/*
	 *左边框x=roomx-statusbarlen 右边框x=roomx+roomWidth
	 *上边框y=roomy 下边框y=roomy+roomheight + 4
	*/
	setcolour(7);
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
	if (mode == 1)
		printf("登录到RPGGame");
	else {
		printf("注册新的RPGGame");
	}
	setxy(roomx - 30 + (+roomWidth + statusbarlen) / 2, roomy + (roomheight + 4) / 2 - 3);
	printf("用户名:");
	setxy(roomx - 30 + (+roomWidth + statusbarlen) / 2, roomy + (roomheight + 4) / 2 - 1);
	printf("密码:");
	if (mode == 0) {
		setxy(roomx - 30 + (+roomWidth + statusbarlen) / 2, roomy + (roomheight + 4) / 2 + 1);
		printf("角色名:");
	}




	OutputDebugString(_T("login pannel successed \n"));

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
void cleanButton()
{
	setcolour(7);
	InsertButtomText(1, "     ");
	InsertButtomText(2, "     ");
	InsertButtomText(3, "     ");
	InsertButtomText(4, "     ");
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
