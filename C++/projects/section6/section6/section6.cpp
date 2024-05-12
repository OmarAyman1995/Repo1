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
#include <stdbool.h>

using namespace std; 
//using std::cin; // use only what you need in the std name space 
//using std::cout;// use only what you need in the std name space 
//using std::endl;// use only what you need in the std name space 

/* GLOBs always initialize by zero  by compiler*/
int age{ 29 };

int main()
{
	/* c++ is a case sensitive !*/
	std::string my_name = "omar ayman";
	std::string MY_NAME = "OMAR AYMAN";
	std::cout << "my name : " << my_name << std::endl;
	std::cout << "MY NAME : " << MY_NAME << std::endl;


	/* illegal names of variable : int , $age , My age , Age+1 , cout , return , ....etc*/

	//int age = 28;  // C - like initialization
	// int age (28); // constructor initialization 
	 int age {28}; // c++11 list intialization 

	/*
	cout << "Room width : ";
	int roomWidth{ 0 }; 
	cin >> roomWidth;

	cout << "Room Length : ";
	int roomLength{ 0 };
	cin >> roomLength;

	std::string roomName;
	cout << "room name is : "; 
	cin >> roomName; 
	cout << "area of " << roomName << " is = " << roomLength * roomWidth << " square feet " << endl;
	*/
	
	 /* primitive data types : implemnted by standard C++ language
	 * chars , int , float, bolean
	 * size is a compiler dependent ! 
	 * bool is mapped to an 8 bits data type 
  	 */

	 /* 
	 bool Q = false;
	 bool A = false, B = false; 

	 Q = A && B;
	 */

	 /*
	 cout << "size of bool in bytes: " << sizeof(bool) << endl;
	 cout << "size of float in bytes: " << sizeof(float) << endl;
	 cout << "size of double in bytes: " << sizeof(double) << endl;

	 cout << " min of int is : " << INT_MIN << endl;
	 cout << " max of int is : " << INT_MAX << endl;
	 */

	/* do NOT use defined constants in Modern C++ !*/
	 /* for example : rather than #define PiConst 3.1415926, do this instead double const PiConst = 3.1415926;*/

	 
	



}

