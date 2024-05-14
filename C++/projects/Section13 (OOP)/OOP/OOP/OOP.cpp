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

using namespace std;


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

	Player frank("frank", 4, 10);
	Player hero("hero", 2, 3);

	Player* enemy{ nullptr };
	enemy = new Player("another person", 7, 8);
	delete enemy;

	frank.talk(frank.name);

	/*
		privates are not accessible outside the class !
	*/
}

void Player::talk(string textToSay)
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
