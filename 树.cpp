#include<stdio.h>
#include<malloc.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
typedef char Qelem;
typedef struct binode
{
    Qelem  data;                                 //定义树
    struct binode  *fchild, *nsib;
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
void crtBiTree(BiTree *T) ;							//递归创建孩子兄弟链表
void CreatBiTree(BiTree *T);						//读边法建立孩子兄弟链表
void preorder(BiTree root) ;						//先根遍历树
void inorder (BiTree  root);						//后根遍历树
int  Depth(BiTree root);							//求树的深度
void search(BiTree T,char x,BiTree *p);             //查找某结点
int insert(BiTree *T,char fa,char ch);              //插入某结点
void postdelete(BiTree T);                          //删除整棵树
void Delete(BiTree p,BiTree f);                     //删除中间结点及其子树
void deletetree(BiTree *T,char fa,char ch);         //综合删除函数
void dispBitree(BiTree T, int n);		        	//凹入表显示树
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


void crtBiTree(BiTree *T)									  //递归建树
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
      crtBiTree(&(*T)->fchild);   
      crtBiTree(&(*T)->nsib);   
    }
    }


void CreatBiTree(BiTree *T)									//读边法建立树
{
	Qlink Q;
	initqueue(&Q);
	*T=NULL;
	char fa,ch;
	scanf("%c%c",&fa,&ch);
	BiTree p,r;
	while (ch!='#')
	{   
		p=(BiTree)malloc(sizeof(BiNode)); 
        p->data=ch; 
        p->fchild= p->nsib=NULL;  
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
	if (s->fchild==NULL) 
	{ 
		s->fchild = p; 
		r=p;
	} 
	else  
	{
		r->nsib =p;
		r=p;
	}    

		}
	scanf("%c%c",&fa,&ch);
    } 
} 

void preorder(BiTree root)										 //先根遍历树
{
   if (root==NULL)  return;     
   else
   {   printf("%c",root->data);                       
       preorder(root->fchild);    
       preorder(root->nsib);    
   }
}
void inorder (BiTree  root)										 //后根遍历树
{
         if (root==NULL) return;     
         else
         {     inorder(root->fchild);            
               printf("%c",root->data);
               inorder(root->nsib);
         }
}

int  Depth(BiTree root)											 //求树的深度
{   
	int hl,hr;
    if (root==NULL) return 0;                     
    else
   {    
		hl= Depth(root->fchild);
        hr= Depth(root ->nsib);
		int max;
        return max=hl+1>hr?hl+1:hr;
   }
}

void search(BiTree T,char x,BiTree *p)                          //查找结点
{
	if(T)
	{
		if(x==T->data)
		{
			*p=T;
			return ;
		}
		search(T->fchild,x,p);
		search(T->nsib,x,p);

	}
	
}

int insert(BiTree *T,char fa,char ch)                          //插入结点
{
	BiTree p=NULL,q,s;
	search(*T,fa,&p);
	if(p)
	{
		s=(BiTree)malloc(sizeof(BiNode));
		s->data=ch;
		s->fchild=s->nsib=NULL;
		if(!p->fchild)
			p->fchild=s;
		else
		{
			q=p->fchild;
			while(q->nsib)
				q=q->nsib;
			q->nsib=s;
		}
		return 1;
	}
	return 0;

}

 void postdelete(BiTree T)                                    //删除整棵树
{
	if(T)
	{
		postdelete(T->fchild);    
		postdelete(T->nsib);
		free(T);
	}
}

void Delete(BiTree p,BiTree f)                               //删除结点
{
	if(f->fchild==p)
	{
		f->fchild=p->nsib;
		p->nsib=NULL;
		postdelete(p);
	}
	if(f->nsib==p)
	{
		f->nsib=p->nsib;
		p->nsib=NULL;
		postdelete(p);
	}
}

void deletetree(BiTree *T,char fa,char ch)                  //删除函数
{
	BiTree pfa=NULL,pch=NULL;
	if(fa=='#')
	{
		postdelete(*T);
		*T=NULL;
		return;
	}
	else
	{
		search(*T,fa,&pfa);
		search(*T,ch,&pch);
		if(pfa==NULL||pch==NULL)
		{
			printf("数据有误，不能删除！\n");
			return;
		}
		else
		{
			if(pfa->fchild!=pch)
			{
				pfa=pfa->fchild;
				while(pfa)
				{
					if(pfa->nsib==pch)  break;
					pfa=pfa->nsib;
				}
			}
			Delete(pch,pfa);
		}
	}
}

void dispBitree(BiTree T, int n)					     	 //凹入表显示树
{	
	int i,k;	
	if(T)
	{  
      //len=strlen(T->data);
		for(i=1;i<n;i++)
			putchar('-');
	    printf("%c\n",T->data);    

		for(k=1+i;k<n;k++)
	    putchar('-');
		putchar('\n');
	    dispBitree(T->fchild,n+4);
        dispBitree(T->nsib,n);
	}	
}

int menu()
{
	int n;
	while(1)
	{
		system("cls");
		printf("***二叉树基本功能应用***\n");
		printf(" 1 根左右顺序创建孩子兄弟链表\n");
		printf(" 2 根据读边法创建孩子兄弟链表\n");
		printf(" 3 先根遍历法输出孩子兄弟链表\n");
		printf(" 4 后序遍历法输出孩子兄弟链表\n");
		printf(" 5 查找结点\n");
		printf(" 6 插入结点\n");
		printf(" 7 求树的深度\n");
		printf(" 8 凹入表输出显示树\n");
		printf(" 9 删除\n");
		printf(" 0 退出程序 \n");
		printf("************************\n");
		printf("请选择功能编号0-9  ");
			scanf("%d",&n);
		getchar();
		if(n<0||n>10)
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
			printf("输入先序遍历形式字符串以创建孩子兄弟链表：\n");
			crtBiTree(&T) ;
			printf("按任意键继续！\n");
			getch();
			break;
		case 2:
			printf("按读边法输入树转化成的二叉树信息，字符与整数之间无间隔（形如#aabacaecdd#）:\n");
			CreatBiTree(&T);
			printf("按任意键继续！\n");
			getch();
			break;
		case 3:
			printf("先根遍历序列为：");
			preorder(T);
			printf("\n");
			printf("按任意键继续！\n");
			getch();
			break;
		case 4:
			printf("后根遍历序列为：");
			inorder (T);	
			printf("\n");
			printf("按任意键继续！\n");
			getch();
			break;
		case 5:
			BiTree p;
			char s;  
			printf("请输入要查找的结点的内容：");
			scanf("%c",&s);
			search(T,s,&p);
			printf("\n");
	    	printf("按任意键继续！\n");
			getch();
			break;
		case 6:
			char fa,ch;
			printf("请输入要插入的结点的双亲结点及要插入的结点的内容：");
			scanf("%c%c",&fa,&ch);
			insert(&T,fa,ch);
			printf("\n");
			printf("按任意键继续！\n");
			getch();
			break;
		case 7:
			int m;
			m=Depth(T);
			printf("该树的深度为%d",m);
			printf("\n");
			printf("按任意键继续！\n");
			getch();
			break;
		case 8:
			int t;
			t=Depth(T);
			dispBitree(T, t);
			printf("按任意键继续！\n");
			getch();
			break;
		case 9:
			char fa1,ch1;
			printf("请输入要删除的结点的双亲结点：");
			scanf("%c",&fa1);
			getchar();
			printf("请输入要删除的结点的内容:");
			scanf("%c",&ch1);
			deletetree(&T,fa1,ch1);
			printf("\n");
			printf("按任意键继续！\n");
			getch();
			break;
		case 0:
			exit(0);

		}
	}

}


