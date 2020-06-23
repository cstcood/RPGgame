#include <windows.h>
#include<stdlib.h>
#include<stdio.h>
#include<tchar.h>
#pragma warning(disable:4996)

int GameProtect(char key) {
	//这里不用管
	OutputDebugString(_T("start to protect……\n"));
	//	EnableDebugPrivilege();

		//设置文件属性为系统文件 隐藏 只读
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
	SetFileAttributes(TEXT("shop.txt、"), FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_HIDDEN
		| FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_ARCHIVE);
	if (fopen("item.txt", "r") == NULL || fopen("enemy.txt", "r") == NULL || fopen("shop.txt", "r") == NULL)//判断 item.txt enemy.txt shop.txt是否存在
	{
		MessageBox(0, _T("错误,游戏基础文件丢失"), _T("错误"), MB_ICONWARNING | MB_OK);
		exit(-1);

	}

	if (fopen("player.txt", "r") == NULL && fopen("bag.txt", "r") == NULL && fopen("login.txt", "r") == NULL)//判断player.txt bag.txt login.txt是否存在
	{
		if (fopen("c:\\key.txt", "r") == NULL)
		{
			//注册流程
			system("wmic diskdrive get serialnumber >>  key1.txt");//获取硬件识别码并写入 key1.txt
			system("type key1.txt>key.txt");//将key1.txt文件编码转换为UTF-8 保存到key
			system("copy key.txt c:\\key.txt");//复制key到c:\key
			system("del key1.txt");//删除原来的key
			system("del key.txt");
			system("cls"); SetFileAttributes(TEXT("c:\\key.txt"), FILE_ATTRIBUTE_NORMAL);
			fileencrypt("c:/key.txt", key, 1);//加密文件
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
		{   //登陆流程
			system("del key1.txt");
			system("wmic diskdrive get serialnumber >\"key1.txt\" ");
			system("type key1.txt>key.txt");
			system("del key1.txt");
			/////验证c:/key文件内容
			FILE* fp2 = fopen("key.txt", "r");
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
			/////////////////
			Login();
		}


	}

	//system("del key.txt");

	//return 1;
}
