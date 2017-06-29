#include <iostream>
#include <vector>

using namespace std;

class Engine {};
class PlaneID {};

struct Lookup
{
	static int engine_count(PlaneID) { return 2; }
	static string manufacturer(PlaneID) { return string("Boeing"); }
	static string model(PlaneID) { return string("737-300"); }


};

class Boat
{
private:
	string _boat_manufacturer;
public:
	Boat(const string& manufacturer) : _boat_manufacturer{manufacturer}
	{}
};


class Plane
{
private:
	// allow initializers in member declarations
	string _manufacturer = "Unknown";
	string _model = "Unknown";
	vector<Engine> _engines{ 2 };
		//= { get_engine_count(_manufacturer, _model )};
		// { Engine{}, Engine{} }; //brand new feature of initializing in c++11/14
	/*static int get_engine_count(const string& manufacturer, const string& model)
	{
		if (manufacturer == "Unknown" || model = "Unknown")
		{
			return 0; // return number of engines
		}
		if (manufacturer == "Airbus")
		{
			return 2; // return number of engines
		}
		return 0;  
	} // end get_engine_count function 
	*/



public:
	// choose constructor initalizers over in-class initalizers
	/*
	Plane(const string& manufacturer) : _engines{ 2 } , 
		_manufacturer(manufacturer), _model("Unknown")
	{}

	Plane(const PlaneID& tail_number) : 
		_engines{ Lookup::engine_count(tail_number) }, 
		_manufacturer{ Lookup::manufacturer(tail_number) }, 
		_model{ Lookup::model(tail_number) }
	{}

	Plane() : _engines{ 2 }, _manufacturer{ "Unknown" }, _model{ "Unknown" }
	{}

	Plane(const string& manufacturer, const string& model) :
		_engines{ 2 }, _manufacturer{ manufacturer }, _model{ model }
	{}
	*/
	// allow all constructors to use this one constructor
	Plane(const int& engine_count, const string& manufacturer, const string& model) :
		_engines{ engine_count }, _manufacturer{ manufacturer }, _model{ model }
	{}

	Plane(const string& manufacturer) : Plane(2, manufacturer, "Unknown")
	{}

	Plane(const PlaneID& tail_number) : 
		Plane(Lookup::engine_count(tail_number), Lookup::manufacturer(tail_number), Lookup::model(tail_number))
	{}

	Plane() : Plane(2,"Unknown","Unknown")
	{}

	Plane(const string& manufacturer, const string& model) : Plane(2, manufacturer, model)
	{}
};

class JetPlane : public Plane
{
private:
	// allow initializers in member declarations
	
public:
	//default constructor
	//JetPlane() : _engines{ 2 }, _manufacturer{ "Unknown" }, _model{ "Unknown" } 
	//{}//body of constructor
	/*delete this block and use 'using Plane::Plane;' // new c++11 Constructor
	JetPlane(const string& manufacturer) 
		: Plane{ manufacturer }
	{} // body of constructor
	JetPlane(const string& tail_number)
		: Plane{ tail_number }
	{}
	*/
	// allow inheriting constructors from a base class
	using Plane::Plane; // new c++11 Constructor, don't give me any default constructors, use the base classes constructors

};

class PropPlane : public Plane
{
public:
	using Plane::Plane;

	PropPlane(const string& manufacturer) : Plane(manufacturer)
	{
		cout << "In PropPlane() " << endl;
	}
};

class FloatPlane : public Plane, public Boat
{
public:
	using Plane::Plane;
	using Boat::Boat;
	// overRide string constructor which allows to resolve base class constructor confilict
	FloatPlane(const string& manufactuer) : Plane(manufactuer), Boat("n/a") {}
	



};

class Employee
{
private:
	int _ID;
	string _name;
public:
	// copy constructor
	//Employee(const Employee& other);
	Employee(const Employee& other) = delete; // add delete for.... destructor? not a copy constuctor? what is it for?
	Employee(int ID);
	//Employee() = default;
	Employee() = delete; // add delete for.... destructor? not a copy constuctor? what is it for?
	Employee(Employee&&) = default;

	//~Employee() = default; // destructor
	// if the base class is ever going to be used as a base class (Even maybe), use a virtual destructor.
	virtual ~Employee() = default;
	//virutal destructors destroy all linked classes info too. Manager would be destroyed with Employee.
	
	Employee& operator=(const Employee&) = default;

};


int main()
{
	JetPlane plane1("Boeing");
	PropPlane plane2("John");
	FloatPlane bPlane1("boat");

} // end main
