#pragma once
#include "Account.h"
#include "Vector.h"
#include "Topic.h"
#include "Stack.h"

#include <string>


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

	void handleViewTopics();
	void printViewTopicsMenu(Vector<std::string>& topicNames);
	bool handleViewTopicsMenu(Vector<std::string>& topicNames, std::string choice);
	void promptNewTopic(Vector<std::string>& topicNames);

	void handleViewTopic(std::string topicName);
	void printViewTopicMenu(Topic& topic);
	bool handleViewTopicMenu(Topic& topic, std::string choice);
};

