/*
* Author		: Omar Ayman
* Date			: 8th June 2024
* Copyrights	: omar.ayman@crewteq.com
*
*
*/

#include <iostream>
#include <string>
#include <vector>

/* library for smart pointer */
#include <memory>
int main()
{
	/*
	what is smart pointer>
	it is an object 
	automatically call delete 
	types : 
	1- unique 
	2- shared 
	3- weak

	You can NOT do pointer arithematic as in RAW pointers !
	*/

	/* creating a smart pointer */
	int x = 100;
	std::unique_ptr<int>ptr{ new int {100} };
	*ptr = 130;

	std::unique_ptr<int>ptr2{ new int {200} };
	//ptr2 = ptr1; // you can NOT assign or copy unique smart pointers with each others, insted move the ownership from one to another 

	ptr2 = std::move(ptr);

	std::cout << *ptr2 << std::endl;
	if (!ptr)
		std::cout << "ptr is a nullptr" << std::endl;
	
	
}