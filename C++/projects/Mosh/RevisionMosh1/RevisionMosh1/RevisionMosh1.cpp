/*
* Author		: Omar Ayman
* Date			: 31th MAY 2024
* Copyrights	: omar.ayman@crewteq.com
*
*
* do NOT use this for adding history to track you code edits,
* use the version control instead (GIT)
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;


void sortArray(int* array, int sizeOfArray)
{
	int i(0), j(0), temp{ 0 };
	for (i=0; i < sizeOfArray-1; i++)
	{
		for (j = 0; j < sizeOfArray - 1; j++)
		{
			if (array[j] > array[j + 1])
			{
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}
}
int main()
{
	int numbers[]{ 30,-11,-2,100,4,51 };


	cout <<  "@ " << numbers << endl;
	int sizeArray = 0;
	/*for (auto element : numbers)
	{
		cout << element << endl;
		sizeArray++;
	}
	cout << "size of array = " << sizeArray << endl;
	cout << "size of array = " << sizeof(numbers)/sizeof(numbers[0])<< endl;
	cout << "size of array = " << size(numbers) << endl;
	*/
	/* size_t */
	//cout << sizeof(size_t) << endl;

	sortArray(numbers, size(numbers));
	for (auto element : numbers)
	{
		cout << element << endl;
		sizeArray++;
	}

}