#include "struct.h"
#include <stdio.h>
#include"linkop.h"
#include"show.h"
#include "draw.h"
#include"tools.h"
#pragma warning(disable:4996)
struct enemyList* enemyhead;
enemy enemy1;
int roundnum;
int roomx;
int roomy;
int curline;
int isinput;
char RoomLine[15][30];
void battlePanel();
void battleThread();

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
	Saveinfomation('k');

}