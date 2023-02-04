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
static const char* delline = "\x1B[2K";

/* Resets the text to default rendering */
static const char* grdefault = "\x1B[0m";
static const char* grunderline = "\x1B[4m";

/* Sets the foreground color */
static const char* fgred = "\x1B[91m";
static const char* fggreen = "\x1B[92m";
static const char* fgyellow = "\x1B[93m";
static const char* fgblue = "\x1B[94m";
static const char* fgmagenta = "\x1B[95m";
static const char* fgcyan = "\x1B[96m";

static const int SLP_UI_DELAY = 700;

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

static std::string set_prev_n_line_vts(int nLine)
{
	return "\x1b[" + std::to_string(nLine) + "F";
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
		<< "[" << fgred << "1" << grdefault << "] Exit" << std::endl
		<< "[2] Register" << std::endl
		<< "[3] Login" << std::endl
		<< fgmagenta << "Your choice? " << grdefault;
}

//function to print the main menu (logged in)
void Application::printMainMenu()
{
	cout << fgyellow << "Logged in as " << acc->getUsername() << grdefault << endl;

	cout << R"(_________________________________________________________
_________________________________________________________
________/\\\\\\\\\_______________________________________  
______/\\\////////_______/\\\__________/\\\______________
______/\\\/______________\/\\\_________\/\\\_____________
______/\\\_____________/\\\\\\\\\\\__/\\\\\\\\\\\________ 
______\/\\\____________\///////////__\///////////________    
_______\//\\\________________\/\\\_________\/\\\_________
________\///\\\______________\///__________\///__________
___________\////\\\\\\\\\________________________________
_______________\/////////________________________________
_________________________________________________________
)" << endl;

	cout << fggreen << "==========" << fgblue << "Weclome to the C++ Programming Forum!" << fggreen << "=========="
		<< grdefault << std::endl
		<< "[" << fgred << "1" << grdefault << "] Log Out" << std::endl
		<< "[2] See Topics" << std::endl
		<< "[3] Change Password" << std::endl
		<< fgmagenta << "Your choice? " << grdefault;
}

bool Application::handleLoginMenu(int choice)
{
	switch (choice)
	{
	case 1:
		cout << fgmagenta << "Goodbye!" << grdefault << endl;
		return false;

	case 2:
		isLoggedIn = promptForRegisterUser();
		break;

	case 3:
		isLoggedIn = promptForLoginUser();
		break;

	default:
		cout << fgred << "Invalid Option!" << grdefault << endl;
		Sleep(SLP_UI_DELAY);
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
		Sleep(SLP_UI_DELAY);
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
		Sleep(SLP_UI_DELAY);
		cout << clrsr;
		return true;
	}

	cout << clrsr << fgred << "Failed to Log In!" << endl;
	Sleep(SLP_UI_DELAY);
	cout << clrsr;
	return false;
}

bool Application::promptForRegisterUser()
{
	string username, password;

	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	//prompt user for new username and password
	while (true)
	{
		cout << "Username: ";
		getline(cin, username);
		if (username.length() > 0)
			break;
		cout << fgred << "Username cannot be empty!" << grdefault;
		Sleep(SLP_UI_DELAY);
		cout << delline << set_prev_n_line_vts(1) << delline;
	}
	while (true)
	{
		cout << "Password: ";
		getline(cin, password);
		if (password.length() > 0)
			break;
		cout << fgred << "Password cannot be empty!" << grdefault;
		Sleep(SLP_UI_DELAY);
		cout << delline << set_prev_n_line_vts(1) << delline;
	}

	//check if there is existing account with username input
	if (!accDA.findUser(username))
	{
		acc = accDA.addObject(Account(username, password));

		cout << clrsr << fggreen << "Account Registered Successfully!" << endl;
		Sleep(SLP_UI_DELAY);
		cout << clrsr;
		return true;
	}
	
	cout << clrsr << fgred << "There exists an account with the same username! Please try again!" << endl;
	Sleep(SLP_UI_DELAY + 200);
	cout << clrsr;

	return false;
}

bool Application::handleChangePassword()
{
	string oldPassword, newPassword;

	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
	//prompt user for old password
	cout << "Enter old password: ";
	getline(cin, oldPassword);

	bool oldMatch = acc->isCorrect(oldPassword);

	if (oldMatch)
	{
		while (true)
		{
			cout << "Enter new password: ";
			getline(cin, newPassword);

			if (newPassword.length() > 0)
				break;

			cout << fgred << "Password cannot be empty!" << grdefault;
			Sleep(SLP_UI_DELAY);
			cout << delline << set_prev_n_line_vts(1) << delline;
		}

		std::string accname = acc->getUsername();
		acc->changePassword(newPassword);

		cout << clrsr << fggreen << "Password changed successfully!" << endl;
		Sleep(SLP_UI_DELAY);
		cout << clrsr;
		return true;
	}
	else
	{
		cout << clrsr << fgred << "Old password does not match!" << endl;
		Sleep(SLP_UI_DELAY);
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
		<< "[" << fggreen << "C" << grdefault << "] Create a new Topic" << endl 
		<< "[" << fgblue << "T" << grdefault << "] Sort Topics by Time" << endl
		<< "[" << fgblue << "A" << grdefault << "] Sort Topics by Alphabet" << endl << endl
		<< fgmagenta << "Your Choice? " << grdefault << save;

	cout << go_down_vts(3) << set_x_pos_vts(0)
		<< fgcyan << "Topics:" << grdefault << endl;

	for (int i = 0; i < topicNames.count(); i++)
	{
		cout << fgyellow << '[' << i + 1 << "] " << grunderline << topicNames[i] << grdefault << endl;
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
	else if (choice == "T")
	{
		topicDA.sortByLatest();
		topicNames = topicDA.getTopics();
	}
	else if (choice == "A")
	{
		topicDA.sortByAlphabet();
		topicNames = topicDA.getTopics();
	}
	else
	{
		nIndex = atoi(choice.c_str());
		if (nIndex && topicNames.count() >= nIndex)
			handleViewTopic(nIndex-1);
		else
		{
			cout << fgred << "Invalid Input! Please try again!" << grdefault;
			Sleep(SLP_UI_DELAY);
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
		topicDA.addObject(Topic(topictitle, topicdesc, acc->getUsername()));
		topicNames.push(topictitle);
	}
	else
	{
		cout << fgred << "Failed to create an already existing Topic!" << grdefault;
		Sleep(SLP_UI_DELAY);
	}
}

void Application::handleViewTopic(int nIndex)
{
	string choice;
	cout << clrsr;
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
	cout << "[" << fgred << "E" << grdefault << "] Go back to other Topics" << endl
		<< "[" << fgblue << "L" << grdefault << "] Like Topic" << endl
		<< "[" << fggreen << "R" << grdefault << "] Create a new Post" << endl << endl
		<< endl << grunderline << fgyellow << topic.getTitle() << grdefault << endl
		<< "Created by: " << topic.getUsername() << endl
		<< "Created at: " << topic.getTimeCreated() << endl
		<< topic.getLikes() << " Likes" << endl
		<< grunderline << "                                        " << grdefault << endl
		<< fgyellow << topic.getDescription() << grdefault << endl << endl
		<< fgmagenta << "Your choice? " << grdefault << save;

	cout << go_down_vts(3) << set_x_pos_vts(0)
		<< fgcyan << "Posts:" << grdefault;

	for (int i = 0; i < topic.posts.count(); i++)
	{
		cout << endl << fgyellow << '[' << i + 1 << "] " << grunderline << topic.posts[i].getTitle() <<  grdefault << endl
			<< "Posted by " << topic.posts[i].getUsername() << endl
			<< "Posted at " << topic.posts[i].getTimeCreated() << endl
			<< topic.posts[i].getLikes() << " Likes" << endl << endl;
	}

	cout << restore;
}

bool Application::handleViewTopicMenu(Topic& topic, string choice)
{
	int nIndex;

	if ("E" == choice)
		return false;
	else if ("L" == choice)
	{
		topic.addLike();

		cout << clrsr;
	}
	else if ("R" == choice)
		promptNewPost(topic);
	else
	{
		nIndex = atoi(choice.c_str());
		if (nIndex && topic.posts.count() >= nIndex)
			handleViewPost(topic.posts[nIndex - 1], topic.getUsername());
		else
		{
			cout << fgred << "Invalid Input! Please try again!" << grdefault;
			Sleep(SLP_UI_DELAY);
			cout << restore;
		}
	}

	return true;
}

void Application::promptNewPost(Topic& topic)
{
	std::string postText;

	cout << clrsr << "Enter text: ";
	getline(cin, postText);
	cout << clrsr;

	topic.addNewPost(Post(postText, acc->getUsername()));
}

void Application::handleViewPost(Post& post, std::string username)
{
	std::string choice;
	cout << clrsr;

	while (true) 
	{
		printViewPostMenu(post);

		getline(cin, choice);
		if (!handleViewPostMenu(post, username, choice))
			break;
	}

	cout << clrsr;
}

void Application::printViewPostMenu(Post& post)
{
	cout << "[" << fgred << "E" << grdefault << "] Go Back to Main Menu" << endl
		<< "[" << fgblue << "L" << grdefault << "] Like Post" << endl
		<< "[" << fggreen << "R" << grdefault << "] Create a new Reply" << endl << endl
		<< fgyellow << grunderline << post.getTitle() << grdefault <<  endl
		<< "Posted at: " << post.getTimeCreated() << endl
		<< "Posted by: " << post.getUsername() << endl
		<< post.getLikes() << " Likes" << endl << endl
		<< fgmagenta << "Your Choice? " << grdefault << save;

	cout << go_down_vts(3) << set_x_pos_vts(0)
		<< fgcyan << "Replies:" << grdefault << endl << post.reply;
	cout << restore;
}

bool Application::handleViewPostMenu(Post& post, std::string username, std::string choice)
{
	if ("E" == choice)
		return false;
	else if ("L" == choice)
	{
		post.addLike();

		cout << clrsr;
	}
	else if ("R" == choice)
		promptNewReply(post);

	return true;
}

void Application::promptNewReply(Post& post)
{
	std::string postreply;

	cout << "Enter reply: ";
	getline(cin, postreply);

	post.reply = postreply;

	cout << clrsr;
}