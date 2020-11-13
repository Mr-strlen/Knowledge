// ����һ��2048��ʵ�֣���Ҫʹ��ncurses�⣬�������ֻ֧��Linuxϵͳ�����������������ϰ
// ����γ�����Ϊ��https://www.shiyanlou.com/courses/155
#include<stdio.h>
#include<stdlib.h>
#include<curses.h>
#include<unistd.h>
#include<signal.h>
#include<time.h>

// ��Ϸ��������һ�� 4*4 �� 16 ����ʹ�ö�ά������б�ʾ���� 0 ��ʾ�ո�
int a[4][4] = { 0 };
// 16 �����пո�ĸ���
int empty;
int old_y, old_x;

void draw();  // ���ڻ�����Ϸ����
void play();  // ��Ϸ���е��߼�����
void init();  // ��ʼ���������������һЩ��Ҫ�ĳ�ʼ������
void draw_one(int y, int x);  // ���Ƶ�������
void cnt_value(int *new_y, int *new_x);
int game_over();  // ������Ϸ
int cnt_one(int y, int x);

int main(){
	init();
	play();
	game_over();

	return 0;
}

void init()
{
	int x, y;

	initscr();
	cbreak();
	noecho();
	curs_set(0);

	empty = 15;
	srand(time(0));
	x = rand() % 4;
	y = rand() % 4;
	a[y][x] = 2;
	draw();
}

void draw()
{
	int n, m, x, y;
	char c[4] = { '0', '0', '0', '0' };
	clear();

	for (n = 0; n < 9; n += 2)   //���ƺ��ߣ�n�����У�m������
	{
		for (m = 0; m < 21; m++)
		{
			move(n, m);
			addch('-');
			refresh();
		}
	}
	for (m = 0; m < 22; m += 5)  //��������
	{
		for (n = 1; n < 8; n++)
		{
			move(n, m);
			addch('|');
			refresh();
		}
	}
	for (y = 0; y < 4; y++)     //��������
	{
		for (x = 0; x < 4; x++)
		{
			draw_one(y, x);
		}
	}
}

void draw_one(int y, int x)
{
	int i, m, k, j;
	char c[5] = { 0x00 };
	i = a[y][x];
	m = 0;
	while (i > 0)
	{
		j = i % 10;
		c[m++] = j + '0';
		i = i / 10;
	}
	m = 0;
	k = (x + 1) * 5 - 1;
	while (c[m] != 0x00)
	{
		move(2 * y + 1, k);
		addch(c[m++]);
		k--;
	}
}

void play()
{
	int x, y, i, new_x, new_y, temp;
	int old_empty, move;
	char ch;

	while (1)
	{
		move = 0;
		old_empty = empty;
		ch = getch();
		switch (ch) {
		case 97:    //����  a
		case 104:   // h
		case 68:    // ���Ʒ����
			for (y = 0; y < 4; y++)
				for (x = 0; x < 4;)
				{
					if (a[y][x] == 0)
					{
						x++;
						continue;
					}
					else
					{
						for (i = x + 1; i < 4; i++)
						{
							if (a[y][i] == 0)
							{
								continue;
							}
							else
							{
								if (a[y][x] == a[y][i])
								{
									a[y][x] += a[y][i];
									a[y][i] = 0;
									empty++;
									break;
								}
								else
								{
									break;
								}
							}
						}
						x = i;
					}
				}
			for (y = 0; y < 4; y++)
				for (x = 0; x < 4; x++)
				{
					if (a[y][x] == 0)
					{
						continue;
					}
					else
					{
						for (i = x; (i > 0) && (a[y][i - 1] == 0); i--)
						{
							a[y][i - 1] = a[y][i];
							a[y][i] = 0;
							move = 1;
						}
					}
				}
			break;
		case 100:   //���� d
		case 108:   // l
		case 67:    //���Ʒ����
			for (y = 0; y < 4; y++)
				for (x = 3; x >= 0;)
				{
					if (a[y][x] == 0)
					{
						x--;
						continue;
					}
					else
					{
						for (i = x - 1; i >= 0; i--)
						{
							if (a[y][i] == 0)
							{
								continue;
							}
							else if (a[y][x] == a[y][i])
							{
								a[y][x] += a[y][i];
								a[y][i] = 0;
								empty++;
								break;
							}
							else
							{
								break;
							}
						}
						x = i;
					}
				}
			for (y = 0; y < 4; y++)
				for (x = 3; x >= 0; x--)
				{
					if (a[y][x] == 0)
					{
						continue;
					}
					else
					{
						for (i = x; (i < 3) && (a[y][i + 1] == 0); i++)
						{
							a[y][i + 1] = a[y][i];
							a[y][i] = 0;
							move = 1;
						}
					}
				}
			break;
		case 119:   //���� w
		case 107:   //k
		case 65:    //���Ʒ����
			for (x = 0; x < 4; x++)
				for (y = 0; y < 4;)
				{
					if (a[y][x] == 0)
					{
						y++;
						continue;
					}
					else
					{
						for (i = y + 1; i < 4; i++)
						{
							if (a[i][x] == 0)
							{
								continue;
							}
							else if (a[y][x] == a[i][x])
							{
								a[y][x] += a[i][x];
								a[i][x] = 0;
								empty++;
								break;
							}
							else
							{
								break;
							}
						}
						y = i;
					}
				}
			for (x = 0; x < 4; x++)
				for (y = 0; y < 4; y++)
				{
					if (a[y][x] == 0)
					{
						continue;
					}
					else
					{
						for (i = y; (i > 0) && (a[i - 1][x] == 0); i--)
						{
							a[i - 1][x] = a[i][x];
							a[i][x] = 0;
							move = 1;
						}
					}
				}
			break;
		case 115:   //���� s
		case 106:   //j
		case 66:    //���Ʒ����
			for (x = 0; x < 4; x++)
				for (y = 3; y >= 0;)
				{
					if (a[y][x] == 0)
					{
						y--;
						continue;
					}
					else
					{
						for (i = y - 1; i >= 0; i--)
						{
							if (a[i][x] == 0)
							{
								continue;
							}
							else if (a[y][x] == a[i][x])
							{
								a[y][x] += a[i][x];
								a[i][x] = 0;
								empty++;
								break;
							}
							else
							{
								break;
							}
						}
						y = i;
					}
				}
			for (x = 0; x < 4; x++)
				for (y = 3; y >= 0; y--)
				{
					if (a[y][x] == 0)
					{
						continue;
					}
					else
					{
						for (i = y; (i < 3) && (a[i + 1][x] == 0); i++)
						{
							a[i + 1][x] = a[i][x];
							a[i][x] = 0;
							move = 1;
						}
					}
				}
			break;
		case 'Q':
		case 'q':
			game_over();
			break;
		default:
			continue;
			break;
		}
		if (empty <= 0)
			game_over();
		if ((empty != old_empty) || (move == 1))
		{
			do{
				new_x = rand() % 4;
				new_y = rand() % 4;
			} while (a[new_y][new_x] != 0);

			cnt_value(&new_y, &new_x);

			do {
				temp = rand() % 4;
			} while (temp == 0 || temp == 2);
			a[new_y][new_x] = temp + 1;
			empty--;
		}
		draw();
	}
}

// ͳ��(y, x)��Ӧ�ĸ�����ΧһȦ�Ŀո�ĸ���
int cnt_one(int y, int x)
{
	int value = 0;

	if (y - 1 > 0)
		a[y - 1][x] ? 0 : value++;
	if (y + 1 < 4)
		a[y + 1][x] ? 0 : value++;
	if (x - 1 >= 0)
		a[y][x - 1] ? 0 : value++;
	if (x + 1 < 4)
		a[y][x + 1] ? 0 : value++;
	if (y - 1 >= 0 && x - 1 >= 0)
		a[y - 1][x - 1] ? 0 : value++;
	if (y - 1 >= 0 && x + 1 < 4)
		a[y - 1][x + 1] ? 0 : value++;
	if (y + 1 < 4 && x - 1 >= 0)
		a[y + 1][x - 1] ? 0 : value++;
	if (y + 1 < 4 && x + 1 < 4)
		a[y + 1][x + 1] ? 0 : value++;

	return value;
}

void cnt_value(int *new_y, int *new_x)
{
	int max_x, max_y, x, y, value;
	int max = 0;

	max = cnt_one(*new_y, *new_x);
	for (y = 0; y < 4; y++)
		for (x = 0; x < 4; x++)
		{
			// ���(y, x)��Ӧ�Ŀո�Ϊ��
			if (!a[y][x])
			{
				// ����ѡȡ��Χ�ո����Ŀո�չʾ������
				value = cnt_one(y, x);
				if (value > max && old_y != y && old_x != x)
				{
					// ������ͬһλ�÷�������������
					*new_y = y;
					*new_x = x;
					old_x = x;
					old_y = y;
					break;
				}
			}
		}
}

int game_over()
{
	sleep(1);
	exit(0);
}

