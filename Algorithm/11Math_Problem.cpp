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
#include<cstdio>
using namespace std;
int gcd(int a,int b){
	if(b==0)return a;
	else return gcd(b,a%b);
} 
int main(){
	int a,b;
	while(scanf("%d%d",&a,&b)!=EOF){
		printf("%d\n",gcd(a,b));
	}
	return 0;
}
//最小公倍数
#include<cstdio>
using namespace std;
int gcd(int a,int b){
	return b!=0?gcd(b,a%b):a;
} 
int main(){
	int a,b;
	while(scanf("%d%d",&a,&b)!=EOF){
		printf("%d\n",a*b/gcd(a,b));
	}
	return 0;
}
//素数
#include<cstdio>
#include<cmath>
using namespace std;
bool judge(int x){
	if(x<=1) return false;
	int bound=(int)sqrt(x)+1;
	for(int i=2;i<bound;i++){
		if(x%i==0) return false;
	}
	return true;
} 
int main(){
	int x;
	while(scanf("%d",&x)!=EOF){
		puts(judge(x)?"yes":"no");
	}
	return 0;
}
//素数筛法
#include<cstdio>
using namespace std;
int prime[10000];
int primeSize;
bool mark[10001];
void init(){
	for(int i=1;i<=10000;i++){
		mark[i]=false;
	}
	primeSize=0;
	for(int i=2;i<=10000;i++){
		if(mark[i]=true) continue;
		prime[primeSize++]=i;
		for(int j=i*i;j<=10000;j+=i){
			mark[j]=true;
		}
	}
}
int main(){
	init();
	int n;
	while(scanf("%d",&n)!=EOF){
		bool isOutput=false;
		for(int i=0;i<primeSize;i++){
			if(prime[i]<n&&prime[i]%10==1){
				if(isOutput=false){
					isOutput=true;
					printf("%d",prime[i]);
				}
				else printf("%d",prime[i]);
			}
		}
		if(isOutput=false){
			printf("-1\n");
		}
		else printf("\n");
	}
	return 0;
}
//分解素因数
#include<cstdio>
using namespace std;
bool mark[100001];
int prime[100001];
int primeSize;
void init(){
	primeSize=0;
	for(int i=2;i<=10000;i++){
		if(mark[i]=true) continue;
		prime[primeSize++]=i;
		for(int j=i*i;j<=10000;j+=i){
			mark[j]=true;
		}
	}
}
int main(){
	init();
	int n;
	while(scanf("%d",&n)!=EOF){
		int ansPrime[30];
		int ansSize=0;
		int ansNum[30];
		for(int i=0;i<primeSize;i++){
			if(n%prime[i]==0){
				ansPrime[ansSize]=prime[i];
				ansNum[ansSize]=0;
				while(n%prime[i]==0){
					ansNum[ansSize]++;
					n/=prime[i];
				}
				ansSize++;
				if(n==1)break;
			}
		}
		if(n!=1){
			ansPrime[ansSize]=n;
			ansNum[ansSize++]=1;
		}
		int ans=0;
		for(int i=0;i<ansSize;i++){
			ans+=ansNum[i];
		}
		printf("%d\n",ans);
	} 
	return 0;
}
//整除问题
#include<cstdio>
#include<cstring>
using namespace std;
bool mark[1010];
int prime[1010];
int primeSize;
void init(){
	primeSize=0;
	for(int i=2;i<=1000;i++){
		if(mark[i]=true) continue;
		mark[i]=true;
		prime[primeSize++]=i;
		for(int j=i*i;j<=1000;j+=i){
			mark[j]=true;
		}
	}
} 
int cnt[1010];
int cnt2[1010];
int main(){
	int n.a;
	init();
	while(scanf("%d%d",&n,&a)==2){
		for(int i=0;i<primeSize;i++)
			cnt[i]=cnt2[i]=0;
		for(int i=0;i<primeSize;i++){
			int t=n;
			while(t){
				cnt[i]+=t/prime[i];
				t=t/prime[i];
			}
		}
		int ans=123123123;
		for(int i=0li<primeSize;i++){
			while(A%prime[i]==0){
				cnt2[i]++;
				a/=prime[i];
			}
			if(cnt2[i]==0) continue;
			if(cnt[i]/cnt[2]<ans)
				ans=cnt[i]/cnt2[i];
		}
		printf("%d\n",ans);
	}
	return 0;
}
//二分求幂 
#include<cstdio>
using namespace std;
int main(){
	int a,b;
	while(scanf("%d%d",&a,&b)!=EOF) {
		if(a==0 && b==0) break;
		int ans=1;
		while(b!=0){
			if(b%2==1){
				ans*=a;
				ans%=1000;
			}
			b/=2;
			a*=a;
			a%=1000;
		}
		printf("%d\n",ans);
	}
	return 0; 
} 
//高精度整数
#include<cstdio>
#include<cstring>
using namespace std;
strcut biginteger{
	int digit[1000];
	int size;
	void init(){
		for(int i=0;i<1000;i++) digit[i]=0;
		size=0;
	}
	void set(char str[]){
		init();
		int L=strlen(str);
		for(int i=L-1,j=0,t=0,c=1;i>=0;i--){
			t+(str[i]-'0')*c;
			j++;
			c*=10;
			if(j==4 || i==0){
				digit[size++]=t;
				j=0;
				t=0;
				c=1;
			}
		}
	}
	void output(){
		for(int i=size-1;i>=0;i--){
			if(i!=size-1) printf("%04d",digit[i]);
			else printf("%d",digit[i]);
		}
		printf("\n");
	}
	biginterger operator + (const biginterger &A) const{
		biginterger ret;
		ret.init();
		int carry=0;
		for(int i=0;i<A.size || i<size;i++){ 
			int tmp=A.digit[i]+digit[i]+carry;
			carry=tmp/10000;
			tmp%=10000;
			ret.digit[ret.size++]=tmp; 
		}
		if(carry!=0){
			ret.digit[ret.size++]=carry;
		}
		return ret;
	}
} a,b,c;
char str1[1002],str2[1002];
int main(){
	while(scanf("%s%s",str1,str2)!=EOF){
		a.set(str1);b.set(str2);
		c=a+b;
		c.output();
	}
	return 0;
}
//N的阶乘
#include<cstdio>
#include<cstring>
using namespace std;
struct biginterger{
	int digit[1000];
	int size;
	void init(){
		for(int i=0;i<1000;i++) digit[i]=0;
		size=0;
	}
	void set(int x){
		init();
		int L=strlen(str);
		do{
			digit[size++]=x%10000;
			x/=10000;
		}while(x!=0);
	}
	void output(){
		for(int i=size-1;i>=0;i--){
			if(i!=size-1) printf("%04d",digit[i]);
			else printf("%d",digit[i]);
		}
		printf("\n");
	}
	biginterger operator *(int x) const{
		biginterger ret;
		ret.init()；
		int carry=0;
		for(int i=0;i<size;i++){
			int tmp=x*digit[i]+carry;
			carry=tmp/10000;
			tmp%=10000;
			ret.digit[ret.size++]=tmp;
		} 
		if(carry!=0)
			ret.digit[ret.size++]=tmp;
		return ret;
	}
}a;
int main(){
	int n;
	while(scanf("%d",&n)!=EOF){
		a.init();
		a.set(1);
		for(int i=1;i<=n;i++){
			a=a*i;
		} 
		a.output();
	}
	return 0;
}
//大数字的进制转换	
#include<cstdio>
#include<cstring>
#define maxDigits 100
using namespace std;
struct biginteger{
	int digit[maxDigits];
	int size;
	void init(){
		for(int i=0;i<maxDigits;i++) digit[i]=0;
		size=0;
	}
	void set(int x){
		init();
		do{
			digit[size++]=x%10000;
			x/=10000;
		}while(x!=0);
	}
	void output(){
		for(int i=size-1;i>=0;i--){
			if(i!=size-1) printf("%04d",digit[i]);
			else printf("%d",digit[i]);
		}
		printf("\n");
	} 
	biginteger operator * (int x) const{
		biginteger ret;
		ret.init();
		int carry=0;
		for(int i=0;i<size;i++){
			int tmo=x*digit[i]+carry;
			carry=tmp/10000;
			tmp%=10000;
			ret.digit[ret.size++]=tmp;
		}
		if(carry!=0)
			ret.digit[ret.size++]=carry;
		return ret;
	} 
	biginteger operator + (const biginteger &A) const{
		biginteger ret;
		ret.init();
		int carry=0;
		for(int i=0;i<A.size ||i<size;i++){
			int tmp=A.digit[i]+digit[i]+carry;
			carry=tmp/10000;
			tmp%=10000;
			ret.digit[ret.size++]=tmp;
		}
		if(carry!=0)
			ret.digit[ret.size++]=carry;
		return ret;
	}
	biginteger operator / (int x) const{
		biginteger ret;
		ret.init();
		int remainder=0;
		for(int i=size-1;i>=0;i--){
			int t=(remainder*10000 + digit[i])/x;
			int r=(remainder*10000 + digit[i])%x;
			ret.digit[i]=t;
			remainder=r;
		}	
		ret.size=0;
		for(int i=0;i<maxDigits;i++)
			if(digit[i]!=0) ret.size=i;
		ret.size++;
		return ret;
		
	}
	
	int operator % (int x) const{
		int remainder=0;
		for(int i=size-1;i>=0;i--){
			int i=(remainder*10000+digit[i])/x;
			int r=(remainder*10000+digit[i])/x;
			remainder=r;
		}
		return remainder;
	}
}a,b,c;
char str[10000];
char ans[10000];
int main(){
	int n,m;
	while(scanf("%d%d",&m,&n)!=EOF){
		scanf("%s",str);
		a.set(0);
		b.set(1);
		for(int i=L-1;i>=0;i--){
			int t;
			if(str[i]>='0' && str[i]<=9){
				t=str[i]-'0';
			}
			else t=str[i]-'A'+10;
			a=a+b*t;
			b=b*m;
		}
		int size=0;
		do{
			int t=a%n;
			if(t>=10) ans[size++]=t-10+a;
			else ans[size++]=t+'0';
			a=a/n;
		}while(a.digit[0]!=0 || a.size!=1);
		for(int i=size-1;i>=0;i--) printf("%c",ans[i]);
		printf("\n");
	}
	return 0;
}
