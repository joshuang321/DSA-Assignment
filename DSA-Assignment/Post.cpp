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

Post::Post() : text(), timeCreated(), username(), reply(), likes() {}

Post::Post(const Post& post) :
	text(post.text),
	timeCreated(post.timeCreated),
	username(post.username),
	reply(post.reply),
	likes(post.likes)
{
#if defined (_DEBUG)
	OutputDebugStringA("Post_CC\n");
#endif
}

Post::Post(Post&& post) :
	text(std::move(post.text)),
	timeCreated(std::move(post.timeCreated)),
	username(std::move(post.username)),
	reply(std::move(post.reply)),
	likes(std::move(post.likes))
{
#if defined (_DEBUG)
	OutputDebugStringA("Post_MC\n");
#endif
}

Post::Post(string text, string username) :
	text(text),
	timeCreated(chrono::system_clock::to_time_t(chrono::system_clock::now())),
	username(username),
	reply(reply),
	likes(0)
{ }

Post::Post(string strline)
{
	size_t ndelim;
	std::string strtimeCreated;
	tm _tm;

	//replaces .split() function
	ndelim = strline.find(';');
	text = strline.substr(0, ndelim);
	strline = strline.substr(ndelim + 1, strline.length() - ndelim - 1);

	ndelim = strline.find(';');
	strtimeCreated = strline.substr(0, ndelim);
	strline = strline.substr(ndelim + 1, strline.length() - ndelim - 1);

	ndelim = strline.find(';');
	username = strline.substr(0, ndelim);
	strline = strline.substr(ndelim + 1, strline.length() - ndelim - 1);

	ndelim = strline.find(';');
	likes = atoi(strline.substr(0, ndelim).c_str());
	strline = strline.substr(ndelim + 1, strline.length() - ndelim - 1);

	reply = strline;
		

	std::istringstream(strtimeCreated.c_str()) >> std::get_time(&_tm, "%Y-%m-%d %H:%M:%S");
	timeCreated = std::mktime(&_tm);
}

string Post::getText() { return text; }

string Post::getTimeCreated()
{
	char strBuf[256];
	size_t szCount;
	tm _tm;

	localtime_s(&_tm, &timeCreated);
	szCount = strftime(strBuf, 256, "%Y-%m-%d %H:%M:%S", &_tm);

	return std::string(strBuf, szCount);
}

string Post::getUsername() { return username; }

int Post::getLikes() { return likes; }

void Post::addLike() { likes++; }

std::ostream& operator<<(std::ostream& os, Post& post)
{
	os << post.text << ';' << post.getTimeCreated() << ';' << post.username << ';' << post.likes << 
		';' << post.reply;
	return os;
}

bool Post::operator==(Post& post)
{
	return post.text == text;
}