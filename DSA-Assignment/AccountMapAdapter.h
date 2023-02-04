#pragma once

#include <string>
#include "Account.h"
#include "Map.h"

class AccountMapAdapter : public Map<std::string&, Account>
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

	Account* push(Account acc) { return Map::push((std::string&) acc.getUsername(), acc); }

	void pop(Account& acc) { Map::pop((std::string&)acc.getUsername(), acc); }
};