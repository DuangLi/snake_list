#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<time.h>
#include<conio.h>

#define LENGTH 80
#define WIDTH 30
#define WALL "��"
#define SNAKENODE "��"
#define FOOD "��"
#define SLOWFOOD "��"
#define SLOWFOODNUM 5
#define GRESS "��"
#define GRESSNUM 6

/*ÿһ���߽ڵ���������*/
typedef struct SnakeNode {
	int x;
	int y;
	struct SnakeNode* next;
	struct SnakeNode* prev;//�̳�������
}Snake;

/*��ʵ����*/
typedef struct Food {
	int x;
	int y;
}Food;

/*���ٹ�����*/
typedef struct SFood {
	int x;
	int y;
	struct SFood* next;
}SFood;

/*��������*/
typedef struct Gress {
	int x;
	int y;
	struct Gress* next;
}Gress;

/*����̨�����ת*/
void gotoxy(int x, int y);

/*�ͷ��ڴ�*/
void Myfree(Snake* head, Food* food, SFood* sfoodhead, Gress* gressfood);

/*���ɵ�ͼ�߽�*/
void PrintMap(void);

/*���ɼ��ٹ�*/
SFood* PrintSFood(const Snake* head, Gress* gresshead, const Food* food, SFood* sfoodhead);

/*���ɶ���*/
Gress* PrintGress(const Snake* head, Gress* gress, const Food* food);

/*���������ʵ*/
Food* PrintFristFood(const Snake* head);

/*���ɹ�ʵ*/
void PrintFood(const Snake* head, Food* food, const Gress* gresshead);

/*��ʼ���ߣ��߳���Ϊ4*/
Snake* InitializeSnake(Snake* head, int x0, int y0);

/*��ӡÿ���ƶ������*/
void PrintSnake(const Snake* head);

/*�ж�������*/
int CheckDeath(const Snake* head);

/*���߶�����*/
int Move(int kb, Snake* head, Food* food, int ifeat, const Gress* gresshead, const SFood* sfoodhead);