#include<stdlib.h>
#include"struct.h"
struct  itemList* machItem(int ID);//ͨ��ID�ҵ���Ʒ
char* getItemName(int ID);//��ȡ��Ʒ������
int getItemRange(int ID);//��Ʒ��Ч����Χ
int getItemEffect(int ID);//Ч������ 
int getmoney(int ID);//��ȡ��Ʒ�ۼ�

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