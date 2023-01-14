#pragma once
#include <iostream>

class Account {
	//attributes
private:
	std::string username;
	std::string password;

	//methods
public:
	Account();
	Account(std::string, std::string);

	void setUsername(std::string);
	std::string getUsername();
	void setPassword(std::string);
	std::string getPassword();
};