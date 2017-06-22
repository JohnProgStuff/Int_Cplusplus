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
	A(const A& rhs)
	{
		//requires lvalue reference then its a copy constructor
		cout << "A's copy constructor" << endl;
	}


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

}