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

/* Topics of the discussion forum */
class Topic : public Comment
{
	//attributes
private:
	std::string description;

public:
	/* Used to store posts associated with the topic */
	Vector<Post> posts;

	/* Constructors, destructor handled by member objects */
	Topic();
	Topic(const Topic& topic);
	Topic& operator=(const Topic& topic) = default;
	Topic(Topic&& topic);

	/* Creates a topic with a title and description by a user with a username */
	Topic(std::string title, std::string description, std::string username);
	
	/* Used by DataAccessor to construct the topic using data from the data file */
	Topic(std::string strline);
	
	/* gets the description of the topic */
	std::string getDescription();
	
	/* Used by DataAccessor to write to the data file */
	friend std::ostream& operator<<(std::ostream& os, Topic& topic);
	
	/* Used in Vector to search for the Topic object */
	bool operator==(Topic& acc);
};
