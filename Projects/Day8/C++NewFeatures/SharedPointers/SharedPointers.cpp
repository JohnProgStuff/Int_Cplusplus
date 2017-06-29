//#include <iostream>
#include <memory> //_ASSERTE
//#include <crtdbg.h>
//#include "stdafx.h"
#define ASSERT _ASSERTE
using namespace std;

int main()
{
	auto sp = shared_ptr<int>{};
	ASSERT(!sp);
	ASSERT(sp.use_count() == 0);

	// highly recommended way to create a shared pointer
	sp = make_shared<int>(123);
	ASSERT(sp.use_count() == 1);
	ASSERT(sp.unique());

	//copy is okay for shared pointers
	auto sp2 = sp;
	ASSERT(!sp.unique());
	ASSERT(sp.use_count() == 2);
	ASSERT(sp2.use_count() == 2);

	// obtain the object itself being pointed to
	int copy = *sp;
	int& ref = *sp;
	int* ptr = sp.get();

	ASSERT(sp.get() == sp2.get());
	ASSERT(sp == sp2); // same result as line above



	return 0;

}