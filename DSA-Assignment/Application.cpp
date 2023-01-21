#include "Application.h"
#include "Account.h"

#include <iostream>
#include <string>

using namespace std;

static const char* clrsr = "\x1B[2J\x1B[H";

Application::Application() : isLoggedIn(false) { }

int Application::Run()
{
	int choice = 0;

	while (true)
	{
		if (isLoggedIn)
			printMainMenu();
		else
			printLoginMenu();

		cin >> choice;
		cout << clrsr;

		if (isLoggedIn)
			handleMainMenu(choice);
		else
			if (!handleLoginMenu(choice))
				break;
	}
	return 0;
}

void Application::printLoginMenu()
{
	cout << "==========Login Menu==========" << std::endl
		<< "[1] Login" << std::endl
		<< "[2] Register" << std::endl
		<< "[3] Exit" << std::endl
		<< "Your choice? ";
}

void Application::printMainMenu()
{
	cout << "==========Login Menu==========" << std::endl
		<< "[1] Log Out" << std::endl
		<< "Your choice? ";
}

bool Application::handleLoginMenu(int choice)
{
	switch (choice)
	{
	case 1:

		isLoggedIn = promptForLoginUser();
		break;

	case 2:
		isLoggedIn = promptForRegisterUser();
		break;

	case 3:
		cout << clrsr << "Goodbye!" << endl;
		return false;

	default:
		cout << "Invalid Option!" << endl;
	}

	return true;
}

void Application::handleMainMenu(int choice)
{
	switch (choice)
	{
	case 1:
		isLoggedIn = false;
		break;
	default:
		cout << "Invalid Option!" << endl;
	}
}

bool Application::promptForLoginUser()
{
	string username, password;

	cout << "Name: ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(std::cin, username);
	cout << "Password: ";
	getline(std::cin, password);

	if (Account::findAccount(username, password))
	{
		acc = Account(username, password);
		cout << clrsr << "Logged In Successfully!" << endl;
		return true;
	}

	cout << clrsr << "Failed to Log In!" << endl;
	return false;
}

bool Application::promptForRegisterUser()
{
	string username, password;

	cout << "Name: ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(std::cin, username);
	cout << "Password: ";
	getline(std::cin, password);

	if (!Account::findUser(username))
	{
		acc = Account(username, password);
		Account::saveAccount(acc);

		cout << clrsr << "Account Registered Successfully!" << endl;
		return true;
	}
}