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
const int statusbarlen;//״̬������
const int blanklen;//�ո��С
const int roomx; //room.x
const int roomy;//room.y
int roundnum;//ս���غ���
const int roomWidth;//room���
const int roomheight;//room�߶�
int process;
int  shopnum;//�̵���Ʒ����
int enemynum;//��������

void judgeProcess();
//           ��ť����Enter����
void Directoryjudgement();//������
void DirectoryjudgementShop();//�̵��������̵����˵���
void DirectoryjudgementShopBuy();//�̵���
void DirectoryjudgementShopsell();//�̵���
void Directoryjudgementbag();//��������
void DirectoryjudgementEnemy();//����ѡ��
void DirectoryjudgementBattle();//ս������
void DirectoryjudgementBattleBag();//ս����Ʒʹ��
void judgeProcess()
{   ///���س�����ʱ����
	if (process == 0)
		Directoryjudgement();//���˵�
	else if (process == 1) {
		DirectoryjudgementShop();//�̵�ѡ��
	}
	else if (process == 2)
	{

		DirectoryjudgementShopBuy();//�̵�����

	}
	else if (process == 3)
	{
		DirectoryjudgementShopsell();//�̵�����

	}
	else if (process == 4)
	{
		Directoryjudgementbag();//����

	}
	else if (process == 6)
	{
		DirectoryjudgementBattle();//ս�����


	}
	else if (process == 5)
	{
		DirectoryjudgementEnemy();//����ѡ��

	}
	else if (process == 7)
	{
		DirectoryjudgementBattleBag();//ս������

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

void Directoryjudgement()//�ж���Ŀ¼
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
void DirectoryjudgementShop()//�ж��̵���Ŀ¼
{
	switch (curPostion)
	{
	case 1: {if (curline > 1) { curline--; redrawroom(1); } } break;
	case 2: {
		if (curline == 1)
		{//����
			process = 2;
			cleanroom();

			showshop();

		}
		if (curline == 2)
		{//����

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
		///�˴�Ϊһ��Ŀ¼�ж�
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
void DirectoryjudgementShopBuy()//�ж��̵�������Ŀ¼
{
	switch (curPostion)
	{
	case 1: {if (curline > 1) { curline--; redrawroom(1); } } break;
	case 2: {  judgebuy(); } break;
	case 3: {if (curline < shopnum) { curline++; redrawroom(2); } }break;
	case 4: {process = 1; drawshopButtom(); drawshopinitRoom();  }  break;

	}


}