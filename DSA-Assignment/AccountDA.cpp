//==================================================================
// Student Number : S10205140B, S10223630K
// Student Name :Joshua Ng, Armirola Roseller Iii Tumolva
// Module Group : P03
//==================================================================

#pragma once
#include "AccountDA.h"

static const char* AccSaveFilename = "Accounts.txt";

AccountDA::AccountDA() : DataAccessor<Account, AccountMapAdapter>(AccSaveFilename)
{ }

bool AccountDA::findUser(Account*& pAcc, std::string username, std::string password)
{
	if (cacheData.get(username, pAcc))
	{
		return (pAcc->isCorrect(password));
	}
	return false;
}

/* Function that finds a user by username */
bool AccountDA::findUser(std::string username)
{
	return cacheData.exists(username);
}