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

/* Application constructor to read configuration (filter sort settings for topic) */
Application::Application() : isLoggedIn(false), acc(NULL)
{
	std::string strline;
	std::ifstream ifConfigFile("AccountConfig.txt", std::ifstream::in);

	std::getline(ifConfigFile, strline);
	sortState = atoi(strline.c_str());
}

/* Application de-constructor to write configuration into a text file */
Application::~Application()
{
	std::ofstream ofConfigFile("AccountConfig.txt");

	ofConfigFile << sortState;
}

/* Function to handle the start-up of the application */
int Application::Run()
{
	cout << clrsr;
	int choice = 0;

	while (true)
	{
		//checks if user is logged in and displays the menu accordingly
		if (isLoggedIn)
			printMainMenu();
		else
			printLoginMenu();

		//prompt for user input to log out or see topics
		cin >> choice;
		
		if (isLoggedIn)
			handleMainMenu(choice);
		else
			if (!handleLoginMenu(choice))
				break;
	}
	return 0;
}

/* Function that displays the login menu */
void Application::printLoginMenu()
{
	cout << fggreen << "==========" << fgblue << "LOGIN MENU" << fggreen << "==========" << grdefault << std::endl
		<< "[" << fgred << "1" << grdefault << "] Exit" << std::endl
		<< "[2] Register" << std::endl
		<< "[3] Login" << std::endl
		<< fgmagenta << "Your choice? " << grdefault;
}

/* Function that displays the main menu if the user is logged in */
void Application::printMainMenu()
{
	cout << fgyellow << "Logged in as " << acc->username << grdefault << endl;

	cout << R"(_________________________________________________________
_________________________________________________________
________/\\\\\\\\\_______________________________________  
______/\\\////////_______/\\\__________/\\\______________
______/\\\/______________\/\\\_________\/\\\_____________
______/\\\_____________/\\\\\\\\\\\__/\\\\\\\\\\\________ 
______\/\\\____________\///////////__\///////////________    
_______\//\\\_______________\/\\\_________\/\\\__________
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

/* Function to handle the login menu when user is not logged in */
bool Application::handleLoginMenu(int choice)
{
	switch (choice)
	{
		//if user chooses to close the application (close with this function to save new changes)
	case 1: 
		cout << clrsr << fgmagenta << "Goodbye!" << grdefault << endl;
		return false;

		//if user chooses to create an account
	case 2: 
		isLoggedIn = promptForRegisterUser();
		break;

		//if user chooses to login to existing account
	case 3: 
		isLoggedIn = promptForLoginUser();
		break;

		//if user does not choose a valid option
	default: 
		cout << fgred << "Invalid Option!" << grdefault << endl;
		Sleep(SLP_UI_DELAY);
		cout << clrsr;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	return true;
}

/* Function to handle main menu when user is logged in */
void Application::handleMainMenu(int choice)
{
	switch (choice)
	{
		//if user chooses to log out
	case 1:
		isLoggedIn = false;
		cout << clrsr;
		break;
	
		//if user chooses to view all topics in the forum
	case 2:
		handleViewTopics();
		break;

		//if user chooses to change password
	case 3:
		handleChangePassword();
		break;

		//if user does not choose a valid option
	default:
		cout << fgred << "Invalid Option!" << grdefault << endl;
		Sleep(SLP_UI_DELAY);
		cout << clrsr;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}

/* Function that prompts user for log in to existing account */
bool Application::promptForLoginUser()
{
	cout << clrsr;
	string username, password;

	//prompt user for username and password
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Username: ";
	getline(cin, username);
	cout << "Password: ";
	getline(cin, password);

	//check if the user exists in the Account data file
	if (accDA.findUser(acc, username, password))
	{
		//display log in success
		cout << clrsr << fggreen << "Logged In Successfully!" << endl;
		Sleep(SLP_UI_DELAY);
		cout << clrsr;
		return true;
	}

	//display log in failure
	cout << clrsr << fgred << "Failed to Log In!" << endl;
	Sleep(SLP_UI_DELAY);
	cout << clrsr;
	return false;
}

/* Function that prompts user to register a new account */
bool Application::promptForRegisterUser()
{
	cout << clrsr;
	string username, password;

	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	//prompt user for new username and password
	while (true)
	{
		cout << "Username: ";
		getline(cin, username);

		if (username.length() > 0)
			break;

		//check if username input is empty
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

		//check if password input is empty
		cout << fgred << "Password cannot be empty!" << grdefault;
		Sleep(SLP_UI_DELAY);
		cout << delline << set_prev_n_line_vts(1) << delline;
	}

	//check if there is existing account with username input
	if (!accDA.findUser(username))
	{
		acc = accDA.addObject(Account(username, password));

		//display account register success
		cout << clrsr << fggreen << "Account Registered Successfully!" << endl;
		Sleep(SLP_UI_DELAY);
		cout << clrsr;
		return true;
	}
	
	//display account register failure
	cout << clrsr << fgred << "There exists an account with the same username! Please try again!" << endl;
	Sleep(SLP_UI_DELAY + 200);
	cout << clrsr;

	return false;
}

/* Function to handle changing of password for the account logged in */
bool Application::handleChangePassword()
{
	cout << clrsr;
	string oldPassword, newPassword;

	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
	//prompt user for old password
	cout << "Enter old password: ";
	getline(cin, oldPassword);

	//checks if the input matches the old password
	bool oldMatch = acc->isCorrect(oldPassword);

	if (oldMatch)
	{
		while (true)
		{
			cout << "Enter new password: ";
			getline(cin, newPassword);

			if (newPassword.length() > 0)
				break;

			//check if password input is empty
			cout << fgred << "Password cannot be empty!" << grdefault;
			Sleep(SLP_UI_DELAY);
			cout << delline << set_prev_n_line_vts(1) << delline;
		}

		//replaces the account with the new password
		std::string accname = acc->username;
		accDA.removeObject(*acc);
		acc = accDA.addObject(Account(accname, newPassword));

		//display password change success
		cout << clrsr << fggreen << "Password changed successfully!" << endl;
		Sleep(SLP_UI_DELAY);
		cout << clrsr;
		return true;
	}
	else
	{
		//display password change failure
		cout << clrsr << fgred << "Old password does not match!" << endl;
		Sleep(SLP_UI_DELAY);
		cout << clrsr;
		return false;
	}
}

/* Function to handle viewing of topics if user chooses the option */
void Application::handleViewTopics()
{
	std::string choice;
	cout << clrsr;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	while (true)
	{
		Vector<string> topicNames = topicDA.getTopics();
		printViewTopicsMenu(topicNames);

		getline(cin, choice);
		if (!handleViewTopicsMenu(topicNames, choice))
			break;
	}
}

/* Function that displays topics */
void Application::printViewTopicsMenu(Vector<string>& topicNames)
{
	cout << "[" << fgred << "E" << grdefault << "] Go Back to Main Menu" << endl
		<< "[" << fggreen << "C" << grdefault << "] Create a new Topic" << endl 
		<< "[" << fgblue; 

	//check if the topic sorting state is saved to sort by latest to earliest
	if (sortState == 1)
		cout << grunderline;
	
	cout << "T" << grdefault << "] Sort Topics by Time" << endl
		<< "[" << fgblue;
	
	//check if the topic sorting state is saved to sort by alphabetical order
	if (sortState == 2)
		cout << grunderline;

	cout << "A" << grdefault << "] Sort Topics by Alphabet" << endl << endl
		<< fgmagenta << "Your Choice? " << grdefault << save;

	cout << go_down_vts(3) << set_x_pos_vts(0)
		<< fgcyan << "Topics:" << grdefault << endl;

	//iterates through the topicNames list to display existing topics
	for (int i = 0; i < topicNames.count(); i++)
	{
		cout << fgyellow << '[' << i + 1 << "] " << grunderline << topicNames[i] << grdefault << endl;
	}

	cout << restore;
}

/* Function to handle topic menu and direct to user's choice */
bool Application::handleViewTopicsMenu(Vector<string>& topicNames, string choice)
{
	int nIndex;

	//if user chooses to exit topic menu
	if (choice == "E")
	{
		cout << clrsr;
		return false;
	}
	//if user chooses to create a new topic
	if (choice == "C")
		promptNewTopic(topicNames);
	//if user chooses to sort the topic list by latest to earliest
	else if (choice == "T")
	{
		sortState = 1;
		topicDA.sortByLatest();
	}
	//if user chooses to sort the topic list by alphabetical order
	else if (choice == "A")
	{
		sortState = 2;
		topicDA.sortByAlphabet();
	}
	else
	{
		//if user chooses to view a topic (inputs the topic number)
		nIndex = atoi(choice.c_str());
		if (nIndex && topicNames.count() >= nIndex)
			handleViewTopic(nIndex-1);
		//if user inputs invalid option
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

/* Function to handle the creation of a new topic */
void Application::promptNewTopic(Vector<string>& topicNames)
{
	std::string topictitle, topicdesc;
	
	//prompt user to enter topic details
	cout << clrsr << "Topic Title: ";
	getline(cin, topictitle);
	cout << "Topic Description: ";
	getline(cin, topicdesc);

	//check if topic title already exists
	if (!topicDA.findTopic(topictitle))
	{
		topicNames.push(topicDA.addObject(Topic(topictitle, topicdesc, acc->username))->getTitle());
	}
	else
	{
		cout << fgred << "Failed to create an already existing Topic!" << grdefault;
		Sleep(SLP_UI_DELAY);
	}
}

/* Function to handle viewing the topic selected */
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

/* Function to display the menu of the topic selected */
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

	//iterates through the post list under the topic and displays their individual information
	for (int i = 0; i < topic.posts.count(); i++)
	{
		cout << endl << fgyellow << '[' << i + 1 << "] " << grunderline << topic.posts[i].getTitle() <<  grdefault << endl
			<< "Posted by " << topic.posts[i].getUsername() << endl
			<< "Posted at " << topic.posts[i].getTimeCreated() << endl
			<< topic.posts[i].getLikes() << " Likes" << endl;
	}

	cout << restore;
}

/* Function to handle the menu of the selected topic and direct to user's choice */
bool Application::handleViewTopicMenu(Topic& topic, string choice)
{
	int nIndex;

	//if user chooses to return back to the topics menu
	if ("E" == choice)
		return false;
	//if user chooses to like the topic
	else if ("L" == choice)
	{
		topic.addLike();

		cout << clrsr;
	}
	//if user chooses to create a new post under the topic
	else if ("R" == choice)
		promptNewPost(topic);
	else
	{
		//if user chooses to view a specific post under the topic
		nIndex = atoi(choice.c_str());
		if (nIndex && topic.posts.count() >= nIndex)
			handleViewPost(topic, topic.posts[nIndex - 1], topic.getUsername());
		//if user chooses an invalid option
		else
		{
			cout << fgred << "Invalid Input! Please try again!" << grdefault;
			Sleep(SLP_UI_DELAY);
			cout << restore << clrsr;
		}
	}

	return true;
}

/* Function to handle the creation of a post under the topic */
void Application::promptNewPost(Topic& topic)
{
	std::string postText;

	//prompts user to enter post text
	cout << clrsr << "Enter text: ";
	getline(cin, postText);
	cout << clrsr;

	topic.posts.push(Post(postText, acc->username));
}

/* Function to handle viewing the post selected under the topic */
void Application::handleViewPost(Topic& topic, Post& post, std::string username)
{
	std::string choice;
	cout << clrsr;

	while (true) 
	{
		printViewPostMenu(post);

		getline(cin, choice);
		if (!handleViewPostMenu(topic, post, username, choice))
			break;
	}

	cout << clrsr;
}

/* Function to display the menu of the post under the topic */
void Application::printViewPostMenu(Post& post)
{
	cout << "[" << fgred << "E" << grdefault << "] Go Back to Main Menu" << endl
		<< "[" << fgblue << "L" << grdefault << "] Like Post" << endl
		<< "[" << fggreen << "R" << grdefault << "] Create a new Reply" << endl;

	//functions (edit & delete post) appear only if the post belongs to user's account
	if (post.getUsername() == acc->username)
	{
		cout << "[" << fggreen << "P" << grdefault << "] Edit Post" << endl;
		cout << "[" << fggreen << "D" << grdefault << "] Delete Post" << endl;
	}

	cout << endl << fgyellow << grunderline << post.getTitle() << grdefault <<  endl
		<< "Posted at: " << post.getTimeCreated() << endl
		<< "Posted by: " << post.getUsername() << endl
		<< post.getLikes() << " Likes" << endl << endl
		<< fgmagenta << "Your Choice? " << grdefault << save;

	cout << go_down_vts(3) << set_x_pos_vts(0)
		<< fgcyan << "Replies:" << grdefault << endl;
		
	//iteratest through list of replies under the post and displays their information
	for (int i = 0; i < post.reply.count(); i++)
	{
		cout << endl << fgyellow << '[' << i + 1 << "] " << grunderline << post.reply[i].getTitle() << grdefault << endl
			<< "Posted by " << post.reply[i].getUsername() << endl
			<< "Posted at " << post.reply[i].getTimeCreated() << endl
			<< post.reply[i].getLikes() << " Likes" << endl;
	}

	cout << restore;
}

/* Function to handle the menu of the selected post and direct to user's choice */
bool Application::handleViewPostMenu(Topic& topic, Post& post, std::string username, std::string choice)
{
	//if user chooses to go back to topic menu
	if ("E" == choice)
		return false;
	//if user chooses to like the post
	else if ("L" == choice)
	{
		post.addLike();
		
		cout << clrsr;
	}
	//if user chooses to reply to the post
	else if ("R" == choice)
		promptNewReply(post);
	//if user chooses to edit the post (available if the post belongs to user's account)
	else if (("P" == choice) && (post.getUsername() == username))
		handleEditPost(topic, post);
	//if user chooses to delete the post (available if the post belongs to user's account)
	else if (("D" == choice) && (post.getUsername() == username))
	{
		handleDeletePost(topic, post);

		return false;
	}
	//if user chooses an invalid choice
	else
	{
		cout << fgred << "Invalid Input! Please try again!" << grdefault;
		Sleep(SLP_UI_DELAY);
		cout << restore << clrsr;
	}

	return true;
}

/* Function to handle creation of new reply under the post */
void Application::promptNewReply(Post& post)
{
	std::string postreply;

	//prompts user to enter their reply
	cout << "Enter reply: ";
	getline(cin, postreply);

	post.reply.push(Comment(postreply, acc->username));

	cout << clrsr;
}

/* Function to handle editing the post (available if the post belongs to user's account) */
bool Application::handleEditPost(Topic& topic, Post& post)
{
	string newText;
	string username = post.getUsername();

	//prompts user to enter new post text
	cout << "Enter new post text: ";
	getline(cin, newText);

	//check if post text is empty
	if (newText.length() == 0)
	{
		cout << fgred << "Text cannot be empty!" << grdefault;
		Sleep(SLP_UI_DELAY);
		cout << delline << set_prev_n_line_vts(1) << delline;

		return false;
	}

	//replaces the instance of post
	topic.posts.pop(post);
	topic.posts.push(Post(newText, username));
	
	cout << clrsr;
	return true;
}

/* Function to handle deletion of post (available if the post belongs to user's account) */
bool Application::handleDeletePost(Topic& topic, Post& post)
{
	topic.posts.pop(post);

	return true;
}