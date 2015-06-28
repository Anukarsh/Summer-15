//Program to implement the Apriori Algorithm to obtain the set of most common itemset
//Input: Transactions list
//Output: The most preferred itemset

struct link 
{
	struct node * p;
	struct link *link;
};

typedef struct link * LINK;

int sup1[5];
int sup2[10];
int sup3[20];
int min_sup = 2;

//Inserting the new itemset to the linked list
struct node* insert(struct node *h,int data)
{
	int index=(int)((data/32)*32);
	struct node *H;

	if(h==NULL)
	{
		h=(struct node*)malloc(sizeof(struct node));
		h->i=index;
		h->s|=1<<(data%32);
		h->next=NULL;
		return h;
	}
	struct node *p;
	p=h;
	H=h;
	while(h!=NULL)
	{
		if(h->i==index)
		{
			h->s|=1<<(data%32);
			return H;
		}

		else if(h->i >index)
		{
			struct node *temp;
			temp=(struct node*)malloc(sizeof(struct node));
			temp->i=index;
			temp->s|=1<<(data%32);
			p->next=temp;
			temp->next=h;
			return H;
		}
		else if(h->i < index)
		{
			p=h;
			int l;
			l=h->i;
			h=h->next;
		}
		else
		{
			struct node *temp;
			temp=(struct node*)malloc(sizeof(struct node));
			temp->i=index;
			temp->s|=1<<(data%32);
			p->next=temp;
			temp->next=NULL;
			return H;
		}
	}
	struct node *temp;
	temp=(struct node*)malloc(sizeof(struct node));
	temp->i=index;
	temp->s|=1<<(data%32);
	p->next=temp;
	temp->next=NULL;
	return H;
}

//to display the decoded set element 
void display(struct node *h)
{
	int i,a;
	printf("Set {");
	while(h!=NULL)
	{
		int x=h->i;
		a=h->s;
		for(i=x;i<x+32;i++)
		{
			if(a>>i & 0x1)
			{
				printf("'%d',",i);
			}
		}
		h=h->next;
	}
	printf("}\n");
}

//to compute the union of two sets
struct node* uni(struct node *A,struct node *B,struct node *C)
{
	int a,x,i;
	while(A!=NULL)
	{
		a=A->s;
		x=A->i;
		for(i=x;i<x+32;i++)
		{
			if(a>>i & 0x1)
			{
				C=insert(C,i);
			}
		}
		A=A->next;
	}
	while(B!=NULL)
	{
		a=B->s;
		x=B->i;
		for(i=x;i<x+32;i++)
		{
			if(a>>i & 0x1)
			{
				C=insert(C,i);
			}
		}
		B=B->next;
	}
	return C;
}

//to compute the intersection of two sets
struct node* inter(struct node *A,struct node *B,struct node *C)
{
	int a,x,i;
	while(A!=NULL && B!=NULL)
	{
		if(A->i==B->i)
		{
			int o,p;
			o=A->s;
			p=B->s;
			a= o & p;
			x=A->i;
			for(i=x;i<x+32;i++)
			{
				if(a>>i & 0x1)
				{

					C=insert(C,i);
				}
			}
			A=A->next;
			B=B->next;
			continue;
		}

		else if(A->i<B->i){A=A->next;continue;}
		else
		{
			A=A->next;
			B=B->next;
		}
	}
	return C;

}

struct node* Set(struct node *a){
a=insert(a,0);
a->s=a->s&0x0;
return a;
}

//To insert a new node into the list of sets
LINK insert_link(LINK tmp , NODE p)
{
	 LINK T;	

	 if( tmp == NULL )

	 {

	  tmp = (LINK)malloc(sizeof(struct link));

	  T = tmp;

	 } 

	 else

	 {

	   T = tmp;

	   	while( T->link != NULL)	

			T = T->link;



	   T->link = (LINK)malloc(sizeof(struct link));

	   T = T->link;

	 }

	 T -> p = p;
	 T->link = NULL;

	

	 return tmp;
}

//to display the list of sets
void display_link(LINK T)
{
	while( T!=NULL )

	{

	  display(T->p);

	  T = T->link;
	}
}

void display_link1(LINK T)
{
	int count = 0;
        while( T!=NULL )
	{

          display(T->p);
	  count++;
	if(count<2)
	{
	  
          T = T->link->link->link;
        }
	else 
		return;
	}
}


//to check for equality of two sets 
int equal( NODE r1 , NODE r2)
{
	while( r1 != NULL && r2 != NULL)
	{
		if( r1->i == r2->i)
		{
			if( r1->s == r2->s)
			{
				r1 = r1->next;
				r2 = r2->next;
			}
			else 
				return 0;
		}
		else 
			return 0;
	}
	if( r1 == NULL && r2 == NULL)
		return 1;
	else 
		return 0;
}


//function to calculate the support count of the itemset
void calsup( LINK D , LINK c , int sup[])
{	
	int count=0 , i = 0;
	LINK t;
	NODE b = NULL;
	while(c)
	{ 
		t = D;
		count = 0;
		while(t)
		{
			if(equal(inter(t->p, c->p,b) , c->p))
			{
				count++;
			}
			t = t->link;
		}
		c = c->link;
		sup[i++] = count;
	}
}

//to form the List of itemsets that surpass the minimum support count 
LINK formL( LINK c , int sup[])
{
	LINK t;
	t = NULL;
	int i ;
	for( i = 0 ; c != NULL ; i++)
	{
		if(sup[i] >= min_sup)
		{
			t = insert_link(t , c->p);
		}
		c = c->link;
	}
	return t;
}


NODE print(int num[], int n)
{	
    NODE a;		
    int i;
    for ( i = 0 ; i < n ; i++)
         a = insert(a , num[i]);
    return a;

}

//funtion to generate all the subsets of the given set							
LINK genrate(LINK c)
{
	LINK T , P;
	T = c;
	LINK S = NULL;
	NODE SS = NULL;
	while(T!=NULL)
	{
		P = T->link;
		while(P)
		{
			SS = NULL;
			SS = uni(T->p , P->p , SS);
			S = insert_link(S,SS);
			P = P->link;
		}
		T = T->link;
	}
	return S;
}

//To remove the duplicates in the itemsets list
LINK dup(LINK l)
{
	LINK tmp, new;
	new = NULL;
	tmp = l->link;
	while(l)
	{
		while(tmp)
		{
			if(!equal(l->p,tmp->p))
			{
				new = insert_link(new , l->p);
				new = dup(new);
				break;
			}
			tmp=tmp->link;
		}
		l = l->link;
	}
	return new;
}


void main()
{

	int i, j , n , item;
	int d = 2;
	int arr[5] = { 1 , 2 , 3, 4, 5};
	NODE a;
	LINK D ;
	LINK l[10] , c[10];
	c[0] = NULL;
	a = NULL;
	D = NULL;
	int k = 0;
	int h = 0;

	for(i =  0 ; i < d ; i++)
	{
		a = NULL;
	 	scanf("%d" , &n);
		for( j = 0 ; j<n ; j++)
		{
			scanf("%d" , &item); 
			a = insert(a , item);
		}
		D = insert_link(D , a);
		
	}
	printf("The Transaction list is\n");
	display_link(D);
	for(i =  0 ; i < 5 ; i++)
        {
                a = NULL;
                for( j = 0 ; j<1 ; j++)
                {
                        a = insert(a , arr[i]);
                }
                c[0] = insert_link(c[0] , a);

        }
	printf("\n");
	printf("C1 is \n");
	display_link(c[0]);
	calsup(D , c[0], sup1);
	printf("\n Support count of C1 is\n");
	for( i = 0 ; i<5 ; i++)
                printf("%d\t",sup1[i]);

	l[0] = formL(c[0] , sup1);
	printf("\n");
	printf("l1 is \n");
	display_link(l[0]);
	
	
	c[1] = genrate( l[0]);
	printf("\n");
	printf("C2 is \n");
	display_link(c[1]);
	calsup(D , c[1] , sup2);
	printf("\n Support count of C2 is\n");
        for( i = 0 ; i<10 ; i++)
                printf("%d\t",sup2[i]);


	printf("\n");
	l[1] = formL(c[1] , sup2);
	printf("L2 is\n");
	display_link(l[1]);
	printf("\n");
	c[2] = genrate(l[1]);
	printf("\n C3 is \n");
	display_link(c[2]);

	calsup( D , c[2] , sup3);	
	printf("\n Support count of C3 is");
        for( i = 0 ; i<15 ; i++)
                printf("%d\t",sup3[i]);


	l[2] = formL( c[2] , sup3);
	printf("\n \n");
//	l[2] = dup(l[2]);
	display_link1(l[2]);
	
}
