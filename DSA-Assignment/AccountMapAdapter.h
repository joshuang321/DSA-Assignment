//==================================================================
// Student Number : S10205140B, S10223630K
// Student Name :Joshua Ng, Armirola Roseller Iii Tumolva
// Module Group : P03
//==================================================================

#pragma once

#include <string>
#include "Account.h"
#include "Map.h"

/* Used as an adapter to the Map to the DataAccessor */
class AccountMapAdapter : public Map<std::string, Account>
{
public:
	AccountMapAdapter() : 
		Map()
	{ }

	AccountMapAdapter(const AccountMapAdapter& adapter) :
		Map(adapter)
	{ }

	AccountMapAdapter& operator=(const AccountMapAdapter& adapter) = default;

	AccountMapAdapter(AccountMapAdapter&& adapter) :
		Map(std::move(adapter))
	{ }

	/* Uses the username of the Account object as key */
	Account* push(Account&& acc)
	{
		Node* pNode = Map::push(acc.username);
		pNode->value = acc;
		return &pNode->value;
	}

	/* Pops the Account object using the username as key */
	void pop(Account& acc) { Map::pop((std::string&)acc.username, acc); }
};