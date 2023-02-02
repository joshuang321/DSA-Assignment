#pragma once
#include <iostream>
#include <ctime>
#include "Account.h"

//
class Post {
	//attributes
private:
	std::string text;
	time_t timeCreated;
	std::string username;
	int likes;

public:
	std::string reply;

	Post();
	Post(const Post& post);
	Post& operator=(const Post & post) = default;
	Post(Post&& post);
	
	Post(std::string text, std::string username);
	Post(std::string strline);


	std::string getText();
	std::string getTimeCreated();
	std::string getUsername();
	int getLikes();
	void addLike();

	friend std::ostream & operator << (std::ostream & os, Post & post);
	bool operator==(Post& acc);
};