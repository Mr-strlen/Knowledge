#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
using namespace std; 
//基础冒泡 
/* 
int main()
{
	int n;
	int buf[100];
	while(scanf("%d",&n)!=EOF){//实现多组数据输入 
		for(int i=0;i<n;i++)
			scanf("%d",&buf[i]); 
	 
		for (int i=0;i<n;i++){
			for(int j=0;j<n-1-i;j++){
				if(buf[j]>buf[j+1]){
					int tmp=buf[j];
					buf[j]=buf[j+1];
					buf[j+1]=tmp;
				}
			}
		}
		for(int i=0;i<n;i++){
			printf("%d\t",buf[i]);
		}
		printf("\n"); 
	}
	return 0;
}*/

//快排
/*int main()
{
	int n;
	int buf[10000];
	while(scanf("%d",&n)!=EOF){//实现多组数据输入 
		for(int i=0;i<n;i++)
			scanf("%d",&buf[i]); 
	 
		sort(buf,buf+n);
		for(int i=0;i<n;i++){
			printf("%d\t",buf[i]);
		}
		printf("\n"); 
	}
	return 0;
}*/

//快排重载
/*
bool cmp(int x,int y){
	return x>y;
}
int main()
{
	int n;
	int buf[10000];
	while(scanf("%d",&n)!=EOF){//实现多组数据输入 
		for(int i=0;i<n;i++)
			scanf("%d",&buf[i]); 
	 
		sort(buf,buf+n,cmp);
		for(int i=0;i<n;i++){
			printf("%d\t",buf[i]);
		}
		printf("\n"); 
	}
	return 0;
} */

//成绩排序
struct E{
	char name[101];
	int age;
	int score;
}buf[1000];
bool cmp(E a,E b){
	if(a.score!=b.score) return a.score<b.score;
	int tmp=strcmp(a.name,b.name);
	if(tmp!=0) return tmp<0;
	else return a.age<b.age;
} 
//重载函数
/*
bool operator < (const E &b) const{
	if(a.score!=b.score) return a.score<b.score;
	int tmp=strcmp(a.name,b.name);
	if(tmp!=0) return tmp<0;
	else return a.age<b.age;
}*/
int main(){
	int n;
	while(scanf("%d",&n)!=EOF){
		for(int i=0;i<n;i++){
			scanf("%s%d%d",buf[i].name,&buf[i].age,&buf[i].score);
		}
		sort(buf,buf+n,cmp);
		for(int i=0;i<n;i++)
			printf("%s %d %d\n",buf[i].name,buf[i].age,buf[i].score)
	}
	return 0;
}
