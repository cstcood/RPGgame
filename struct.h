#pragma once
typedef struct
{
	char name[20]; //��ɫ��
	int level; //�ȼ�
	int MAXhp;//�������
	int hp;//����
	int attack;//����
	int defence;//����
	int exp;//����
	int money;//Ǯ


}player;
typedef struct
{
	int ID;//���
	char name[20];//����
	int effect;//Ч������
	int range;//��Χ
}item;
struct itemList
{
	item item1;//��ǰ��Ʒ
	struct itemList* next;//��һ����Ʒ �ĵ�ַ
};
typedef struct
{
	int ID;//��Ʒ�ı��
	int money;//��Ʒ��Ǯ

}commodity;
struct  commodityList
{
	commodity commodity1;//��ǰ��Ʒ
	struct commodityList* next;//��һ����Ʒ�ĵ�ַ
};
struct bagList
{
	int ID;//��ǰ��Ʒ���
	int num;//��ǰ��Ʒ����
	struct bagList* next;//��һ����Ʒ�ĵ�ַ
	struct bagList* preview;//��һ����Ʒ�ĵ�ַ

};
typedef struct {
	int ID;//����ID
	char name[20];//������
	int level;//�ȼ�
	int MAXhp;//���HP
	int hp;//��ǰhp
	int attack;//��ǰ����
	int defence;//��ǰ����
	int exp;//����
	int money;//ս��ʤ�����ý�Ǯ

}enemy;
struct enemyList
{
	struct enemyList* next;//��һ�������ַ
	enemy enemy;//��ǰ������Ϣ
};
