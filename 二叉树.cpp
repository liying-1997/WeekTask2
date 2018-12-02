#include<stdio.h>
#include<malloc.h>
#include <stdlib.h>
#include <conio.h>
typedef char Qelem;
typedef struct binode
{
    Qelem  data;                                 //������
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
	Queuelink front;                             //�������
	Queuelink rear;
}Qlink; 


int initqueue(Qlink *Q);							//��ʼ������
int queueempty(Qlink Q);							//�ж϶����Ƿ�Ϊ��
int enqueue(Qlink *Q,Lelem e);						//������
BiTree getheadqueue(Qlink Q);						//ȡ��ͷԪ��
BiTree deletequeue(Qlink *Q);						//������
void crtBiTree(BiTree *T) ;							//���ַ�����������������������ʽ����������
void CreatBiTree(BiTree *T);						//���߷�����������
void preorder(BiTree root) ;						//ǰ�����
void inorder (BiTree  root);						//�������
void postorder(BiTree  root);						//�������
void layer (BiTree T);								//�������
int  Depth(BiTree root);							//����������
void dispBitree(BiTree T, int n, char c);			//�����İ������ʾ������
int menu();											//�˵�


int initqueue(Qlink *Q)										 //��ʼ������
{
	Q->front=Q->rear=(Queuelink)malloc(sizeof(Qnode));  
	if(Q->front==NULL)
		return 0;
	Q->front->next=NULL;
	return 1;
}
int queueempty(Qlink Q)										 //�ж϶����Ƿ�Ϊ��
{
	if(Q.front==Q.rear)                                
		return 1;
	else 

		return 0;
}

int enqueue(Qlink *Q,Lelem e)								 //������
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

BiTree getheadqueue(Qlink Q)								 //ȡ��ͷԪ��
{
	BiTree e;
	if(Q.rear==Q.front)                             
		return 0;
	e=Q.front->next->data;
	return e;
}

BiTree deletequeue(Qlink *Q)								 //������
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


void crtBiTree(BiTree *T)									  //���ַ�����������������������ʽ����������
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


void CreatBiTree(BiTree *T)									//���߷�����������
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



void preorder(BiTree root)										 //ǰ�����
{
   if (root==NULL)  return;     
   else
   {   printf("%c",root->data);                       
       preorder(root->lchild);    
       preorder(root->rchild);    
   }
}
void inorder (BiTree  root)										 //�������
{
         if (root==NULL) return;     
         else
         {     inorder(root->lchild);            
               printf("%c",root->data);
               inorder(root->rchild);
         }
}
void postorder(BiTree  root)									 //�������
{	
    if (root==NULL) return; 
    else
    {    postorder(root->lchild);                
         postorder(root->rchild); 
         printf("%c",root->data);       
    }
}
void layer (BiTree T)											  //�������
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
int  Depth(BiTree root)											 //������������
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
void dispBitree(BiTree T, int n, char c)						 //�����İ������ʾ������
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
		printf("***��������������Ӧ��***\n");
		printf(" 1 ������˳�򴴽�������\n");
		printf(" 2 ���ݶ��߷�����������\n");
		printf(" 3 ������������������\n");
		printf(" 4 ������������������\n");
		printf(" 5 ������������������\n");
		printf(" 6 ������������������\n");
		printf(" 7 ������Ķ����������\n");
		printf(" 8 ����������ʾ������\n");
		printf(" 0 �˳����� \n");
		printf("************************\n");
		printf("��ѡ���ܱ��0-8  ");
			scanf("%d",&n);
		getchar();
		if(n<0||n>9)
		{	printf("��������������ѡ�񣡰����������\n");
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
			printf("�������������ʽ�ַ����Դ�����������\n");
			crtBiTree(&T) ;
			printf("�������������\n");
			getch();
			break;
		case 2:
			printf("�����߷������������Ϣ���ַ�������֮���޼��������#a0ab0bc1cd0ce1d#0��:\n");
			CreatBiTree(&T);
			printf("�������������\n");
			getch();
			break;
		case 3:
			printf("�����������Ϊ��");
			preorder(T);
			printf("\n");
			printf("�������������\n");
			getch();
			break;
		case 4:
			printf("�����������Ϊ��");
			inorder (T);	
			printf("\n");
			printf("�������������\n");
			getch();
			break;
		case 5:
			printf("�����������Ϊ��");
			postorder(T);
			printf("\n");
			printf("�������������\n");
			getch();
			break;
		case 6:
			printf("�����������Ϊ��");
			layer (T);
			printf("\n");
			printf("�������������\n");
			getch();
			break;
		case 7:
			int m;
			m=Depth(T);
			printf("�ö����������Ϊ%d",m);
			printf("\n");
			printf("�������������\n");
			getch();
			break;
		case 8:
			int t;
			t=Depth(T);
			dispBitree(T, t, s);
			printf("�������������\n");
			getch();
			break;
		case 0:
			exit(0);

		}
	}

}


