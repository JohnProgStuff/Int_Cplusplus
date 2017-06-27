#pragma once
#include <string>
using namespace std;

class BankAccount
{
private:
	string _holderName;
	int _balance;

public:
	BankAccount() = default;
	BankAccount(string name, int balance) : _holderName{ name }, _balance{ balance } 
	{}

	int getBalance() { return _balance; }
	string getHolderName() { return _holderName; }

	bool operator<(const BankAccount& b)
	{
		return _holderName < b._holderName;  // < has already been defined for strings just not for BankAccount until now.
		// return _balance < b._balance; //what do you want it to test for
	}

	// you should implement move semantics but we won't here because we are working on Template functions.
};