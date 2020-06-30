#include<stdlib.h>
#include"struct.h"
struct  itemList* machItem(int ID);//通过ID找到物品
char* getItemName(int ID);//获取物品的名称
int getItemRange(int ID);//物品的效果范围
int getItemEffect(int ID);//效果种类 
int getmoney(int ID);//获取物品售价

struct  itemList* itemhead;
struct commodityList* shophead;

/*
	函数名：machItem
	返回值：struct  itemList*
	参数：int ID
	全局参数：NULL
	作用：通过ID获取对用的物品的信息
*/
struct  itemList* machItem(int ID)
{
	struct  itemList* newNode = itemhead->next;
	while (newNode != NULL)
	{
		if (ID == newNode->item1.ID)
		{

			return newNode;
		}
		newNode = newNode->next;
	}
	return NULL;

}

/*
	函数名：getItemName
	返回值：char*
	参数：int ID
	全局参数：NULL
	作用：通过ID获取对用的物品的名称
*/
char* getItemName(int ID)
{
	return machItem(ID)->item1.name;


}

/*
	函数名：getItemEffect
	返回值：int
	参数：int ID
	全局参数：NULL
	作用：通过ID获取对用的物品的效果
*/
int getItemEffect(int ID)
{
	return machItem(ID)->item1.effect;


}

/*
	函数名：getItemRange
	返回值：int
	参数：int ID
	全局参数：NULL
	作用：通过ID获取对用的物品的效果范围
*/
int getItemRange(int ID)
{

	return machItem(ID)->item1.range;
}

/*
	函数名：getmoney
	返回值：int
	参数：int ID
	全局参数：NULL
	作用：通过ID获取对用的物品的金钱
*/
int getmoney(int ID)
{
	struct  commodityList* newNode = shophead->next;
	while (newNode != NULL)
	{
		if (ID == newNode->commodity1.ID)
		{

			return newNode->commodity1.money;
		}
		newNode = newNode->next;
	}
	return 0;

}