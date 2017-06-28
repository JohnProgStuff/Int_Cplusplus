// SharedPointers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <memory>
#include <crtdbg.h>

#define ASSERT _ASSERTE

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	auto sp = shared_ptr<int>{};
	ASSERT(!sp);
	ASSERT(sp.use_count() == 0);

	// reset a shared pointer and give it an object to manage
	sp.reset(new int{ 123 });
	sp = make_shared<int>(123);
	ASSERT(sp.use_count() == 1);
	ASSERT(sp.unique());

	// copy a shared pointer
	auto sp2 = sp;
	ASSERT(sp.use_count() == 2);
	ASSERT(!sp.unique());
	ASSERT(sp2.use_count() == 2);
	ASSERT(!sp2.unique());

	// obtain the object using shared pointer
	int copy = *sp;
	int& ref = *sp;
	int* ptr = sp.get();

	// get() will return the same raw pointer
	ASSERT(sp2.get() == sp.get());
	ASSERT(sp == sp2);



	return 0;
}

