#include "snake.h"

void gotoxy(int x, int y)
{
	COORD loc;
	loc.X = x;
	loc.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), loc);
}

void Myfree(Snake* head, Food* food, SFood* sfoodhead, Gress* gresshead)
{
	free(food);
	void* temp;
	while (head != NULL)
	{
		temp = head->next;
		free(head);
		head = temp;
	}
	while (gresshead != NULL)
	{
		temp = gresshead->next;
		free(gresshead);
		gresshead = temp;
	}
	while (sfoodhead != NULL)
	{
		temp = sfoodhead->next;
		free(sfoodhead);
		sfoodhead = temp;
	}
}

void PrintMap(void)
{
	int i;
	for (i = 0; i <= LENGTH - 2; i += 2)//生成水平边界
	{
		gotoxy(i, 0);
		printf(WALL);
		gotoxy(i, WIDTH - 1);
		printf(WALL);
	}

	for (i = 1; i <= WIDTH - 2; i++)//生成竖直边界
	{
		gotoxy(0, i);
		printf(WALL);
		gotoxy(LENGTH-2, i);
		printf(WALL);
	}

	/*打印相关游戏信息*/
	gotoxy(81, 0);
	printf("聪明的小蛇1.0");
	gotoxy(81, 2);
	printf("制作者：小李同学");
	gotoxy(81, 4);
	printf("您当前的分数为：");
	gotoxy(81, 6);
	printf("您当前的步数为：");
	gotoxy(81, 9);
	printf("道具列表");
	gotoxy(81, 11);
	printf(GRESS);
	printf("：毒草，吃到就死");
	gotoxy(81, 13);
	printf(SLOWFOOD);
	printf("：减速果，降低速度");
	gotoxy(81, 15);
	printf(FOOD);
	printf("：普通果实，蛇身增长，速度增加，10分");
}

Gress* PrintGress(const Snake* head, Gress* gresshead, const Food* food)
{
	Snake* p = head;
	Gress* current;
	Gress* gress;
	int tempx, tempy;
	int flag;
	int k = 1;
	srand((unsigned)(time(NULL)));
	while (k <= GRESSNUM)
	{
		do
		{
			tempx = rand() % (LENGTH - 4 - 2 + 1) + 2;
			tempy = rand() % (WIDTH - 2 - 1 + 1) + 1;
			flag = tempx % 2;					//保证初始毒草与蛇头对齐，防止吃到半个毒草
			
			while (p != NULL && !flag)//防止和蛇身重叠
			{
				if (tempx == p->x && tempy == p->y) flag = 1;
				p = p->next;
			}

			if (tempx == food->x && tempy == food->y) flag = 1;//防止和食物重叠
		} while (flag);//直至生成合格毒草

		current = (Gress*)malloc(sizeof(Gress));
		if (gresshead == NULL)
			gresshead = current;
		else
			gress->next = current;
		current->x = tempx;
		current->y = tempy;
		current->next = NULL;
		gress = current;
		gotoxy(tempx, tempy);
		printf(GRESS);
		k++;
	}
	return gresshead;
}

SFood* PrintSFood(const Snake* head, Gress* gresshead, const Food* food, SFood* sfoodhead)
{
	Snake* p1 = head;
	Gress* current;
	Gress* p2 = gresshead;
	SFood* sfood;
	int tempx, tempy;
	int flag;
	int k = 1;
	srand((unsigned)(time(NULL) + 1));
	while (k <= SLOWFOODNUM)
	{
		do
		{
			tempx = rand() % (LENGTH - 4 - 2 + 1) + 2;
			tempy = rand() % (WIDTH - 2 - 1 + 1) + 1;
			flag = tempx % 2;					//保证初始毒草与蛇头对齐，防止吃到半个毒草

			while (p1 != NULL && !flag)//防止和蛇身重叠
			{
				if (tempx == p1->x && tempy == p1->y) flag = 1;
				p1 = p1->next;
			}

			while (p2 != NULL && !flag)//防止和毒草重叠
			{
				if (tempx == p2->x && tempy == p2->y) flag = 1;
				p2 = p2->next;
			}
			if (tempx == food->x && tempy == food->y) flag = 1;//防止和食物重叠
		} while (flag);//直至生成合格毒草

		current = (SFood*)malloc(sizeof(SFood));
		if (sfoodhead == NULL)
			sfoodhead = current;
		else
			sfood->next = current;
		current->x = tempx;
		current->y = tempy;
		current->next = NULL;
		sfood = current;
		gotoxy(tempx, tempy);
		printf(SLOWFOOD);
		k++;
	}
	return sfoodhead;
}

Snake* InitializeSnake(Snake* head, int x0, int y0)
{
	Snake* current;
	Snake* pre;
	for (int i = 1; i <= 4; i++)
	{
		current = (Snake*)malloc(sizeof(Snake));
		if (head == NULL)		//构建蛇头
			head = current;
		else					//构建下一个蛇身
			pre->next = current;

		if (head == current)
			current->prev = NULL;
		else
			current->prev = pre;
		current->next = NULL;
		current->x = x0;
		current->y = y0 + i - 1;
		pre = current;
	}
	return head;
}

void PrintSnake(const Snake* head)
{
	extern speed;
	Snake* current = head;
	while (current != NULL)
	{
		gotoxy(current->x, current->y);
		printf(SNAKENODE);
		current = current->next;
	}
	Sleep(speed);//可通过改变时间调整速度
}

Food* PrintFristFood(const Snake* head, Food* food)
{
	Snake* p = head;
	food = (Food*)malloc(sizeof(Food));
	int tempx, tempy;
	int flag;
	srand((unsigned)(time(NULL)));
	do
	{
		tempx = rand() % (LENGTH - 4 - 2 + 1) + 2;
		tempy = rand() % (WIDTH - 2 - 1 + 1) + 1;
		flag = tempx % 2;					//保证初始食物与蛇头对齐，防止吃到半个食物
		while (p != NULL && !flag)
		{
			if (tempx == p->x && tempy == p->y) flag = 1;
			p = p->next;
		}
	} while (flag);//直至生成合格食物
	food->x = tempx;
	food->y = tempy;
	gotoxy(tempx, tempy);
	printf(FOOD);
	return food;
}

void PrintFood(const Snake* head, Food* food, const Gress* gresshead, const SFood* sfoodhead)
{
	Snake* p1 = head;
	Gress* p2 = gresshead;
	SFood* p3 = sfoodhead;
	int tempx, tempy;
	int flag;
	srand((unsigned)(time(NULL)));
	do
	{
		tempx = rand() % (LENGTH - 4 - 2 + 1) + 2;
		tempy = rand() % (WIDTH - 2 - 1 + 1) + 1;
		flag = tempx % 2;					//保证初始食物与蛇头对齐，防止吃到半个食物
		while (p1 != NULL && !flag)
		{
			if (tempx == p1->x && tempy == p1->y) flag = 1;
			p1 = p1->next;
		}

		while (p2 != NULL && !flag)
		{
			if (tempx == p2->x && tempy == p2->y) flag = 1;
			p2 = p2->next;
		}

		while (p3 != NULL && !flag)
		{
			if (tempx == p3->x && tempy == p3->y) flag = 1;
			p3 = p3->next;
		}
	} while (flag);//直至生成合格食物
	gotoxy(tempx, tempy);
	food->x = tempx;
	food->y = tempy;
	printf(FOOD);
}

int CheckDeath(const Snake* head, const Gress* gresshead)
{
	int flag = 1;
	if (head->next == NULL) flag = 0;//蛇身长度为零
	else if (head->x <= 0 || head->x >= LENGTH - 1) flag = 0;//撞击左右边界
	else if (head->y <= 0 || head->y >= WIDTH - 1) flag = 0;//撞击上下边界
	else//咬到自己 
	{
		Snake* temp;
		temp = head->next;
		while (temp != NULL)
		{
			if (temp->x == head->x && temp->y == head->y)
			{
				flag = 0;
				break;
			}
			temp = temp->next;
		}
	}
	if (flag)//如果前几种都不是，判有没有吃到毒草（不然不判，提高效率）
	{
		Gress* temp;
		temp = gresshead;
		while (temp != NULL)
		{
			if (temp->x == head->x && temp->y == head->y)
			{
				flag = 0;
				break;
			}
			temp = temp->next;
		}
	}
	return flag;
}

int Move(int kb, Snake* head, Food* food,int ifeat, const Gress* gresshead, const SFood* sfoodhead)
{

	/*获取移动方向*/
	int prev_kb = kb;
	int flag = 0, ch;
	/*if(!kbhit())
	{
		while(!kbhit())

	如果写成这个样子，函数会在while内部的getch()函数处卡住，导致蛇的移动变成一令一动
	造成这一现象的原因是kbhit()是非阻塞函数，getch()是阻塞函数
	所以为了保证蛇的连贯移动，需保证kbhit()和getch()必须同时满足运行条件
	换言之，必须在键盘有输入时进入循环获取方向
	*/

	if (kbhit() != 0)
	{
		while (!kbhit() == 0)
		{
			ch = getch();
			ch = getch();
			switch (ch) {
			case 72:
				if (prev_kb != 80) kb = ch; break;
			case 80:
				if (prev_kb != 72) kb = ch; break;
			case 75:
				if (prev_kb != 77) kb = ch; break;
			case 77:
				if (prev_kb != 75) kb = ch; break;
			}
			break;
		}
	}
 	
	/*移动蛇身*/
	Snake* now=head;

	/*判断是否吃到食物*/
	switch (kb)
	{
	case 72:
		if (head->y - 1 == food->y && head->x == food->x) ifeat = 1;
		break;
	case 80:
		if (head->y + 1 == food->y && head->x == food->x) ifeat = 1;
		break;
	case 75:
		if (head->x - 2 == food->x && head->y == food->y) ifeat = 1;
		break;
	case 77:
		if (head->x + 2 == food->x && head->y == food->y) ifeat = 1;
		break;
	}

	/*如果吃到食物，蛇身长度+1，不进行其他操作*/
	if (ifeat)
	{
		/*增加分数*/
		extern int score;
		score += 10;

		/*增加蛇身*/
		Snake* current=head;
		Snake* temp;
		temp = (Snake*)malloc(sizeof(Snake));
		while (current->next != NULL)
			current = current->next;
		current->next = temp;
		temp->x = current->x;
		temp->y = current->y;
		temp->prev = current;
		temp->next = NULL;

		/*从尾到头依次取代*/
		temp = temp->prev;
		while (temp->prev != NULL)
		{
			temp->x = temp->prev->x;
			temp->y = temp->prev->y;
			temp = temp->prev;
		}
		switch (kb)
		{
			/*实际上只移动蛇头，之后的每一节蛇身（链节）取代上一节蛇身（链节）
			*也正因如此，要从最后一节开始往前取代（否则只剩一个蛇头）
			*上:72
			*下:80
			*左:75
			*右:77
			*/
		case 72:
			head->y--;
			head->x = head->next->x;
			break;
		case 80:
			head->y++;
			head->x = head->next->x;
			break;
		case 75:
			head->x -= 2;
			head->y = head->next->y;
			break;
		case 77:
			head->x += 2;
			head->y = head->next->y;
			break;
		}
	}
	/*如果没吃到食物，删除蛇尾*/
	else
	{
		while (now->next != NULL)
		{
			now = now->next;
		}
		gotoxy(now->x, now->y);
		printf("  ");

		/*从尾到头依次取代*/
		while (now->prev != NULL)
		{
			now->x = now->prev->x;
			now->y = now->prev->y;
			now = now->prev;
		}
		switch (kb)
		{
			/*实际上只移动蛇头，之后的每一节蛇身（链节）取代上一节蛇身（链节）
			*也正因如此，要从最后一节开始往前取代（否则只剩一个蛇头）
			*上:72
			*下:80
			*左:75
			*右:77
			*/
		case 72:
			head->y--;
			head->x = head->next->x;
			break;
		case 80:
			head->y++;
			head->x = head->next->x;
			break;
		case 75:
			head->x -= 2;
			head->y = head->next->y;
			break;
		case 77:
			head->x += 2;
			head->y = head->next->y;
			break;
		}
	}
	/*每次判断是否吃到食物，若吃到食物，需重置ifeat，并且重新生成食物*/
	if (ifeat)
	{
		extern speed;
		speed -= 3;
		ifeat = 0;
		PrintFood(head, food, gresshead, sfoodhead);//放在蛇身改变之后，确保食物生成不会出现在新蛇头或新蛇尾处
	}
	else//判断是否吃到减速果，吃到则减速
	{
		extern speed;
		SFood* temp = sfoodhead;
		while (temp != NULL)
		{
			if (temp->x == head->x && temp->y == head->y) speed += 60;
			temp = temp->next;
		}
	}
	return kb;
}