#include <windows.h>
#include<stdlib.h>
#include<stdio.h>
#include<tchar.h>
#pragma warning(disable:4996)

int GameProtect(char key) {
	//���ﲻ�ù�
	OutputDebugString(_T("start to protect����\n"));
	//	EnableDebugPrivilege();

		//�����ļ�����Ϊϵͳ�ļ� ���� ֻ��
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
	SetFileAttributes(TEXT("shop.txt��"), FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_HIDDEN
		| FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_ARCHIVE);
	if (fopen("item.txt", "r") == NULL || fopen("enemy.txt", "r") == NULL || fopen("shop.txt", "r") == NULL)//�ж� item.txt enemy.txt shop.txt�Ƿ����
	{
		MessageBox(0, _T("����,��Ϸ�����ļ���ʧ"), _T("����"), MB_ICONWARNING | MB_OK);
		exit(-1);

	}

	if (fopen("player.txt", "r") == NULL && fopen("bag.txt", "r") == NULL && fopen("login.txt", "r") == NULL)//�ж�player.txt bag.txt login.txt�Ƿ����
	{
		if (fopen("c:\\key.txt", "r") == NULL)
		{
			//ע������
			system("wmic diskdrive get serialnumber >>  key1.txt");//��ȡӲ��ʶ���벢д�� key1.txt
			system("type key1.txt>key.txt");//��key1.txt�ļ�����ת��ΪUTF-8 ���浽key
			system("copy key.txt c:\\key.txt");//����key��c:\key
			system("del key1.txt");//ɾ��ԭ����key
			system("del key.txt");
			system("cls"); SetFileAttributes(TEXT("c:\\key.txt"), FILE_ATTRIBUTE_NORMAL);
			fileencrypt("c:/key.txt", key, 1);//�����ļ�
			SetFileAttributes(TEXT("c:\\key.txt"), FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_HIDDEN
				| FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_ARCHIVE);
			regist();
		}
		else
		{
			MessageBox(0, _T("����,��Ϸ�����ļ���ʧ"), _T("����"), MB_ICONWARNING | MB_OK);
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
			MessageBox(0, _T("����KEY�ļ���ʧ"), _T("����"), MB_ICONWARNING | MB_OK);
			exit(-1);

		}
		else
		{   //��½����
			system("del key1.txt");
			system("wmic diskdrive get serialnumber >\"key1.txt\" ");
			system("type key1.txt>key.txt");
			system("del key1.txt");
			/////��֤c:/key�ļ�����
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
					MessageBox(0, _T("�Ƿ��޸�����"), _T("����"), MB_ICONWARNING | MB_OK);
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
