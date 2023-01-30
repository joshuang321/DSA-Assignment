#pragma once

#include <string>

class Account {
	//attributes
private:
	std::string username;
	std::string password;
		
public:
	Account(std::string username, std::string password);
	Account() { }
	Account(std::string strline);
	Account(const Account&) = default;
	Account& operator=(const Account&) = default;
	Account(Account&& acc);

	std::string getUsername();
	bool isCorrect(std::string password);

	friend std::ostream& operator<<(std::ostream& os, Account& acc);
	bool operator==(Account& acc);
};