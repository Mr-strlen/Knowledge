/*
1.平年365天（52周+1天），闰年366天（52周+2天），平年2月28天，闰年2月29天。
由于公元2000年1月1日设为星期六，故3月1日为星期三。
为使算法达到最简，故本算法以“星期”为计算单位，且选3月1日为基月。

2. 每400年整一闰，或每4年且不为百年的一闰，即凡能被400整除，或不能被100整除但能被4整除的年份为润年。

3. 每 4年（3个平年+1个闰年）共208周+5天 
每百年共100（208周+5天）-1天=5217周+5天 
每400年共4（5217周+5天）+1天（整400年闰）=20871周+0天，即每400年一个轮回。
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
	scanf("%s",date);//两种输入模式 

	while (date[i])/*遍历传入的参数日期，计算出year，month，day*/
	{
		if ((date[i] == '/' || date[i] == '.') && d == -1) { d = 0; i++; continue; }
		if ((date[i] == '/' || date[i] == '.') && d == 0) { d = 1; i++; continue; }
		if (d == -1) year = year * 10 + (date[i] - '0');
		if (d == 0) month = month * 10 + (date[i] - '0');
		if (d == 1) day = day * 10 + (date[i] - '0');
		i++;
	}

	if (month < 1 || month>12)/*若月份传入错误数字*/
	{
		printf("\n ERROR! the entered MONTH is invalid\n");
		exit(0);
	}
	if (year == 2000)
	{
		dy = 0;				/*年引起的星期差为0个*/
		m2 = 1;				/*2月引起的星期差为1个*/
		goto la_100;
	}

	if (year > 2000)
		d = (year - 1 - 2000) / 4 - (year - 1 - 2000) / 100 + (year - 1 - 2000) / 400 + 1;
	else
		d = (year - 2000) / 4 - (year - 2000) / 100 + (year - 2000) / 400;
	dy = (year - 2000) + d;     /*** 该年 1月1号 到2000年1月1号的 " 星期差 " ***/
	if ((year % 4 == 0 && year % 100 != 0) || (year % 100 == 0 && year % 400 == 0))
		m2 = 1;
	else
		m2 = 0;  /*** 该年是否润 ***/
		la_100:                    /**** la_100 ****/
		/*** 该月以前的月所引起的 " 星期差 " ***/
	switch (month)
	{
	case 1: dm = 0; month = 31; break;   /*** month 在此存放该月天数 ***/
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
		switch (week)// 缺少具体日期的输出 
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
