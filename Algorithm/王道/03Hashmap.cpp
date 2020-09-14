//某个特定分数人数
#include<cstdio>
using namespace std;
int main(){
	int n;
	while(scanf("%d",&n)!=EOF && n!=0){
		int Hash[101]={0};
		for(int i=1;i<=n;i++){
			int x;
			scanf("%d",&x);
			Hash[x]++;
		}
		int x;
		scanf("%d",&x);
		printf("%d\n",Hash[x]);
	}
	return 0;
} 
//大规模整数输出前m大的数 输入数字各不相同
#include<cstdio>
#define OFFSET 500000
using namespace std;
int Hash[1000001];
int main(){
	int n,m;
	while(scanf("%d%d",&n,&m)!=EOF){
		for(int i=-500000;i<=500000;i++){
			Hash[i+OFFSET]=0;
		}
		for(int i=1;i<=n;i++){
			int x;
			scanf("%d",&x);
			Hash[x+OFFSET]=1;
		}
		
		for(int i=500000;i>=-500000;i--){//格式控制 
			if(Hash[i+OFFSET]==1){
				printf("%d",i);
				m--;
				if(m!=0) printf(" ");
			}
			else{
				printf("\n");
				break;
			}
		}
	}
	return 0;
}
 
