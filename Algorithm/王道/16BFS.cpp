//BFS+剪枝（已经到过的状态不重复） 
#include<stdio.h>
#include<queue>
using namespace std;
bool mark[50][50][50];
int maze[50][50][50];
struct N{
	int x,y,z;
	int t;
}; 
queue<N> Q;
int go[][3]={
	1,0,0,
	-1,0,0,
	0,1,0,
	0,-1,0,
	0,0,1,
	0,0,-1
}; 
int BFS(int a,int b,int c){
	while(Q.empty()==false){
		N now=Q.front();
		Q.pop();
		for(int i=0;i<6;i++){
			int nx=now.x+go[i][0];
			int ny=now.y+go[i][1];
			int nz=now.z+go[i][2];
			if(nx<0 || nx>=a || ny<0 || ny>=b || nz<0 ||nz>=c) continue;
			if(maze[nx][ny][nz]==1) continue;
			if(mark[nx][ny][nz]==true) continue;
			N tmp;
			tmp.x=nx;
			tmp.y=ny;
			tmp.z=nz;
			tmp.t=now.t+1;
			Q.push(tmp);
			mark[nx][ny][nz]=true;
			if(nx=a-1 && ny==b-1 && nz==c-1) return tmp.t; 
		}
	}
	return -1;
} 
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		int a,b,c,t;
		scanf("%d%d%d%d",&a,&b,&c,&t);
		for(int i=0;i<a;i++){
			for(int j=0;j<b;j++){
				for(int k=0;k<c;k++){
					scanf("%d",&maze[i][j][k]);
					mark[i][j][k]=false;
				}
			}
		}
		while(Q.empty==false) Q.pop();
		mark[0][0][0]=true;
		N tmp;
		tmp.t=tmp.y=tmp.x=tmp.z=0;
		Q.push(tmp);
		int rec=BFS(a,b,c);
		if(rec<=t) printf("%d\n",rec);
		else printf("-1\n"); 
	}
	return 0;
}
//倒可乐次数问题
#include<stdio.h>
#include<queue>
using namespace std;
struct N{
	int a,b,c;
	int t;
}; 
queue<N> Q;
bool mark[101][101][101];
void AtoB(int &a,int sa,int &b,int sb){
	if(sb-b>=a){
		b+=a;
		a=0;
	}
	else{
		a-=sb-b;
		b=sb;
	}
} 
int BFS(int s,int nn,int m){
	while(Q.empty()==false){
		N now=Q.front();
		Q.pop();
		int a,b,c;
		
		a=now.a;
		b=now.b;
		c=now.c;
		AtoB(a,s,b,n);//a倒b 
		if(mark[a][b][c]==false){
			mark[a][b][c]=true;
			N tmp;
			tmp.a=a;
			tmp.b=b;
			tmp.c=c;
			tmp.t=now.t+1;
			if(a==s/2 && b==s/2) return tmp.t;
			if(c==s/2 && b==s/2) return tmp.t;
			if(a==s/2 && b==s/2) return tmp.t;
			Q.push(tmp);
		}
		
		a=now.a;
		b=now.b;
		c=now.c;
		AtoB(b,n,a,s);//b倒a 
		if(mark[a][b][c]==false){
			mark[a][b][c]=true;
			N tmp;
			tmp.a=a;
			tmp.b=b;
			tmp.c=c;
			tmp.t=now.t+1;
			if(a==s/2 && b==s/2) return tmp.t;
			if(c==s/2 && b==s/2) return tmp.t;
			if(a==s/2 && b==s/2) return tmp.t;
			Q.push(tmp);
		}
		
		a=now.a;
		b=now.b;
		c=now.c;
		AtoB(a,s,c,m);//a倒c 
		if(mark[a][b][c]==false){
			mark[a][b][c]=true;
			N tmp;
			tmp.a=a;
			tmp.b=b;
			tmp.c=c;
			tmp.t=now.t+1;
			if(a==s/2 && b==s/2) return tmp.t;
			if(c==s/2 && b==s/2) return tmp.t;
			if(a==s/2 && b==s/2) return tmp.t;
			Q.push(tmp);
		}
		
		a=now.a;
		b=now.b;
		c=now.c;
		AtoB(c,m,a,s);//c倒a 
		if(mark[a][b][c]==false){
			mark[a][b][c]=true;
			N tmp;
			tmp.a=a;
			tmp.b=b;
			tmp.c=c;
			tmp.t=now.t+1;
			if(a==s/2 && b==s/2) return tmp.t;
			if(c==s/2 && b==s/2) return tmp.t;
			if(a==s/2 && b==s/2) return tmp.t;
			Q.push(tmp);
		}
		
		a=now.a;
		b=now.b;
		c=now.c;
		AtoB(b,n,c,m);//b倒c 
		if(mark[a][b][c]==false){
			mark[a][b][c]=true;
			N tmp;
			tmp.a=a;
			tmp.b=b;
			tmp.c=c;
			tmp.t=now.t+1;
			if(a==s/2 && b==s/2) return tmp.t;
			if(c==s/2 && b==s/2) return tmp.t;
			if(a==s/2 && b==s/2) return tmp.t;
			Q.push(tmp);
		}
		
		a=now.a;
		b=now.b;
		c=now.c;
		AtoB(c,m,b,n);//c倒b 
		if(mark[a][b][c]==false){
			mark[a][b][c]=true;
			N tmp;
			tmp.a=a;
			tmp.b=b;
			tmp.c=c;
			tmp.t=now.t+1;
			if(a==s/2 && b==s/2) return tmp.t;
			if(c==s/2 && b==s/2) return tmp.t;
			if(a==s/2 && b==s/2) return tmp.t;
			Q.push(tmp);
		}
	}
	return -1;
}
int main(){
	int s,n,m;
	while(scanf("%d%d%d",&s,&n,&m)!=EOF){
		if(s==0) break;
		if(S%2==1){
			puts("NO");
			continue;
		}
		for(int i=0;i<=s;i++){
			for(int j=0;j<=n;j++){
				for(int k=0;k<=m;k++){
					mark[i][j][k]=false;
				}
			}
		}
		N tmp;
		tmp.a=s;
		tmp.b=0;
		tmp.c=0;
		tmp.t=0;
		while(Q.empty()==false) Q.pop();
		Q.push(tmp);
		mark[s][0][0]=true;
		int rec=BFS(s,n,m);
		if(rec==-1)
			puts("NO");
		else printf("%d\n",rec);
	}
	return 0;
}
