#include "Account.h"

Account::Account() {}
Account::Account(std::string un, std::string pwd) : username(un), password(pwd) {}

//functions for methods
void Account::setUsername(std::string un) { username = un; }
std::string Account::getUsername() { return username; }

void Account::setPassword(std::string pwd) { password = pwd; }
std::string Account::getPassword() { return password; }