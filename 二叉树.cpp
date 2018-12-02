#include<stdio.h>
#include<malloc.h>
#include <stdlib.h>
#include <conio.h>
typedef char Qelem;
typedef struct binode
{
    Qelem  data;                                 //定义树
    struct binode  *lchild, *rchild;
}BiNode,*BiTree;
typedef	BiTree Lelem;

typedef struct qnode
{
	Lelem data;
	struct qnode *next;
}Qnode, *Queuelink;
typedef struct 
{
	Queuelink front;                             //定义队列
	Queuelink rear;
}Qlink; 


int initqueue(Qlink *Q);							//初始化队列
int queueempty(Qlink Q);							//判断队列是否为空
int enqueue(Qlink *Q,Lelem e);						//进队列
BiTree getheadqueue(Qlink Q);						//取队头元素
BiTree deletequeue(Qlink *Q);						//出队列
void crtBiTree(BiTree *T) ;							//以字符串“根左子树右子树”形式创建二叉树
void CreatBiTree(BiTree *T);						//读边法建立二叉树
void preorder(BiTree root) ;						//前序遍历
void inorder (BiTree  root);						//中序遍历
void postorder(BiTree  root);						//后序遍历
void layer (BiTree T);								//层序遍历
int  Depth(BiTree root);							//求二叉树深度
void dispBitree(BiTree T, int n, char c);			//左对齐的凹入表显示二叉树
int menu();											//菜单


int initqueue(Qlink *Q)										 //初始化队列
{
	Q->front=Q->rear=(Queuelink)malloc(sizeof(Qnode));  
	if(Q->front==NULL)
		return 0;
	Q->front->next=NULL;
	return 1;
}
int queueempty(Qlink Q)										 //判断队列是否为空
{
	if(Q.front==Q.rear)                                
		return 1;
	else 

		return 0;
}

int enqueue(Qlink *Q,Lelem e)								 //进队列
{
	Queuelink p=(Queuelink)malloc(sizeof(Qnode));     
	if(p==NULL)
		return 0;
	p->data=e;
	p->next=NULL;
	Q->rear->next=p;
	Q->rear=p;
	return 1;
}

BiTree getheadqueue(Qlink Q)								 //取队头元素
{
	BiTree e;
	if(Q.rear==Q.front)                             
		return 0;
	e=Q.front->next->data;
	return e;
}

BiTree deletequeue(Qlink *Q)								 //出队列
{
	Queuelink p;
	if(Q->front==Q->rear)
		return NULL;
	Lelem e;
	e=Q->front->next->data;
	p=Q->front->next;
	Q->front->next=p->next;                          
	if(Q->rear==p)
		Q->rear=Q->front;
	free(p);
	return e;
}


void crtBiTree(BiTree *T)									  //以字符串“根左子树右子树”形式创建二叉树
{
	char ch;
    scanf("%c",&ch);
    if (ch=='#') 
		*T=NULL;
    else 
	{
		*T=(BiTree)malloc(sizeof(BiNode));
      if (*T==NULL)                                     
		  return ;
      (*T)->data = ch;             
      crtBiTree(&(*T)->lchild);   
      crtBiTree(&(*T)->rchild);   
    }
    }


void CreatBiTree(BiTree *T)									//读边法建立二叉树
{
	Qlink Q;
	initqueue(&Q);
	*T=NULL;
	char fa,ch;
	int lrflag;
	scanf("%c%c%d",&fa,&ch,&lrflag);
	BiTree p;
	while (ch!='#')
	{   
		p=(BiTree)malloc(sizeof(BiNode)); 
        p->data=ch; 
        p->lchild= p->rchild=NULL;  
        enqueue(&Q,p);
        if (fa=='#') 
			*T=p;  
        else 
		 {  
			BiTree s;
			s=getheadqueue(Q);   
		while (s->data!=fa ) 
		{  
			deletequeue(&Q);
			s=getheadqueue(Q);
		}                     
	if (lrflag==0) 
    s->lchild = p;  
	else  
    s->rchild = p;    

		}
	scanf("%c%c%d",&fa,&ch,&lrflag);
    } 
} 



void preorder(BiTree root)										 //前序遍历
{
   if (root==NULL)  return;     
   else
   {   printf("%c",root->data);                       
       preorder(root->lchild);    
       preorder(root->rchild);    
   }
}
void inorder (BiTree  root)										 //中序遍历
{
         if (root==NULL) return;     
         else
         {     inorder(root->lchild);            
               printf("%c",root->data);
               inorder(root->rchild);
         }
}
void postorder(BiTree  root)									 //后序遍历
{	
    if (root==NULL) return; 
    else
    {    postorder(root->lchild);                
         postorder(root->rchild); 
         printf("%c",root->data);       
    }
}
void layer (BiTree T)											  //层序遍历
{
	Qlink Q;
	initqueue(&Q);
   if(T)                                  
   enqueue(&Q,T); 
   while(!queueempty(Q))
   { 
	   BiTree p;
	   p=deletequeue(&Q); 
       printf("%c",p->data);
       if(p->lchild)
		   enqueue(&Q, p->lchild); 
       if(p->rchild)
		   enqueue(&Q, p->rchild);  
   }
 }
int  Depth(BiTree root)											 //求二叉树的深度
{   
	int hl,hr;
    if (root==NULL) return 0;                     
    else
   {    
		hl= Depth(root->lchild);
        hr= Depth(root ->rchild);
		int max;
        return max=(hl>hr?hl:hr)+1;
   }
}
void dispBitree(BiTree T, int n, char c)						 //左对齐的凹入表显示二叉树
{	
	int i;
	if(T)
	{   
		for(i=1;i<n+2;i++)
			putchar('-');
        putchar('+');
	    printf("%c(%c)\n",T->data,c);               
	    n=n-1;
	    dispBitree(T->lchild,n,'L');
        dispBitree(T->rchild,n,'R');
	}	
}

int menu()
{
	int n;
	while(1)
	{
		system("cls");
		printf("***二叉树基本功能应用***\n");
		printf(" 1 根左右顺序创建二叉树\n");
		printf(" 2 根据读边法创建二叉树\n");
		printf(" 3 先序遍历法输出二叉树\n");
		printf(" 4 中序遍历法输出二叉树\n");
		printf(" 5 后序遍历法输出二叉树\n");
		printf(" 6 层序遍历法输出二叉树\n");
		printf(" 7 求输入的二叉树的深度\n");
		printf(" 8 凹入表输出显示二叉树\n");
		printf(" 0 退出程序 \n");
		printf("************************\n");
		printf("请选择功能编号0-8  ");
			scanf("%d",&n);
		getchar();
		if(n<0||n>9)
		{	printf("输入有误，请重新选择！按任意键继续\n");
		getch();}
		else
			return n;
	}
}

void main()
{
	int n;
	char s='D';
	BiTree T ;
	while(1)
	{
		
		n=menu();
		switch(n)
		{
		case 1:
			printf("输入先序遍历形式字符串以创建二叉树：\n");
			crtBiTree(&T) ;
			printf("按任意键继续！\n");
			getch();
			break;
		case 2:
			printf("按读边法输入二叉树信息，字符与整数之间无间隔（形如#a0ab0bc1cd0ce1d#0）:\n");
			CreatBiTree(&T);
			printf("按任意键继续！\n");
			getch();
			break;
		case 3:
			printf("先序遍历序列为：");
			preorder(T);
			printf("\n");
			printf("按任意键继续！\n");
			getch();
			break;
		case 4:
			printf("中序遍历序列为：");
			inorder (T);	
			printf("\n");
			printf("按任意键继续！\n");
			getch();
			break;
		case 5:
			printf("后序遍历序列为：");
			postorder(T);
			printf("\n");
			printf("按任意键继续！\n");
			getch();
			break;
		case 6:
			printf("层序遍历序列为：");
			layer (T);
			printf("\n");
			printf("按任意键继续！\n");
			getch();
			break;
		case 7:
			int m;
			m=Depth(T);
			printf("该二叉树的深度为%d",m);
			printf("\n");
			printf("按任意键继续！\n");
			getch();
			break;
		case 8:
			int t;
			t=Depth(T);
			dispBitree(T, t, s);
			printf("按任意键继续！\n");
			getch();
			break;
		case 0:
			exit(0);

		}
	}

}


