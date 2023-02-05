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

Post::Post(string strline) : Comment(strline.substr(0, strline.find_last_of(';')))
{

}

std::ostream& operator<<(std::ostream& os, Post& post)
{
	os << ((Comment&)post);
	return os;
}

bool Post::operator==(Post& post) { return Comment::operator==(post); }