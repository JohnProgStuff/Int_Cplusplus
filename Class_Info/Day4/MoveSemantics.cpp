// MoveSemantics.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <utility>	// move()
#include <string>

using namespace std;

class JetPlane
{
private:
	string _model;
public:
	JetPlane() = default;
	JetPlane(const string& model) : _model(model)
	{}

};

class A
{
private:
	double _d;
	int* _p;
	string _str;
public:
	A()
	{
		cout << "A's constructor." << endl;
	}
	A(const A& rhs)
	{
		cout << "A's copy constructor." << endl;
	}
	A(A&& rhs) 
		: _d(rhs._d), _p(rhs._p), _str(move(rhs._str))
	{
		rhs._p = nullptr;
		rhs._str.clear();
		cout << "A's move constructor" << endl;
	}

	A& operator=(A&& rhs)
	{
		delete _p;

		_d = rhs._d;
		_p = rhs._p;
		_str = move(rhs._str);
		rhs._p = nullptr;
		rhs._str.clear();
		return *this;
	}

	// allows member function reference qualifiers
	///bool run() const & { return false; }
	// bool run() && {return true; }

};

//A a;
//a.run()	
//A().run()

// enables creation of move-only types
class MoveOnly
{
private:
	int* _p;
public:
	MoveOnly() : _p(new int(10))
	{
	}
	~MoveOnly()
	{
		delete _p;
	}
	// disable copy constructor and 
	// also disable copy assignment operator
	MoveOnly(const MoveOnly& rhs) = delete;
	MoveOnly& operator=(const MoveOnly& rhs) = delete;
	
	// implement move cosntructor
	MoveOnly(MoveOnly&& rhs) : _p(rhs._p)
	{
		//_p = rhs._p;
		rhs._p = nullptr;
	}
	
	// move assignment operator
	MoveOnly& operator=(MoveOnly&& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}
		delete _p;
		_p = rhs._p;
		rhs._p = nullptr;
		return *this;

	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	// copies in the absense of move semantics
	vector<string> v;
	v.push_back(string("a"));
	v.push_back(string("b"));
	// constructing a string like this results in 
	// many temporary objects
	string s = string("Boeing") + "737" + "-" + "300";
	cout << s << endl;

	vector<A> v2;
	cout << "==> push_back(A): " << endl;
	v2.push_back(A());
	cout << "==> push_back(A): " << endl;
	v2.push_back(A());

	MoveOnly m1;	// invokes default contructor
	MoveOnly m2(m1);// error: copying does not compile
	MoveOnly m3 = m1;//error: copying does not compile
	MoveOnly m4;	// invokes default constructor
	m4 = m1;		// error: copy assignment does not compile
	m4 = MoveOnly();// okay
	m4 = move(m1);	// okay

	return 0;
}

