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



int main()
{
   /* --- all pointers have the same size ---- */
	/*
		int* p1 = nullptr;
		double* p2 = nullptr;
		std::vector <int> *p0 = nullptr;
		void* p3 = nullptr;

		cout << "size of p0 " << sizeof(p0) << endl;
		cout << "size of p1 " << sizeof(p1) << endl;
		cout << "size of p2 " << sizeof(p2) << endl;


		int n1 = 100; 
		double d1{ 34.24 };
		p1 = &n1; 
		//p1 = &d1; //Compiler Error!
		p3 = &d1;
		p3 = &n1; 
	*/

	/* --- De-referencing pointers ---*/
	/*
	int score{ 100 };
	int *score_ptr{ &score };
	
	cout << " at : " << score_ptr << " >>>>>> " << *score_ptr <<endl;

	*score_ptr = 200;
	cout << " at : " << score_ptr << " >>>>>> " << *score_ptr <<endl;

	std::string MyName = "Omar Ayman";
	std::string *MyNamePtr = &MyName;
	cout << *MyNamePtr << endl;
	
	MyName = "Omar Mohamed Ayman";
	cout << *MyNamePtr << endl;
	*/
	

	/* for to show all vector elements */
	
	/*
	std::vector <int> vec1{ 1,2,3,4,5,6,7 };
	for (auto elements : vec1)
	{
		cout << elements << endl;
	}
	*/

	/*dynamic memory allocation*/
	
	//use (new) to allocate storage 
	/*
		int *heapPtr;
		heapPtr = new int; 
		*heapPtr = 1984; 
		cout << " at : " << heapPtr << " >>>>>> " << *heapPtr << endl;
	
		heapPtr = new int[2];
		heapPtr[0] = 1995;
		heapPtr[1] = 2024;
		cout << " at : " << heapPtr << " >>>>>> " << *heapPtr << endl;
		cout << " at : " << &(heapPtr[1]) << " >>>>>> " << *(heapPtr+1) << endl;
	
	
		delete heapPtr;
	*/


	

 
	


	
}

