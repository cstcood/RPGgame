#include"struct.h"
#include<windows.h>
#include<tchar.h>
#pragma warning(disable:4996)
extern const int statusbarlen = 20;//״̬������
extern const int blanklen = 2;//�ո��С
extern const int roomx = 28;//room.x
extern const int roomy = 1;//room.y
extern const int roomWidth = 40;//room���
extern const int roomheight = 15;//room�߶�
extern char* buttomText[5][4];//�洢��ͬ��ť����
extern int curPostion = 1;//��ǰѡ�а�ť
extern int curline = 1;
extern int curline1 = 1;
extern int isinput = 0;
extern char RoomLine[15][30];//�洢room���� ��ͨ����
extern char RoomLine1[15][30];//�洢room��ÿ�����֣�ս��ϵͳ��
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
void refeshmessage(); // ��room������ʱ��ˢ�¹���
void cleanEnemyInfomation();
void showEnemyInfomation(enemy purpose);
void redrawroom1(int control);
void redrawroom(int control);
void cleanroom();//���room��
void reDrawText(int perPostion, int curPostion);
player player1;
void drawOther() {
	setxy(0, 0);
	//�������Կ�
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
	//����״̬������ ��ʼ���꣺X:roomx-13 Y:roomy+x
	setxy(roomx - statusbarlen + blanklen, roomy + 1); printf("����:");
	setxy(roomx - statusbarlen + blanklen, roomy + 2); printf("�ȼ�:");
	setxy(roomx - statusbarlen + blanklen, roomy + 3); printf("����ֵ:");
	setxy(roomx - statusbarlen + blanklen, roomy + 4); printf("����:");
	setxy(roomx - statusbarlen + blanklen, roomy + 5); printf("����:");
	setxy(roomx - statusbarlen + blanklen, roomy + 6); printf("����:");
	setxy(roomx - statusbarlen + blanklen, roomy + 7); printf("��Ǯ:");

	//���ư�ť�� ��ʼ���꣺x:roomx - statusbarlen Y: roomy + roomheight + i
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
{   //���˵�����
	setcolour(4);
	buttomText[0][0] = InsertButtomText(1, "ս��");
	setcolour(7);
	buttomText[0][1] = InsertButtomText(2, "�̵�");

	buttomText[0][2] = InsertButtomText(3, "����");

	buttomText[0][3] = InsertButtomText(4, "�˳�");
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

	///��ť���ֻ���
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


	//             ���Ƶ�½����
	/*
	 *��߿�x=roomx-statusbarlen �ұ߿�x=roomx+roomWidth
	 *�ϱ߿�y=roomy �±߿�y=roomy+roomheight + 4
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
		printf("��¼��RPGGame");
	else {
		printf("ע���µ�RPGGame");
	}
	setxy(roomx - 30 + (+roomWidth + statusbarlen) / 2, roomy + (roomheight + 4) / 2 - 3);
	printf("�û���:");
	setxy(roomx - 30 + (+roomWidth + statusbarlen) / 2, roomy + (roomheight + 4) / 2 - 1);
	printf("����:");
	if (mode == 0) {
		setxy(roomx - 30 + (+roomWidth + statusbarlen) / 2, roomy + (roomheight + 4) / 2 + 1);
		printf("��ɫ��:");
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
{ //�ÿո񸲸��Ѿ�д������
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
	buttomText[1][0] = InsertButtomText(1, "��");
	setcolour(7);
	buttomText[1][2] = InsertButtomText(3, "��");
	buttomText[1][1] = InsertButtomText(2, "ȷ��");
	buttomText[1][3] = InsertButtomText(4, "����");



}
void drawbagButtom()
{
	cleanButton();
	curPostion = 1;
	setcolour(4);
	buttomText[2][0] = InsertButtomText(1, "��");
	setcolour(7);
	buttomText[2][2] = InsertButtomText(3, "��");
	buttomText[2][1] = InsertButtomText(2, "ʹ��");
	buttomText[2][3] = InsertButtomText(4, "����");


}
void drawsellButtom() {

	cleanButton();
	curPostion = 1;
	setcolour(4);
	buttomText[3][0] = InsertButtomText(1, "��");
	setcolour(7);
	buttomText[3][2] = InsertButtomText(3, "��");
	buttomText[3][1] = InsertButtomText(2, "����");
	buttomText[3][3] = InsertButtomText(4, "����");

}
void drawbattleButtom() {

	cleanButton();
	curPostion = 1;
	setcolour(4);
	buttomText[4][0] = InsertButtomText(1, "����");
	setcolour(7);
	buttomText[4][2] = InsertButtomText(3, "��Ʒ");
	buttomText[4][1] = InsertButtomText(2, "δ����");
	buttomText[4][3] = InsertButtomText(4, "����");
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
	strcpy(RoomLine[0], "======�̵�ϵͳ=====");
	strcpy(RoomLine[1], "1.����");
	strcpy(RoomLine[2], "2.����");
	strcpy(RoomLine[3], "3.����");
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
	setxy(roomx - statusbarlen + blanklen, roomy + 9); printf("������Ϣ");
	setxy(roomx - statusbarlen + blanklen, roomy + 10); printf("������:");
	setxy(roomx - statusbarlen + blanklen + 7, roomy + 10);  printf("%s", purpose.name);
	setxy(roomx - statusbarlen + blanklen, roomy + 11); printf("Ѫ��:");
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
{   //W A S D�����ػ水ť �����ƶ�
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
