#include <iostream>
#include <cstring>
//Not recommended to use c style strings in your code but
// it is being used here to demonstrate Null Pointers

using namespace std;

bool ambiguous(int a)
{
	return false;
}

bool ambiguous(int* ptr)
{
	return true;
}

int main()
{
	int* p1 = NULL; // p1 doesn't point to anything currently NULL is defined as 0
	int* p2 = 0;

	bool a = ambiguous(p2);
	cout << a << endl;
	bool b = ambiguous(NULL);
	cout << b << endl;


	int* p3 = nullptr;
	bool c = ambiguous(p3);
	cout << c << endl;

	delete p1;  // nullptr is assigned to p1
	c = ambiguous(p1);
	cout << c << endl;

	if (p3 == 0)
	{
		cout << "true" << endl;
	}

	p1 = NULL;
	cout << ambiguous(p1) << endl;

	int* p4{};


}// end main