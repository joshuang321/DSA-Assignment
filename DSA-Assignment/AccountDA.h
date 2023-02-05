//==================================================================
// Student Number : S10205140B, S10223630K
// Student Name :Joshua Ng, Armirola Roseller Iii Tumolva
// Module Group : P03
//==================================================================

#pragma once

#include "DataAccessor.h"
#include "Account.h"
#include "AccountMapAdapter.h"

/* Used to read and write data for Accounts and data access for external purposes */
class AccountDA : public DataAccessor<Account, AccountMapAdapter>
{	
public:
	/* Constructor */
	AccountDA();

	/* Returns true is the account with the username and password exists, false otherwise */
	bool findUser(Account*& pAcc, std::string username, std::string password);

	/* Returns true is the account with the username */
	bool findUser(std::string username);
};