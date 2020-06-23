#pragma once
#include"struct.h"
#include<windows.h>
#include<tchar.h>
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
void refeshmessage();
void cleanEnemyInfomation();
void showEnemyInfomation(enemy purpose);
void cleanroom();
void drawbagButtom();
void redrawroom1(int control);
void redrawroom(int control);
void reDrawText(int perPostion, int curPostion);