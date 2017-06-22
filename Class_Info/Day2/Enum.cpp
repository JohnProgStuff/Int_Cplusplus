// Enum.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	// allows scoped enums
	enum class Proportion
	{
		OneHalf,
		OneThird,
		OneQuarter
	};

	// Proportion pro = OneHalf; // error
	Proportion pro = Proportion::OneHalf;

	// scoped enum has to be explicitly converted to integer
	//if (OneHalf == 1)
	//{
	//	pro = 1;
	//}

	// allows specifying enum type
	enum Direction : unsigned short 
	{
		Sout,
		West,
		East,
		North
	};
	cout << sizeof(North) << endl;

	// allows forward declaration of enums
	enum class AirportCode;

	class FlightBoard
	{
	public:
		void print_airport_name(AirportCode code)
		{}

		void print_flight(AirportCode code, const string& flight)
		{
			//...
			print_airport_name(code);
		}
	};

	// more rules for forward declaration
	enum E : short;  // okay
	enum F;			 // error, underlying type is required
	enum class G : short;	// OK
	enum class H;			// OK, default type is int

	enum class E : short;	// error, cannot change from unscoped to scoped
	enum E : int;			// error, underlying type cannot be changed


	return 0;
}

