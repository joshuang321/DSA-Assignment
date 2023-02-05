#pragma once

#include <string>

class Account
{
	std::string password;

public:
	std::string username;

	Account() { }
	Account(std::string strline);
	Account(const Account&);
	Account(Account&& acc);

	Account(std::string username, std::string password);
	Account& operator=(const Account&) = default;

	bool isCorrect(std::string password);

	friend std::ostream& operator<<(std::ostream& os, Account& acc);
	bool operator==(Account& acc);
};