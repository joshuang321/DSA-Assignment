#pragma once

#include "DataAccessor.h"
#include "Account.h"
#include "AccountMapAdapter.h"

class AccountDA : public DataAccessor<Account, AccountMapAdapter>
{	
public:
	AccountDA();
	bool findUser(Account*& pAcc, std::string username, std::string password);
	bool findUser(std::string username);
};