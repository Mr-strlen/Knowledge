//N��¥����¥���� ״̬ת�Ʒ��� F[n]=F[n-1]+F[n-2]
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

//�ŷ�װ�� F[n]=(n-1)*F[n-1]+(n-2)*F[n-2] �Ŵ�ʽ 
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
