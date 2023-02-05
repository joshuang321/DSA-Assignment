//==================================================================
// Student Number : S10205140B, S10223630K
// Student Name :Joshua Ng, Armirola Roseller Iii Tumolva
// Module Group : P03
//==================================================================

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
	Topic& operator=(const Topic& topic) = default;
	Topic(Topic&& topic);

	Topic(std::string title, std::string description, std::string username);
	Topic(std::string strline);

	std::string getDescription();

	friend std::ostream& operator<<(std::ostream& os, Topic& topic);
	bool operator==(Topic& acc);
};
