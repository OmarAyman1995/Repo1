/*
* Author		: Omar Ayman
* Date			: 15th Apr 2024
* Copyrights	: omar.ayman@crewteq.com
*
*
* do NOT use this for adding history to track you code edits,
* use the version control instead (GIT)
*/

#include <iostream>
#include <string>
#include <vector>

using std::cin; // use only what you need in the std name space 
using std::cout;// use only what you need in the std name space 
using std::endl;// use only what you need in the std name space 

/* note that there is no cheaking to see if you are out of bounds*/



int main()
{
	/*
	int scores[5]{ 99,77,57,100,88 }; // note that this line will give you an error here, you should add (=) equality operator between the cuerly braket.
    
	double GPA[5];

	cout << "GPA[0] : ";
	cin >> GPA[0];

	cout << "GPA[1] : ";
	cin >> GPA[1];

	cout << "GPA[2] : ";
	cin >> GPA[2];

	cout << "GPA[3] : ";
	cin >> GPA[3];

	cout << "GPA[4] : ";
	cin >> GPA[4];

	cout << "GPA[] = " << GPA[0] << endl << GPA[1] << GPA[2] << GPA[3]<< GPA[4] <<endl;
	*/
	
	/* - - - - - - VECTORS - - - - - - */
	/*
	it is an option for us when we do NOT know exactly the size of array we want to store
	its a container in C++ standard template library 
	vector can grow and shrink in size at execution time .
	can provide bounds checking ! 
	can use lots of functions like sort, reverse, and find , .....etc 
	stored contiguously in memory
	no checking of bounds

	do not forget to include the library
	#include <vector>
	using std
	*/

	/* Declaring*/
	std::vector <int> test_scores1(10);

	/*initialization : this intializes all 100 elements to 10 */
	std::vector <int> test_scores2(100,10);

	/* another way to intialize */
	std::vector <int> test_scores3{ 13,44,22,44,65,67,66 };

	/* accessing elements methods */

	/* indexing */
	cout << "test_scores3[4] : " << test_scores3[4] <<endl;
	
	/* .at */
	cout << "test_scores3.at(4) : " << test_scores3.at(4) << endl;

	/* to grow the size ?*/
	test_scores3.push_back(77);
	cout << "last element added  : " << test_scores3.at(7) << endl;

	/* to know the current size : */
	cout << "size of test_scores3 : " << test_scores3.size() << endl;

	/* to shrink the size ?*/
	test_scores3.pop_back();
	
	/* this will through an exception : 
	cout << "last element added  : " << test_scores3.at(7) << endl;

	so you can use (exception handling) to make sure that your program will not crash
	*/

	/* try the exception !*/
	try
	{
		cout << "last element added  : " << test_scores3.at(7) << endl;
		throw 999;
	}
	catch (...)
	{
		cout << "VECTOR EXCEPTION ERROR" << endl;
	}

	/* to know the current size : */
	cout << "size of test_scores3 : " << test_scores3.size() << endl ;


	/* 2D vector  */

	std::vector <std::vector<double>> GPAs
	{
		{3.45,4.00,2.56,4.0},
		{2.95,3.00,3.56,4.0},
		{3.33,2.05,3.16,4.0}
	};
	

	
	/* add a vector to 2D vector */
	
	std::vector <double> GPA_Level1{ 2.44,3.78,2,85 ,3.00};
	std::vector <double> GPA_Level2{ 1.88,3.23,4.00 ,2.54 };

	GPAs.push_back(GPA_Level1);
	GPAs.push_back(GPA_Level2);
	
	/* --- no change is gonna happen in GPAs elements!, but for GPA_Level2,sure  there is a change !*/
	GPA_Level2.at(2) = 3.00;

	
	for (int i = 0; i < GPAs.size(); i++)
	{
		for (int j = 0; j < GPAs[j].size(); j++)
		{
			cout << GPAs.at(i).at(j) << " , ";
		}
		cout << endl;
	}
	




	
	
	
}


