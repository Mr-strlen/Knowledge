//最小生成树Kruskal算法
#include<cstdio>
#include<algorithm>
using namespace std;
#define N 101
int Tree[N];
int findRoot(int x){
	if(Tree[x]==-1) return x;
	else{
		int tmp=findRoot(Tree[x]);
		Tree[x]=tmp;
		return tmp;
	}
}
struct Edge{
	int a,b;
	int cost;
	bool operator < (const Edge &A) const{
		return cost<A.cost;
	}
}edge[6000];
int main(){
	int n;
	while(scanf("%d",&n)!=EOF && n!=0){
		for(int i=1;i<=n*(n-1)/2;i++)
			scanf("%d%d%d",&edge[i].a,&edge[i].b,&edge[i].cost);
		sort(edge+1,edge+1+n*(n-1)/2);
		for(int i=1;i<=n;i++)
			Tree[i]=-1;
		int ans=0;
		for(int i=1;i<=n*(n-1)/2;i++){
			int a=findRoot(edge[i].a);
			int b=findRoot(edge[i].b);
			if(a!=b){
				Tree[a]=b;
				ans+=edge[i].cost;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
//点连线最短
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define N 101
int Tree[N];
int findRoot(int x){
	if(Tree[x]==-1) return x;
	else{
		int tmp=findRoot(Tree[x]);
		Tree[x]=tmp;
		return tmp;
	}
}
struct Edge{
	int a,b;
	double cost;
	bool operator < (const Edge &A) const{
		return cost<A.cost;	
	}
}edge[6000];
struct Point{
	double x,y;
	double getDistance(Point A){
		double tmp=(x-A.x)*(x-A.x)+(y-A.y)*(y-A.y);
		return sqrt(tmp) 
	}
}list[101];
int main(){
	int n;
	while(scanf("%d",&n)!=EOF){
		for(int i=1;i<=n;i++)
			scanf("%lf%lf",&list[i].x,&list[i].y);
		int size=0;
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++){
				edge[size].a=i;
				edge[size].b=j;
				edge[size].cost=list[i].getDistance(list[j]);
				size++;
			}
		}
		sort(edge,edge+size);
		for(int i=1;i<=n;i++)
			Tree[i]=-1;
		double ans=0;
		for(int i=0;i<size;i++){
			int a=findRoot(edge[i].a);
			int b=findRoot(edge[i].b);
			if(a!=b){
				Tree[a]=b;
				ans+=edge[i].cost;
			}
		}
		printf("%.2f\n",ans);
	}
	return 0;
}
