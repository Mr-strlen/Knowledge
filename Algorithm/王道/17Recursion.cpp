//限制移动的汉诺塔
#include<stdio.h>
#include<string.h>
long long F (int num){
	if(num==1) return 2;
	else
		return 3*F(num-1)+2; 
} 
int main(){
	int n;
	while(scanf("%d",&n)!=EOF){
		printf("%lld\n",F(n));
	}
	return 0; 
} 
//素数环问题
#include<stdio.h>
#include<string.h>
int ans[22];
bool hash[22];
int n;
int prime[]={2,3,5,7,11,13,17,19,23,29,31,37,41};
bool judge(int x){
	for(int i=0;i<13;i++){
		if(prime[i]==x) return true;
	} 
	return false;
} 
void check(){
	if(judge(ans[n]+ans[i])==false) return;
	for(int i=1;i<=n;i++){
		if(i!=1) printf(" ");
	}
	printf("\n");
} 
void DFS(int num){
	if(num>1)
		if(judge(ans[num]+ans[num-1]==false)) return;
	if(num==n){
		cheack();
		return ;
	}
	for(int i=2;i<=n;i++){
		if(hash[i]==false){
			hash[i]=true;
			ans[num+1]=i;
			DFS(num+1);
			hash[i]=false; 
		}
	}
} 
int main(){
	int cas=0;
	while(scanf("%d",&n)!=EOF){
		cas++;
		for(int i=0;i<22;i++) hash[i]=false;
		ans[1]=1;
		printf("Case %d\n",cas);
		hash[1]=true;
		DFS(1);
		printf("\n");
	}
	return 0;
}
//图的遍历
#include<stdio.h>
char maze[101][101];
bool mark[101][101];
int n,m;
int go[][2]={1,0,-1,0,0,1,0,-1,1,1,1,-1,-1,-1,-1,1};
void DFS(int x,int y){
	for(int i=0;i<8;i++){
		int nx=x+go[i][0];
		int ny=y+go[i][1];
		if(nx<1 || nx>n || ny<1 |ny>m) continue;
		if(maze[nx][ny]=='*') continue;
		if(mark[nx][ny]==true) continue;
		mark[nx][ny]=true;
		DFS(nx,ny); 
	}
	return ;
} 
int main(){
	while(scanf("%d%d",&n,&m)!=EOF){
		if(n==0 && m==0) break;
		for(int i=1;i<=n;i++){
			scanf("%s",maze[i]+1);
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				mark[i][j]=false;
			}
		}
		int ans=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(mark[i][j]==true) continue;
				if(maze[i][j]=='*') continue;
				DFS(i,j);
				ans++;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
