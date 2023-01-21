#include "Account.h"
#include <string>
#include <fstream>
#include <filesystem>

static const char* AccSaveFilename = "Accounts.dat";

Account::Account(std::string username, std::string password) : username(username),
	password(password)
{
}

bool Account::findAccount(std::string username, std::string password)
{
	std::string _name, _password;
	size_t ndelim = 0;

	std::ifstream ifAccFile(AccSaveFilename, std::ifstream::in);

	while (std::getline(ifAccFile, _name))
	{
		ndelim = _name.find(';');
		_password = _name.substr(ndelim + 1, _name.length() - ndelim - 1);
		_name = _name.substr(0, ndelim);

		if (username == _name)
			if (password == _password)
				return true;
			else
				return false;
	}
	
	return false;
}

bool Account::findUser(std::string username)
{
	std::string _name, _password;
	size_t ndelim = 0;

	std::ifstream ifAccFile(AccSaveFilename, std::ifstream::in);

	while (std::getline(ifAccFile, _name))
	{
		ndelim = _name.find(';');
		_password = _name.substr(ndelim + 1, _name.length() - ndelim - 1);
		_name = _name.substr(0, ndelim);

		if (username == _name)
			return true;
	}

	return false;
}

void Account::saveAccount(Account& acc)
{
	std::filesystem::path fsPath = std::filesystem::current_path();
	fsPath += AccSaveFilename;

	bool isExisting;

	isExisting = std::filesystem::exists(fsPath) &&
		std::filesystem::is_regular_file(fsPath);

	std::ofstream ofAccFile(AccSaveFilename, std::ofstream::app);

	if (isExisting)
		ofAccFile.write("\n", 1);

	ofAccFile.write(acc.username.c_str(), acc.username.length());
	ofAccFile.write(";", 1);
	ofAccFile.write(acc.password.c_str(), acc.password.length());
}