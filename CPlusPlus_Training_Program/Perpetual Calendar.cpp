/*
1.ƽ��365�죨52��+1�죩������366�죨52��+2�죩��ƽ��2��28�죬����2��29�졣
���ڹ�Ԫ2000��1��1����Ϊ����������3��1��Ϊ��������
Ϊʹ�㷨�ﵽ��򣬹ʱ��㷨�ԡ����ڡ�Ϊ���㵥λ����ѡ3��1��Ϊ���¡�

2. ÿ400����һ�򣬻�ÿ4���Ҳ�Ϊ�����һ�򣬼����ܱ�400���������ܱ�100�������ܱ�4���������Ϊ���ꡣ

3. ÿ 4�꣨3��ƽ��+1�����꣩��208��+5�� 
ÿ���깲100��208��+5�죩-1��=5217��+5�� 
ÿ400�깲4��5217��+5�죩+1�죨��400����=20871��+0�죬��ÿ400��һ���ֻء�
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//int main(int a, char **date)
int main()
{
	char date[10]={'\0'};
	int year = 0, month = 0, day = 0, week;
	int d, i, dm, dy, m2;
	char WEEK[9];

	i = 0; d = -1;
	scanf("%s",date);//��������ģʽ 

	while (date[i])/*��������Ĳ������ڣ������year��month��day*/
	{
		if ((date[i] == '/' || date[i] == '.') && d == -1) { d = 0; i++; continue; }
		if ((date[i] == '/' || date[i] == '.') && d == 0) { d = 1; i++; continue; }
		if (d == -1) year = year * 10 + (date[i] - '0');
		if (d == 0) month = month * 10 + (date[i] - '0');
		if (d == 1) day = day * 10 + (date[i] - '0');
		i++;
	}

	if (month < 1 || month>12)/*���·ݴ����������*/
	{
		printf("\n ERROR! the entered MONTH is invalid\n");
		exit(0);
	}
	if (year == 2000)
	{
		dy = 0;				/*����������ڲ�Ϊ0��*/
		m2 = 1;				/*2����������ڲ�Ϊ1��*/
		goto la_100;
	}

	if (year > 2000)
		d = (year - 1 - 2000) / 4 - (year - 1 - 2000) / 100 + (year - 1 - 2000) / 400 + 1;
	else
		d = (year - 2000) / 4 - (year - 2000) / 100 + (year - 2000) / 400;
	dy = (year - 2000) + d;     /*** ���� 1��1�� ��2000��1��1�ŵ� " ���ڲ� " ***/
	if ((year % 4 == 0 && year % 100 != 0) || (year % 100 == 0 && year % 400 == 0))
		m2 = 1;
	else
		m2 = 0;  /*** �����Ƿ��� ***/
		la_100:                    /**** la_100 ****/
		/*** ������ǰ����������� " ���ڲ� " ***/
	switch (month)
	{
	case 1: dm = 0; month = 31; break;   /*** month �ڴ˴�Ÿ������� ***/
	case 2: dm = 3; month = d == 1 ? 29 : 28; break;
	case 3: dm = 3 + m2; month = 31; break;
	case 4: dm = 6 + m2; month = 30; break;
	case 5: dm = 1 + m2; month = 31; break;
	case 6: dm = 4 + m2; month = 30; break;
	case 7: dm = 6 + m2; month = 31; break;
	case 8: dm = 2 + m2; month = 31; break;
	case 9: dm = 5 + m2; month = 30; break;
	case 10: dm = m2; month = 31; break;
	case 11: dm = 3 + m2; month = 30; break;
	case 12: dm = 5 + m2; month = 31; break;
	}

	if (day<0 || day>month)
	{
		printf("\n ERROR! the entered DAY is invalid\n");
		exit(0);
	}

	week = (dy + dm + day - 1 + 6) % 7;
	if (week < 0)
		week += 7;

	if (day > 0)
	{
		switch (week)// ȱ�پ������ڵ���� 
		{
		case 0: strcpy(WEEK, "SUNDAY"); break;
		case 1: strcpy(WEEK, "MONDAY"); break;
		case 2: strcpy(WEEK, "TUESDAY"); break;
		case 3: strcpy(WEEK, "WEDNESDAY"); break;
		case 4: strcpy(WEEK, "THURSDAY"); break;
		case 5: strcpy(WEEK, "FRIDAY"); break;
		case 6: strcpy(WEEK, "SATURDAY"); break;
		default: "null"; break;
		}
	}
	else
	{
		week = ++week % 7;
		printf("\n the calender of this month as following\n");
		printf("\n *********************************\n");
		printf(" SUN  MON  TUE  WEN  THU  FRI  STA\n");

		for (i = 0; i < week; i++)
			printf("     ");
		for (i = 1; i <= month; i++)
		{
			printf(" %2d  ", i);
			week++;
			if (week % 7 == 0 && i != month)
				printf("\n");
		}
		printf("\n *********************************\n");
		printf("\n OK!\n");
	}

	return 0;
}
