/*
* Author		: Omar Ayman
* Date			: 5th June 2024
* Copyrights	: omar.ayman@crewteq.com
*
*
* do NOT use this for adding history to track you code edits,
* use the version control instead (GIT)


	In C++, stream insertion operator “<<” is used for output and extraction operator “>>” is used for input.
	We must know the following things before we start overloading these operators.
	1) cout is an object of ostream class and cin is an object of istream class
	2) These operators must be overloaded as a global function. And if we want to allow them to access private data members of the class, we must make them friend.

*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Complex
{
private:
	int real, imag;
public:
	Complex(int r = 0, int i = 0)
	{
		real = r; imag = i;
	}
	friend ostream & operator << (ostream &out, const Complex &c);
	friend istream & operator >> (istream &in, Complex &c);
	friend Complex & operator + (Complex &c,int n);
	void print(Complex& c1) { cout << "Complex number : " << c1.real << "+" << c1.imag << "i" << endl; }
};

ostream & operator << (ostream &out, const Complex &c)
{
	out << c.real;
	out << "+i" << c.imag << endl;
	return out;
}

istream & operator >> (istream &in, Complex &c)
{
	cout << "Enter Real Part ";
	in >> c.real;
	cout << "Enter Imaginary Part ";
	in >> c.imag;
	return in;
}

Complex & operator+(Complex & c, int n)
{
	c.real = c.real + n;
	c.imag = c.imag + n;
	return c;
}

int main()
{
	Complex c1(3,5);
	c1.print(c1);
	c1 = c1 + 2;
	c1.print(c1);
	
	return 0;
}
