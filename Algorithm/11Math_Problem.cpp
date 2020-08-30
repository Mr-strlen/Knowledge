//%运算符
//数位拆解
#include<cstdio>
int main()
{
	int a,b;
	while(scanf("%d%d",&a,&b)!=EOF){
		int buf1[20],buf[20],size1=0.size2=0;
		while(a!=0){
			buf1[size1++]=a%10;
			a/=10;
		}
		while(b!=0){
			buf2[size2++]=b%10;
			b/=10;
		}
		int ans=0;
		for(int i=0;i<size1;i++)
			for(int j=0;j<size2;j++)
				ans+=buf1[i]*buf2[j];
		printf("%d\n",ans);
	}	
	return 0;
} 

#include<cstdio>
using namespace std;
int main()
{
	char a[11],b[11];
	while(scanf("%s%s",a,b)!=EOF){
		int ans=0;
		for(int i=0;a[i]!=0;i++)
			for(int j=0;b[j]!=0;j++)
				ans+=(a[i]-'0')*(b[i]-'0');
		printf("%d\n",ans);
	}
	return 0;
}
//进制转换
#include<cstdio>
using namespace std;
int main(){
	long long a,b;
	int m;
	while(scanf("%d",&m)!=EOF){
		if(m==0) break;
		scanf("%lld%lld",&a,&b);
		a=a+b;
		int ans[50],size=0;
		do{
			ans[size++]=a%m;
			a/=m;
		}while(a!=0)
		for(int i=size-1;i>=0;i--){
			printf("%d",ans[i]); 
		} 
		printf("\n");
	}
	return 0;
} 
//进制互转
#include<cstdio>
#include<cstring>
using namespace std;
int main(){
	int a,b;
	char str[40];
	while(scanf("%d%s%d",&a,str,&b)!=EOF){
		int tmp=0,lenth=strlen(str),c=1;
		for(int i=lenth-1;i>=0;i--){
		int x;
		if(str[i]>='0' && str[i]<='9') x=str[i]-'0';
		else if(str[i]>='a'&&str[i]<='z') x=str[i]-'a'+10;
		else x=str[i]-'A'+10;
		tmp+=x*c;
		c*=a; 
	}
	char ans[40],size=0;
	do{
		int x=tmp%b;
		ans[size++]=(x<10)?x+'0':x-10+'A';
		tmp/=b;
	}while(tmp);
	for(int i=size-1;i>=0;i--)	
		printf("%c",ans[i]);
	printf("\n");
	}
	return 0;
} 
//最大公约数 
 
