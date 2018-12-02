#include<stdio.h>
#include<malloc.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
typedef char Qelem;
typedef struct binode
{
    Qelem  data;                                 //������
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
	Queuelink front;                             //�������
	Queuelink rear;
}Qlink; 

int initqueue(Qlink *Q);							//��ʼ������
int queueempty(Qlink Q);							//�ж϶����Ƿ�Ϊ��
int enqueue(Qlink *Q,Lelem e);						//������
BiTree getheadqueue(Qlink Q);						//ȡ��ͷԪ��
BiTree deletequeue(Qlink *Q);						//������
void crtBiTree(BiTree *T) ;							//�ݹ鴴�������ֵ�����
void CreatBiTree(BiTree *T);						//���߷����������ֵ�����
void preorder(BiTree root) ;						//�ȸ�������
void inorder (BiTree  root);						//���������
int  Depth(BiTree root);							//���������
void search(BiTree T,char x,BiTree *p);             //����ĳ���
int insert(BiTree *T,char fa,char ch);              //����ĳ���
void postdelete(BiTree T);                          //ɾ��������
void Delete(BiTree p,BiTree f);                     //ɾ���м��㼰������
void deletetree(BiTree *T,char fa,char ch);         //�ۺ�ɾ������
void dispBitree(BiTree T, int n);		        	//�������ʾ��
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


void crtBiTree(BiTree *T)									  //�ݹ齨��
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


void CreatBiTree(BiTree *T)									//���߷�������
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

void preorder(BiTree root)										 //�ȸ�������
{
   if (root==NULL)  return;     
   else
   {   printf("%c",root->data);                       
       preorder(root->fchild);    
       preorder(root->nsib);    
   }
}
void inorder (BiTree  root)										 //���������
{
         if (root==NULL) return;     
         else
         {     inorder(root->fchild);            
               printf("%c",root->data);
               inorder(root->nsib);
         }
}

int  Depth(BiTree root)											 //���������
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

void search(BiTree T,char x,BiTree *p)                          //���ҽ��
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

int insert(BiTree *T,char fa,char ch)                          //������
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

 void postdelete(BiTree T)                                    //ɾ��������
{
	if(T)
	{
		postdelete(T->fchild);    
		postdelete(T->nsib);
		free(T);
	}
}

void Delete(BiTree p,BiTree f)                               //ɾ�����
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

void deletetree(BiTree *T,char fa,char ch)                  //ɾ������
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
			printf("�������󣬲���ɾ����\n");
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

void dispBitree(BiTree T, int n)					     	 //�������ʾ��
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
		printf("***��������������Ӧ��***\n");
		printf(" 1 ������˳�򴴽������ֵ�����\n");
		printf(" 2 ���ݶ��߷����������ֵ�����\n");
		printf(" 3 �ȸ���������������ֵ�����\n");
		printf(" 4 �����������������ֵ�����\n");
		printf(" 5 ���ҽ��\n");
		printf(" 6 ������\n");
		printf(" 7 ���������\n");
		printf(" 8 ����������ʾ��\n");
		printf(" 9 ɾ��\n");
		printf(" 0 �˳����� \n");
		printf("************************\n");
		printf("��ѡ���ܱ��0-9  ");
			scanf("%d",&n);
		getchar();
		if(n<0||n>10)
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
			printf("�������������ʽ�ַ����Դ��������ֵ�����\n");
			crtBiTree(&T) ;
			printf("�������������\n");
			getch();
			break;
		case 2:
			printf("�����߷�������ת���ɵĶ�������Ϣ���ַ�������֮���޼��������#aabacaecdd#��:\n");
			CreatBiTree(&T);
			printf("�������������\n");
			getch();
			break;
		case 3:
			printf("�ȸ���������Ϊ��");
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
			BiTree p;
			char s;  
			printf("������Ҫ���ҵĽ������ݣ�");
			scanf("%c",&s);
			search(T,s,&p);
			printf("\n");
	    	printf("�������������\n");
			getch();
			break;
		case 6:
			char fa,ch;
			printf("������Ҫ����Ľ���˫�׽�㼰Ҫ����Ľ������ݣ�");
			scanf("%c%c",&fa,&ch);
			insert(&T,fa,ch);
			printf("\n");
			printf("�������������\n");
			getch();
			break;
		case 7:
			int m;
			m=Depth(T);
			printf("���������Ϊ%d",m);
			printf("\n");
			printf("�������������\n");
			getch();
			break;
		case 8:
			int t;
			t=Depth(T);
			dispBitree(T, t);
			printf("�������������\n");
			getch();
			break;
		case 9:
			char fa1,ch1;
			printf("������Ҫɾ���Ľ���˫�׽�㣺");
			scanf("%c",&fa1);
			getchar();
			printf("������Ҫɾ���Ľ�������:");
			scanf("%c",&ch1);
			deletetree(&T,fa1,ch1);
			printf("\n");
			printf("�������������\n");
			getch();
			break;
		case 0:
			exit(0);

		}
	}

}


