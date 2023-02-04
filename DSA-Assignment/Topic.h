#pragma once
#include <iostream>
#include <chrono>
#include <ctime>

#include "Vector.h"
#include "Post.h"
#include "Comment.h"

class Topic : public Comment
{
	//attributes
private:
	std::string description;

public:
	Vector<Post> posts;

	Topic();
	Topic(const Topic& topic);
	Topic& operator=(const Topic & topic) = default;
	Topic(Topic&& topic);

	Topic(std::string title, std::string description, std::string username);
	Topic(std::string strline);

	void addNewPost(Post newPost);
	std::string getDescription();

	friend std::ostream& operator<<(std::ostream& os, Topic& topic);
	bool operator==(Topic& acc);
};
