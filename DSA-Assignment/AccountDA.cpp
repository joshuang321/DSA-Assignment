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