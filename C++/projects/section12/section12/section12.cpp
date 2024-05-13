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

int* apply_all(int* arr1, int size1,int* arr2,int size2)
{
	//1,2,3,4
	//10,20,30
	int sizeT = size1 * size2;
	int* arrT = new int[sizeT];
	int i = 0; 
	int j = 0;
	int k = 0;
	for (; i < size1; i++)
	{
		for (j=0; j < size2; j++)
		{
			arrT[k++] = arr1[i] * arr2[j];
		}
	}
	return arrT;
}

void print(const int* arr,int size)
{
	int i{ 0 };
	for (;i<size;i++)
	{
		cout << arr[i] << " ";
	}
}
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


	/* references */
	/*
	its an alias to a variable 
	can NOT be NULL
	can NOT to refer to another variable
	very useful in function parameters 
	*/

	//use1 
	std::vector <std::string> FullName{ "OMAR" , "MOHAMED" , "AYMAN" };
	/*for (auto str : FullName)
	{
		str = "AHMED";
	}
	//output wont change ! its changing the copy 
	for (auto str : FullName)
	{
		cout << str << endl;
	}
	*/
	
	/*for (auto &str : FullName)
	{
		str = "AHMED";
	}
	//output will change ! its changing the reference 
	for (auto const &str : FullName)
	{
		cout << str << endl;
	}

	*/
	
	

	//use2 
	/*int num = 100; 
	int &ref{ num };
	cout << num << " .. " << ref << endl;

	num = 200; 
	cout << num << " .. " << ref << endl;

	ref = 400;
	cout << num << " .. " << ref << endl;

	*/
	
	/*
	L value is the value that has a name and is addressable , modifiable if they are not constant
	R value is anything that is not L value 
	*/

	int arr1[]{ 1,2,3,4 };
	int arr2[]{ 10,20,30 };
	int resultSize = (sizeof(arr2) / sizeof(arr2[0])) * (sizeof(arr1) / sizeof(arr1[0]));
	print(apply_all(arr1, (sizeof(arr1) / sizeof(arr1[0])), arr2, sizeof(arr2) / sizeof(arr2[0])) , resultSize);
	


	
}

