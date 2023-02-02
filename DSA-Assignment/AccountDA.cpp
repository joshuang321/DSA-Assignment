#pragma once
#include "AccountDA.h"

static const char* AccSaveFilename = "Accounts.txt";

AccountDA::AccountDA() : DataAccessor<Account>(AccSaveFilename)
{ }

bool AccountDA::findUser(Account*& pAcc, std::string username, std::string password)
{
	for (int i = 0; i < cacheData.count(); i++)
	{
		if (username == cacheData[i].getUsername() &&
			cacheData[i].isCorrect(password))
		{
			pAcc = &cacheData[i];
			return true;
		}
	}
	return false;
}

bool AccountDA::findUser(std::string username)
{
	for (int i = 0; i < cacheData.count(); i++)
	{
		if (username == cacheData[i].getUsername())
			return true;
	}
	return false;
}