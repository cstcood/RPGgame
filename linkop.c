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
	函数名：init
	返回值：NULL
	参数：NULL
	作用：总体初始化（读取）各个文件
*/
void init()
{

	initEnemy();
	initshop();
	inititem();
	initbag('k');
	
}

/*
	函数名：initEnemy
	返回值：NULL
	参数：NULL 
	全局参数：enemyhead
	作用：从文件（enemy.txt）读取对应的敌人数据
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
	函数名：initshop
	返回值：NULL
	参数：NULL
	全局参数：shophead
	作用：从文件（shop.txt）读取对应的商店数据
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
	函数名：inititem
	返回值：NULL
	参数：NULL
	全局参数：itemhead
	作用：从文件（item.txt）读取对应的物品数据
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
	函数名：initbag
	返回值：NULL
	参数：key
	全局参数：baghaed
	作用：通过key解密文件读入背包文件
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
	函数名：Saveinfomation
	返回值：NULL
	参数：key
	全局参数：NULL
	作用：根据key加密数据并将角色信息存入文件
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
	函数名：Savebag
	返回值：NULL
	参数：key
	全局参数：baghaed
	作用：根据key加密数据并将背包信息存入文件
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
	函数名：loadThePlayerInformation
	返回值：NULL
	参数：key
	全局参数：NULL
	作用：根据key解密数据读取角色信息
*/
void loadThePlayerInformation(char key) {
	FILE* file;
	SetFileAttributes(TEXT("player.txt"), FILE_ATTRIBUTE_NORMAL);
	fileencrypt("player.txt", key, 0);
	file = fopen("player.txt", "r");
	if (file == 0) {
		MessageBox(NULL, TEXT("游戏文件破坏"), TEXT("错误"), MB_OK);
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
	函数名：deleteItem
	返回值：NULL
	参数：struct bagList* node
	全局参数：NULL
	作用：删除当前节点
*/
void deleteItem(struct bagList* node)
{
	struct bagList* newNode;
	newNode = node->preview;
	newNode->next = node->next;
	free(node);

}