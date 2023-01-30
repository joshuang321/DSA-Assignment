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
	int likes;
	Vector<Post> posts;

public:
	Topic();
	Topic(const Topic& topic);
	Topic(std::string title, std::string description, std::string username);
	Topic(std::string strline);



	void addNewPost(Post& newPost);

	std::string getTitle();
	std::string getDescription();
	std::string getUsername();
	std::string getTimeCreated();
	int getLikes();

	friend std::ostream& operator<<(std::ostream& os, Topic& topic);
};