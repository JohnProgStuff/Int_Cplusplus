// TypeInference.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <map>
#include <vector>
#include <iostream>

int func(double)
{
	return 10;
}

template<typename X, typename Y>
auto automultiply(X x, Y y) -> decltype(x * y)
{
	return x * y;
}

int _tmain(int argc, _TCHAR* argv[])
{
	auto x = 5;
	auto str = "hello world";

	//auto arr[10];
	auto a = 1, b = 2;
	auto c = 5.0, d = 10.5;
	auto i = 1.0, *ptr = &c, &ref = d;
	//auto j = 20, str2 = "error";

	std::map<std::string, int> index;
	auto& ref2 = index;
	auto* ptr2 = &index;
	std::map<std::string, int>* ptr3 = &index;
	const auto j = index;
	const auto& cref = index;

	const std::vector<int> values;
	auto avec = values;	// type of avec is vector<int>
	auto& bvec = values;// type of bvec is const vector<int>&
	volatile long clock = 0;
	auto cint = clock;
	//volatile auto dint = clock;
	
	class JetPlane
	{
	};

	JetPlane fleet[10];
	auto fptr = fleet;	// type of fptr is JetPlane*
	auto& gref = fleet;	// type of gref is a reference

	auto gf = func;		// type of gf is int(*)(double)
	auto& hf = func;	// type of hf is int(&)(double)

	// decltype
	int k = 0;
	std::cout << typeid(decltype(k + 1.0)).name() << std::endl;
	std::vector<int> v2;
	decltype(v2) v3;
	v3.push_back(10);

	auto aa = automultiply(x, c);



	return 0;
}

template<class X, class Y>
void do_magic(const X& x, const Y& y)
{
	auto result = x * y;
}
