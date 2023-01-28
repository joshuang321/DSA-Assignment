#include "Topic.h"
#include <fstream>
#include <string>
#include <chrono>
#include <filesystem>
#include <sstream>

#include <Windows.h>

static const char* TopicSaveFilename = "Topics.txt";

Topic::Topic(std::string title, std::string description, std::string username, std::time_t timeCreated) :
	title(title),
	description(description),
	username(username),
	timeCreated(timeCreated) 
{ }

Topic::Topic() { }

Topic::Topic(std::string title, std::string description, std::string username) :
	title(title),
	description(description),
	username(username),
	timeCreated(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()))
{ }

void Topic::addNewPost(Post& newPost)
{
	posts.push(newPost);
}

bool Topic::findTopic(std::string topicName)
{
	return false;
}

bool Topic::getTopic(std::string topicName, Topic& topic)
{
	std::string text,
		title,
		description,
		username,
		strtimeCreated;
	
	tm _tm;
	size_t ndelim = 0;

	std::filesystem::path fsPath = std::filesystem::current_path();
	fsPath += TopicSaveFilename;

	std::ifstream ifTopicFile(TopicSaveFilename, std::ifstream::in);

	while (std::getline(ifTopicFile, text))
	{
		ndelim = text.find(';');
		title = text.substr(0, ndelim);
			
		if (title == topicName)
		{
			text = text.substr(ndelim + 1, text.length() - ndelim -1);
			ndelim = text.find(';');
			description = text.substr(0, ndelim);
			text = text.substr(ndelim + 1, text.length() - ndelim - 1);
			ndelim = text.find(';');
			username = text.substr(0, ndelim);


			text = text.substr(ndelim + 1, text.length() - ndelim - 1);
			strtimeCreated = text;

			std::istringstream(strtimeCreated.c_str()) >> std::get_time(&_tm, "%Y-%m-%d %H:%M:%S");
			topic = Topic(title, description, username, std::mktime(&_tm));
			return true;
		}
	}
	return false;
}

void Topic::saveTopic(Topic& topic)
{
	char timeBuf[256];
	std::size_t szCount;
	tm _tm;

	std::filesystem::path fsPath = std::filesystem::current_path();
	fsPath += std::string("//") + TopicSaveFilename;

	bool isExisting;

	/* Checks if the file exists, and add a newline if it does */
	isExisting = std::filesystem::exists(fsPath) &&
		std::filesystem::is_regular_file(fsPath);

	std::ofstream ofAccFile(TopicSaveFilename, std::ofstream::app);

	if (isExisting)
		ofAccFile.write("\n", 1);

	/* Writes the username and password seperated by ';' */
	ofAccFile.write(topic.title.c_str(), topic.title.length());
	ofAccFile.write(";", 1);
	ofAccFile.write(topic.description.c_str(), topic.description.length());
	ofAccFile.write(";", 1);
	ofAccFile.write(topic.username.c_str(), topic.username.length());
	
	ofAccFile.write(";", 1);
	localtime_s(&_tm, &topic.timeCreated);
	szCount = strftime(timeBuf, 256, "%Y-%m-%d %H:%M:%S", &_tm);
	ofAccFile.write(timeBuf, szCount);
}

Vector<std::string> Topic::getTopics()
{
	Vector<std::string> topicNames;
	std::string text;
	size_t ndelim = 0;

	std::ifstream ifTopicFile(TopicSaveFilename, std::ifstream::in);

	while (std::getline(ifTopicFile, text))
	{
		ndelim = text.find(';');
		text = text.substr(0, ndelim);
		topicNames.push(text);
	}

	return topicNames;
}

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