#include "stdafx.h"
#include "BankAccount.h"


BankAccount::BankAccount(void)
{
}

BankAccount::~BankAccount(void)
{
}

BankAccount::BankAccount(int balanceInPennies, string owner)
: _balanceInPennies(balanceInPennies), _owner(owner)
{
}

bool BankAccount::operator<(BankAccount& b)
{
	//return _balanceInPennies < b._balanceInPennies;
	return _owner < b._owner;
}