#pragma once
#include <string>
#include <iostream>

namespace YongZhang
{
	class Employee
	{
	private:
		std::string name;
		int number;
		static int maxnum;
		friend std::ostream& operator<<(std::ostream& o,
			const Employee& e);
		bool manager;
	
	public:
		Employee(std::string n, bool mgr = false)
			: name(n), number(++maxnum), manager(mgr)
		{}

		std::string getName() const
		{
			return name;
		}

		bool operator<(const Employee& e)
		{
			return name < e.name;
		}

	};

}