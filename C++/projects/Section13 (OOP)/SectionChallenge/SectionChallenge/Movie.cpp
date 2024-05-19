#include "Movie.h"

Movie::Movie(string movieName, Rating movieRating, int movieWatched)
	: movieName{ movieName }, movieRating{ movieRating }, movieWatched{ movieWatched }
{
}

Movie::Movie(const Movie & source)
{
	this->movieName = source.movieName;
	this->movieRating = source.movieRating;
	this->movieWatched = source.movieWatched; 
}

Movie::~Movie()
{
}

void Movie::setMovieName(string movieName)
{
	this->movieName = movieName;
}

string Movie::getMovieName(void) const
{
	return this->movieName;
}

void Movie::setMovieRating(Rating movieRating)
{
	this->movieRating = movieRating;
}

Rating Movie::getMovieRating(void) const
{
	return this->movieRating;
}

void Movie::setMovieWatched(int movieWatched)
{
	this->movieWatched = movieWatched;
}

int Movie::getMovieWatched(void) const
{
	return this->movieWatched;
}

void Movie::display(void) const
{
	cout << movieName << "," << movieRating << "," << movieWatched << endl ;
}
