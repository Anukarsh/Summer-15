//Program to generate a Threaded Tree
//Input: The values to be inserted into the tree and then form the output to be displayed
//Output : Either dotty representation or the inorder represention of the Threaded Tree


#include <stdio.h>
#include <stdlib.h>

struct node
{
         struct node *left;
         int data;
         struct node *right;
        struct node *thread;
         int th;
};

typedef struct node * NODE;

struct node * a[50];
int i=0;

void addnew( struct node ** , int );

//to create a new node
NODE getnode()
{
         return ( struct node *) malloc( sizeof( struct node ));
}

//to display the inorder traversal of the threaded tree
void inorder( struct node *q )
{
        if( q!= NULL )
        {
                 inorder( q->left );
                 a[i++] = q;
                 inorder( q->right);
        }
}

//To generate the threads in the tree
void CreateThread( NODE r)
{
        if(r == NULL)
                return;
        if(r->left)
              CreateThread(r->left);
        i++;
        if(r->right)
                CreateThread(r->right);
        else
        {
                r->thread = a[i] ;

                r->th = 1;
        }
}

//To arrive at the leftmost node of the tree to begin the traversal
NODE left( NODE  t)
{
  if(t == NULL)
                return NULL;
        while(t->left)
                t = t->left;
        return t;
}

//To print the nodes of the tree
void print(NODE root)
{
        NODE t;
        t = left(root);

        while(t)
        {
                printf("%d\t" , t->data);
                if(t->th)
                        t = t->thread;
                else
                        t = left(t->right);
        }
}


static int gName=0;

//to dump the tree into a file in preorder format
void preorderDotDump (NODE root, FILE* outputFile)
{
        if (root != NULL)
        {



                if (root->left != NULL) {
                         fprintf (outputFile, "%d -> %d ;\n", root->data, (root->left)->data);
                         }
		//dumping the thread pointer 
                if (root->thread != NULL)
                         fprintf (outputFile, "%d -> %d[style=dashed];\n", root->data, (root->thread)->data);

        	if (root->right != NULL)
                        fprintf (outputFile, "%d -> %d;\n", root->data, root->right->data);



                preorderDotDump (root->right, outputFile);

                preorderDotDump (root->left, outputFile);
        }
}

//Dumping the data into data file
void dotDump(NODE root, FILE *outFile)
{
        gName++;
        fprintf (outFile, "digraph BST {\n",gName);

        preorderDotDump (root, outFile);
        fprintf (outFile, "}\n");
}
FILE *outputFile;

main( )
{

        FILE *pipe;
        struct node *R;
        int n , j, ch , data;
        R = NULL;
        printf("Enter number of nodes to create \n");
        scanf("%d", &n);
        outputFile = fopen ("bst.dot", "a");
        for(j=0; j<n ;j++)
        {
                printf("Enter the %d element\n",j+1);
                scanf("%d", &data );
                addnew( &R , data );
        }

        inorder( R);
        i = 0;
        CreateThread(R);
        dotDump (R,  outputFile);fclose (outputFile);
       printf("Enter your choice \n 1. print the nodes in order \n 2. display the dotty \n ");
        scanf("%d" , &ch);
        switch(ch)
        {
                case 1:  print(R);
                        break;
                case 2 : pipe=popen("dot -Tps bst.dot -o bst.ps","w");
                         pclose(pipe);
                         pipe=popen("evince bst.ps","r");
                         pclose(pipe);
                         break;
        }
}

//Function to add new node to the tree
void addnew( struct node **q,int data )
{
        if( *q == NULL )
        {
           *q = getnode( );
           (*q)->left = NULL;
           (*q)->right =NULL;
           (*q)->data = data;
           (*q)->thread=NULL;
           return;
        }

        if( (*q)->data > data )
         addnew( &(*q)->left , data );
        else
         addnew( &(*q)->right , data );
}                 
