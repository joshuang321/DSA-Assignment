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

//
class Post : public Comment
{
	//attributes
private:

public:
	Vector<Comment> reply;

	Post();
	Post(const Post& post);
	Post& operator=(const Post & post) = default;
	Post(Post&& post);

	Post(std::string text, std::string username);
	Post(std::string strline);

	friend std::ostream & operator << (std::ostream & os, Post & post);
	bool operator==(Post& acc);
};