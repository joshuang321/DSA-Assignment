#pragma once

#include "TopicDA.h"
#include <iostream>
static const char* TopicSaveFilename = "Topics.txt";

TopicDA::TopicDA() : DataAccessor<Topic>(TopicSaveFilename)
{
	for (int i = 0; i < cacheData.count(); i++)
	{
		std::ifstream ifDataFile(cacheData[i].getTitle() + ".txt", std::ifstream::in);
		std::string strline;

		while (std::getline(ifDataFile, strline))
			cacheData[i].addNewPost(Post(strline));
	}
}

TopicDA::~TopicDA()
{
	for (int i = 0; i < cacheData.count(); i++)
	{
		std::ofstream ofDataFile(cacheData[i].getTitle() + ".txt");

		if (cacheData[i].posts.count() != 0)
			ofDataFile << cacheData[i].posts[0];

		for (int j = 1; j < cacheData[i].posts.count(); j++)
			ofDataFile << '\n' << cacheData[i].posts[j];
	}
}

Vector<std::string> TopicDA::getTopics()
{
	Vector<std::string> topicNames;

	for (int i = 0; i < cacheData.count(); i++)
		topicNames.push(cacheData[i].getTitle());
	return topicNames;
}

Topic& TopicDA::getTopic(int nIndex)
{
	return cacheData[nIndex];
}

bool TopicDA::findTopic(std::string topicName)
{
	for (int i = 0; i < cacheData.count(); i++)
		if (cacheData[i].getTitle() == topicName)
			return true;
	return false;
}

void TopicDA::sortByLatest()
{
	int arraySize = cacheData.count();

	//use selection sort to sort by time
	for (int i = 0; i < arraySize; i++)
	{
		int min_index = i;

		for (int j = i + 1; j < arraySize; j++)
		{
			if (cacheData[j].getTimeCreated() < cacheData[min_index].getTimeCreated())
			{
				min_index = j;
			}
		}

		Topic temp = cacheData[i];
		cacheData[i] = cacheData[min_index];
		cacheData[min_index] = temp;
	}
}

void TopicDA::sortByAlphabet()
{

}