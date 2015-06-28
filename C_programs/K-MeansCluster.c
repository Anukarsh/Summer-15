//Implementation of k-mean cluster algorithm 
//Input - Random input generated , no user input 
//Output - The cluster sets for the various study centers in terms of their co-ordinates

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

struct c
{
	int x;
	int y;
};

int  mean(struct c [],int );
void dist(struct c p);

int sc[5],z[5];
struct c set1[100],set2[100],set3[100],set4[100],set5[100];
struct c stu[100];
int a,b,c,d,e;

void main()
{
	int i,j;
	//generation of random co-ordinates
	for(i=0;i<100;i++)
	{       stu[i].x = rand()%100;
		stu[i].y = rand()%100;
	}
	//initialisation of study center co-ordinates
	sc[0] = 10;
	sc[1] = 20;
	sc[2] = 30;
	sc[3] = 40;
	sc[4] = 50;
	//calculation of distances for every point from the study center and assigning the point to the nearest study center
	for(i=0;i<100;i++)
	{
		dist(stu[i]);
	}

	//calculationg the mean of the clusters and thus deriving new study center co-ordinates
	for(i =0 ; i<5 ; i++)
	{
	        sc[0] = mean(set1, a);
		sc[1] = mean(set2, b);
		sc[2] = mean(set3, c);
		sc[3] = mean(set4, d);
		sc[4] = mean(set5, e);
		for(j=0;j<100;j++)
        	{
                	dist(stu[i]);
        	}
	}
	
	printf("Elements in set1 are : %d " , a);

	for(i=0;i<a;i++)
		printf("(%d,%d)",stu[i].x,stu[i].y);
	  printf("Elements in set2 are : %d " , b);
	 for(i=0;i<b;i++)
	 	  printf("(%d,%d)",stu[i].x,stu[i].y);
	  printf("Elements in set3 are : %d " , c);
	 for(i=0;i<c;i++)
                printf("(%d,%d)",stu[i].x,stu[i].y);
	  printf("Elements in set4 are : %d " , d);

	 for(i=0;i<d;i++)
                printf("(%d,%d)",stu[i].x,stu[i].y);
	printf("Elements in set5 are : %d " , e);

	 for(i=0;i<e;i++)
                printf("(%d,%d)",stu[i].x,stu[i].y);


}
// function to calculate minimum distance 
// takes one argument that of a structure and assigns the points to the study centers
void dist(struct c p)
{	int i , j,min;
	
	for(i=0;i<5;i++)
	{
		//to calculate the distance from the study center using the euclidian formulae
		z[i] = sqrt(((stu[sc[i]].x-p.x)*(stu[sc[i]].x-p.x))+((stu[sc[i]].y-p.y)*(stu[sc[i]].y-p.y)));
	}
	min = z[0];
	j =0;
	for(i=0;i<5;i++)
	{	
		// calculating the minimum distance
		if(min>z[i])
			j = i;
	}
	switch(j)//assigining to the nearest study center
	{	case 1: set1[a].x = stu[i].x;
			set1[a].y = stu[i].y;
			a++;
			break;
		case 2:set2[b].x = stu[i].x;
                        set2[b].y = stu[i].y;
			b++;
                        break;
		case 3: set3[c].x = stu[i].x;
                        set3[c].y = stu[i].y;
                        break;
		case 4: set4[d].x = stu[i].x;
                        set4[d].y = stu[i].y;
                        break;
		case 5: set5[e].x = stu[i].x;
                        set5[e].y = stu[i].y;
                        break;
	}

}

//function to calculate the mean of the study centers 
// Takes input of a structure and  modifies the study center to the nearest one

int  mean(struct c a[],int n )
{  
	if(n!=0)
	{
		int i,j;
		float d,min,m;
		int mx , my;
		int sumx , sumy;
		for(i =0; i<n ; i++)
		{
			sumx += a[i].x;
			sumy += a[i].y;
		}
		mx = sumx/n;//calculation of mean
		my = sumy/n;
		m = sqrt(((stu[0].x-mx)*(stu[0].x-mx))+((stu[0].y-my)*(stu[0].y-my)));
	        for(i=0;i<100;i++)
	        {
	                d = sqrt(((stu[i].x-mx)*(stu[i].x-mx))+((stu[i].y-my)*(stu[i].y-my)));
	     		if(min>d)
			     j = i;
		}
		return j;
	}
}

