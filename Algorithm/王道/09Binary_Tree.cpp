//二叉树遍历 利用前中 还原后
#include<cstdio>
#include<cstring>
using namespace std;
struct Node{
	Node *lchild;
	Node *rchild;
	char c;
}Tree[50];
int loc;
Node *creat(){
	Tree[loc].lchild=Tree[loc].rchild =NULL;
	return &Tree[loc++];
}
char str1[30],str2[30];
void postOrder(Node *T){
	if(T->lchild!=NULL){
		postOrder(T->lchild);
	}
	if(T->rchild!=NULL){
		postOrder(T->rchild);
	}
	printf("%c",T->c);
}
Node *build(int s1,int e1,int s2,int e2){
	Node* ret=creat();
	ret->c=creat();
	ret->c=str1[s1];
	int rootldx;
	for(int i=s2;i<=e2;i++){
		if(str2[i]==str1[s1]){
			rootldx=i;
			break;
		}
	}
	if(rootldx!=s2){
		ret->lchild=build(s1+1,s1+(rootldx-s2),s2,rootidx-1);
	}
	if(rootldx!=e2){
		ret->rchild=build(s1+(rootldx-s2)+1,e1,rootldx+1,e2);
	}
	return ret;
}

int main()
{
	while(scanf("%s",str1)!=EOF){
		scanf("%s",str2);
		loc=0;
		int L1=strlen(str1);
		int L2=strlen(str2);
		Node *T=build(0,L1-1,0,L2-1);
		postOrder(T);
		printf("\n"); 
	}
	return 0;
}
