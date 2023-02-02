#pragma once

#include <string>

class Account {
	//attributes
private:
	std::string username;
	std::string password;
		
public:
	Account() { }
	Account(std::string strline);
	Account(const Account&);
	Account(Account&& acc);

	Account(std::string username, std::string password);
	Account& operator=(const Account&) = default;

	std::string getUsername();
	bool isCorrect(std::string password);

	friend std::ostream& operator<<(std::ostream& os, Account& acc);
	bool operator==(Account& acc);
};