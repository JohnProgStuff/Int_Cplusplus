#include <iostream>
#include <crtdbg.h> // c runtime library for debugging
#include <cassert>
#include <Windows.h>
#include <stdio.h>


#define ASSERT _ASSERTE
#ifdef _DEBUG	// is it debug mode or release mode
#define VERIFY ASSERT 
#else
#define VERIFY (expression) (expression)
#endif // _DEBUG

class LastException
{
public:
	DWORD result;
	LastException() : result{ GetLastError() }
	{}

};
class ManualResetEvent
{

public:
	HANDLE _handle;
	ManualResetEvent()
	{
		_handle = CreateEvent(nullptr, true, false, nullptr);
		if (!_handle)
		{
			throw LastException();
		}
	}
	~ManualResetEvent()
	{
		//ASSERT(CloseHandle(_handle));
		VERIFY(CloseHandle(_handle));
	}
};
using namespace std;

static_assert(sizeof(float) == 4, "Can't serialize floats! "); //this line is checked at compile time.


int main()
{
	//ASSERT(4 > 5); //this line kill the program
	ASSERT(6 > 5);

	printf("success\n");

	auto e = ManualResetEvent{};
	auto e2 = e;


}
