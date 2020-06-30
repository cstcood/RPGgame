#include<windows.h>
#include<stdio.h>
#include"struct.h"
#pragma warning(disable:4996)
struct  itemList* itemhead;
struct commodityList* shophead;
struct enemyList* enemyhead;
player player1;
struct bagList* baghaed;
void init();
void loadThePlayerInformation(char key);
void initEnemy();
void initshop();
void inititem();
void initbag(char key);
void Saveinfomation(char key);
void Savebag(char key);
void deleteItem(struct bagList* node);

/*
	��������init
	����ֵ��NULL
	������NULL
	���ã������ʼ������ȡ�������ļ�
*/
void init()
{

	initEnemy();
	initshop();
	inititem();
	initbag('k');
	
}

/*
	��������initEnemy
	����ֵ��NULL
	������NULL 
	ȫ�ֲ�����enemyhead
	���ã����ļ���enemy.txt����ȡ��Ӧ�ĵ�������
*/
void initEnemy() {
	FILE* fp;
	fp = fopen("enemy.txt", "r");
	struct enemyList* newNode, * tail;
	tail = (struct enemyList*)malloc(sizeof(struct enemyList));
	enemyhead = tail;
	while (!feof(fp))
	{
		newNode = (struct enemyList*)malloc(sizeof(struct enemyList));
		fscanf(fp, "%d %s %d %d %d %d %d %d %d", &newNode->enemy.ID, newNode->enemy.name, &newNode->enemy.level, &newNode->enemy.MAXhp, &newNode->enemy.hp, &newNode->enemy.attack, &newNode->enemy.defence, &newNode->enemy.exp, &newNode->enemy.money);
		//printf("%d %d", newNode->commodity1.ID, newNode->commodity1.money);
		tail->next = newNode;
		tail = newNode;

	}
	fclose(fp);
	tail->next = NULL;



}

/*
	��������initshop
	����ֵ��NULL
	������NULL
	ȫ�ֲ�����shophead
	���ã����ļ���shop.txt����ȡ��Ӧ���̵�����
*/
void initshop() {
	FILE* fp;
	fp = fopen("shop.txt", "r");
	struct commodityList* newNode, * tail;
	tail = (struct commodityList*)malloc(sizeof(struct commodityList));
	shophead = tail;
	while (!feof(fp))
	{
		newNode = (struct commodityList*)malloc(sizeof(struct commodityList));
		fscanf(fp, "%d %d", &newNode->commodity1.ID, &newNode->commodity1.money);
		//printf("%d %d", newNode->commodity1.ID, newNode->commodity1.money);
		tail->next = newNode;
		tail = newNode;

	}
	fclose(fp);
	tail->next = NULL;



}

/*
	��������inititem
	����ֵ��NULL
	������NULL
	ȫ�ֲ�����itemhead
	���ã����ļ���item.txt����ȡ��Ӧ����Ʒ����
*/
void inititem() {
	FILE* fp;
	fp = fopen("item.txt", "r");
	struct  itemList* newNode, * tail;
	tail = (struct  itemList*)malloc(sizeof(struct  itemList));
	itemhead = tail;
	while (!feof(fp))
	{
		newNode = (struct  itemList*)malloc(sizeof(struct  itemList));
		fscanf(fp, "%d %s %d %d", &newNode->item1.ID, newNode->item1.name, &newNode->item1.effect, &newNode->item1.range);
		//printf("%d %d", newNode->commodity1.ID, newNode->commodity1.money);
		tail->next = newNode;
		tail = newNode;

	}
	fclose(fp);
	tail->next = NULL;



}

/*
	��������initbag
	����ֵ��NULL
	������key
	ȫ�ֲ�����baghaed
	���ã�ͨ��key�����ļ����뱳���ļ�
*/
void initbag(char key) {

	FILE* fp;
	SetFileAttributes(TEXT("bag.txt"), FILE_ATTRIBUTE_NORMAL);
	fileencrypt("bag.txt", key, 0);
	fp = fopen("bag.txt", "r");
	struct  bagList* newNode, * tail;
	tail = (struct   bagList*)malloc(sizeof(struct   bagList));
	baghaed = tail;
	baghaed->preview = NULL;
	int id = -1, pre = 0;
	int num;
	while (!feof(fp))
	{
		newNode = (struct   bagList*)malloc(sizeof(struct  bagList));


		fscanf(fp, "%d %d", &id, &num);
		if (pre == id) break;
		pre = id;
		if (id > 0)
		{
			newNode->ID = id;
			newNode->num = num;
			tail->next = newNode;
			newNode->preview = tail;
			tail = newNode;
		}
		else
		{
			break;
		}

	}
	fclose(fp);
	tail->next = NULL;
	fileencrypt("bag.txt", key, 1);
	SetFileAttributes(TEXT("bag.txt"), FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_HIDDEN
		| FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_ARCHIVE);


}

/*
	��������Saveinfomation
	����ֵ��NULL
	������key
	ȫ�ֲ�����NULL
	���ã�����key�������ݲ�����ɫ��Ϣ�����ļ�
*/
void Saveinfomation(char key) {
	FILE* file;
	SetFileAttributes(TEXT("player.txt"), FILE_ATTRIBUTE_NORMAL);
	file = fopen("player.txt", "w+");
	fprintf(file, "%s %d %d %d %d %d %d %d", player1.name, player1.level, player1.MAXhp, player1.hp, player1.attack, player1.defence, player1.exp, player1.money);
	fclose(file);
	fileencrypt("player.txt", key, 1);
	SetFileAttributes(TEXT("player.txt"), FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_HIDDEN
		| FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_ARCHIVE);


}

/*
	��������Savebag
	����ֵ��NULL
	������key
	ȫ�ֲ�����baghaed
	���ã�����key�������ݲ���������Ϣ�����ļ�
*/
void Savebag(char key)
{
	SetFileAttributes(TEXT("bag.txt"), FILE_ATTRIBUTE_NORMAL);
	struct bagList* newnode = baghaed->next;
	FILE* fp, * fp1;
	fp = fopen("bag.txt", "w");
	//fp1 = fopen("bag1.txt", "w");
	int id = 0;
	while (newnode != NULL && newnode->ID > 0)
	{
		if (id == newnode->ID) break;
		id = newnode->ID;

		fprintf(fp, "%d %d \n", newnode->ID, newnode->num);
		//fprintf(fp1, "%d %d \n", newnode->ID, newnode->num);
		newnode = newnode->next;
	}
	fclose(fp);
	//fclose(fp1);

	fileencrypt("bag.txt", key, 1);
	SetFileAttributes(TEXT("bag.txt"), FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_HIDDEN
		| FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_ARCHIVE);
}

/*
	��������loadThePlayerInformation
	����ֵ��NULL
	������key
	ȫ�ֲ�����NULL
	���ã�����key�������ݶ�ȡ��ɫ��Ϣ
*/
void loadThePlayerInformation(char key) {
	FILE* file;
	SetFileAttributes(TEXT("player.txt"), FILE_ATTRIBUTE_NORMAL);
	fileencrypt("player.txt", key, 0);
	file = fopen("player.txt", "r");
	if (file == 0) {
		MessageBox(NULL, TEXT("��Ϸ�ļ��ƻ�"), TEXT("����"), MB_OK);
		exit(-1);
	}
	fscanf(file, "%s %d %d %d %d %d %d %d", player1.name, &player1.level, &player1.MAXhp, &player1.hp, &player1.attack, &player1.defence, &player1.exp, &player1.money);
	fclose(file);
	fileencrypt("player.txt", key, 1);
	SetFileAttributes(TEXT("player.txt"), FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_HIDDEN
		| FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_ARCHIVE);
	drawthePlayInformation();




}

/*
	��������deleteItem
	����ֵ��NULL
	������struct bagList* node
	ȫ�ֲ�����NULL
	���ã�ɾ����ǰ�ڵ�
*/
void deleteItem(struct bagList* node)
{
	struct bagList* newNode;
	newNode = node->preview;
	newNode->next = node->next;
	free(node);

}