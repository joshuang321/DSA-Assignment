//==================================================================
// Student Number : S10205140B, S10223630K
// Student Name :Joshua Ng, Armirola Roseller Iii Tumolva
// Module Group : P03
//==================================================================

#pragma once

#include <string>

/* The Account of the user */
class Account
{
	std::string password;

public:
	std::string username;

	/* Constructors */
	Account() { }
	Account(std::string strline);
	Account(const Account&);
	Account(Account&& acc);

	/* Constructors the Account using the username and password provided in registration */
	Account(std::string username, std::string password);

	/* Used to construct Account using data from line. See Topic and Post for more details. */
	Account& operator=(const Account&) = default;

	/* Returns true if the password matches the provided password, return false otherwise */
	bool isCorrect(std::string password);

	/* Used for writing to DataAccessor, see Topic and Post for more details */
	friend std::ostream& operator<<(std::ostream& os, Account& acc);

	/* Used for Vector for comparison, see Topic and Post for more details */
	bool operator==(Account& acc);
};