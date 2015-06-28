/* A Movie Recommender System Designed in Scala */
/* Description: The Program recommends the user with a list of Three movies which are predicted based on his prevoius interest and ratings and after analysis of the trends that are most similar to the user */

/*Input : The Program needs two inputs
	1. The Data file with User Id , Movie Ids and Ratings - Data read from file
	2. The User Id of the user seeking recommendation - Data read from console
*/

/*Output: The Three movies that are recomended to the user and the Ratings those movies have recieved from the similar user */

import io.Source 
import scala.util.control.Breaks._

//Number of Users
val row = 942
//Number of Movies
val col = 1681

//An array to store the intersection of user other users
var inter = Array.ofDim[Int](943)
//An array to store the union of user other users
var uni = Array.ofDim[Int](943)

//An array to store the Jaccard Similarity for the user
var sim = Array.ofDim[Double](943)

//Other declarations
var mov = Array.ofDim[Int](1682)
var watch = Array.ofDim[Int](50)
var best_rat = Array.ofDim[Int](50)
var best = Array.ofDim[Int](50)

//An array to store all the ratings considering the rows as user id and colums as movie id
var rat = Array.ofDim[Int](944,1683)

//Reading the file for input
var s = Source.fromFile("u.data")

//Spliting the String to obtain separatly the User Id , Movie Id and the Rating
var t = s.mkString.split("\\s+")

//Parsing the values to Integer type 
var z = for(w<-t) yield w.toInt

//Reading the user ID of the user who needs Recommendation
print("Please enter your User Id\n")
val m = readInt

//Creating the Rating Matrix
for( i<-0 to z.size/4-1)
{
	var k = i*4
	rat(z(k))(z(k+1)) = z(k+2)
}

//Calculating the Jaccard Similarities for the user
for(i<-0 to row)
{
	breakable
	{
		for(j<-0 to col)
		{
			if(i==m)//breaking if the iterater is equal to the user id
				break
			if((rat(m)(j)-rat(i)(j))<2 && rat(m)(j) != 0 && rat(i)(j)!=0){
				inter(i) = inter(i) + 1 //Incrementing the intersection value if the user have the similar tastes
		}
			if(!(rat(m)(j)==0&&rat(i)(j)==0))
			{
				uni(i) = uni(i) + 1
			}
		}
		sim(i) = (inter(i)*1.0)/(uni(i)*1.0) //Calculation of the Jaccard Similarity 
	}
}

//Identifying the Two most Similar user to the user who needs recommendation	
var m1 = sim.indexOf(sim.max)
sim(m1) = 0
var m2 = sim.indexOf(sim.max)

//Computing how many users have watched a particular movie 
for(i<- 0 to col-1)
{
	for( j <- 0 to row-1)
	{
		if(rat(j)(i) != 0)
		{
			mov(i) = mov(i) + 1
		}
	}
}
 
//Computing the Top 50 most viewed movies
for(i<- 0 to 49)
{
	var x = mov.indexOf(mov.max)
	mov(x) = 0
	watch(i) = x
}

//Computing the best rated movies among the Top 50 most watched movies
var ind = 0
for(i<- 0 to 49)
{
	ind = watch(i)
	for(j<- 0 to row-1)
	{
		if(rat(j)(ind) == 5)
		{
			best_rat(i) = best_rat(i) + 1
		}
	}
}


for(i<- 0 to 49)
{
	var g = best_rat.indexOf(best_rat.max)
	best_rat(g) = 0
	best(i) = watch(g)
}

/*Recommending the user a list of three movies in three different cases
	1. Out of the movies recommended for the user the three movies which are in the top 50 are preferred over others
	2. If less than three movies recommended are in the two movies then the rest of the recomendation are based on the most similar user
	3. If the user has not watched any movies then the top rated movies are recommended 
*/
var count = 0
var cnt = 0
breakable{
	// case 1 recommendation 
	for( i<- 0 to row)
	{
		if(rat(m)(i) == 0&&(rat(m1)(i)==5||rat(m2)(i)==5))
		{
			if((rat(m1)(i) > rat(m2)(i)) && rat(m1)(i) > 2 && best.contains(i))
			{
				count = count + 1
				println("Movie recommended " + (i+1) + " it has been rated " + rat(m1)(i) + " by user " + m1)
		
			}	
			else
			{
				if(rat(m2)(i) > 2 && best.contains(i))
				{
					count = count + 1
					println("Movie recommended  " + (i+1) + " it has been rated " + rat(m2)(i) + " by user " + m2)
				}
			}
		}
	if(count==3)break
	}
	// case 2 recommendation 
	if(count < 3)
	{
		cnt = cnt + count
		breakable
		{
			for( i<- 0 to row)
			{
				if(rat(m)(i) == 0&&(rat(m1)(i)==5||rat(m2)(i)==5))
				{	
					if((rat(m1)(i) > rat(m2)(i)) && rat(m1)(i) > 2)
					{
						cnt = cnt + 1
						println("Movie recommended  " + (i+1) + " it has been rated " + rat(m1)(i) + " by user " + m1)
		
					}	
					else
					{
						if(rat(m2)(i) > 2)
						{
						   cnt = cnt + 1
						   println("Movie recommended " + (i+1) + " it has been rated " + rat(m2)(i) + " by user " + m2)
						}
					}	
				}
			if(cnt == 3)break	
			}
			
		}		
	}
	// case 3 recommendation
	if(cnt < 3)
	{
		var k = 0
		for(i<-cnt to 2)
		{ 
			println("Movie recommended "+best(k))
			k = k+1
		}
	}
}
