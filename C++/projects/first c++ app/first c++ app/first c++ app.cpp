/*
* Author		: Omar Ayman
* Date			: 15th Apr 2024
* Copyrights	: omar.ayman@crewteq.com
* 
*
* do NOT use this for adding history to track you code edits, 
* use the version control instead (GIT)
*/

/*
* note that : the c++ preprocessr does NOT understand the C++
*/
#include <iostream>
#include <string>

/*
*In C++, a namespace is a declarative region that provides a scope for the identifiers (such as variables, functions, classes, etc.) declared within it.
* Namespaces help in organizing code by preventing naming conflicts between different parts of a program
*/
//using namespace std; 
//using std::cin; // use only what you need in the std name space 
//using std::cout;// use only what you need in the std name space 
//using std::endl;// use only what you need in the std name space 

/*
*argc : "argument count"  number of information (strings) we passed in through CLI .
*argv : "argument vector" actual arguments  (strings) we passed in through CLI .
*  for example    :  app.exe arg1 arg2
*/
int main(int argc, char *argv[])
{
	std::string myName; // std is a namespace contains classes, :: is the scope resolution operator
    std::cout << "Hello in C++ course!" << std::endl; // << is a stream insertion operator
	std::cin >> myName; // >> is an extraction operator
	std::cout << "your name is " << myName;

	/*
	string myName; // std is a namespace contains classes
    cout << "Hello in C++ course!\n"; // << is a stream insertion operator
	cin >> myName; // >> is an extraction operator
	cout << "your name is " + myName;
	*/

	return 0; // return successfully !
}