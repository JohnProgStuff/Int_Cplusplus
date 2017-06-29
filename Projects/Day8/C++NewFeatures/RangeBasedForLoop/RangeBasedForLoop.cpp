#include <iostream>
#include <vector>
#include <string>
#include <list>

using namespace std;
/*
class MyContainer1
{
private:
	list<int> _values{ 111,222,333 };
	friend list<int>::iterator begin(MyContainer& con);
	friend list<int>::iterator end(MyContainer& con);
};
*/
class MyContainer  // create a Container type
{
private:
	list<int> _values;
public:
	MyContainer() : _values{ {111,222,333} } // inside makes initializer list, outside brackets assign to _values
	{} // body of constructor
	friend list<int>::iterator begin(MyContainer& con);
	friend list<int>::iterator end(MyContainer& con);
};

list<int>::iterator begin(MyContainer& con)
{
	return con._values.begin();
}

list<int>::iterator end(MyContainer& con)
{
	return con._values.end();
}

int main()
{
	vector<int> v{ 1,2,3,4,5 };
	
	// REGULAR FOR LOOP
	cout << "Regular For Loop" << endl;
	for (vector<int>::iterator itor = begin(v);
		itor != end(v); ++itor)
	{
		auto element = *itor;
		cout << element << " ";
	}

	cout << endl;

	// RANGE BASED FOR LOOP
	// element is a copy of the item stored in v so it won't change v.
	cout << "\nRange BasedFor Loop \nUsing copies" << endl;
	for (auto element : v)
	{
		element *= 2;
		cout << element << " ";
	}
	cout << "\nOriginal vector v unchanged" << endl;
	// now see that v is still the original vector
	for (auto element : v)
	{
		cout << element << " ";
	}

	// but if you want to change the values then use the & reference pointer.
	cout << "\n\nRange BasedFor Loop\nUsing Original items" << endl;
	for (auto& element : v)
	{
		element *= 2;
		cout << element << " ";
	}
	cout << "\nOriginal vector v now updated" << endl;
	// now see that v is still the original vector
	for (auto element : v)
	{
		cout << element << " ";
	}
	cout << endl << endl;

	// Range based for loop allows iteration of simple arrays
	//  Arrays note: arrays are not resizable like vectors are.
	int arr[] = { 10,20,30,40 };
	cout << "For loop using array" << endl;
	for (auto elem : arr)
	{
		cout << elem << " ";
	}
	cout << endl << endl;

	// Range Based For Loop allows iteration over initializer list instances
	initializer_list<int> list = { 100,200,300,400 };
	auto list1 = { 100,200,300,400,500 }; // another list
	cout << "For loop using initializer_list instance" << endl;
	for (auto elem : list1)
	{
		cout << elem << " ";
	}
	cout << endl << endl;

	// Range Based For Loop allows iteration over user defined types
	MyContainer con;
	cout << "For loop using user defined type Container instance" << endl;
	for (auto elem : con)
	{
		cout << elem << " ";
	}
	cout << endl << endl;

	// REGULAR FOR LOOP
	cout << "Regular For Loop" << endl;
	for (vector<int>::iterator itor = begin(v), seq_end = end(v); // define 2 variables of iterator type
		itor != seq_end; ++itor)
	{
		// the above use is similar to:
		// int a, b      or
		// int a=5, b=10

		auto element = *itor;
		cout << element << " ";
	}

}// end main