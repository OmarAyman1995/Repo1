/*
* Author		: Omar Ayman
* Date			: 19th MAY 2024
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

/*
Operator overloading declaration 

Type &operator<the operator>(const Type &name); 
--------or--------
returnType operator symbol (arguments) {
	... .. ...
}
for example 
Mystring &operator=(const Mystring& rhs);

do NOT forget -----> the object on the left hand side is refer to by (this) pointer , 
                     while the object on the RHS is being passed to the method  .
*/



class Player
{




private:
	int prtot;
public:
	// attributes 
	string name;
	int health;
	int experience;

	//methods
	void talk(string textToSay);

	//constructor
	Player();

	//constructor 
	Player(string name, int health, int experience);

	// distructor 
	~Player();

	//overloaded operator (=)
	Player &operator=(const Player &player);

	//overloaded operator (+)
	Player &operator+(const Player &player);

	/*overloaded operator += */
	Player &operator+=(const Player &Player);
	
};

int main()
{
	Player p1("Omar", 98, 1);
	Player p2("Ayman", 98, 1);;
	
	
	
	p2 += p1;
	cout << p2.name<<endl;

	p2 = p1;
	cout << p2.name << endl;
}

void Player::talk(string textToSay)
{
	cout << name << " says " << textToSay << endl;
}

Player::Player()
{
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

Player & Player::operator=(const Player &player)
{
	this->name = player.name;
	this->health = player.health;
	this->experience = player.experience;

	return *this;
}

Player & Player::operator+(const Player & player)
{
	this->name = this->name + player.name;
	return *this;
}
Player & Player::operator+=(const Player & source)
{
	this->name +=  source.name;
	return *this;
}
