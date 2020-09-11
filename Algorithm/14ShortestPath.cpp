//最短路径  
//Floyd算法
#include<stdio.h>
int ans[101][101];
int main(){
	int n,m;
	while(scanf("%d%d",&n,&m)!=EOF){
		if(n==0 && m==0) break;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				ans[i][j]=-1;
			}
			ans[i][j]=0;
		}
		while(m--){
			int a,b,c;
			scanf("%d%d%d",&a,&b,&c);
			ans[a][b]=ans[b][a]=c;
		}
		for(int k=1;k<=n;k++){
			for(int i=1;i<=n;i++){
				for(int j=1;j<=n;j++){
					if(ans[i][k]==-1 || ans[k][j]==-1) continue;
					if(ans[i][j]==-1 || ans[i][k]+ans[k][j]<ans[i][j])
						ans[i][j]=ans[i][k]+ans[k][j];
				}
			}
		}
		printf("%d\n",ans[1][n]);
	}
	return 0;
}
//Dijkstra算法
#include<stdio.h>
#include<vector>
using namespace std;
struct E{
	int next;
	int c;
};
vector<E> edge[101];
bool mark[101];
int Dis[101];
int main(){
	int n,m;
	while(scanf("%d%d",&n,&m)!=EOF){
		if(n==0 && m==0) break;
		for(int i=1;i<=n;i++) edge[i].clear();
		while(m--){
			int a,b,c;
			scanf("%d%d%d",&a,&b,&c);
			E tmp;
			tmp.c=c;
			tmp.next=b;
			edge[a].push_back(tmp);
			tmp.next=a;
			edge[b].push_back(tmp);
		}
		for(int i=1;i<=n;i++){
			Dis[i]=-1;
			mark[i]=false;
		}
		Dis[1]=0;
		mark[1]=true;
		int newP=1;
		for(int i=1;i<n;i++){
			for(int j=0;j<edge[newP].size();j++){
				int t=edge[newP][j].next;
				int c=edge[newP][j].c;
				if(mark[t]==true) continue;
				if(Dis[t]==-1 || Dis[t]>Dis[newP]+c)
					Dis[t]=Dis[newP]+c;
			}
			int min=123123123;
			for(int j=1;j<=n;j++){
				if(mark[j]==true) continue;
				if(Dis[j]==-1) continue;
				if(Dis[j]<min){
					min=Dis[j];
					newP=j;
				}
			}
			mark[newP]=true;
		}
		printf("%d\n",Dis[n]);
	}
	return 0;
}
//最短路径问题
#include<stdio.h>
#include<vector>
using namespace std;
struct E{
	int next;
	int c;
	int cost;
}; 
vector<E> edge[1001];
int Dis[1001];
int cost[1001];
bool mark[1001];
int main(){
	int n,m;
	int S,T;
	while(scanf("%d%d",&n,&m)!=EOF){
		if(n==0 && m==0) break;
		for(int i=1;i<=n;i++) edge[i].clear();
		while(m--){
			int a,b,c,cost;
			scanf("%d%d%d%d",&a,&b,&c,&cost);
			E tmp;
			tmp.c=c;
			tmp.cost=cost;
			tmp.next=b;
			edge[a].push_back(tmp);
			tmp.next=a;
			edge[b].push_back(tmp);
		}
		scanf("%d%d",&S,&T);
		for(int i=1;i<=n;i++){
			Dis[i]=-1;
			mark[i]=false;
		}
		Dis[S]=0;
		mark[S]=true;
		int newP=S;
		for(int i=1;i<n;i++){
			for(int j=0;j<edge[newP].size;j++){
				int t=edge[newP][j].next;
				int c=edge[newP][j].c;
				int co=edge[newP][j].cost;
				if(mark[t]==true) continue;
				if(Dis[t]==-1 || Dis[t]>Dis[newP]+c || Dis[t]==Dis[newP]+c && cost[t]>cost[newP]+co){
					Dis[t]=Dis[newP]+c;
					cost[t]=cost[newP]=co;
				}
			}
			int min=123123123;
			for(int j=1;j<=n;j++){
				if(mark[j]==true) continue;
				if(Dis[j]==-1) continue;
				if(Dis[j]<min){
					min=Dis[j];
					newP=j;
				}
			}
			mark[newP]=true;
		} 
		printf("%d %d\n",Dis[T],cost[T]);
	}
	return 0;
}
