#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>

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


	// use list
	auto d = list<int>{};
	ASSERT(d.empty());
	ASSERT(d.size() == 0);
	d = list<int>{ 1,2,3,4,5 };
	ASSERT(d.size() == 5);
	d = list<int>(10, 555); // ten items, give every item value 555
	ASSERT(d.size() == 10);
	for (auto e : d)
	{
		ASSERT(e == 555);
	}

	d.emplace_back(6);
	d.emplace_back(0);
	d.emplace(begin(d), -1);

	// set
	auto c = set<int, less<int>>{};
	ASSERT(c.empty());
	c = set<int>{ 3,1,4,2,5 };  // a set is always sorted.
	for (auto e : c)
	{
		cout << e << endl;
	}

	 // map
	auto m = map<string, int>{};
	m["Utah"] = 2345670;
	m["California"] = 9999990;
	
	cout << "Population of the state of Utah is " << m.find("Utah") -> second << endl;


	return 0;

}