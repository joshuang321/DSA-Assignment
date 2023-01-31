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

public:
	Vector<Post> posts;

	Topic();
	Topic(const Topic& topic);
	Topic(std::string title, std::string description, std::string username);
	Topic(std::string strline);

	void addNewPost(Post newPost);

	std::string getTitle();
	std::string getDescription();
	std::string getUsername();
	std::string getTimeCreated();
	int getLikes();
	void addLike();

	friend std::ostream& operator<<(std::ostream& os, Topic& topic);
	bool operator==(Topic& acc);
};
