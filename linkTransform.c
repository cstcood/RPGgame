#include<stdlib.h>
#include"struct.h"
struct  itemList* machItem(int ID);//通过ID找到物品
char* getItemName(int ID);//获取物品的名称
int getItemRange(int ID);//物品的效果范围
int getItemEffect(int ID);//效果种类 
int getmoney(int ID);//获取物品售价

struct  itemList* itemhead;
struct commodityList* shophead;
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
char* getItemName(int ID)
{
	return machItem(ID)->item1.name;


}
int getItemEffect(int ID)
{
	return machItem(ID)->item1.effect;


}
int getItemRange(int ID)
{

	return machItem(ID)->item1.range;
}
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