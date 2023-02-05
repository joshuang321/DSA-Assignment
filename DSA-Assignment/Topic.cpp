//==================================================================
// Student Number : S10205140B, S10223630K
// Student Name :Joshua Ng, Armirola Roseller Iii Tumolva
// Module Group : P03
//==================================================================

#include "Topic.h"
#include <fstream>
#include <string>
#include <chrono>
#include <filesystem>
#include <sstream>

#include <Windows.h>

Topic::Topic() : Comment(), description(), posts() { }

Topic::Topic(const Topic& topic) :
	Comment(topic),
	description(topic.description),
	posts(topic.posts)
{
#if defined (_DEBUG)
	OutputDebugStringA("Topic_CC\n");
#endif
}

Topic::Topic(Topic&& topic) :
	Comment(std::move(topic)),
	description(std::move(topic.description)),
	posts(std::move(topic.posts))
{
#if defined(_DEBUG)
	OutputDebugStringA("Topic_MC\n");
#endif
}

Topic::Topic(std::string title, std::string description, std::string username) :
	Comment(title, username),
	description(description),
	posts()
{ }

Topic::Topic(std::string strline) : Comment(strline.substr(0, strline.find_last_of(';')))
{
	size_t ndelim = strline.find_last_of(';');
	description = strline.substr(ndelim + 1, strline.length() - ndelim - 1);
}

std::string Topic::getDescription() { return description; }

std::ostream& operator<<(std::ostream& os, Topic& topic)
{
	os << ((Comment&)topic) << ';' << topic.description;
	return os;
}

bool Topic::operator==(Topic& topic)
{
	return Comment::operator==(topic);
}