#include "Comment.h"

#include <fstream>
#include <chrono>
#include <filesystem>
#include <sstream>
#include <chrono>

#include "Tools.h"

Comment::Comment() : title(), timeCreated(), username(), likes()
{ }

Comment::Comment(const Comment& comment) :
	title(comment.title),
	timeCreated(comment.timeCreated),
	username(comment.username),
	likes(comment.likes)
{ }

Comment::Comment(Comment&& comment) :
	title(std::move(comment.title)),
	timeCreated(std::move(comment.timeCreated)),
	username(std::move(comment.username)),
	likes(std::move(comment.likes))
{ }

Comment::Comment(std::string strline)
{
	Vector<std::string> strs = Tools::split(strline, ';');
	
	title = strs[0];
	timeCreated = Tools::strToTime(strs[1]);
	username = strs[2];
	likes = atoi(strs[3].c_str());
}

Comment::Comment(std::string title, std::string username) :
	title(title),
	timeCreated(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())),
	username(username),
	likes(0)
{ }

std::string Comment::getTitle() { return title; }

std::string Comment::getTimeCreated() { return Tools::timeToString(timeCreated); }

std::string Comment::getUsername() { return username; }

int Comment::getLikes() { return likes; }

void Comment::addLike() { likes++; }

bool Comment::isLaterThan(Comment& comment)
{
	return timeCreated > comment.timeCreated;
}

std::ostream& operator << (std::ostream& os, Comment& comment)
{
	os << comment.title << ';' << comment.getTimeCreated() << ';' << comment.username
		<< ';' << comment.likes;
	return os;
}

bool Comment::operator==(Comment& comment) { return title == comment.title; }