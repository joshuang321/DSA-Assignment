//==================================================================
// Student Number : S10205140B, S10223630K
// Student Name :Joshua Ng, Armirola Roseller Iii Tumolva
// Module Group : P03
//==================================================================

#pragma once
#include "Post.h"
#include <fstream>
#include <string>
#include <chrono>
#include <filesystem>
#include <sstream>

#include <Windows.h>

using namespace std;

static const char* PostSaveFileName = "Posts.txt";

Post::Post() : Comment(), reply()
{ }

Post::Post(const Post& post) :
	reply(post.reply),
	Comment(post)
{
#if defined (_DEBUG)
	OutputDebugStringA("Post_CC\n");
#endif
}

Post::Post(Post&& post) :
	Comment(std::move(post)),
	reply(std::move(post.reply))
{
#if defined (_DEBUG)
	OutputDebugStringA("Post_MC\n");
#endif
}

Post::Post(string title, string username) :
	Comment(title, username),
	reply()
{ }

Post::Post(string strline) : Comment(strline)
{

}

std::ostream& operator<<(std::ostream& os, Post& post)
{
	os << ((Comment&)post);
	return os;
}

bool Post::operator==(Post& post) { return Comment::operator==(post); }