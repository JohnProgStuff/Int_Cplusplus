#include <iostream>
#include <vector>

using namespace std;

class JetPlane
{
public:
	JetPlane() = default;

};

// introduce 4 new types
void foo(JetPlane&) {
	cout << "foo(JetPlane&)" << endl;
}
void foo(const JetPlane&) {
	cout << "foo(const JetPlane&)" << endl;
}
void foo(JetPlane&&) {
	cout << "foo(JetPlane&&)" << endl;
}
void foo(const JetPlane&&) {
	cout << "foo(const JetPlane&&)" << endl;
}

class A
{
public:
	A() { cout << "A's constructor!" << endl; }
	A(const A& rhs) = delete;  // use = delete when you have a defined move constructor.
	/*{
		//requires lvalue reference then its a copy constructor
		cout << "A's copy constructor" << endl;
	}*/

	A(A&& rhs)
	{
		cout << "A's move constructor" << endl;
	}


};

// a resource refers to an object that requires significatn effort to construct copy and destroy.
class B
{
private:
	double _d;
	int* _p;
	string _str;
public:
	// default constructor
	B() : _p{ new int{10} }
	{}
	// destructor
	~B()
	{
		delete _p;  // makes _p point to nullptr
	}
	// move semantics = move constructor + move assignment operator.
	// Move constructor
	// move() changes a lvalue to a rvalue
	B(B&& rhs) : _d{ rhs._d }, _p{ rhs._p }, _str{ rhs._str }
	{
		cout << "B's move constructor" << endl;
		// simple objects like a double are just copied, but more complex things like ptrs, 
		// strings etc the location in memory stays the same but the new object points to it 
		// so we must tell the old object not to point to it.
		// clear original object data
		rhs._p = nullptr; 
		// don't use rhs._p = delete here because it would delete the block of memory and the 
		// new _p is pointing to the existing block in memory, so we don't want it deleted.
		rhs._str.clear();
	}

	// move assignment operator =
	B& operator=(B&& rhs)
	{
		// release the resources _p points to 
		delete _p;

		_d = rhs._d;
		_p = rhs._p;
		_str = move(rhs._str);

		rhs._p = nullptr;
		rhs._str.clear();
		return *this;
	}


	// copy constructor
	B(const B& rhs) = delete;

};



int main() 
{
	JetPlane jet;

	// a reference to a non-const type can only be initialized with a non-const lvalue
	JetPlane& jet_ref = jet;
	const JetPlane grounded_jet;
	// following does not compile because grounded_jet is a const lvalue. and jef_ref2 is a non constant lvalue.
	// try to use a const lvalue to initialize a reference
	//JetPlane& jet_ref2 = grounded_jet;
	const JetPlane& jet_ref2 = grounded_jet; // works because they are both const but not sure it should work.
	// try to use a rvalue to initialize a reference
	JetPlane& jet_ref3 = JetPlane();
	// try to use a const rvalue to initialize a reference
	auto make_const_jet = []() -> const JetPlane
	{
		return JetPlane();
	};
	
	const JetPlane& jet_ref4 = make_const_jet();


	// now lets talk about rvalue references
	JetPlane&& jet_ref5 = JetPlane();
	// lvalue cannot be used to initalize rvalue references.
	//JetPlane&& jet_ref6 = jet; //jet is a lvalue.
	// cant use lvalue if its const or non-const
	//JetPlane&& jet_ref7 = grounded_jet;
	// const rvalue cannot be used to initialize rvalue references
	//JetPlane&& jet_ref8 = make_const_jet();
	
	// 4 types of references:
	// rvalue reference, constant rvalue reference, lvalue reference, constant lvalue reference

	// 4 new types:*************************************************
	// declared before main()
	// introduce 4 new types
	foo(jet);		//	void foo(JetPlane&)
	foo(jet_ref);	//	void foo(JetPlane&)
	foo(jet_ref2);	//	void foo(const JetPlane&)
	foo(JetPlane());//	void foo(JetPlane&&)
	foo(make_const_jet()); //	void foo(const JetPlane&&)

	//C++ chooses what function to call at compile time and program is more efficient
	//java chooses what function to call at runtime decreasing efficiency slightly.

	vector<A> v;
	cout << "==> push_back A(): " << endl;
	v.push_back(A());
	cout << "==> push_back A(): " << endl;
	v.push_back(A());
	cout << "==> push_back A(): " << endl;
	v.push_back(A());
	cout << "==> push_back A(): " << endl;
	v.push_back(A());
	/*
	create object constructor is called
	| A() | .pushback pushes a copy of the object by calling copy constructor
	create object constructor is called
	vector needs to be expanded so it copies the first one.
	| A() | .pushback pushes a copy of the object by calling copy constructor
	then copies the 2nd one.
	| A() | .pushback pushes a copy of the object by calling copy constructor

	output:
		==> push_back A():
		A's constructor!
		A's copy constructor
		==> push_back A():
		A's constructor!
		A's copy constructor
		A's copy constructor
	*/
	B b1;
	B b2(move(b1));
	// B b3{ B() }; // this line works in VS2015 but for some reason not in VS2017.


	return 0;

}