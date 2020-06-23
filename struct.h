#pragma once
typedef struct
{
	char name[20]; //角色名
	int level; //等级
	int MAXhp;//最大生命
	int hp;//生命
	int attack;//攻击
	int defence;//防御
	int exp;//经验
	int money;//钱


}player;
typedef struct
{
	int ID;//编号
	char name[20];//姓名
	int effect;//效果类型
	int range;//范围
}item;
struct itemList
{
	item item1;//当前物品
	struct itemList* next;//下一个物品 的地址
};
typedef struct
{
	int ID;//商品的编号
	int money;//商品的钱

}commodity;
struct  commodityList
{
	commodity commodity1;//当前商品
	struct commodityList* next;//下一个商品的地址
};
struct bagList
{
	int ID;//当前物品编号
	int num;//当前商品数量
	struct bagList* next;//下一个商品的地址
	struct bagList* preview;//上一个商品的地址

};
typedef struct {
	int ID;//怪物ID
	char name[20];//怪物名
	int level;//等级
	int MAXhp;//最大HP
	int hp;//当前hp
	int attack;//当前攻击
	int defence;//当前防御
	int exp;//经验
	int money;//战斗胜利后获得金钱

}enemy;
struct enemyList
{
	struct enemyList* next;//下一个怪物地址
	enemy enemy;//当前怪物信息
};
