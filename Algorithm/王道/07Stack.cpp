//括号匹配问题
#include<cstdio>
#include<stack> 
using namespace std;
stack<int> S;
char str[110];
char ans[110];
int main(){
	while(scanf("%s",str)!=EOF){
		int i;
		for(i=0;str[i]!='\0';i++){
			if(str[i]=='('){
				S.push(i);
				ans[i]=' '; 
			}
			else if(str[i]==')'){
				if(S.empty()==false){
					S.pop();
					ans[i]=' ';
				}
				else ans[i]='?';
			}
			else ans[i]=' ';
		}
		while (!S.empty()){
			ans[S.top()]='$';
			S.pop();
		}
		ans[i]='\0';
		puts(str);
		puts(ans);
	}
	return 0;
}
//加减乘除简易计算器
#include<stack>
#include<cstdio>
using namespace std;
char str[220];
int mat[][5]={ //优先级矩阵
1,0,0,0,0,
1,0,0,0,0,
1,0,0,0,0,
1,1,1,0,0,
1,1,1,0,0,
};
stack<int> op;
stack<double> in;
void getOp(bool &reto,int &retn,int &i){
	if(i==0 && op.empty()==true){
		reto=true;
		tetn=0;
		return ;
	}
	if(str[i]==0){
		reto=true;
		retn=0;
		return ;
	}
	if(str[i]>='0'&&str[i]<='9'){
		reto = false;
	}
	else{
		reto=true;
		if(str[i]=='+') retn=1;
		else if(str[i]=='-') retn=2;
		else if(str[i]=='*') retn=3;
		else if(str[i]=='/') retn=4;
		i+=2;
		return ; 
	}
	retn =0;
	for(;str[i]!=' '&&str[i]!=0;i++){
		retn*=10;
		retn+=str[i]-'0';
	}
	if(str[i]==' ')
		i++;
	return ;
} 

int main()
{
	while(gets(str)){
		if(str[0]=='0'&&str[1]==0) break;
		bool retop;
		int retnum;
		int idx=0;
		while(!op.empty()) op.pop();
		while(!in.empty()) in.pop();
		while(1){
			getOp(retop,retnum,idx);
			if(retop==false){
				in.push((double)retnum);
			}
			else{
				double tmp;
				if(op.empty()==true || mat[return][op.top()]==1){
					op.push(retnum); 
				} 
				else{
					while(mat[retnum][op.top()]==0){
						int ret=op.top();
						op.top();
						double b=in.top();
						in.pop();
						double a=in.top();
						in.pop(); 
						if(ret==1) tmp=a+b;
						else if(ret==2) tmp=a-b;
						else if(ret==3) tmp=a*b;
						else tmp=a/b;
						in.push(tmp);
					}
					op.push(retnum);
				}
			}
			if(op.size()==2 && op.top()==0) break;
		}
		printf("%.2f\n",in.top());
	}
	return 0;
}
