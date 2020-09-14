//N阶楼梯上楼问题 状态转移方程 F[n]=F[n-1]+F[n-2]
#include<stdio.h>
long long F[91];
int main(){
	F[1]=1;
	F[2]=2;
	for(int i=3;i<=90;i++)
		F[i]=F[i-1]+F[i-2];
	int n;
	while(scanf("%d",&n)!=EOF){
		printf("%lld\n",F[n]);
	}
	return 0;
} 

//信封装错 F[n]=(n-1)*F[n-1]+(n-2)*F[n-2] 排错公式 
#include<stdio.h>
long long F[21];
int main(){
	F[1]=0;
	F[2]=1;
	for(int i=3;i<=20;i++)
		F[i]=(i-1)*F[i-1]+(i-1)*F[i-2];
	int n;
	while(scanf("%d",&n)!=EOF){
		printf("%lld\n",F[n]);
	}
	return 0; 
}
