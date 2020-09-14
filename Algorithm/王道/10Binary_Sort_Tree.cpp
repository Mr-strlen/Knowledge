//二叉排序树建立 前序 中序 后序输出
#include<cstdio>
#include<cstring>
using namespace std; 
struct Node{
	Node *lchild;
	Node *rchild;
	int c;
}Tree[110];
int loc;
Node *creat(){
	Tree[loc].lchild=Tree[loc].rchild=NULL;
	return &Tree[loc++];
}
//后序遍历
void postOrder(Node *T){
	if(T->lchild!=NULL){
		postOrder(T->lchild);
	}
	if(T->rchild!=NULL){
		postOrder(T->rchild);
	}
	printf("%d",T->c);
}
//中序遍历
void inOrder(Node *T){
	if(T->lchild!=NULL){
		postOrder(T->lchild);
	}
	printf("%d",T->c);
	if(T->rchild!=NULL){
		postOrder(T->rchild);
	}
} 
//前序遍历 
void preOrder(Node *T){
	printf("%d",T->c);
	if(T->lchild!=NULL){
		postOrder(T->lchild);
	}
	if(T->rchild!=NULL){
		postOrder(T->rchild);
	}
} 
Node *Insert(Node *T,int x){
	if(T==NULL){
		T=creat();
		T->c=x;
		return T;
	}
	else if(x<T->c)
	T->lchild=Insert(T->lchild,x);
	else if(x>T->c)
	T->rchild=Insert(T->rchild,x);
	return T;
}
int main(){
	int n;
	while(scanf("%d",&n)!=EOF){
		loc=0;
		Node *T=NULL;
		for(int i=0;i<n;i++){
			int x;
			scanf("%d",&x);
			T=Insert(T,x);
		}
		preOrder(T);
		printf("\n");
		inOrder(T);
		printf("\n");
		postOrder(T);
		printf("\n");
	}
	return 0;
}
//二叉树是否相同 两种遍历结果都一样
#include<cstdio>
#include<cstring>
struct Node{
	Node *lchild;
	Node *rchild;
	int c;
}Tree[110]; 
int loc;
Node *creat(){
	Tree[loc].lchild=Tree[loc].rchild=NULL;
	return &Tree[loc++];
}
char str1[25],str2[25];
int size1.size2;
char *str;
int *size;
//后序遍历
void postOrder(Node *T){
	if(T->lchild!=NULL){
		postOrder(T->lchild);
	}
	if(T->rchild!=NULL){
		postOrder(T->rchild);
	}
	str[(*size)++]=T->c+'0'; 
}
//中序遍历
void inOrder(Node *T){
	if(T->lchild!=NULL){
		postOrder(T->lchild);
	}
	str[(*size)++]=T->c+'0'; 
	if(T->rchild!=NULL){
		postOrder(T->rchild);
	}
} 
Node *Insert(Node *T,int x){
	if(T==NULL){
		T=creat();
		T->c=x;
		return T;
	}
	else if(x<T->c)
	T->lchild=Insert(T->lchild,x);
	else if(x>T->c)
	T->rchild=Insert(T->rchild,x);
	return T;
}
int main(){
	int n;
	char tmp[12];
	while(scanf("%d",&n)!=EOF && n!=0){
		loc=0;
		Node *T=NULL;
		scanf("%s",tmp);
		for(int i=0;tmp[i]!=0;i++){
			T=Insert(T,tmp[i]-'0');
		}
		size1=0;
		str=str1;
		size=&size1;
		postOrder(T);
		inOrder(T);
		str1[size1]='\0';
		while(n--!=0){
			scanf("%s",tmp);
			Node *T2=NULL;
			for(int i=0;tmp[i]!=0;i++){
				T2=Insert(T2,tmp[i]-'0');
			}
			size2=0;
			str=str2;
			size=&size2;
			postOrder(T2);
			inOrder(T2);
			str2[size2]='\0';
			puts(strcmp(str1,str2)==0?"YES":"NO");
		}
	}
	return 0;
}
