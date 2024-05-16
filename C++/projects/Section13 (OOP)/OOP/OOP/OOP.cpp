/*
* Author		: Omar Ayman
* Date			: 13th MAY 2024
* Copyrights	: omar.ayman@crewteq.com
*
*
* do NOT use this for adding history to track you code edits,
* use the version control instead (GIT)
*/

#include <iostream>
#include <string>
#include <vector>
#include "student.h"

using namespace std;

/*
class Player
{
public:
	// attributes 
	string name; 
	int health;
	int experience;

	//methods
	void talk(string textToSay);
	bool isDead();

	//constructor 
	Player(string name, int health, int experience);

	// distructor 
	~Player();
};

*/

int main()
{
	/* what is OOP (Object Oriented Programming)
	- focus on classes that model real world domain entities
	- allows devlopers to think at a higher level of abstraction
	- used successfully in very large programs
	- Encapsulation (information - hiding )
	- reusability (easy to reuse classes in other applications)
	- inheritance (create a new class in term of existing classes)

	- programs can be :
	 1- large in size
	 2- slower
	 3- More complex

	 * classes (blueprint from which objects are created)
	 - has methods
	 - can hide data and methods
	 - provide public interface
	 - has attributes (data)
	 Examples from standard library
	 :
	  1- std::vector
	  2- std::string

	  * the object is an instance from the class

	   === creating classes
	   class ClassNew
		{
		//attributes
			std::string name;
			int age ;
			int salary

		//methods
			bool SalIsEnough(int sal);
		};

		//creating object
		ClassNew ClassNew1 ;



	   */

	   /*Player frank("frank", 4, 10);
	   Player hero("hero", 2, 3);

	   Player* enemy{ nullptr };
	   enemy = new Player("another person", 7, 8);
	   delete enemy;

	   frank.talk(frank.name);*/



	   /*
		   privates are not accessible outside the class !
	   */


	   student stud1("Omar", 3.44);
	   /*
	   	   student stud2("Mohamed");
	   student stud3;
	
	   stud2.setGPA(3.55);
	  
		// copy constructor
	   student studCopy= stud1;

	   //copy constructor using the one we have made in the class !
	   student studCopy2(stud2);
	   cout << "student1 : " << "Name : " << stud1.getStudentName() << "  GPA : " << stud1.getGPA() << endl;
	   cout << "student2 : " << "Name : " << stud2.getStudentName()  << "  GPA : " << stud2.getGPA() << endl;
	   cout << "student3 : " << "Name : " << stud3.getStudentName() << "  GPA : " << stud3.getGPA() << endl;	 
	   cout << "studCopy : " << "Name : " << studCopy.getStudentName()  << "  GPA : " << studCopy.getGPA() << endl;   
	   cout << "studCopy2 : " << "Name : " << studCopy2.getStudentName()  << "  GPA : " << studCopy2.getGPA() << endl;
	   */








}

/*void Player::talk(string textToSay)
{
	cout << name << " says " << textToSay << endl;
}

Player::Player(string name, int health, int experience)
{
	this->name = name;
	this->experience = experience;
	this->health = health;

}

Player::~Player()
{
}

*/
