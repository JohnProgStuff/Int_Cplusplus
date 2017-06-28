#pragma once
#include "Student.h"

template<class T>
class Accum
{
private:
	T total;
public:
	// constructor with a starting value
	Accum(T start) : total(start) {}

	// overload += opreator for class Accum
	T operator+=(const T& t)
	{
		return total = total + t;
	}

	// get total
	T getTotal()
	{
		return total;
	}
};

// fix3: template specification
template<>
class Accum<Student>
{
private:
	double total;
public:
	Accum(double start) : total(start){}
	double operator+=(Student& s)
	{
		return total = total + s.getGPA();
	}
	double getTotal() { return total; }
};