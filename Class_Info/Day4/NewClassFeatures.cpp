#include <iostream>
#include <vector>
using namespace std;

int main()
{
	/*
	There's a fairly long list of class-related changes, so let's start with an overview. We've got in-class initializers for non-static data members;
we've got delegating constructors, which call other constructors; inheriting constructors from a base class; control of the default methods;
marking methods as uncallable with a delete keyword; we've got override and final specifiers; extended friend declarations; and finally nested
class access rights. I'm going to look at each of these in detail. C++11 gives you a new option for initializing non-static data members.
Instead of initializing members in constructors, you can add an in-class initializer to the member declaration. You can use either the
assignment form or curly braces, but not parentheses. This is useful when you have several constructors and they initialize some of the
members with the same expressions. Previously you had to duplicate initialization code between these constructors like this, but now you
can use a data member initializer instead. So, here I moved the initialization of engines manufacturer and model from the constructors to the
in-class initializers. The rules are quite flexible. You can use other members or member function calls in the initializing expression. Note the
initializer for the vector. It calls a static member function get_engine_count with the other two data members as arguments. Generally the
initializing expression can contain any names which are in scope at that point. However, when using member functions, bear in mind that
some members can still be uninitialized. The initialization is done in declaration order. Another thing to remember is that the type is no longer
an aggregate if it has in-class initializers, so you can't do this. This definition of C will make the compiler complain. So, what happens if you
use an in-class initializer and then initialize the member with some other value in the constructor? In this situation the initializer in the
constructor overrides the in-class initializer, so the number of engines will be 4, not 2.
	*/
	// support for in-class initializers
	class Engine {};

	// old method: example of duplication in constructors
	class JetPlane
	{
		vector<Engine> _engines;
		string _manufacturer;
		string _model;
	public:
		JetPlane() : _engines(2), _manufacturer("Unknown"), _model("Unknown")
		{}

		JetPlane(const string& manufacturer) : _engines(2), _manufacturer(manufacturer), _model("Unknown")
		{}
	};

	// new method: allows initializers in member declarations
	class JetPlane
	{
	private:
		//string _manufacturer("Boeing");
		string _manufacturer = "Unknown";
		string _model = "Unknown";
		vector<Engine> _engines = { Engine(), Engine() };
		//AssertThat(JetPlane()._engines.size(), Equals(2));
		//AssertThat(JetPlane()._model, Equals("Unknown"));
	public:
	};

	// new feature: allows function calls in in-class initializers
	class JetPlane
	{
	public:
		string _manufacturer = "Unknown";
		string _model = "Unknown";
		vector<Engine> _engines{ get_engine_count(_manufacturer, _model) };

		static size_t get_engine_count(const string& manufacturer, const string& model)
		{
			if (manufacturer == "Unknown" || model == "Unknown")
				return 0;

			if (manufacturer == "Airbus")
			{
				if (model == "A380-500")
					return 2;
			}
			// ...
		}
	};
	//AssertThat(JetPlane()._engines.size(), Equals(0));

	// chooses constructor initializers over in-class initializers
	class JetPlane
	{
	public:
		vector<Engine> _engines{ 2 };

		JetPlane() : _engines(4)
		{}
	};
	//AssertThat(JetPlane()._engines.size(), Equals(4));

	/*
	Let's talk about constructors now. You know how you have to re-implement constructors in derived classes. So, I've got a class called Plane
here, which has some data members, and it has a couple of constructors. JetPlane derives from plane, and I want JetPlane to be
constructed in the same way, but that means I have to re-implement the constructs in the JetPlane class even though they don't do anything
other than passing their parameters to the base class constructors. Obviously that's not the best use of mine or your time, so C++11 makes
an improvement in this department. In addition to regular functions, you can now apply the using directive to base class constructors. This
using statement means that JetPlane now has constructors from Plane available to it, and they are referred to as inherited constructors.
Inherited constructors keep attributes such as explicit and exception specifications. If you also declare a constructor in the derived class, it
overrides the base class constructor with the same signature. So, if I have a class called PropPlane, which inherits from Plane, and I define a
constructor, which takes a sting parameter, then this constructor is going to override the constructor from the base class. And when I
construct an instance of PropPlane, it will use the constructor from the PropPlane class. This behavior can also be used to resolve conflict
arising from multiple inheritance. So, this is another class hierarchy. I have class Plane and I have class Boat, and then I have class
FloatPlane, which inherits from both Plane and Boat. And I also want to make the constructors from both Plane and Boat available to
FloatPlane, so I've got two using statements in there. However, given those definitions of Boat and Plane, the definition of FloatPlane isn't
going to compile. That's because both Boat and Plane classes have a constructor which takes a string argument, in this case the
manufacturer name. So, what I need to do is override that particular constructor to resolve the ambiguity. The rest of the constructors from
Boat and Plane will still be available in the FloatPlane class. It's probably not a good idea to use inherited constructors if you add data
members to your derived class because it's easy to forget to initialize them. The effect of this code is the same as if you omitted the derived
class data members from the constructor initialization list. So, when you instantiate PropPlane, prop_count isn't going to be initialized. If you
do want to combine adding data members with inheriting constructors, you can mitigate the issue by using in-class initializers for the data
members in the derived class. Another source of duplication in constructors is when they have to execute the same initialization code. So,
here's my JetPlane class again. It's got a few data members, and it's got two constructors. Both of the constructors initialize as members and
then call configure_engines(). Again, C++11 makes things better by allowing a constructor to call another constructor from the same class in
the initialization list. So, this is how it looks. Both of the public constructors now call another constructor, which takes three parameters. Note
that the new constructor is private because I don't want the users of the class to create instances that way. The call to configure_engines() is
now only in one place in the private constructor. A constructor which invokes another constructor like this is called a delegating constructor. If
you employ delegation, you can't do anything else in the member initialization list. The constructor which is delegated to executes first
followed by the body of the delegating constructor. So, in the case of the JetPlane constructor, which takes a manufacturer and model list
parameters, it means that the private constructor will be executed first followed by the call to assign_tail_number(). Be careful not to cause a
recursive invocation of a constructor as that makes the program ill-formed.

	*/
	class PlaneID {};

	struct Lookup
	{
		static size_t engine_count(PlaneID) { return 2; }
		static string manufacturer(PlaneID) { return string("Boeing"); }
		static string model(PlaneID) { return string("737-300"); }
	};
	// requires constructors to be reimplemented in derived classes
	// broken example without inheriting constructors
	class Plane
	{
	public:
		vector<Engine> _engines;
		string _manufacturer;
		string _model;

		Plane(const string& manufacturer) : _engines(2), _manufacturer(manufacturer), _model("Unknown")
		{}

		Plane(const PlaneID& tail_number) : _engines(Lookup::engine_count(tail_number)),
			_manufacturer(Lookup::manufacturer(tail_number)), _model(Lookup::model(tail_number))
		{}
	};
	// example of constructor duplication in a derived class
	class JetPlane : public Plane
	{
	public:
		// boring
		JetPlane(const string& manufacturer) : Plane(manufacturer)
		{}

		// boring
		JetPlane(const PlaneID& tail_number) : Plane(tail_number)
		{}
	};
	//AssertThat(JetPlane("Boeing")._engines.size(), Equals(2));

	// allows inheriting constructors
	// inheriting constructors from a base class
	class JetPlane : public Plane
	{
		using Plane::Plane;
	};
	JetPlane plane("Boeing");	// OK
	//AssertThat(JetPlane("Boeing")._engines.size(), Equals(2));  // OK

	// allows inherited constructors to be overridden
	// override an inherited constructor
	class PropPlane : public Plane
	{
	public:
		using Plane::Plane;

		// overrides Plane constructor with the same parameters
		PropPlane(const string& manufacturer) : Plane(manufacturer)
		{
			cout << "In PropPlane()" << endl;
		}
	};
	PropPlane prop_plane("ATR");

	// solves complains when there's a conflict between base constructors
	class Boat
	{
		string _boat_manufacturer;
	public:
		Boat(const string& manufacturer) : _boat_manufacturer(manufacturer)
		{}

	};
	class FloatPlane : public Plane, public Boat
	{
		using Plane::Plane;
		using Boat::Boat;	// conflict because Boat also has a ctr that takes a string as argument
	};
	// allows to resolve base class constructor conflict
	class FloatPlane : public Plane, public Boat
	{
		using Plane::Plane;
		using Boat::Boat;
		FloatPlane(const string& manufacturer) : Plane(manufacturer), Boat("n/a")
		{}
	};

	// compiler support for delegating constructors
	struct Lookup
	{
		static size_t engine_count(const string& manufacturer, const string& model) { return 2; }
	};
	// bad example: can cause code duplication without delegation
	class JetPlane
	{
	private:
		vector<Engine> _engines;
		string _manufacturer;
		string _model;
	public:
		JetPlane() : _engines(2), _manufacturer("Unknown"), _model("Unknown")
		{
			configure_engines();
		}

		JetPlane(const string& manufacturer, const string& model) :
			_engines(Lookup::engine_count(manufacturer, model)), _manufacturer(manufacturer), _model(model)
		{
			configure_engines();
			assign_tail_number();
		}

		// ...
	private:
		void configure_engines()
		{}

		void assign_tail_number()
		{}
	};

	// good example: allows delegating to other constructors
	class JetPlane
	{
	public:
		vector<Engine> _engines;

	private:
		string _manufacturer;
		string _model;
	public:
		JetPlane() : JetPlane(2, "Unknown", "Unknown")
		{}

		JetPlane(const string& manufacturer, const string& model) :
			JetPlane(Lookup::engine_count(manufacturer, model), manufacturer, model)
		{
			assign_tail_number();
		}
	private:
		JetPlane(size_t engine_count, const string& manufacturer, const string& model) :
			_engines(engine_count), _manufacturer(manufacturer), _model(model)
		{
			configure_engines();
		}

		// ...

		void configure_engines()
		{}

		void assign_tail_number()
		{}
	};
	JetPlane plane;
	//AssertThat(plane._engines.size(), Equals(2));

	/*
	The next item on the menu is default methods. The compiler can generate a default constructor, destructor, copy constructor, and copy
assignment operator, as well as move operations, which I'll tell you about in the next module. However, if you declare your own constructor, it
prevents the generation of the default version. If you declare your own copy operations, then the compiler won't generate the move
operations and so on, but sometimes it's convenient to preserve some of these default operations, so C++11 provides a way to explicitly
request default implementations from the compiler. You do this by adding = default to the declaration. As an example, you can use this to
reinstate the default versions of the constructors. In this example I'd like to have my own version of the copy constructor, but when I declare
it, it disables compiler-generated default constructor and move constructor. Using the default keyword I can reinstate them. Not only that, but
this keyword also allows you to change the declaration at the same time. This is convenient because the compiler-generated versions are
public, inline, and non-explicit, which isn't always what you want. So, if you want, you can make the copy operations protected while
preserving the default implementation or you can make the default destructor virtual. Note that all of these declarations are marked with =
default. Generally it's better to use the default implementation when suitable rather than providing your own. You can also apply the delete
keyword to methods, which is sort of the opposite to default. Delete means that the function doesn't have an implementation, it's uncallable,
and can't be used in any way. The first use for it is to disable compiler-generated methods like this. So, here I've got a mix of default and
delete marked methods. This example disables copying for JetPlane while still allowing moving. Of course the previously existing idiom for
this was to declare the copy operations as private and not implement them. An interesting thing about delete is that it can be applied to any
function, not just those generated by the compiler and not just the class methods. This gives it a range of additional uses. It allows you to
disable particular instantiations for a template, you can use it to disable unwanted conversion, and also you can disable heap allocation. Let's
look at examples of this. If you have a template, you can disable instantiations for particular types like this. The result of this code is that
serialize can be called on instances of PasswordStore. Similarly, you can disable unwanted conversions. So, with this Altimeter class
definition, you'll be able to initialize Altimeter instances with doubles, but not with ints. Finally, to disable heap allocation you need to mark
operator new as deleted. With this definition of StackOnly, you'll be able to create instances on the stack, but you won't be able to allocate it
with new. You can mark virtual functions with delete too, but bear in mind that any other declarations of that function in the class hierarchy
will also need to be deleted. The key aspect of delete is that a deleted function still participates in name lookup, so the difference between
not declaring a function and marking it with delete is that in the case of undeclared function the compiler will continue looking for alternatives
whereas if it finds an explicitly deleted function it will stop with an error message. The end result is that delete gives you additional control
over function lookup.
	*/
	// allows defaulted functions
	class JetPlane
	{
	public:
		JetPlane() = default;
		JetPlane(const JetPlane& other);
		JetPlane(JetPlane&&) = default;
	};
	JetPlane plane;

	//allows modified declarations of compiler-generated functions
	class JetPlane
	{
	public:
		JetPlane() = default;
		virtual ~JetPlane() = default;	// this destructor is modified to virtual
	protected:
		JetPlane(const JetPlane& other) = default;
		JetPlane& operator=(const JetPlane&) = default;
	};

	//allows deleting compiler generated methods
	class JetPlane
	{
	public:
		JetPlane() = default;
		JetPlane(const JetPlane&) = delete;
		JetPlane& operator=(const JetPlane&) = delete;
		JetPlane(JetPlane&&) = default;
		JetPlane& operator=(JetPlane&&) = default;
	};
	JetPlane plane1;
	// auto plane2 = plane1; // error


	/*
	Speaking of control, the new keywords override and final allow you to enforce strict rules around inheritance. Both of these keywords are
context sensitive, so they can be used as identifiers outside of the context of class or member function declarations, so both of these
definitions are fine. The override keyword is applied to a virtual function to tell the compiler that it must be overriding a function in the base
class. It helps to prevent errors caused by overriding the virtual function with a function that has a different parameter list. So, here I've got
Base in the derived class, and there's a virtual function called F. The first definition of F in the derived class is okay because it overrides the
Base class definition, but the second definition is going to cause a compilation error because it's got the override keyword and it doesn't
override any Base class method. Without override, it would've simply created a new method, which may not be what I want. the final keyword
can be applied either to classes or to methods. When it's applied to a class, it disallows inheritance from that class. Because Base is
declared final, the Derived definition will fail to compile. When final is applied to a method, it means that the method can't be overridden in a
derived class. So, if I have a virtual function called F in the Interface class and then I derive Base from the Interface and declare this function
final there, I won't be able to override this function F in a class derived from Base.
	*/
	//support for inheritance control:
	// allows override and final as variable names
	int override = 5;       // OK
	int final = 10;         // OK

	//enforces override specifier
	struct Base
	{
		virtual void f(int)
		{}
	};

	struct Derived : public Base
	{
		virtual void f(int) override        // OK
		{}
		virtual void f(double) override      // error, no such function in the base 
		{}
	};
	
	//enforces final specifier on a class
	struct Base final
	{};
	struct Derived : public Base            // compile error, can't inherit from final class
	{};
	
	//enforces final specifier on a method
	struct Interface
	{
		virtual void f()
		{}
	};

	struct Base : public Interface
	{
		virtual void f() final
		{}
	};

	struct Derived : public Base
	{
		virtual void f()                    // compile error, can't override 
		{}                                  // a final method
	};

	/*
	In C++03 members of a nested class didn't have special access to members of an enclosing class. This was a
defect in the standard, which was rectified in C++11. The current rule is that a nested class is a member and therefore has the same access
rights as other members. In this example I'm using this rule to declare a GPSNavigator member in the nested Autopilot class. GPSNavigator
is also a member. I'm also using it to set flap_angle from the Autopilot class. Note that flap_angle is a private member of the outer class, and
I still can access it. This change allows you to improve encapsulation and locality in your code.
	*/
	//support for nested classes: gives nested class member rights
	class JetPlane
	{
		// ...
	private:
		int _flap_angle;

		class GPSNavigator {};

		class Autopilot
		{
			GPSNavigator _gps_navigator;        // OK, JetPlane::Autopilot can access 
			// JetPlane::GPSNavigator
			void adjust_flaps(JetPlane& plane, int flap_angle)
			{
				plane._flap_angle = flap_angle; // OK, JetPlane::Autopilot can
				// access JetPlane::_flap_angle
			}
		};
	};
	JetPlane plane;

	/*
	In addition to explicit constructors, you can now declare conversion operators explicit too. It allows you to prevent unwanted implicit
conversions. For example, the standard template std::function has an explicit bool() operator. This operator returns true if the function object
has as target, so things like this will not compile without an explicit cast. The attempts to define both sum and flag result in compilation errors
because implicit conversion to bool is disallowed by the operator; however, you can check whether a function instance has a target before
calling the function. This is because operator bool gets special treatment from the compiler, and its explicit specifier is ignored where it's
considered safe to do so. Examples of safe contexts are conditional statements and the turnery operator. The explicit specifier will be
enforced when checking for equality or inequality though.
	*/
	//explicit conversion operators: disables implicit conversions using explicit operators
	class Probability
	{
		double _value;
	public:
		Probability(double value) : _value(value)
		{}

		explicit operator bool() const noexcept
		{
			return _value > 0.0;
		}
	};

	Probability p1(0.5), p2(0.0);

	double sum = p1 + p2;       // this would compile if operator bool wasn't explicit; but likely not what you'd want

	if (!p1)
		//AssertThat(false, Equals(true));

	if (p2)
		//AssertThat(false, Equals(true));


	return 0;
}