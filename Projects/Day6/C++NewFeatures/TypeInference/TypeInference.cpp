#include <string>
#include <vector>
#include <map>  //Template class that allows mapping between types.
#include <iostream>
using namespace std;

// function declaration and definition
int func(double d)
{
	return 10;
}

//void invalid(auto i) // you cannot specify auto as function parameter. Confuses Compiler.
//{
//  	//..............
//}

//class A
//{
//	auto _m;  //cannot use auto if Compiler cannot figure out the type.
//};

template<typename X, typename Y>
void do_magic(const X& x, const Y& y)   // we are making a copy of the variables and passing them in.
{
	auto result = x * y;	// we don't know what type 'result' is going to be.
}

/*template<typename A, typename B>
ReturnType multiple(A a, B b) // there is now way of determining the ReturnType type yet.
// auto  multiple(A a, B b) // won't work either
{
	return a * b;
}
*/

template<typename A, typename B>
auto multiple(A a, B b) -> decltype(a*b) // declare the returning type to compiler.
{
	return a * b;
}

//template<typename A, typename B>
//decltype(a*b) multiple(A a, B b) // won't work. decltype has to be at the end
//{
//	return a*b;
//}


int main()  // c++11 made it optional to actually return the int in the main() program.
{
	int number = 0;
	double weight = 124.89;
	double total = number * 10;
	
	auto x = 5;
	auto y = 1.0;
	auto str = "Hello John!";
	// the following is not allowed:
	// auto z;
	// declaring multiple variables in a single statements
	auto a = 2.0, b = 5.9;
	auto str1 = "Okay", str2 = "Error";

	// declaring multiple variables of different types in a single statement.
	auto i = 1.0, *ptr = &a, &ref = b;
	//     double *ptr = &a;			// pointer to a
	//               double  &ref = b;  // Just another name for b

	// declare a variable of user defined type
	// auto myaccount = new MyBankAccount(); //comment out because MyBankAccount() is not defined.

	// syntax sugar
	vector<int> myvector;
	//vector<double> v2;
	//vector<BankAccount> v3; //comment out because BankAccount Type is not defined.
	for (std::vector<int>::const_iterator itr = myvector.cbegin();
		itr != myvector.cend(); ++itr) 
	{
		
	}
	// same as previous for loop, using TypeInference 'auto'.
	for (auto itr = myvector.cbegin(); itr != myvector.cend(); ++itr)
	{

	}

	// using the map class
	map<string, int> index;
	auto& ref2 = index; //ref2 is a reference to the map called index.
	auto* prt2 = &index; //prt2 is a pointer that points to a map type.

	// map<string, int>* ptr3; //Don't forget to initialize ptr3
	//using auto prt2 we are required to assign prt2 a value
	const auto in = index;
	const auto& inref = index;

	const vector<int> values;
	auto aa = values; // aa is a vector<int> type
	auto& bb = values; // bb is a const vector<int> type
	volatile long clock = 0;
	auto c = clock;		// c is not volatile

	
	// auto with arrays
	//BankAccount accounts[10];
	//auto e = accounts;	// e is BankAccount* type
	//auto& f = accounts;	// f is BankAccount(&)[10] 


	// auto with functions
	auto g = func;		// type of g is int(*)(double)
	auto& h = func;		// type of h is int(&)(double)

	do_magic<double, int>(a, x);

	// auto works only with variables
	auto cc = 10 * 4.0 - 5;		//this isn't going to work
	auto cd = 10 * a - 5 * b;	//this isn't going to work

	// decltype is a generalized tool that works with anything
	decltype(values) v3;
	decltype(values)::const_iterator iter = v3.end();

	auto i2 = 1;			// type of i is integer
	cout << "Before decltype, i2 = " << i2 << endl;
	decltype(i2++) j;	// type of j is integer
	cout << "after decltype, i2 = " << i2 << endl;




	return 0;
}


