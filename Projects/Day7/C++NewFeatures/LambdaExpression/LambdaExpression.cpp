#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <deque>
#include <functional>


using namespace std;
class Scale
{
private:

	int _scale;

public:
	Scale(int scale) : _scale{ scale } {}

	void applyScale(vector<int>& v) const
	{
		transform(
			v.begin(),
			v.end(),
			v.begin(),
			[=](int n)
			{
				return n * _scale;
			}
		);
	}
}; // end class Scale

template<typename T>
void print_all(const vector<T>& v)
{ // works with any vector that contains any type.
	for_each(v.begin(), v.end(), [](const T& n) {cout << n << endl; });
}



int main()
{
	vector<int> v;
	
	for  (int i = 0; i < 10; i++)
	{
		v.push_back(i); // load items into vector
	}

	for each (auto var in v)
	{
		cout << var << " ";
	}
	cout << endl << endl;

	// now use a lambda expression to display each item.
	for_each(
		v.begin(), 
		v.end(), 
		[](auto n) {cout << n << " "; } //Lambda Expression
	);

	cout << endl << endl;
	// multiple statements in a lambda expression
	// lets say we only want to display even number in vector v
	for_each(
		v.begin(),
		v.end(),
		//LambdaExpression
		[](auto n)
		{
			cout << n << " ";
			if (n % 2 == 0) 
			{
				cout << "even" << endl;
			}
			else
			{
				cout << "odd" << endl;
			}
		}
	);

	// lambda expression with returning type
	// explicitly specifying the return type

	vector<double> dv;
	transform(
		v.begin(),
		v.end(),
		back_inserter(dv),
		[](int n) -> double // -> double is the trailing return type
		{
			if (n % 2 == 0)
			{
				return n * n * n;
			}
			else
			{
				return n / 2;
			}
		}
	);
	// print the transformed vector.
	for_each(
		dv.begin(),
		dv.end(),
		[](double d) {cout << d << " "; }
	);
	cout << endl << endl;

	// deciding the return type from the code
	vector<int> v2;
	transform(
		v.begin(),
		v.end(),
		back_inserter(v2),
		[](int n) {return n*n; } // compiler doesn't need the -> int trailing return type.
	);

	// print the transformed vector.
	for_each(
		v2.begin(),
		v2.end(),
		[](double d) {cout << d << " "; }
	);
	cout << endl << endl;

	// capture by value explicitly
	int x = 3;
	int y = 7;
	cout << "Printing elements between " << x << " and " << y << endl;
	for_each(
		v.begin(),
		v.end(),
		[x, y](int n) // x and y have to be passed into lambda expression functions just like in real functions.
		{
			if (n >= x && n <= y)
			{
				cout << n << " ";
			}
		}
	);
	cout << endl << endl;
	// capture the value implicitly
	x = 2;
	y = 8;
	cout << "Printing elements between " << x << " and " << y << endl;
	for_each(
		v.begin(),
		v.end(),
		[=](int n) // = says capture everything and pass it in. 
		{
			// x and y have to be implicitly passed into lambda expression function.
			if (n >= x && n <= y)
			{
				cout << n << " ";
			}
		}
	);

	// capture by reference
	for_each(
		v.begin(),
		v.end(),
		[&x, &y](int& r) 
		{
			const int old = r;
			r *= 2;
			x = y;
			y = old;

		}
	);

	cout << endl << endl;

	// capture the whole stack by reference
	v.clear();
	int i = 0;
	generate_n(
		back_inserter(v),
		10,
		[&]{ return i++; }
	);

	// assign a lambda expression to a variable
	function<int(int, int)> f1 =
		[](int a, int b) {return a * b; }; // compiler figures out return type.
	// f2 works the same as f1
	auto f2 = [](int a, int b) {return a + b; }; 

	cout << f1(2, 3) << endl;
	cout << f2(3, 5) << endl;

	auto f3 = { f1 }; // These functions are treated as objects and can be used as objects.

	// call a lambda expression immediately with arguments
	int n = [](int a, int b) {return a*b; }(5, 6);
	cout << "n = " << n << endl;

	cout << [](int a, int b) {return a + b; }(4, 5) << endl;

	// nested lambda expression
	int result = [](int a)
	{
		return [a](int b) 
		{
			cout << "a: " << a << " and b: " << b << endl;
			return b * 3;
		}(a)+6;
	}(5);

	Scale s{ 3 };
	s.applyScale(v);
	print_all<int>(v);
	print_all<double>(dv);
} // end main