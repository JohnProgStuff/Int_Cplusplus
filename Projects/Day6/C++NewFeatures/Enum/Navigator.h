#pragma once  //always put #pragma once in every header file
//			  //it checks if Navigator.h has already been included and if so it won't include it again.
// pre C++11 way of doing it.
//  #ifndef _Navigator_H
//  #define _Navigator_H
//  #endif // !_Navigator_H



#include "Airport.h"
//use forward declaration instead
//enum class CompassPoint;	// don't need Airport.h header file anymore to use
							// CompassPoint but we do to access Airport Class


enum class AirportCode
{
	SLC, MCO, CHI
	//..........
};

class Navigator
{
private:
	CompassPoint _compassPoint;
public:
	Navigator();
};
