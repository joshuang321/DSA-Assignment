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
	cout << fggreen << "==========" << fgblue << "LOGIN MENU" << fggreen << "==========" << grdefault << std::endl
		<< "[1] Login" << std::endl
		<< "[2] Register" << std::endl
		<< "[3] Exit" << std::endl
		<< "Your choice? ";
}

void Application::printMainMenu()
{
	cout << fgyellow << "Logged in as " << acc.getUsername() << endl << endl
		<< fggreen << "==========" << fgblue << "Weclome to the C++ Programming Forum!" << fggreen << "=========="
		<< grdefault << std::endl
		<< "[1] Log Out" << std::endl
		<< "[2] See Topics" << std::endl
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
	case 1:
		isLoggedIn = false;
		break;
	
	case 2:
		handleViewTopics();
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

	if (Account::findAccount(username, password))
	{
		acc = Account(username, password);
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
	cout << "Username: ";
	getline(cin, username);
	cout << "Password: ";
	getline(cin, password);

	if (!Account::findUser(username))
	{
		acc = Account(username, password);
		Account::saveAccount(acc);

		cout << clrsr << "Account Registered Successfully!" << endl;
		return true;
	}
	
	cout << clrsr << fgred << "There exists an account with the same username! Please try again!" << endl;
	Sleep(SLP_UI_DEPLAY + 200);
	cout << clrsr;

	return false;
}

void Application::handleViewTopics()
{
	std::string choice;
	cout << clrsr;
	Vector<string> topicNames = Topic::getTopics();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	while (true)
	{
		printViewTopicsMenu(topicNames);

		getline(cin, choice);
		if (!handleViewTopicsMenu(topicNames, choice))
			break;
	}
}

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
bool Application::handleViewTopicsMenu(Vector<string>&  topicNames, string choice)
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
			handleViewTopic(topicNames[nIndex - 1]);
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

	if (!Topic::findTopic(topictitle))
	{
		Topic topic(topictitle, topicdesc, acc.getUsername());
		Topic::saveTopic(topic);

		topicNames.push(topictitle);
	}
	else
	{
		cout << fgred << "Failed to create an already existing Topic!" << grdefault;
	}
}

void Application::handleViewTopic(string topicName)
{
	string choice;
	Topic topic;
	if (Topic::getTopic(topicName, topic))
	{
		while (true)
		{
			printViewTopicMenu(topic);
			getline(cin, choice);
			if (!handleViewTopicMenu(topic, choice))
				break;
		}
	}
}

void Application::printViewTopicMenu(Topic& topic)
{
	cout << clrsr << "[" << fgred << "E" << grdefault << "] Go back to other Topics" << endl 
		<< endl << topic.getTitle() << endl
		<< "Created at " << topic.getTimeCreated() << endl
		<< "Created by " << topic.getUsername() << endl
		<< endl
		<< topic.getDescription() << endl << endl
		<< "Your choice? " << save;
}

bool Application::handleViewTopicMenu(Topic& topic, string choice)
{
	if ("E" == choice)
		return false;

	return true;
}