//==================================================================
// Student Number : S10205140B, S10223630K
// Student Name :Joshua Ng, Armirola Roseller Iii Tumolva
// Module Group : P03
//==================================================================

#pragma once
#include <string>

/* Class Used to reply to posts and subclass in Post and Topic as common traits */
class Comment
{
private:
	std::string title;
	time_t timeCreated;
	std::string username;
	int likes;

public:
	/* Constructors */
	Comment();
	Comment(const Comment& comment);
	Comment& operator=(const Comment& comment) = default;
	Comment(Comment&& comment);
	Comment& operator=(Comment&&) = default;

	Comment(std::string title, std::string username);
	Comment(std::string strline);

	/* Getters for fields */
	std::string getTitle();
	/* Gets the string form of timeCreated */
	std::string getTimeCreated();
	std::string getUsername();
	int getLikes();
	void addLike();

	/* Used to compare the time, return true if it is latter, false otherwise */
	bool isLaterThan(Comment& comment);

	/* Insertion into DataAccessor, see Topic and Post for more details */
	friend std::ostream& operator << (std::ostream& os, Comment& comment);
	
	/* Comparison for subclasses, see Topic and Post for more detials */
	bool operator==(Comment& comment);
};