//==================================================================
// Student Number : S10205140B, S10223630K
// Student Name :Joshua Ng, Armirola Roseller Iii Tumolva
// Module Group : P03
//==================================================================

#pragma once
#include <iostream>
#include <ctime>
#include "Vector.h"
#include "Comment.h"


/* Post of a topic in a discussion forum */
class Post : public Comment
{
	//attributes
private:

public:
	Vector<Comment> reply;

	/* Constructors */
	Post();
	Post(const Post& post);
	Post& operator=(const Post & post) = default;
	Post(Post&& post);

	/* Construct a post using a text by a user */
	Post(std::string text, std::string username);

	/* Used by DataAccessor to construct the post using data from the data file */
	Post(std::string strline);

	/* Used by DataAccessor to write to the data file */
	friend std::ostream & operator << (std::ostream & os, Post & post);
	
	/* Used by Vector to search for Post object */
	bool operator==(Post& acc);
};