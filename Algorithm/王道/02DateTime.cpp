//日期差值
/*
#include<cstdio>
#define ISYEAP(x) x%100!=0 && x%4==0 || x%400 == 0?1:0 
using namespace std;
int dayOfMonth[13][2]={
	0,0,
	31,31,
	28,29,
	31,31,
	30,30,
	31,31,
	30,30,
	31,31,
	31,31,
	30,30,
	31,31,
	30,30,
	31,31
};
struct Date{
	int Day;
	int Month;
	int Year;
	void nextDay(){//计算下一天的日期 
		Day++;
		if(Day>dayOfMonth[Month][ISYEAP(Year)]){//超过最大天数 
			Day=1;
			Month++;//进入下一月 
			if(Month>12){//月数超过12 
				Month=1;
				Year++; //进入下一年 
			}
		}
	}
};
int buf[5001][13][32];//储存预处理的天数
int Abs(int x){
	return x<0?-x:x;
}
int main(){
	Date tmp;
	int cnt=0;
	tmp.Day=1;
	tmp.Month=1;
	tmp.Year=0;
	while(tmp.Year!=5001){
		buf[tmp.Year][tmp.Month][tmp.Day]=cnt;
		tmp.nextDay();
		cnt++;
	}
	int d1,m1,y1;
	int d2,m2,y2;
	while(scanf("%4d%2d%2d",&y1,&m1,&d1)!=EOF){
		scanf("%4d%2d%2d",&y2,&m2,&d2);
		printf("%d\n",Abs(buf[y2][m2][d2]-buf[y1][m1][d1])+1);
	}
	return 0;
} */

//日期是星期几
#include<cstdio>
#include<cstring>
#define ISYEAP(x) x%100!=0 && x%4==0 || x%400 == 0?1:0 
using namespace std;
int dayOfMonth[13][2]={
	0,0,
	31,31,
	28,29,
	31,31,
	30,30,
	31,31,
	30,30,
	31,31,
	31,31,
	30,30,
	31,31,
	30,30,
	31,31
};
struct Date{
	int Day;
	int Month;
	int Year;
	void nextDay(){//计算下一天的日期 
		Day++;
		if(Day>dayOfMonth[Month][ISYEAP(Year)]){//超过最大天数 
			Day=1;
			Month++;//进入下一月 
			if(Month>12){//月数超过12 
				Month=1;
				Year++; //进入下一年 
			}
		}
	}
};
int buf[3001][13][32];//储存预处理的天数
char monthName[13][20]={
	"",
	"January",
	"February",
	"March",
	"April",
	"May",
	"June",
	"July",
	"August",
	"September",
	"October",
	"November",
	"December"
};
char weekName[7][20]={
	"Sunday",
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday",
	"Friday",
	"Saturday"
};
int main(){
	Date tmp;
	int cnt=0;
	tmp.Day=1;
	tmp.Month=1;
	tmp.Year=0;
	while(tmp.Year!=5001){
		buf[tmp.Year][tmp.Month][tmp.Day]=cnt;
		tmp.nextDay();
		cnt++;
	}
	int d,m,y;
	char s[20];
	while(scanf("%d%d%d",&d,s,&y)!=EOF){
		for(m=1;m<=12;m++){
			if(strcmp(s,monthName[m])==0){
				break;
			}
		}
		int days=buf[y][m][d]-buf[2012][7][6];
		day+=1；
		printf("%s\n",weekName[(days%7+7)%7]); 
	}
	return 0;
} 
 


