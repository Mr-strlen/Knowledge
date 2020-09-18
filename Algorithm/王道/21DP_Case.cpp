//搬运物品疲劳程度最低
//dp[i][j]=min{dp[i][j-1],dp[i-1][j-2]+(list[j]-list[j-1]^2)}
#include<stdio.h>
#include<algorithm>
using namespace std;
#define INF 0x7fffffff
int list[2001];
int dp[1001][2001];
int main(){
	int n,k;
	while(scanf("%d%d",&n,&k)!=EOF){
		for(int i=1;i<=n;i++){
			scanf("%d",&list[i]);
		}
		sort(list+1,list+1+n);
		for(int i=1;i<=n;i++)
			dp[0][i]=0;
		for(int i=1;i<=k;i++){
			for(int j=2*i;j<=n;j++){
				if(j>2*i)
					dp[i][j]=dp[i][j-1];
				else
					dp[i][j]=INF;
				if(dp[i][j]>dp[i-1][j-2]+(list[j]-list[j-1])*(list[j]-list[j-1]))
					dp[i][j]=dp[i-1][j-2]+(list[j]-list[j-1])*(list[j]-list[j-1]);
			}
		}
		printf("%d\n",dp[k][n]);
	}
	return 0;
}
//橘子重量相等
//dp[i][j]=max(dp[i-1][j-list[i]]+list[i]),dp[i-1][j+list[i]]+list[i],dp[i-1][j]); 
#include<stdio.h>
#define OFFSET 2000
int dp[101][4001];
int list[101];
#define INF 0x7fffffff
int main(){
	int T;
	int cas=0;
	scanf("%d",&T);
	while(T--!=0){
		int n;
		scanf("%d",&n);
		bool HaveZero=false;
		int cnt=0;
		for(int i=1;i<=n;i++){
			scanf("%d",&list[++cnt]);
			if(list[cnt]==0){
				cnt--;
				HaveZero=true;
			}
		}
		n=cnt;
		for(int i=-2000;i<=2000;i++){
			dp[0][i+OFFSET]=-INF;
		}
		dp[0][0+OFFSET]=0;
		for(int i=1;i<=n;i++){
			for(int j=-2000;j<=2000;j++){
				int tmp1=-INF,tmp2=-INF;
				if(j+list[i]<=2000 && dp[i-1][j+list[i]+OFFSET]!=-INF){
					tmp1=dp[i-1][j+list[i]+OFFSET]+list[i];
				}
				if(j-list[i]>=-2000 && dp[i-1][j-listp[i]+OFFSET]!=-INF){
					tmp2=dp[i-1][j-list[i]+OFFSET]+list[i];
				}
				if(tmp1<tmp2){
					tmp1=tmp2;
				}
				if(tmp1<dp[i-1][j+OFFFSET]){
					tmp1=dp[i-1][j+OFFFSET];
				}
				dp[i][j+OFFSET]=tmp1;
			}
		}
		printf("Case %d:",++cas);
		if(dp[n][0+OFFSET]==0){
			puts(HaveZero==true?"0":"-1");
		}
		else printf("%d\n",dp[n][0+OFFSET]/2);
	}
	return 0;
}
