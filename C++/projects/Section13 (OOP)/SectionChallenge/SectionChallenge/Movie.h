#pragma once

#include <iostream>
#include <string>

using namespace std;

typedef enum 
{
	G = 0,
	PG = 1,
	PG_13 = 2, 
	R = 3
}Rating;

class Movie
{
private:
	string movieName;
	Rating movieRating;
	int movieWatched;
public :
	
	//construtor
	Movie(string movieName, Rating movieRating , int movieWatched);
	
	//copy constructor 
	Movie(const Movie &source);

	// Distructor
	~Movie();
	
	// Getters & Setters
	
	void setMovieName(string movieName);
	string getMovieName(void)const;

	void setMovieRating(Rating movieRating);
	Rating getMovieRating(void)const;

	void setMovieWatched(int movieWatched);
	int getMovieWatched(void)const;

	//Display API 
	void display(void) const;
};
