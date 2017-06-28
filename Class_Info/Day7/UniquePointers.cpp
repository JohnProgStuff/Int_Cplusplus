// UniquePointers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <memory>
#include <iostream>

using namespace std;

class Hen
{
public:
	unsigned _id;
	float _eggs; // average number of eggs each hen produces each week
public:
	Hen(unsigned id, float eggs) : _id{ id }, _eggs{ eggs }
	{}
	~Hen()
	{
		cout << "Chicken Soup!" << endl;
	}
};

auto getHen() -> unique_ptr<Hen>
{
	return make_unique<Hen>(2, 3.9f);
}

auto updateHen(unique_ptr<Hen> hen) -> unique_ptr<Hen>
{
	hen->_eggs += 1.8f;
	return hen;
}

int _tmain(int argc, _TCHAR* argv[])
{
	auto sp = unique_ptr<int>{};
	auto sp2 = unique_ptr<int>{new int{ 123 }};
	auto sp3 = make_unique<int>(123);

	// make_unique uses perfect forwarding to trigger the constructor
	auto hen = make_unique<Hen>(1, 5.6f);

	// error: the compile will not allow to copy a unique pointer
	// auto hen2 = hen;

	auto hen2 = move(hen);
	if (hen)
	{
		cout << "hen owns the hen!" << endl;
	}
	if (hen2)
	{
		cout << "hen2 owns the hen!" << endl;
	}

	// copy a hen object
	Hen copy = *hen2;

	// grad a reference instead
	Hen& ref = *hen2;

	// obtain a raw/naked pointer from a unique pointer
	Hen* ptr = hen2.get();
	if (hen2)
	{
		cout << "hen2 still owns the hen!" << endl;
	}

	// request a unique pointer to realease its ownership
	Hen* ptr2 = hen2.release();
	if (hen2)
	{
		cout << "hen2 still owns the hen!" << endl;
	}
	else
	{
		cout << "hen2 does not own it after calling release!" << endl;
	}

	hen2.reset(ptr2);

	// hen3 exclusively owns the underperforming hen
	auto hen3 = getHen();

	hen2 = updateHen(move(hen2));

	return 0;
}

