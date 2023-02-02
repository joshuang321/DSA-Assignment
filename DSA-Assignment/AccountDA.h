#pragma once

#include "DataAccessor.h"
#include "Account.h"

class AccountDA : public DataAccessor<Account>
{	
public:
	AccountDA();
	bool findUser(Account*& pAcc, std::string username, std::string password);
	bool findUser(std::string username);
};