#include <string>
using namespace std;

#ifndef _Student_H
#define _Student_H
class Student
{
private:
	string firstname;
	string lastname;
	double gpa;
public:
	Student(string first, string last, double d);
	~Student();
	string getName();
	double getGPA() { return gpa; }
	void setGPA(double d) { gpa = d; }
	Student operator+(const Student& s);

};


#endif