#pragma once
#include "Account.h"
#include "Vector.h"
#include "Topic.h"

#include "AccountDA.h"
#include "TopicDA.h"

#include <string>


class Application
{
private:
	Account* acc;
	bool isLoggedIn;

	AccountDA accDA;
	TopicDA topicDA;

	int sortState;

public:
	Application();
	~Application();

	int Run();

	void printLoginMenu();
	void printMainMenu();

	bool handleLoginMenu(int choice);
	void handleMainMenu(int choice);

	bool promptForLoginUser();
	bool promptForRegisterUser();
	bool handleChangePassword();

	void handleViewTopics();
	void printViewTopicsMenu(Vector<std::string>& topicNames);
	bool handleViewTopicsMenu(Vector<std::string>& topicNames, std::string choice);
	void promptNewTopic(Vector<std::string>& topicNames);

	void handleViewTopic(int nIndex);
	//displays topics and posts
	void printViewTopicMenu(Topic& topic);
	bool handleViewTopicMenu(Topic& topic, std::string choice);
	void promptNewPost(Topic& topic);

	void handleViewPost(Topic& topic, Post& post, std::string username);
	void printViewPostMenu(Post& post);
	bool handleViewPostMenu(Topic& topic, Post& post, std::string username, std::string choice);
	void promptNewReply(Post& post);
	bool handleEditPost(Topic& topic, Post& post);
	bool handleDeletePost(Topic& topic, Post& post);
};

