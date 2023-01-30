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

	std::string getUsername();
	bool isCorrect(std::string password);

	friend std::ostream& operator<<(std::ostream& os, Account& acc);
};