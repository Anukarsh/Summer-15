//To compute the edit distance of any two words
//Input: Any two random words
//Output: The minimum edit distance of the two entered two words

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//To obtain the minimum of three numbers
int min( int a , int b ,int c)
{
	if(a<b)
	{	
		if(a<c)
			return a;
		else 
			return c;
	}
	else 
	{
		if(b<c)
			return b;
	 	else
			return c;
	}

}

//To calculate the edit distance of the words
int Cal_dist(char a[] , char b[])
{
	int i , j , cost;

	int left, set , top , corner;
	
	int m = strlen(a)+1;
	int n = strlen(b)+1;
	
	int table[100][100];

	for( i =0 ; i<m ; i++)
		for( j = 0 ; j<n ;  j++)
			table[i][j] = -1;
		
	for( i =0 ; i< m ; i++)
		table[i][0] = i;
	
	for( j = 0 ; j<n ; j++)
		table[0][j] = j;

	for( i = 1 ; i<m ; i++)
		for( j = 1 ; j<n ; j++)
	{
		//for computing operations for insertion 
		top = table[i-1][j] + 1;
		//for computing operations for deletion
		left = table[i][j-1] + 1;
		//for computing operations for rearragement
		if(a[i-1] == b[j-1])
			set = 0;
		else
			set = 2;
		corner = table[i-1][j-1]+set;
		table[i][j] = min( left , corner , top);
	}
	cost = table[m-1][n-1];

	for( i = 0; i<m ; i++)
	{
		for(j = 0 ; j<n ; j++)
			printf("%d\t" , table[i][j]);
		printf("\n");
	}
	return cost;
	
}




int main()
{
	int min;
	char str1[10] , str2[10] ;
	printf("Enter String 1 \n");
	scanf("%s" , str1);
	printf("Enter String 2\n");
	scanf("%s" , str2);
	min = Cal_dist( str1 , str2);
	printf("\n\n\n");
	printf("Minimum number of transformation is %d " , min);

}

	
