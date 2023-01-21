#pragma once
#include "Account.h"

class Application
{
private:

	Account acc;
	bool isLoggedIn;

public:
	Application();

	int Run();

	void printLoginMenu();
	void printMainMenu();

	bool handleLoginMenu(int choice);
	void handleMainMenu(int choice);

	bool promptForLoginUser();
	bool promptForRegisterUser();
};

