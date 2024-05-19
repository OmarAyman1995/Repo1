#pragma once
// add movie API  (return bool)
// increament watched count for a movie !(return bool)
// display 

#include <string>
#include <vector>
#include "Movie.h"

using namespace std; 

class Movies
{
private:
	vector <Movie> MoviesList;
public:

	//construtor
	Movies();

	//copy constructor 

	//Distructor 
	~Movies();

	//setters and getters 

	// display movies (calls movie.display for each object)
	void display(void)const;
	
	// add movie 
	bool addMovie(string name, Rating rate, int watched);
	
	// increament 
	bool increment(string name);
};