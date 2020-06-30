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

#pragma warning(disable:4996)
extern int process = 0;//��Ϸ����
/*
0 ������
1 �̵�ѡ��
2 �̵깺��
3 �̵�����
4 ��������
5 ����ѡ�����
6 ս������
7 ս��ʹ�õ��߽���
*/
int curline;//��Ҫ������Ϣ�����
int curline1;//ս������ר����Ϣ
int bagnum;//������Ʒ����
int isinput;//ս���׶�������Ӧ��־
int  shopnum;//�̵����Ʒ����
int enemynum;//��������

////////
//WARNING THIS IS THE initAllData MODE
void initAllData(char* name);
///////////////////
void userOperater();




player player1;//�����Ϣ
enemy enemy1;//������Ϣ
struct commodityList* shophead;//�̵�����ͷָ��
struct enemyList* enemyhead;//��������ͷͷָ��
struct itemList* itemhead;//��Ʒ����ͷָ��
struct bagList* baghaed;//��������ͷָ��
const int statusbarlen;//״̬������
const int blanklen;//�ո��С
const int roomx; //room.x
const int roomy;//room.y
int roundnum;//ս���غ���
const int roomWidth ;//room���
const int roomheight;//room�߶�
char RoomLine[15][30];//�洢room���� ��ͨ����
char RoomLine1[15][30];//�洢room��ÿ�����֣�ս��ϵͳ��
int curPostion ;//��ǰѡ�а�ť
char* buttomText[5][4];//�洢��ͬ��ť����
/* 0 ���˵�
 * 1  ͨ�� ���� �� ���� ȷ�ϣ�
 * 2  ����ʹ��
 * 3  ����
 * 4  ս��
 */


void Login();//��ڵ�¼
void MainPanel();
int validation(char*, char*);//��½Control��


/*
	��������main
	����ֵ��NULL
	������NULL
	���ã�������ں���
*/
int main()
{

	OutputDebugString(_T("start to thread \n"));
	GameProtect('k');
	SetConsoleTitle(TEXT("RPGgame"));
	setxy(0, roomy + roomheight + 4);
	return 0;
	
}

void enterInfomation(char *user,char *password)
{

	int len = 0, k = 0;
	setxy(roomx - 23 + (+roomWidth + statusbarlen) / 2, roomy + (roomheight + 4) / 2 - 3);
	len = scanf("%s", user);
	getchar();//���������
	setxy(roomx - 25 + (+roomWidth + statusbarlen) / 2, roomy + (roomheight + 4) / 2 - 1);
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
	password[k] = '\0';//���������ʶ len��ʶ

}
void Login()
{
	char user[20];
	char password[20];
	drawlogin(1);
	enterInfomation(user, password);
	//            ��֤����
	if (validation(user, password) == 1)//�ж��û��������Ƿ���ȷ 1 T 0 F
	{
		init();
		loadThePlayerInformation('k');
		MainPanel();

	}
	else {

		MessageBox(NULL, TEXT("�û������������"), TEXT("����"), MB_OK);
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

	//д��ע����û�������
	FILE* fp = fopen("login.txt","w+");
	fprintf(fp, "%s %s", user, password);
	fclose(fp);
	initAllData(name);//��ʼ����������


	init();//��ȡ�ļ�
	loadThePlayerInformation('k');
	MainPanel();

}

void MainPanel()
{
	int timeRecovery = 10;
	curPostion = 1;

	//    ������Ϸ����
	hidecursor();
	system("cls");
	drawRoom();//room��
	drawOther();
	drawthePlayInformation();
	/////////////////////

	time_t timep;
	struct tm* p;
	time(&timep);
	p = gmtime(&timep);
	//����ʱ��ṹ��

	setxy(roomx + 3, roomy + 1);
	printf("===Welcome to RPGGame��BATE 1.1v��===");

	char debugs[256];
	sprintf(debugs, "itemhead: %p  \nshophead: %p \nbaghead: %p \nenemyhead: %p \n ", itemhead, shophead, baghaed, enemyhead);
	OutputDebugStringA(debugs);
	while (1)
	{
		 static int temp=-1;
		if (process != temp) {
			sprintf(debugs, "process: %d \n", process);
			OutputDebugStringA(debugs);
			temp = process;
		}


		userOperater();
		Sleep(100);
		if (process == 0)
		{
			setxy(roomx + 3, roomy + 2);
			time(&timep);
			p = gmtime(&timep);
			printf("����ʱ��%d%��%d��%d��%dʱ%d��%d��", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, 8 + p->tm_hour, p->tm_min, p->tm_sec);

			//     ��Ȼ��Ѫ
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
	
	//1 2 3 4�ֱ��Ӧ���� ���� ���� ���µİ�ť 

	if (_kbhit())//�ж��Ƿ��°�ť
	{
		char input = _getch();//��ȡ���µ�ֵ
		switch (input) {

		case 'a':
			if (curPostion == 2) { 
				curPostion = 1;
				reDrawText(2, 1); }
			if (curPostion == 4) {
				curPostion = 3;
				reDrawText(4, 3); }
			break;

		case 'w':
			if (curPostion == 3) {
				curPostion = 1;
				reDrawText(3, 1); }
			if (curPostion == 4) {
				curPostion = 2;
				reDrawText(4, 2); }
			break;
		case 'd':
			if (curPostion == 1) { 
				curPostion = 2; 
				reDrawText(1, 2); }
			if (curPostion == 3) { 
				curPostion = 4; 
				reDrawText(3, 4); }
			break;
		case 's':
			if (curPostion == 1) {
				curPostion = 3;
				reDrawText(1, 3); }
			if (curPostion == 2) { 
				curPostion = 4;
				reDrawText(2, 4); }
			break;
		case 13: judgeProcess();
			break;
		default: break;
		}

	}


}





//��д�ļ��ж���ȷ��
int validation(char* user, char* password) {
	FILE* file;
	char Fileuser[20]="\0";
	char Filepassword[40]="\0";
	file = fopen("login.txt", "r");
	fscanf(file, "%s %s", Fileuser, Filepassword);
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

