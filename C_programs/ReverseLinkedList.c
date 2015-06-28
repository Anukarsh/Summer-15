/*Program to Reverse a linked list */
//Input - Any integer 
//Output -A linked list which has been reversed from its original form
 
#include <stdio.h>
#include <stdlib.h>

struct node
{
 	int data;
	struct node *link;
};

struct node * insert(struct node *);
void display( struct node *);
struct node * reverse(struct node *);
 
struct node *getnode()
{
	return (struct node *)(malloc(sizeof(struct node)));
}

int main() 
{
	struct node *first;
	first = NULL;
	int ch , val;
	while(1)
	{
		printf("Choose your option: \n 1.Insert \n 2.Display \n 3.Reverse \n 4.Exit \n");//Menu displayed to provide user with various choices
		scanf("%d", &ch);
		switch(ch)
		{
			case 1:	first =(struct node *)insert(first);
				break;
			case 2: display(first);
				break;
			case 3: first = reverse(first);
				break;
			case 4: exit(1);
		}
	}
}
//Function to insert a new node to the linked list 
//Takes an argument of a poointer and returns the same
struct node * insert(struct node *first)
{
	struct node *t;
	if(first == NULL)
	{
		t = getnode();
		first = t;
	}
	else 
	{
		t = first; 
		while(t->link!=NULL)
			t = t->link;
		
		t->link = getnode();
		t = t->link;
	}
	printf("enter the data\n");
	scanf("%d" , &t->data);
	t->link = NULL;
	return first;

}

//Funtion to display the linked list 
//Takes one argument input during call and does not return any value 
void display(struct node *t)
{
	while(t!=NULL)
	{
		printf("%d->",t->data);
		t = t->link;
	}
}

//Reverse the given linked list and returns the newly formed list 
struct node * reverse(struct node * first)
{
  struct node* p = 0;
  struct node *next; 
  while (first)
 {
    next = first->link;
    first->link = p;
    p = first;
    first = next;
 }
  return p;
}

	
