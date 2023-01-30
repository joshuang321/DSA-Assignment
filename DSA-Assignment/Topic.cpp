#include "Topic.h"
#include <fstream>
#include <string>
#include <chrono>
#include <filesystem>
#include <sstream>

#include <Windows.h>

static const char* TopicSaveFilename = "Topics.txt";

Topic::Topic() : title(), description(), username(), timeCreated(), likes(), posts() { }

Topic::Topic(const Topic& topic) :
	title(topic.title),
	description(topic.description),
	username(topic.username),
	timeCreated(topic.timeCreated),
	likes(topic.likes),
	posts()
{
}

Topic::Topic(std::string title, std::string description, std::string username) :
	title(title),
	description(description),
	username(username),
	timeCreated(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())),
	likes(0),
	posts()
{ }

Topic::Topic(std::string strline)
{
	size_t ndelim;
	std::string strtimeCreated = strline;
	tm _tm;

	ndelim = strline.find(';');
	title = strline.substr(0, ndelim);
	strline = strline.substr(ndelim + 1, strline.length() - ndelim - 1);
	ndelim = strline.find(';');
	description = strline.substr(0, ndelim);
	strline = strline.substr(ndelim + 1, strline.length() - ndelim - 1);
	ndelim = strline.find(';');
	username = strline.substr(0, ndelim);


	strline = strline.substr(ndelim + 1, strline.length() - ndelim - 1);
	ndelim = strline.find(';');
	strtimeCreated = strline;
	strline = strline.substr(ndelim + 1, strline.length() - ndelim - 1);
	likes = atoi(strline.c_str());

	std::istringstream(strtimeCreated.c_str()) >> std::get_time(&_tm, "%Y-%m-%d %H:%M:%S");
	timeCreated = std::mktime(&_tm);
}

void Topic::addNewPost(Post& newPost) { posts.push(newPost); }

std::string Topic::getTitle() { return title; }

std::string Topic::getDescription() { return description; }

std::string Topic::getUsername() { return username; }

std::string Topic::getTimeCreated() 
{
	char strBuf[256];
	std::size_t szCount;
	tm _tm;

	localtime_s(&_tm, &timeCreated);
	szCount = strftime(strBuf, 256, "%Y-%m-%d %H:%M:%S", &_tm);
	
	return std::string(strBuf, szCount);
}

int Topic::getLikes() { return likes; }

std::ostream& operator<<(std::ostream& os, Topic& topic)
{
	os << topic.title << ';' << topic.description << ';' << topic.username
		<< ';' << topic.getTimeCreated() << ';' << topic.likes;
	return os;
}

bool Topic::operator==(Topic& topic)
{
	return topic.title == title;
}