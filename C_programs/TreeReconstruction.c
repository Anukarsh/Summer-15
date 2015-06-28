//Program to reconstruct a tree from the given traversal.
//Program works for the option of preorder and inorder AND inorder and postorder
//Input - User options menu offered 
//Output - The inorder traversal of the reconstructed tree , dotty implementation not executed

#include <stdlib.h>
#include <stdio.h>

struct node 
{
	 int data;
	 struct node *l;
	 struct node *r;
};

int gName = 0;
typedef struct node *NODE;
NODE  buildtree1( int pre[] , int in[],int start ,int end );
NODE  buildtree2( int post[] , int in[],int start ,int end );
void inorder( NODE );
int i = 0, k = 10;

void preorderDotDump (NODE root, FILE* outputFile)
{
        if (root != NULL)
        {
                fprintf (outputFile, "%d [label=%d,color=black];\n",root->data, root->data);
                if (root->l != NULL)
                         fprintf (outputFile, "%d -> %d ;\n", root->data, (root->l)->data);

                if (root->r != NULL)
                        fprintf (outputFile, "%d -> %d;\n", root->data, root->r->data);
        //      if (root->pptr != NULL)
         //             fprintf (outputFile, "%d -> %d [style = dashed];\n", root->info, (root->pptr)->info);
                preorderDotDump (root->r, outputFile);
                preorderDotDump (root->l, outputFile);
        }
}

void dotDump(NODE root, FILE *outFile)
{
        gName++;
        fprintf (outFile, "digraph BST {\n",gName);

        preorderDotDump (root, outFile);
        fprintf (outFile, "}\n");
}
FILE *outputFile;




int main()
{
	NODE root;
	root = NULL;
	int in[100] , pre[100] , post[100] ;
	int n;
	FILE *pipe;
        int item;       

	int ch;
	printf("Enter the number of nodes in the tree\n");
	scanf("%d" , &n);
//	outputFile = fopen ("bst.dot", "w");
/*                fclose (outputFile);
                for(i=0;i<n;i++)
                {
			
                        item=random()%100;
                	pre[i] = item;
			post[i] = item;
			in[i] = item;        
		}

                        outputFile = fopen ("bst.dot", "a");
                        if (outputFile != NULL)
                        {

                                dotDump (root,  outputFile);
                        }
                        fclose (outputFile);
                
*/
	//user option menu
	printf("enter your choice\n1.Pre and In \n 2.In and post \n 3. Pre and post\n");
	scanf("%d" , &ch);
	switch(ch)
	{
		case 1 :printf("Enter the preorder \n");
			for(i = 0 ; i<n; i++)
			{
				scanf("%d" , &item);
				pre[i] = item;
			}
			printf("Enter the Inorder\n");
			for(i = 0 ; i<n; i++)
                        {
                                scanf("%d" , &item);
                                in[i] = item;
                        }
			 root = buildtree1( pre , in , 0 , n-1);
			 break;
		case 2 :printf("Enter the postorder \n");
                        for(i = 0 ; i<n; i++)
                        {
                                scanf("%d" , &item);
                                post[i] = item;
                        } 
                        printf("Enter the Inorder\n");
                        for(i = 0 ; i<n; i++)
                        {       
                                scanf("%d" , &item);
                                in[i] = item;
                        }
 			root = buildtree2(post , in , 0 , n-1);
			 break;
	// reconstruction of tree for preorder and postorder is not implemented
	//	case 3 : root= buildtree3(pre , post);
	//		 break;
	}
	inorder(root);
}

NODE newNode(char data)
{
  NODE no = (NODE) malloc(sizeof(struct node));
  no->data = data;
  no->l = NULL;
  no->r = NULL;
 
  return(no);
}

//function to rebuild tree from pre and inorder traversals
NODE  buildtree1( int pre[] , int in[],int start ,int end ) 		
{
	int j , ind;
	NODE root;
	root = NULL;
	root = newNode(pre[i++]);
	
	if(start>end)
		return NULL;	

	for(j=start;j<end ;j++)
	{
		if(in[j] == root->data)
			ind = j;
	}
	
	if(start == end)
		return root;

	//recursive calls for reconstruction of the left and rigth children
	root->l = buildtree1( pre , in , start , ind-1);
	root->r = buildtree1( pre , in , ind+1 , end);	

	return root;
}


//funtion to display the inorder traversal of the tree
void inorder( NODE q )
{
	if( q!= NULL )
	{
		  inorder( q->l );
			  printf("%d\t", q->data );
		  inorder( q->r);
	}
}


//program to reconstruct the tree from pre and inorder
NODE buildtree2(int post[] , int in[] , int start , int end )
{

        int j , ind;
       

        if(start>end)
                return NULL;
	
	NODE root = newNode(post[k--]);
	
	 if(start == end)
                return root;

        for(j=start;j<end ;j++)
        {
                if(in[j] == root->data)
                        ind = j;
        }

        

	//recursive calls to reconstruct the left and rigth children
        root->r = buildtree2( post , in , ind+1 , end );
        root->l = buildtree2( post, in , start , ind - 1);

        return root;
}
 


