#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<time.h>
#include<conio.h>

#define LENGTH 80
#define WIDTH 30
#define WALL "□"
#define SNAKENODE "■"
#define FOOD "★"
#define SLOWFOOD "☆"
#define SLOWFOODNUM 5
#define GRESS "▲"
#define GRESSNUM 6

/*每一个蛇节点的相关属性*/
typedef struct SnakeNode {
	int x;
	int y;
	struct SnakeNode* next;
	struct SnakeNode* prev;//继承坐标用
}Snake;

/*果实坐标*/
typedef struct Food {
	int x;
	int y;
}Food;

/*减速果坐标*/
typedef struct SFood {
	int x;
	int y;
	struct SFood* next;
}SFood;

/*毒草坐标*/
typedef struct Gress {
	int x;
	int y;
	struct Gress* next;
}Gress;

/*控制台光标跳转*/
void gotoxy(int x, int y);

/*释放内存*/
void Myfree(Snake* head, Food* food, SFood* sfoodhead, Gress* gressfood);

/*生成地图边界*/
void PrintMap(void);

/*生成减速果*/
SFood* PrintSFood(const Snake* head, Gress* gresshead, const Food* food, SFood* sfoodhead);

/*生成毒草*/
Gress* PrintGress(const Snake* head, Gress* gress, const Food* food);

/*生成最初果实*/
Food* PrintFristFood(const Snake* head);

/*生成果实*/
void PrintFood(const Snake* head, Food* food, const Gress* gresshead);

/*初始化蛇，蛇长度为4*/
Snake* InitializeSnake(Snake* head, int x0, int y0);

/*打印每次移动后的蛇*/
void PrintSnake(const Snake* head);

/*判定蛇死亡*/
int CheckDeath(const Snake* head);

/*让蛇动起来*/
int Move(int kb, Snake* head, Food* food, int ifeat, const Gress* gresshead, const SFood* sfoodhead);