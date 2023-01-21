#pragma once
#include <iostream>

class Account {
	//attributes
private:
	std::string username;
	std::string password;
		
public:
	Account(std::string username, std::string password);
	Account() { }

	static bool findAccount(std::string username, std::string password);
	static bool findUser(std::string username);
	static void saveAccount(Account& acc);
};