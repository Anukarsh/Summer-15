//Program to construct an AVL tree
//Input : The number of nodes in the tree
//Output : The inorder traversal of the Tree

#include<stdio.h>
#include<stdlib.h>

struct node
{
	int key;
	char BI;
	struct node *llink,*rlink;
};

int level,mark,i;
char dir[20];
typedef struct node *NODE;
NODE t,x,y,z,f,p;
NODE path[20];
char d;

//function to create a new leaf node
NODE Create_Leaf(int key,NODE N)
{
	N=(NODE)malloc(sizeof(struct node));
	if(N==NULL)
	{
		printf("\n No memory ");
		exit(0);
	}
	N->llink=N->rlink=NULL;
	N->BI='B';
	N->key=key;
	return N;
}


//Program to create a header node
NODE Create_Head(int key,NODE H)
{
	H=Create_Leaf(0,H);
	H->llink=H->rlink=H;
	return H;
}


//Program to insert a node into the tree
NODE Insert(int key,NODE H)
{
	NODE NN;
	if(H->llink==H)
	{
		NN=Create_Leaf(key,NN);
		H->llink=NN;
		return H;
	}
	level=0;
	dir[level]='L';
	path[level]=H;
	t=H->llink;
	while(1)
	{
		//if the key entered is lesser than the present key
		if(key<t->key)
		{
			if(t->llink!=NULL)
			{
				level=level+1;
				path[level]=t;
				dir[level]='L';
				t=t->llink;
			}
			else
			{
				NN=Create_Leaf(key,NN);
				t->llink=NN;
				level=level+1;
				path[level]=t;
				dir[level]='L';
				break;
			}
		}
		else if(key>t->key)
		{
			if(t->rlink!=NULL)
			{
				level=level+1;
				path[level]=t;
				dir[level]='R';
				t=t->rlink;
			}
			else
			{
				NN=Create_Leaf(key,NN);
				t->rlink=NN;
				level=level+1;
				path[level]=t;
				dir[level]='R';
				break;
			}
		}//if the keys are equal 
		else
		{
			key = key + 1;
			return H;
		}
	}
	mark=0;
	//to maintain the balance factor of the nodes
	for(i=level;i>=1;i--)
	{
		p=path[i];
		if(p->BI!='B')
		{
			mark=1;
			break;
		}
	}
	//To maintain the path of the tree
	for(i=mark+1;i<=level;i++)
	{
		if(key<path[i]->key)
		{
			path[i]->BI='L';
		}
		else path[i]->BI='R';
	}
	if(mark==0)
	{
		return H;
	}
	d=dir[mark];
	x=path[mark];
	y=path[mark+1];
	if(x->BI!=d)
	{
		x->BI='B';
		return H;
	}
	if(y->BI==d)
	{
		if(d=='L')
		{
			x->llink=y->rlink;
			y->rlink=x;
		}
		else
		{
			x->rlink=y->llink;
			y->llink=x;
		}
		x->BI=y->BI='B';
		f=path[mark-1];
		if(x==f->llink)
		{
			f->llink=y;
		}
		else f->rlink=y;
		return H;
	}
	if(d=='L')
	{
		z=y->rlink;
		y->rlink=z->llink;
		z->llink=y;
		x->llink=z->rlink;
		z->rlink=x;
	}
	else
	{
		z=y->llink;
		y->llink=z->rlink;
		z->rlink=y;
		x->rlink=z->llink;
		z->llink=x;
	}
	f=path[mark-1];
	if(x==f->llink)
	{
		f->llink=z;
	}
	else f->rlink=z;
	if(z->BI==d)
	{
		y->BI=z->BI='B';
		if(d=='L')
		{
			x->BI='R';
		}
		else x->BI='L';
	}
	else
	{
		if(z->BI=='B')
		{
			x->BI=y->BI=z->BI='B';
		}
		else
		{
			x->BI=z->BI='B';
			y->BI=d;
		}
	}
	return H;
}

//Program to display the tree in preorder
void Preorder(NODE R)
{
	if(R==NULL)
		return;
	printf(" %d\t",R->key);
	Preorder(R->llink);
	Preorder(R->rlink);
}


int main()
{
	NODE H=NULL;
	int n,k,j;
	H=Create_Head(0,H);
	printf("\n Enter number of nodes ");
	scanf("%d",&n);
	for(j=0;j<n;j++)
	{
		k = rand()%10;
		H=Insert(k,H);
	}
	if(H->llink!=NULL)
	{
		Preorder(H->llink);
		printf("\n");
	}
	else
	{
		Preorder(H->rlink);
		printf("\n");
	}
}

