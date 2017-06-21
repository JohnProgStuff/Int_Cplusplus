#include <iostream>
#include <vector>

using namespace std;

class Engine
{};

class JetPlane
{
private:
	// allow initializers in member declarations
	vector<Engine> _engines = { Engine{}, Engine{} }; //brand new feature of initializing in c++11/14
	string _manufacturer = "Unknown";
	string _model = "Unknown";
public:
	//default constructor
	JetPlane() : _engines{ 2 }, _manufacturer{ "Unknown" }, _model{ "Unknown" } 
	{}//body of constructor

	JetPlane(const string& manufacturer) : _engines{ 2 }, _manufacturer{ manufacturer }, _model{ "Unknown" } 
	{} // body of constructor
};





int main()
{

} // end main
