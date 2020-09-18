//����������� LIS
// F[i]=max{1,F[j]+1 | aj<ai && j<i}

//�����������
// F[i]=max{1,F[j]+1 | aj<=ai && j<i}
#include<stdio.h>
int max(int a,int b) {return a>b?a:b;}
int list[26];
int dp[26];
int main(){
	int n;
	while(scanf("%d",&n)!=EOF){
		for(int i=1;i<=n;i++)
			scanf("%d",&list[i]);
		for(int i=1;i<=n;i++){
			int tmax=1;
			for(int j=1;j<=i;j++){
				if(list[j]>=list[i]){
					tmax=max(tmax,dp[j]+1);
				}
			}
			dp[i]=tmax;
		}
		int ans=1;
		for(int i=1;i<=n;i++)
			ans=max(ans,dp[i]); 
		printf("%d\n",ans);
	}
	return 0;
} 

//����������� LCS
/*
dp[0][j](0<=j<=m)=0;
dp[i][0](0<=i<=n)=0;
dp[i][j]=dp[i-1][j-1]+1;(s1[i]==s2[j])
dp[i][j]=max{dp[i-1][j],dp[i][j-1]};(s1[i]!=s2[j])
*/ 
#include<stdio.h>
#include<string.h>
int dp[101][101]; 
int max(int a,int b){return a>b?a:b;}
int main(){
	char S1[101],S2[101];
	while(scanf("%s%s",S1,S2)!=EOF){
		int L1=strlen(S1);
		int L2=strlen(S2);
		for(int i=0;i<=L1;i++) dp[i][0]=0;
		for(int j=0;j<L2;j++) dp[0][j]=0;
		for(int i=1;i<L1;i++){
			for(int j=1;j<L2;j++){
				if(S1[i-1]!=S2[j-1])
					dp[i][j]=max(dp[i][j-1],dp[i-1][j]);
				else 
					dp[i][j]=dp[i-1][j-1]+1;
			}
		}
		printf("%d\n",dp[L1][L2]);
	}
	return 0;
}

/*
�������⣺KMP�ַ���ƥ��
Next��������  
ȡ���ַ�ǰ����ַ������������Լ�������ǰ׺�ַ����ͺ�׺�ַ�����ͬ�ַ����������� +1 ���Ǹ��ַ���Ӧ�� next ֵ 
*/
#include <stdio.h>
#include <string.h>
void Next(char*T,int *next){
    int i=1;
    next[1]=0;
    int j=0;
    while (i<strlen(T)) {
        if (j==0||T[i-1]==T[j-1]) {
            i++;
            j++;
            if (T[i-1]!=T[j-1]) {
               next[i]=j;
            }
            else{
                next[i]=next[j];
            }
        }else{
            j=next[j];
        }
    }
}
int KMP(char * S,char * T){
    int next[10];
    Next(T,next);//����ģʽ��T,��ʼ��next����
    int i=1;
    int j=1;
    while (i<=strlen(S)&&j<=strlen(T)) {
        //j==0:����ģʽ���ĵ�һ���ַ��ͺ͵�ǰ���Ե��ַ�����ȣ�S[i-1]==T[j-1],�����Ӧλ���ַ���ȣ���������£�ָ��ǰ���Ե�����ָ���±�i��j�������
        if (j==0 || S[i-1]==T[j-1]) {
            i++;
            j++;
        }
        else{
            j=next[j];//������Ե������ַ�����ȣ�i������j��Ϊ��ǰ�����ַ�����nextֵ
        }
    }
    if (j>strlen(T)) {//�������Ϊ�棬˵��ƥ��ɹ�
        return i-(int)strlen(T);
    }
    return -1;
}
int main() {
    int i=KMP("ababcabcacbab","abcac");
    printf("%d",i);
    return 0;
}
 
