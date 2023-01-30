#include "Account.h"
#include <string>
#include <fstream>
#include <filesystem>

static const char* AccSaveFilename = "Accounts.dat";

Account::Account(std::string username, std::string password) : username(username),
	password(password)
{ }

Account::Account(std::string strline)
{
	int ndelim = strline.find(';');
	password = strline.substr(ndelim + 1, strline.length() - ndelim - 1);
	username = strline.substr(0, ndelim);
}

std::string Account::getUsername() { return username; }

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