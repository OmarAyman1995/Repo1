#include "student.h"
#include <iostream>
using namespace std;
bool student::IsStudentPassed(double GPA)
{
	if (this->GPA > 2.0)
	{
		return true;
	}
	return false;
}

void student::setGPA(double GPA)
{
	this->GPA = GPA;
}

double student::getGPA(void)
{
	return this->GPA;
}

std::string student::getStudentName(void)
{
	return this->nameOfStudent;
}

void student::setStudentName(std::string nameOfStudent)
{
	this->nameOfStudent = nameOfStudent;

}

student::student(std::string Name, double currentGPA)
	:student{Name}
{
	this->GPA = currentGPA;
}

student::student(std::string Name)
	:nameOfStudent{Name}
{
	
}

student::student(double currentGPA)
{
	this->GPA = currentGPA;
}

student::student()
	:nameOfStudent{ "None" }, GPA{ 3.00 }
{

}


student::student(const student &source)
{
	this->nameOfStudent = source.nameOfStudent;
	this->GPA = source.GPA;
	
}

student::~student()
{
	cout <<endl << "distructor of " << this->nameOfStudent << " is called here ! " << endl;
}

