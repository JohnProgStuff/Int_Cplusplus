#include <iostream>
#include <memory> // make_unique

using namespace std;

class Hen
{
private:
	unsigned _id;
	double _eggs; // average number of eggs each hen produces each week
public:
	Hen(unsigned id, double eggs) : _id{ id }, _eggs{ eggs }
	{}
	~Hen()
	{
		cout << "Chicken Soup!" << endl;
	}
	
	void setEggs(double a)
	{
		_eggs = a;
	}
	double getEggs()
	{
		return _eggs;
	}
	
};


auto getHen() -> unique_ptr<Hen>
{
	return make_unique<Hen>(2, 4.8);
}

auto updateHen(unique_ptr<Hen> hen) -> unique_ptr<Hen>
{
	hen->setEggs(hen->getEggs() + 1.8);
	return hen;
}

int main()
{
	// make some Smart Pointers
	auto sp = unique_ptr<int>{};
	//int* ptr = new int{};
	auto sp2 = unique_ptr<int>{ new int{123} };
	// highly recommended way to create a smart pointer...
	auto sp3 = make_unique<int>(123);

	auto hen = make_unique<Hen>(1, 5.6);
	//cannot copy a unique pointer
	//auto hen2 = hen; won't work, it tries to call the copy constructor
	// but you can move a unique pointer. unique pointers explicitly support move semantics
	auto hen2 = move(hen);
	// unique pointer supports an explicit conversion to boolean to determine whether it holds nullptr
	if (hen) // hen is currently pointing to nullptr which is also false in c++
	{
		cout << "hen owns the hen object" << endl;
	}
	else
	{
		cout << "hen2 owns the hen object" << endl;
	}
	
	// create a copy of a hen object
	Hen copy = *hen2;
	copy.setEggs(3.5);

	// we may destroy the object being pointed to by a unique pointer anytime we want
	//hen2.reset(); // we use this in 3 lines so don't clear it.

	auto hen3 = getHen();
	//auto hen3 = make_unique<Hen>(2, 4.8); // same as line above.

	hen2 = updateHen(move(hen2));

	// get raw pointer from a unique pointer
	Hen* ptr = hen3.get();
	Hen* ptr2 = hen3.release();

	return 0;


}