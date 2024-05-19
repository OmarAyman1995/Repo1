#include "Movies.h"

Movies::Movies()
{

}

Movies::~Movies()
{
}

void Movies::display(void) const
{
	if (MoviesList.size() > 0)
	{
		for (auto movieMember : MoviesList)
		{
			movieMember.display();
		}
	}
	else
	{
		cout << "error :: there are no movies yet ! " << endl;
	}
	
}

bool Movies::addMovie(string name, Rating rate, int watched)
{
	bool retVal = true; 
	
	for (const Movie &movieMember : MoviesList)
	{
		if (movieMember.getMovieName() == name)
		{
			retVal = false;
			break;
		}
	}
	if (retVal == true)
	{
		/* push a new Movie !*/
		Movie newMovie(name,rate,watched);
		MoviesList.push_back(newMovie);
		cout << "the " << name << " Movie is Added successfully !" << endl;
	}
	else
	{
		cout << "the " << name << " Movie is ALREADY EXISTED !" << endl; 
	}

	return retVal;

}

bool Movies::increment(string name)
{
	bool retVal = false;
	int temp;
	for ( Movie &movieMember : MoviesList)
	{
		if (movieMember.getMovieName() == name)
		{
			retVal = true;
			temp = movieMember.getMovieWatched();
			temp++;
			movieMember.setMovieWatched(temp);
			break;
		}
		else
		{
			/* do nothing */
		}
	}
	if (retVal == false)
	{
		cout << "the " << name << " Movie is NOT EXISTED !" << endl;
	}
	
	return retVal;
}
