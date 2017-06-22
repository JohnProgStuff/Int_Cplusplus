#pragma once
#include <string>

using namespace std;

class BankAccount
{
private:
	int _balanceInPennies;
	string _owner;
public:
	BankAccount(void);
	BankAccount(int, string);
	~BankAccount(void);
	string getOwnerName() { return _owner; }
	bool operator< (BankAccount& b);
};