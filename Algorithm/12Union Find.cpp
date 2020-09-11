//vector连接表
//并查集
#include<cstdio>
using namespace std;
#define N 100
int Tree[N];
int findRoot(int x){
	if(Tree[x]==-1) return x;
	else{
		int tmp=findRoot(Tree[x]);
		Tree[x]=tmp;
		return tmp; 
	}
} 
int main(){
	int n,m;
	while(scanf("%d",&n)!=EOF && n!=0){
		scanf("%d",&m);
		for(int i=1;i<=n;i++) Tree[i]=-1;
		while(m--!=0){
			int a,b;
			scanf("%d%d",&a,&b);
			a=findRoot(a);
			b=findRoot(b);
			if(a!=b) Tree[a]=b;
		}
		int ans=0;
		for(int i=1;i<=n;i++)
			if(Tree[i]==-1) ans++;
		printf("%d\n",ans-1); 
	}
	return 0;
}
//计算节点数最大的树
#include<cstdio>
using namespace std;
#define N 10000001
int Tree[N];
int findRoot(int x){
	if(Tree[x]==-1) return x;
	else{
		int tmp=findRoot(Tree[x]);
		Tree[x]=tmp;
		return tmp;
	}
} 
int sum[N];
int main(){
	int n;
	while(scanf("%d",&n)!=EOF){
		for(int i=1;i<n;i++){
			Tree[i]=-1;
			sum[i]=1;
		}
		while(n--!=0){
			int a,b;
			scanf("%d%d",&a,&b);
			a=findRoot(a);
			b=findRoot(b);
			if(a!=b){
				Tree[a]=b;
				sum[b]+=sum[a];
			}
		}
		int ans=1;
		for(int i=1;i<=N;i++){
			if(Tree[i]==-1 && sum[i]>ans) ans=sum[i];
		}
		printf("%d\n",ans);
	}
	return 0;
}
