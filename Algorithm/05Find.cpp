#include<cstdio>
using namespace std;
//寻找X 
int main(){
	int buf[200];
	int n;
	while(scanf("%d",&n)!=EOF){
		for(int i=0;i<n;i++){
			scanf("%d",&buf[i]);
		}
		int x,ans=-1;
		scanf("%d",&x);
		for(int i=0;i<n;i++){
			if(x==buf[i]){
				ans=i;
				break;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
// 查找学生信息 二分查找
#include<algorithm>
#include<cstring>
using namespace std;
struct Student{
	char no[100];
	char name[100];
	int age;
	char sex[5];
	bool operator < (const Student & A) const{
		return strcmp(no,A.no)<0;
	} 
}buf[1000];

int main(){
	int n;
	while(scanf("%d",&n)!=EOF){
		for(int i=0;i<n;i++){
			scanf("%s%s%s%d",buf[i].no,buf[i].name,buf[i].sex,&buf[i].age);
		}
		sort(buf,buf+n);
		int t;
		scanf("%d",&t);
		while(t--!=0){
			int ans=-1;
			char x[30];
			scanf("%s",x);
			int top=n-1,base=0;
			while(top>=base){
				int mid=(top+base)/2;
				int tmp=strcmp(buf[mid].no,x);
				if(tmp==0){
					ans=mid;
					break;
				}
				else if(tmp>0)top=mid-1;
				else base=mid+1;
			}
			if(ans==-1){
				printf("No Answer\n");
			}
			else
			{
				printf("%s%s%s%d",buf[i].no,buf[i].name,buf[i].sex,buf[i].age);
			}
		}
		
	}
	return 0;
}
//二分查找伪代码
//存在一个升序有序的数组buf，其大小为size，目标数字为target
/*
int base=0,top=size;
while(base<=top){
	int mid=(base+top)/2;
	if(buf(mid)<=target) base=mid+1;
	else top=mid-1;
}
int ans = top;
*/ 
