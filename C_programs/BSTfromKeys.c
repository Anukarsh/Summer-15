//Program to generate binary trees from given set of keys and traverse them
//Input - The number of nodes needed in the given tree
//Output - Pre ordered traversal of the generated random tree

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct node
{
 	struct node *left;
	int data;
	struct node *right;
};

struct node * root;
void addnew( struct node ** , int );
void inorder( struct node *);
void preorder( struct node *);
void postorder( struct node *);

struct node * getnode()
{
	return ( struct node *) malloc( sizeof( struct node ));
}

void printArray(int *a,int n) 
{
	int i;
	for(i=0;i<=n;i++)	
		addnew(&root , a[i]);
	preorder(root);
}


void swap (int *x, int *y) {
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

//to generate all the permutation of the keys
void permute(int *a, int i, int n) 
{
	int j;
	if(i==n)
		printArray(a,n);
	else 
	{
	        for (j = i; j <= n; j++) 	
		{
	          swap((a+i), (a+j));
	          permute(a, i+1, n);
	          swap((a+i), (a+j)); 
	       }
	}
}
	
void main( )
{
	struct node *R;
	int n , i , data;
	R = NULL;
	int a[100];
	printf("Enter number of nodes to create \n");
	scanf("%d", &n);
	printf("Entert the nodes of the tree\n");
	for(i = 0 ; i<n ; i++)
		scanf("%d" , &a[i]);

	permute(a,0,n-1);
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


//function to display the preorder traversal of the tree
void preorder( struct node *q )
{
	if( q!= NULL )
	{
		printf("%d\t", q->data );
		preorder( q->left );
		preorder( q->right);
	}
	printf("\n");
}













