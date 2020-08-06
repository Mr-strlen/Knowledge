#include<cstdio>
using namespace std;
//Êä³öÌİĞÎ 
int main(){
	int h;
	while(scanf("%d",&h)!=EOF){
		int maxLine=h+(h-1)*2;
		for(int i=1;i<=h;i++){
			for(int j=1;j<=maxLine;j++){
				if(j<maxLine-h--(i-1)*2+1)
					printf(" ");
				else printf("*"); 
			}
			printf("\n");
		}
	} 
	return 0;
} 
//µşÂá¿ğ
int main(){
	int outPutBuf[82][82];
	char a,b;
	int n;
	bool firstCase = true;
	while(scanf("%d%c%c",&n,&a,&b)==3){
		if(firstCase==true)
			firstCase=false;
		else printf("\n");
		for(int i=1,j=1;i<=n;i+=2,j++){
			int x=n/2+1,y=x;
			x-=j-1;y-=j-1;
		} 
	}
} 
