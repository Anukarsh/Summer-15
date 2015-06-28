//Program to generate random tree and traverse them
//Input - The number of nodes needed in the given tree
//Output - All the three ordered traversal of the generated random tree

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct node
{
 	struct node *left;
	int data;
	struct node *right;
};

void addnew( struct node ** , int );
void inorder( struct node *);
void preorder( struct node *);
void postorder( struct node *);

struct node * getnode()
{
	return ( struct node *) malloc( sizeof( struct node ));
}

	
void main( )
{
	struct node *R;
	int n , i , data;
	R = NULL;

	printf("Enter number of nodes to create \n");
	scanf("%d", &n);
	//randomly generating the nodes and adding them into the tree
	for(i=1; i<=n ;i++)
	{
		data = rand()%100;
		addnew( &R , data );
	}
	
	printf("\n Inorder traversal \n");
	inorder( R );

	printf("\n Preorder traversal \n");
	preorder( R );

	printf("\n Postorder traversal \n");
	postorder( R );



}

//function to add new nodes to the tree
void addnew( struct node **q,int data )
{
	if( *q == NULL )
	{
	   *q = getnode( );
	   (*q)->left = NULL;
	   (*q)->right =NULL;
	   (*q)->data = data;
	   return;
	}

	if( (*q)->data > data )
	 addnew( &(*q)->left , data );
	else
	 addnew( &(*q)->right , data );
}

//function to display the inorder traversal of the tree
void inorder( struct node *q )
{
	if( q!= NULL )
	{
		 inorder( q->left );
		 printf("%d\t", q->data );
		 inorder( q->right);
	}
}

//function to display the preorder traversal of the tree
void preorder( struct node *q )
{
	if( q!= NULL )
	{
		printf("%d\t", q->data );
		preorder( q->left );
		preorder( q->right);
	}
}

//function to display the postorder traversal of the tree
void postorder( struct node *q )
{
	if( q!= NULL )
	{
		postorder( q->left );
		postorder( q->right);
		printf("%d\t", q->data );
	}
}











