//�Լ۱���ߵļ�ֵ���
#include<cstdio>
#include<algorithm>
using namespace std;
struct goods{
	double j;
	double f;
	double s;
	bool operator < (const goods &A) const{
	return s>A.s;
}
}buf[1000];
int main(){
	double m;
	int n;
	while(scanf("%lf%d",&m,&n)!=EOF){
		if(m==-1&&n==-1) break;
		for(int i=0;i<n;i++){
			scanf("%lf%lf",&buf[i].j,&buf[i].f);
			buf[i].s=buf[i].j/buf[i].f; 
		}
		sort(buf,buf+n);
		int idx=0;
		double ans=0;
		while(m>0 && idx<n){
			if(m>buf[i].f){
				ans+=buf[idx].j;
				m-=buf[idx].f;
			}
			else{
				ans+=buf[idx].j*m/buf[idx].f;
				m=0;
			}
			idx++;
		}
		printf("%.3f\n",ans);
	}
	return 0;
} 
//֪�����е��ӽ�Ŀ�Ŀ�ʼ����ʱ�䣬��ΰ��ſ�����������
//����ʱ������Ľ�Ŀ
#include<cstdio>
#include<algorithm>
using namespace std;
struct program{
	int startTime;
	int endTime;
	bool operator < (const program &A) const{
		return endTime<A.endTime;
	}
}buf[100];
int main()
{
	int n;
	while(scanf("%d",&n)!=EOF){
		if(n==0) break;
		for(int i=0;i<n;i++){
			scanf("%d%d",&buf[i].startTime,&buf[i].endTime);
		}
		sort(buf,buf+n);
		int currentTime=0,ans=0;
		for(int i=0;i<n;i++){
			if(currentTime<=buf[i].startTime){
				currentTime=buf[i].endTime;
				ans++;
			}
		}
		printf("%d\n",ans); 
	}
	return 0;
} 
