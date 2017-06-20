#include "stdafx.h"
#include "Employee.h"

using namespace YongZhang;

int Employee::maxnum = 0;

std::ostream& YongZhang::operator<<(std::ostream& o,
	const Employee& e)
{
	o << "Employee " << e.number << " is " << e.name;
	return o;
}
