/* A Movie Recommender System Designed in Scala */
/* Description: The Program recommends the user with a list of Three movies which are predicted based on his prevoius interest and ratings and after analysis of the trends that are most similar to the user */

/*Input : The Program needs two inputs
	1. The Data file with User Id , Movie Ids and Ratings - Data read from file
	2. The User Id of the user seeking recommendation - Data read from console
*/

/*Output: The Three movies that are recomended to the user and the Ratings those movies have recieved from the similar user */

import io.Source 
import scala.util.control.Breaks._
import math._

//Number of Users
val row = 946
//Number of Movies
val col = 1682

//An array to store the Normalised ratings
var norm_rat = Array.ofDim[Double](947,1683)
//An array to store the cosine distances all the user w.r.t to one user 
var sim = Array.ofDim[Double](947)
//An array to store all the movie names
var names = Array.ofDim[String](1683)
//An array to store the number of times a movie has been watched
var mov = Array.ofDim[Int](1683)
//An array to store the 50 most watched movies
var watch = Array.ofDim[Int](51)
//An array to store the number of times the 50 most watched movies have been rated 5 
var best_rat = Array.ofDim[Int](51)
//An array to store the top 50 most watched movies in descending order of the best ratings recieved 
var best = Array.ofDim[Int](51)

var y = 0

//Reading the movie names from the file 'u.item' 
for(line <- Source.fromFile("u.item").getLines())
{
	names(y) = line
	y = y + 1
}

//An array to store all the ratings considering the rows as user id and colums as movie id
var rat = Array.ofDim[Double](947,1683)

//Reading the file for input
var s = Source.fromFile("u.data")

//Spliting the String to obtain separatly the User Id , Movie Id and the Rating
var t = s.mkString.split("\\s+")

//Parsing the values to Integer type 
var z = for(w<-t) yield w.toInt

//The number of top movies to compute 
var num = 50


print("---------------------------------------------------------------------WELCOME----------------------------------------------------------------------------")
print("Please enter your User Id\n")
//Reading the user ID of the user who needs Recommendation
val m = readInt

//Creating the Rating Matrix
for( i<-0 to z.size/4-1){
	var k = i*4
	rat(z(k))(z(k+1)) = z(k+2)
}
 
var sum = 0.0
var ct = 0
var avg = 0.0

//Normalising of the rating matrix
for(i<-0 to row)
{
	sum = 0
	ct = 0
	avg = 0
	for(j<- 0 to col)
	{
			
		if(rat(i)(j) != 0)
		{
			sum = sum + rat(i)(j)
			ct = ct+1  
		}
	}
	avg = sum/ct
	for(j<- 0 to col)
	{
		if(rat(i)(j)!=0)
		{	//Generating the normal rating matrix
			norm_rat(i)(j) = rat(i)(j) - avg
		}
	}
}
var dec1 = 0.0 
var dec2 = 0.0

//Computing the cosine distanc of the user w.r.t to other users 
for(i<- 0 to row)
{
	dec1 = 0.0
	dec2 = 0.0	
	breakable{
	for(j<- 0 to col)
	{	
		if(i==m)
			break
		if(norm_rat(i)(j) != 0 && norm_rat(m)(j)!=0) 
		{
			sim(i) = sim(i) + (norm_rat(m)(j)*norm_rat(i)(j))
		}
		dec1 = dec1 + (norm_rat(i)(j)*norm_rat(i)(j))
		dec2 = dec2 + (norm_rat(m)(j)*norm_rat(m)(j))
	}
	}
	if((sqrt(dec1)*sqrt(dec2))!=0)
	{	//Cosine distance calculation 
		sim(i) = sim(i)/(sqrt(dec1)*sqrt(dec2))
	}
}
		
//Computing the most similar users 
var m1 = sim.indexOf(sim.max)
sim(m1) = -99999.99
var m2 = sim.indexOf(sim.max)

//Computing the Top 50 movies
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
 

for(i<- 0 to num)
{
	var x = mov.indexOf(mov.max)
	mov(x) = 0
	watch(i) = x
}


var ind = 0
for(i<- 0 to num)
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


for(i<- 0 to num)
{
	var g = best_rat.indexOf(best_rat.max)
	best_rat(g) = 0
	best(i) = watch(g)
}


var count = 0
var cnt = 0

/*Recommending the user a list of three movies in three different cases
	1. Out of the movies recommended for the user the three movies which are in the top 50 are preferred over others
	2. If less than three movies recommended are in the two movies then the rest of the recomendation are based on the most similar user
	3. If the user has not watched any movies then the top rated movies are recommended 
*/
breakable{
	// case 1 recommendation 
	for( i<- 1 to row)
	{
		if(rat(m)(i) == 0&&(rat(m1)(i)>4||rat(m2)(i)>4))
		{
			if((rat(m1)(i) > rat(m2)(i)) && rat(m1)(i) > 2 && best.contains(i))
			{
				count = count + 1
				println("Watch " + names(i-1) + i  + "!!!! it has been rated " + rat(m1)(i) + " by user " + m1)
		
			}	
			else
			{
				if(rat(m2)(i) > 2 && best.contains(i))
				{
					count = count + 1
					println("Watch  " + names(i-1)+ i + "!!! it has been rated " + rat(m2)(i) + " by user " + m2)
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
				if(rat(m)(i) == 0&&(rat(m1)(i)>4||rat(m2)(i)>4))
				{	
					if((rat(m1)(i) > rat(m2)(i)) && rat(m1)(i) > 2)
					{
						cnt = cnt + 1
						println("Watch  " + names(i-1) + "!!! it has been rated " + rat(m1)(i) + " by user " + m1)
		
					}	
					else
					{
						if(rat(m2)(i) > 2)
						{
						   cnt = cnt + 1
						   println("Watch " + names(i-1) + "!!! it has been rated " + rat(m2)(i) + " by user " + m2)
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
			println("Watch "+ names(best(k-1)) +"!!!")
			k = k+1
		}
	}
}
println("____________________________________________________________Thank You For Using Our Service_____________________________________________________________")
