/*
* Author		: Omar Ayman
* Date : 19th MAY 2024
* Copyrights : omar.ayman@crewteq.com
*
*
* do NOT use this for adding history to track you code edits,
*use the version control instead(GIT)
*/

#include <iostream>
#include <string>
#include <vector>
#include "Movies.h"

using namespace std;


// checking if we can add movie <movie existed>
void addMovie(Movies &movies, string name, Rating rate, int watched)
{
	movies.addMovie(name, rate, watched);
}

//incremanting 
void incrementWatched(Movies &movies, string name)
{
	movies.increment(name);
}

int main()
{
	Movies movies;

	movies.display();


	addMovie(movies, "Interstaller", PG, 10);
	movies.display();

	addMovie(movies, "Interstaller", PG_13, 20);
	movies.display();

	addMovie(movies, "Start Wars", PG_13, 3);
	addMovie(movies, "Inception", G, 7);
	addMovie(movies, "Cindrella", R, 3);

	movies.display();

	incrementWatched(movies, "Start Wars");
	incrementWatched(movies, "Cindrella");
	movies.display();

	incrementWatched(movies, "Super Man");


}
