#pragma once
#include "Navigator.h" //headers not from library(user defined) must use "" and have .h

enum class CompassPoint : unsigned int
{
	North, South, East, West
};




class Airport
{
private:
	Navigator* ptr;
};