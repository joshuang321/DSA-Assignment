//==================================================================
// Student Number : S10205140B, S10223630K
// Student Name :Joshua Ng, Armirola Roseller Iii Tumolva
// Module Group : P03
//==================================================================

#pragma once
#include "Account.h"
#include "Vector.h"
#include "Topic.h"

#include "AccountDA.h"
#include "TopicDA.h"

#include <string>


/* Main body of the application and exposes Run method to run the application */
class Application
{
private:
	Account* acc;
	bool isLoggedIn;

	AccountDA accDA;
	TopicDA topicDA;

	int sortState;

public:
	/* Constructor and Destructor */
	Application();
	~Application();

	/* Runs the program */
	int Run();

	/* Prints the login menu and main menu */
	void printLoginMenu();
	void printMainMenu();

	bool handleLoginMenu(int choice);
	void handleMainMenu(int choice);

	/* Prompts the user to log in to an Account */
	bool promptForLoginUser();
	
	/* Prompts the user to register an Account, checks for duplicates */
	bool promptForRegisterUser();

	/* Handle the changing of the password for the current account */
	bool handleChangePassword();

	/* Displays and handle the topics */
	void handleViewTopics();
	void printViewTopicsMenu(Vector<std::string>& topicNames);
	bool handleViewTopicsMenu(Vector<std::string>& topicNames, std::string choice);
	void promptNewTopic(Vector<std::string>& topicNames);

	void handleViewTopic(int nIndex);
	
	/* Displays and handles the topic details and posts of the topic */
	void printViewTopicMenu(Topic& topic);
	bool handleViewTopicMenu(Topic& topic, std::string choice);
	void promptNewPost(Topic& topic);

	/* Display and handle the post details and replies of the post */
	void handleViewPost(Topic& topic, Post& post, std::string username);
	void printViewPostMenu(Post& post);
	bool handleViewPostMenu(Topic& topic, Post& post, std::string username, std::string choice);
	void promptNewReply(Post& post);
	bool handleEditPost(Topic& topic, Post& post);
	bool handleDeletePost(Topic& topic, Post& post);
};

