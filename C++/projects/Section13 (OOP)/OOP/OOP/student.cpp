#include "student.h"

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
{
	this->nameOfStudent = Name;
	this->GPA = currentGPA;
}

student::~student()
{
}
