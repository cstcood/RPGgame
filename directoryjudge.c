#include "judge.h"
#include "draw.h"
#include<windows.h>
#include<stdio.h>
#include"show.h"
#include"tools.h"
#include"linkop.h"
#include"linkTransform.h"
#include"battle.h"
int curPostion;
int curline;
int curline1;
int bagnum;
int process;
int isinput;
const int statusbarlen;//状态栏长度
const int blanklen;//空格大小
const int roomx; //room.x
const int roomy;//room.y
int roundnum;//战斗回合数
const int roomWidth;//room宽度
const int roomheight;//room高度
int process;
int  shopnum;//商店商品数量
int enemynum;//敌人数量

void judgeProcess();
//           按钮按下Enter决策
void Directoryjudgement();//主界面
void DirectoryjudgementShop();//商店买卖（商店主菜单）
void DirectoryjudgementShopBuy();//商店买
void DirectoryjudgementShopsell();//商店卖
void Directoryjudgementbag();//背包界面
void DirectoryjudgementEnemy();//敌人选择
void DirectoryjudgementBattle();//战斗过程
void DirectoryjudgementBattleBag();//战斗物品使用
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
void DirectoryjudgementBattleBag() {
	switch (curPostion)
	{
	case 1: {if (curline1 > 1) { curline1--; redrawroom1(1); } } break;
	case 2: {  judgeuse1(); } break;
	case 3: {if (curline1 < bagnum) { curline1++; redrawroom1(2); } }break;
	case 4: {process = 6;  }  break;

	}


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

void Directoryjudgement()//判断主目录
{

	switch (curPostion)
	{
	case 1: {process = 5; drawshopButtom(); showEnemy(); }break;
	case 2: {process = 1;  drawshopButtom(); drawshopinitRoom(); } break;
	case 3: {process = 4; drawbagButtom(); showbag(); }break;
	case 4: {setxy(0, roomy + roomheight + 4); Savebag('k'); Saveinfomation('k'); exit(-1); }  break;

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