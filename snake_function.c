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
	for (i = 0; i <= LENGTH - 2; i += 2)//����ˮƽ�߽�
	{
		gotoxy(i, 0);
		printf(WALL);
		gotoxy(i, WIDTH - 1);
		printf(WALL);
	}

	for (i = 1; i <= WIDTH - 2; i++)//������ֱ�߽�
	{
		gotoxy(0, i);
		printf(WALL);
		gotoxy(LENGTH-2, i);
		printf(WALL);
	}

	/*��ӡ�����Ϸ��Ϣ*/
	gotoxy(81, 0);
	printf("������С��1.0");
	gotoxy(81, 2);
	printf("�����ߣ�С��ͬѧ");
	gotoxy(81, 4);
	printf("����ǰ�ķ���Ϊ��");
	gotoxy(81, 6);
	printf("����ǰ�Ĳ���Ϊ��");
	gotoxy(81, 9);
	printf("�����б�");
	gotoxy(81, 11);
	printf(GRESS);
	printf("�����ݣ��Ե�����");
	gotoxy(81, 13);
	printf(SLOWFOOD);
	printf("�����ٹ��������ٶ�");
	gotoxy(81, 15);
	printf(FOOD);
	printf("����ͨ��ʵ�������������ٶ����ӣ�10��");
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
			flag = tempx % 2;					//��֤��ʼ��������ͷ���룬��ֹ�Ե��������
			
			while (p != NULL && !flag)//��ֹ�������ص�
			{
				if (tempx == p->x && tempy == p->y) flag = 1;
				p = p->next;
			}

			if (tempx == food->x && tempy == food->y) flag = 1;//��ֹ��ʳ���ص�
		} while (flag);//ֱ�����ɺϸ񶾲�

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
			flag = tempx % 2;					//��֤��ʼ��������ͷ���룬��ֹ�Ե��������

			while (p1 != NULL && !flag)//��ֹ�������ص�
			{
				if (tempx == p1->x && tempy == p1->y) flag = 1;
				p1 = p1->next;
			}

			while (p2 != NULL && !flag)//��ֹ�Ͷ����ص�
			{
				if (tempx == p2->x && tempy == p2->y) flag = 1;
				p2 = p2->next;
			}
			if (tempx == food->x && tempy == food->y) flag = 1;//��ֹ��ʳ���ص�
		} while (flag);//ֱ�����ɺϸ񶾲�

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
		if (head == NULL)		//������ͷ
			head = current;
		else					//������һ������
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
	Sleep(speed);//��ͨ���ı�ʱ������ٶ�
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
		flag = tempx % 2;					//��֤��ʼʳ������ͷ���룬��ֹ�Ե����ʳ��
		while (p != NULL && !flag)
		{
			if (tempx == p->x && tempy == p->y) flag = 1;
			p = p->next;
		}
	} while (flag);//ֱ�����ɺϸ�ʳ��
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
		flag = tempx % 2;					//��֤��ʼʳ������ͷ���룬��ֹ�Ե����ʳ��
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
	} while (flag);//ֱ�����ɺϸ�ʳ��
	gotoxy(tempx, tempy);
	food->x = tempx;
	food->y = tempy;
	printf(FOOD);
}

int CheckDeath(const Snake* head, const Gress* gresshead)
{
	int flag = 1;
	if (head->next == NULL) flag = 0;//������Ϊ��
	else if (head->x <= 0 || head->x >= LENGTH - 1) flag = 0;//ײ�����ұ߽�
	else if (head->y <= 0 || head->y >= WIDTH - 1) flag = 0;//ײ�����±߽�
	else//ҧ���Լ� 
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
	if (flag)//���ǰ���ֶ����ǣ�����û�гԵ����ݣ���Ȼ���У����Ч�ʣ�
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

	/*��ȡ�ƶ�����*/
	int prev_kb = kb;
	int flag = 0, ch;
	/*if(!kbhit())
	{
		while(!kbhit())

	���д��������ӣ���������while�ڲ���getch()��������ס�������ߵ��ƶ����һ��һ��
	�����һ�����ԭ����kbhit()�Ƿ�����������getch()����������
	����Ϊ�˱�֤�ߵ������ƶ����豣֤kbhit()��getch()����ͬʱ������������
	����֮�������ڼ���������ʱ����ѭ����ȡ����
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
 	
	/*�ƶ�����*/
	Snake* now=head;

	/*�ж��Ƿ�Ե�ʳ��*/
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

	/*����Ե�ʳ�������+1����������������*/
	if (ifeat)
	{
		/*���ӷ���*/
		extern int score;
		score += 10;

		/*��������*/
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

		/*��β��ͷ����ȡ��*/
		temp = temp->prev;
		while (temp->prev != NULL)
		{
			temp->x = temp->prev->x;
			temp->y = temp->prev->y;
			temp = temp->prev;
		}
		switch (kb)
		{
			/*ʵ����ֻ�ƶ���ͷ��֮���ÿһ���������ڣ�ȡ����һ���������ڣ�
			*Ҳ������ˣ�Ҫ�����һ�ڿ�ʼ��ǰȡ��������ֻʣһ����ͷ��
			*��:72
			*��:80
			*��:75
			*��:77
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
	/*���û�Ե�ʳ�ɾ����β*/
	else
	{
		while (now->next != NULL)
		{
			now = now->next;
		}
		gotoxy(now->x, now->y);
		printf("  ");

		/*��β��ͷ����ȡ��*/
		while (now->prev != NULL)
		{
			now->x = now->prev->x;
			now->y = now->prev->y;
			now = now->prev;
		}
		switch (kb)
		{
			/*ʵ����ֻ�ƶ���ͷ��֮���ÿһ���������ڣ�ȡ����һ���������ڣ�
			*Ҳ������ˣ�Ҫ�����һ�ڿ�ʼ��ǰȡ��������ֻʣһ����ͷ��
			*��:72
			*��:80
			*��:75
			*��:77
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
	/*ÿ���ж��Ƿ�Ե�ʳ����Ե�ʳ�������ifeat��������������ʳ��*/
	if (ifeat)
	{
		extern speed;
		speed -= 3;
		ifeat = 0;
		PrintFood(head, food, gresshead, sfoodhead);//��������ı�֮��ȷ��ʳ�����ɲ������������ͷ������β��
	}
	else//�ж��Ƿ�Ե����ٹ����Ե������
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