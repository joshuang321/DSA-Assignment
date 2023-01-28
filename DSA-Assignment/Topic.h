#pragma once
#include <iostream>
#include <chrono>
#include <ctime>

#include "Vector.h"
#include "Post.h"

class Topic {
	//attributes
private:
	std::string title;
	std::string description;
	std::string username;
	std::time_t timeCreated;
	Vector<Post> posts;

	Topic(std::string title, std::string description, std::string username, std::time_t timeCreated);

	//methods
public:
	Topic();
	Topic(std::string title, std::string description, std::string username);

	void addNewPost(Post& newPost);

	static bool findTopic(std::string topicName);
	static bool getTopic(std::string topicName, Topic &topic);
	static void saveTopic(Topic& topic);

	static Vector<std::string> getTopics();

	std::string getTitle();
	std::string getDescription();
	std::string getUsername();
	std::string getTimeCreated();
};