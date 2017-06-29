#include <iostream>
#include <string>
#include "Navigator.h"


using namespace std;

enum class days_of_week {Sun, Mon, Tue, Wed, Thu, Fri, Sat}; //start from any value by assigning 1st item a value. Sun=1 or Sun=0

enum class Color{RED, BLUE, YELLOW};

enum class Direction {SOUTH, NORTH, EAST, WEST};

void foo(int val)
{
	if (val == 0)
	{
		cout << "Sunday" << endl;
	}
}

void betterfoo(days_of_week val)
{
	if (val == days_of_week::Sun)
	{
		cout << "Sunday" << endl;
	}
}


int main()
{
	days_of_week day1, day2;
	day1 = days_of_week::Sun;
	day2 = days_of_week::Thu;
	int diff = static_cast<int>(day2) - static_cast<int>(day1);
	//cout << diff << " days between " << day1 << " and " << day2 << endl;
	//above line works with pre c++11 style of enum without the class keyword.
	if (day2 < day1)
	{
		cout << "day2 comes before day1" << endl;
	}

	//foo(day1); // doesn't work because it is a scope integer.
	foo(-1);
	betterfoo(day1);
	//betterfoo(-1); // doesn't work because it needs a days_of_week enum type 

	Color color = Color::YELLOW;
	Direction direction = Direction::EAST;
	//Cannot compare two scoped enumerations
		//if( Color == direction)...
	if (color == Color::BLUE)
	{
		cout << "Color is blue" << endl;
	}
	// has to explicitly convert to an int
	cout << static_cast<int>(color) << endl;
	enum class Proportion
	{
		OneHalf,
		OneThird,
		OneQuarter
	};

	Proportion prop = Proportion::OneQuarter;
	auto prop2 = Proportion::OneHalf;

	// We can specify enum type
	enum class Direct : unsigned short
	{
		South, North, East, West
	};
	cout << "size of Direct::East " << sizeof(Direct::East) << endl;

	enum E : short;
	enum F; // by default, it is int
	enum class G : short;

	Navigator nav1 = Navigator();



}