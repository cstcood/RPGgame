//固定回血
#include"struct.h"
player player1;
int recoverRatrHP(int rate);//2
int recoverFixHP(int hp);
int recoverFixHP(int hp)//1 
{
	if (player1.hp == player1.MAXhp) return 0;
	if (player1.hp + hp > player1.MAXhp)
		player1.hp = player1.MAXhp;
	else
		player1.hp += hp;
	return 1;

}
//比例回血
int recoverRatrHP(int rate)//2
{
	int recoverHP = (int)(player1.MAXhp * (double)rate / 100);
	if (player1.hp == player1.MAXhp) return 0;
	if (player1.hp + recoverHP > player1.MAXhp)
		player1.hp = player1.MAXhp;
	else
		player1.hp += recoverHP;
	return 1;

}