#include <iostream>

#include "Application.h"
#include "Account.h"
#include "Topic.h"

#include <Windows.h>

#undef max
#undef min

using namespace std;

static const char* clrsr = "\x1B[2J\x1B[H";
static const char* save = "\x1B[s";
static const char* restore = "\x1B[u";

/* Resets the text to default rendering */
static const char* grdefault = "\x1B[0m";

/* Sets the foreground color */
static const char* fgred = "\x1B[91m";
static const char* fggreen = "\x1B[92m";
static const char* fgyellow = "\x1B[93m";
static const char* fgblue = "\x1B[94m";
static const char* fgmagenta = "\x1B[95m";
static const char* fgcyan = "\x1B[96m";

static const int SLP_UI_DEPLAY = 700;

/* Neat function that returns when printed goes up/down nAmount */
static std::string go_up_vts(int nAmount)
{
	return "\x1B[" + std::to_string(nAmount) + "A";
}

static std::string go_down_vts(int nAmount)
{
	return "\x1B[" + std::to_string(nAmount) + "B";
}

static std::string set_x_pos_vts(int nPosition)
{
	return "\x1B[" + std::to_string(nPosition) + "G";
}

Application::Application() : isLoggedIn(false) { }

int Application::Run()
{
	cout << clrsr;
	int choice = 0;

	while (true)
	{
		if (isLoggedIn)
			printMainMenu();
		else
			printLoginMenu();

		//prompt for user input to log out or see topics
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

//function to print the login menu
void Application::printLoginMenu()
{
	cout << fggreen << "==========" << fgblue << "LOGIN MENU" << fggreen << "==========" << grdefault << std::endl
		<< "[1] Login" << std::endl
		<< "[2] Register" << std::endl
		<< "[3] Exit" << std::endl
		<< "Your choice? ";
}

//function to print the main menu (logged in)
void Application::printMainMenu()
{
	cout << fgyellow << "Logged in as " << acc.getUsername() << endl << endl
		<< fggreen << "==========" << fgblue << "Weclome to the C++ Programming Forum!" << fggreen << "=========="
		<< grdefault << std::endl
		<< "[1] Log Out" << std::endl
		<< "[2] See Topics" << std::endl
		<< "[3] Change Password" << std::endl
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
		cout << fgmagenta << "Goodbye!" << grdefault << endl;
		return false;

	default:
		cout << fgred << "Invalid Option!" << grdefault << endl;
		Sleep(SLP_UI_DEPLAY);
		cout << clrsr;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	return true;
}

void Application::handleMainMenu(int choice)
{
	switch (choice)
	{
		//if user chooses to log out
	case 1:
		isLoggedIn = false;
		break;
	
		//if user chooses to view all topics in the forum
	case 2:
		handleViewTopics();
		break;

		//if user chooses to change password
	case 3:
		handleChangePassword();
		break;

	default:
		cout << fgred << "Invalid Option!" << grdefault << endl;
		Sleep(SLP_UI_DEPLAY);
		cout << clrsr;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}

bool Application::promptForLoginUser()
{
	string username, password;

	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Username: ";
	getline(cin, username);
	cout << "Password: ";
	getline(cin, password);

	if (accDA.findUser(acc, username, password))
	{
		cout << clrsr << fggreen << "Logged In Successfully!" << endl;
		Sleep(SLP_UI_DEPLAY);
		cout << clrsr;
		return true;
	}

	cout << clrsr << fgred << "Failed to Log In!" << endl;
	Sleep(SLP_UI_DEPLAY);
	cout << clrsr;
	return false;
}

bool Application::promptForRegisterUser()
{
	string username, password;

	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	//prompt user for new username and password
	cout << "Username: ";
	getline(cin, username);
	cout << "Password: ";
	getline(cin, password);

	//check if there is existing account with username input
	if (!accDA.findUser(username))
	{
		acc = Account(username, password);
		accDA.addObject(acc);

		cout << clrsr << fggreen << "Account Registered Successfully!" << endl;
		Sleep(SLP_UI_DEPLAY);
		cout << clrsr;
		return true;
	}
	
	cout << clrsr << fgred << "There exists an account with the same username! Please try again!" << endl;
	Sleep(SLP_UI_DEPLAY + 200);
	cout << clrsr;

	return false;
}

bool Application::handleChangePassword()
{
	string oldPassword, newPassword, checkPassword;

	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
	//prompt user for old password
	cout << "Enter old password: ";
	getline(cin, oldPassword);

	bool oldMatch = acc.isCorrect(oldPassword);

	if (oldMatch)
	{
		cout << "Enter new password: ";
		getline(cin, newPassword);

		cout << "Re-enter new password: ";
		getline(cin, checkPassword);

		if (newPassword == checkPassword)
		{
			accDA.removeObject(acc);
			acc = Account(acc.getUsername(), newPassword);
			accDA.addObject(acc);

			cout << clrsr << fggreen << "Password changed successfully!" << endl;
			Sleep(SLP_UI_DEPLAY);
			cout << clrsr;
			return true;
		}
		else
		{
			cout << clrsr << fgred << "New passwords do not match!" << endl;
			Sleep(SLP_UI_DEPLAY);
			cout << clrsr;
			return false;
		}
	}
	else
	{
		cout << clrsr << fgred << "Old password does not match!" << endl;
		Sleep(SLP_UI_DEPLAY);
		cout << clrsr;
		return false;
	}
}

void Application::handleViewTopics()
{
	std::string choice;
	cout << clrsr;
	Vector<string> topicNames = topicDA.getTopics();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	while (true)
	{
		printViewTopicsMenu(topicNames);

		getline(cin, choice);
		if (!handleViewTopicsMenu(topicNames, choice))
			break;
	}
}

//when you select option "2" in the main menu
void Application::printViewTopicsMenu(Vector<string>& topicNames)
{
	cout << "[" << fgred << "E" << grdefault << "] Go Back to Main Menu" << endl
		<< "[" << fggreen << "C" << grdefault << "] Create a new Topic" << endl << endl
		<< "Your Choice? " << save;

	cout << go_down_vts(3) << set_x_pos_vts(0);

	for (int i = 0;
		i < topicNames.count();
		i++)
	{
		cout << '[' << i + 1 << "] " << topicNames[i] << endl;
	}
	cout << restore;
}

bool Application::handleViewTopicsMenu(Vector<string>& topicNames, string choice)
{
	int nIndex;

	if (choice == "E")
	{
		cout << clrsr;
		return false;
	}
	if (choice == "C")
		promptNewTopic(topicNames);
	else
	{
		nIndex = atoi(choice.c_str());
		if (nIndex && topicNames.count() >= nIndex)
			handleViewTopic(nIndex-1);
		else
		{
			cout << fgred << "Invalid Input! Please try again!" << grdefault;
			Sleep(SLP_UI_DEPLAY);
			cout << restore;
		}
	}
	cout << clrsr;

	return true;
}

void Application::promptNewTopic(Vector<string>& topicNames)
{
	std::string topictitle, topicdesc;
	
	cout << clrsr << "Topic Title: ";
	getline(cin, topictitle);
	cout << "Topic Description: ";
	getline(cin, topicdesc);

	if (!topicDA.findTopic(topictitle))
	{
		topicDA.addObject(Topic(topictitle, topicdesc, acc.getUsername()));
		topicNames.push(topictitle);
	}
	else
	{
		cout << fgred << "Failed to create an already existing Topic!" << grdefault;
		Sleep(SLP_UI_DEPLAY);
	}
}

void Application::handleViewTopic(int nIndex)
{
	string choice;
	Topic& topic = topicDA.getTopic(nIndex);
	while (true)
	{
		printViewTopicMenu(topic);
		getline(cin, choice);
		if (!handleViewTopicMenu(topic, choice))
			break;
	}
}

void Application::printViewTopicMenu(Topic& topic)
{
	cout << clrsr << "[" << fgred << "E" << grdefault << "] Go back to other Topics" << endl 
		<< endl << topic.getTitle() << endl
		<< "Created at " << topic.getTimeCreated() << endl
		<< "Created by " << topic.getUsername() << endl
		<< topic.getLikes() << " Likes" << endl
		<< topic.getDescription() << endl << endl
		<< "Your choice? " << save;
}

bool Application::handleViewTopicMenu(Topic& topic, string choice)
{
	if ("E" == choice)
		return false;

	return true;
}