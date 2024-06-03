/*
* Author		: Omar Ayman
* Date			: 29th MAY 2024
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

class coach
{
	public:
		void functionToAccessPrivatesOfPlayer(void);
	private:

};


class Player
{

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
	
	
	
private:
	int salary;
	friend int getMyFriend1Salary(Player Px);
	friend class coach;
};

int main()
{
	Player P1; 
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
	this->name += source.name;
	return *this;
}

int getMyFriend1Salary(Player Px)
{
	return Px.salary;
}

void coach::functionToAccessPrivatesOfPlayer(void)
{
	Player Px;
	Px.salary = 100;
}
