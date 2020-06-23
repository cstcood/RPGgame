#pragma once
#include"struct.h"
void initEnemy();
void initshop();
void inititem();
void loadThePlayerInformation(char key);
void initbag(char key);
void Saveinfomation(char key);
void Savebag(char key);
void init();
void deleteItem(struct bagList* node);