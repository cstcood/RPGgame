#include "linkTransform.h"
#include"linkop.h"
#include"effect.h"
#include"draw.h"
#include"show.h"
#include<stdio.h>
#include"tools.h"
#include "battle.h"
#pragma warning(disable:4996)
struct  itemList* itemhead;
struct commodityList* shophead;
struct enemyList* enemyhead;
player player1;
struct bagList* baghaed;
enemy enemy1;
struct commodityList* shophead;//商店链表头指针
struct enemyList* enemyhead;//敌人链表头头指针
struct itemList* itemhead;//物品链表头指针
struct bagList* baghaed;//背包链表头指针
const int statusbarlen;//状态栏长度
const int blanklen;//空格大小
const int roomx; //room.x
const int roomy;//room.y
extern int roundnum;//战斗回合数
const int roomWidth;//room宽度
const int roomheight;//room高度
char RoomLine[15][30];//存储room文字 （通常）
char RoomLine1[15][30];//存储room中每行文字（战斗系统）
int curPostion;//当前选中按钮
char* buttomText[5][4];//存储不同按钮文字
int curline;
extern int process;
extern int isinput;
int curline1;
extern int isWin;

void judgeUse();
void judgesell();
void judgebuy();
void huntjudge();
void judgehuntPlayer();
void judgehuntEnemy();
void afterBattle();
void upgrade();
void judgeuse1();
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
	if (func != NULL && func(getItemRange(ID)))
	{
		while (node != NULL)
		{
			if (node->ID == ID) {
				node->num--;
				break;
			}
			node = node->next;

		}
		if (node != NULL && node->num <= 0)
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
	Savebag('k');
	Saveinfomation('k');


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
	if (node != NULL && node->num <= 0)
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

		if (node->next == NULL || node->next->ID <= 0)
		{
			newNode = (struct   bagList*)malloc(sizeof(struct   bagList));
			baghaed = newNode;
			baghaed->preview = NULL;
			newNode = newNode = (struct   bagList*)malloc(sizeof(struct   bagList));
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
				while (node->next != NULL)
				{
					node = node->next;
				}
				node->next = newNode;
				newNode->preview = node;
				newNode->next = NULL;

			}
		}
		Savebag('k');
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
	int PlayerBloodDeduction = (int)((2 * enemy1.level + 10) / 10 + (enemy1.attack / player1.defence) * enemy1.attack);//伤害判定核心

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
	Saveinfomation('k');
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
	Savebag('k');
	Saveinfomation('k');
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
		Saveinfomation('k');
		//败北
		roundnum = 0;
		process = 0;
		MainPanel();

	}


}
