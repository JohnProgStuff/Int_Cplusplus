#include <iostream>
#include <vector>

#define ASSERT _ASSERTE
using namespace std;


int main()
{
	vector<int> v;
	v.push_back(3);
	v.push_back(5);
	v.push_back(9);

	for (auto i = v.rbegin(); i != v.rend(); ++i)
	{
		cout << *i << endl;
	}

}