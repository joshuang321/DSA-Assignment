//==================================================================
// Student Number : S10205140B, S10223630K
// Student Name :Joshua Ng, Armirola Roseller Iii Tumolva
// Module Group : P03
//==================================================================

#include "Account.h"
#include <string>
#include <fstream>
#include <filesystem>

#include <Windows.h>

Account::Account(std::string username, std::string password) : username(username),
	password(password)
{ }

Account::Account(const Account& acc) :
	username(acc.username),
	password(acc.password)
{
#if defined(_DEBUG)
	OutputDebugStringA("Account_CC\n");
#endif
}

Account::Account(Account&& acc) :
	username(std::move(acc.username)),
	password(std::move(acc.password))
{
#if defined(_DEBUG)
	OutputDebugStringA("Account_MC\n");
#endif
}

/* String template to save account data */
Account::Account(std::string strline)
{
	size_t ndelim = strline.find(';');
	password = strline.substr(ndelim + 1, strline.length() - ndelim - 1);
	username = strline.substr(0, ndelim);
}

/* Function to check if the account password matches the password input */
bool Account::isCorrect(std::string password) { return password == this->password; }


std::ostream& operator<<(std::ostream& os, Account& acc)
{
	os << acc.username << ';' << acc.password;
	return os;
}

bool Account::operator==(Account& acc)
{
	return acc.username == username;
}