#include "snake.h"

int kb = 72;
int ifeat = 0;
int score, step, speed;

void main(void)
{
	speed = 200;
	step = 0;
	score = 0;
	PrintMap();
	Snake* head = NULL;
	Food* food = NULL;
	Gress* gresshead = NULL;
	SFood* sfoodhead = NULL;
	head = InitializeSnake(head, LENGTH / 2, WIDTH / 2);
	food = PrintFristFood(head);
	gresshead = PrintGress(head, gresshead, food);
	sfoodhead = PrintSFood(head, gresshead, food, sfoodhead);
	while (1)
	{
		PrintSnake(head);
		kb = Move(kb, head, food, ifeat, gresshead, sfoodhead);
		if (!CheckDeath(head, gresshead))
			break;
		step++;
		gotoxy(105, 4);
		printf("%d", score);
		gotoxy(105, 6);
		printf("%d", step);
	}
	gotoxy(0, 35);
	system("pause");
	printf("over");
	
	/*ÊÍ·ÅÄÚ´æ*/
	Myfree(head, food, sfoodhead, gresshead);
}