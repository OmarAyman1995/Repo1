#ifndef __STUDENT_H__
#define __STUDENT_H__

#include <string>

class student
{
private:
	std::string nameOfStudent;
	double GPA;


public:
	bool IsStudentPassed(double GPA);
	void setGPA(double NewGPA);
	double getGPA(void);

	std::string getStudentName(void);
	void setStudentName(std::string nameOfStudent);


	//constructor 
	student(std::string Name,double currentGPA);

	//Distructor
	~student();

};

#endif // !__STUDENT_H__

