#include "struct.h"
#include<windows.h>
#include<stdio.h>
#include"draw.h"
#include"tools.h"

#pragma warning(disable:4996)
int curPostion;
int curline;
int curline1;
int bagnum;
int process;
int isinput;
int isWin;
const int statusbarlen;//״̬������
const int blanklen;//�ո��С
const int roomx; //room.x
const int roomy;//room.y
int roundnum;//ս���غ���
const int roomWidth;//room���
const int roomheight;//room�߶�
int process;
int  shopnum;
int enemynum;
struct  itemList* itemhead;
struct commodityList* shophead;
struct enemyList* enemyhead;
player player1;
struct bagList* baghaed;
char RoomLine[15][30];//�洢room���� ��ͨ����
char RoomLine1[15][30];//�洢room��ÿ�����֣�ս��ϵͳ��

void showsell();//��ʾ������Ʒ
void showbag();//��ʾ������Ʒ
void showbattlebag();//��ʾս������
void showshop();//��ʾ�̵���Ʒ
void showEnemy();
void showbag()
{

	drawbagButtom();
	curPostion = 1;
	curline = 1;
	int num = 0;
	cleanroom();
	setxy(roomx + 3, roomy + 1);
	strcpy(RoomLine[0], "========����ϵͳ========");
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
	strcpy(RoomLine1[0], "========����ʹ��ϵͳ========");
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
/////��Ʒ���ݳ�ʼ��

////��Ʒ������Ϣƥ��

void showsell()
{
	drawshopButtom();
	curPostion = 1;
	curline = 1;
	int num = 0;
	cleanroom();
	setxy(roomx + 3, roomy + 1);
	strcpy(RoomLine[0], "========����ϵͳ========");
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


void showEnemy() {
	isWin = 0;
	curPostion = 1;
	curline = 1;
	int num = 0;
	cleanroom();
	setxy(roomx + 3, roomy + 1);
	strcpy(RoomLine[0], "========�����б�========");
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
void showshop()
{
	drawshopButtom();
	curPostion = 1;
	curline = 1;
	int num = 0;
	cleanroom();
	setxy(roomx + 3, roomy + 1);
	strcpy(RoomLine[0], "========����ϵͳ=========");
	printf("%s", RoomLine[0]);
	struct commodityList* newNode = shophead->next;
	int line = 2;
	while (newNode != NULL)
	{
		num++;
		if (num == 1) { setcolour(4); }
		else { setcolour(7); }
		setxy(roomx + 3, roomy + line);
		sprintf(RoomLine[line - 1], "%d %s %d G", newNode->commodity1.ID, getItemName(newNode->commodity1.ID), newNode->commodity1.money);
		printf("%s", RoomLine[line - 1]);
		++line;
		newNode = newNode->next;
	}
	shopnum = num;
}

