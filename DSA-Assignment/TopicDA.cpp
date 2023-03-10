//==================================================================
// Student Number : S10205140B, S10223630K
// Student Name :Joshua Ng, Armirola Roseller Iii Tumolva
// Module Group : P03
//==================================================================

#pragma once

#include "TopicDA.h"
#include <iostream>
#include "Tools.h"
static const char* TopicSaveFilename = "Topics.txt";

TopicDA::TopicDA() : DataAccessor<Topic>(TopicSaveFilename)
{
	/* Gets the posts for each topic */
	for (int i = 0; i < cacheData.count(); i++)
	{
		std::ifstream ifDataFile(cacheData[i].getTitle() + ".txt", std::ifstream::in);
		std::string strline;

		while (std::getline(ifDataFile, strline))
			cacheData[i].posts.push(Post(strline));

		/* Get the comments for each posts */
		for (int j = 0; j < cacheData[i].posts.count(); j++)
		{
			std::ifstream ifCommentFile(cacheData[i].getTitle() + "_" +
				cacheData[i].posts[j].getTitle() + ".txt", std::ifstream::in);

			while (std::getline(ifCommentFile, strline))
				cacheData[i].posts[j].reply.push(Comment(strline));
		}
	}
}

TopicDA::~TopicDA()
{
	/* Save the posts for each topic */
	for (int i = 0; i < cacheData.count(); i++)
	{
		std::ofstream ofDataFile(cacheData[i].getTitle() + ".txt");

		if (cacheData[i].posts.count() != 0)
		{
			ofDataFile << cacheData[i].posts[0];

			std::ofstream ofCommentFile(cacheData[i].getTitle() + "_" +
				cacheData[i].posts[0].getTitle() + ".txt");

			/* Saves the comments for each post */
			if (cacheData[i].posts[0].reply.count() != 0)
				ofCommentFile << cacheData[i].posts[0].reply[0];

			for (int k = i; k < cacheData[i].posts[0].reply.count(); k++)
			{
				ofCommentFile << '\n' << cacheData[i].posts[0].reply[k];
			}
		}

		//WARNING duplicate replies written into file
		for (int j = 1; j < cacheData[i].posts.count(); j++)
		{
			ofDataFile << '\n' << cacheData[i].posts[j];

			std::ofstream ofCommentFile(cacheData[i].getTitle() + "_" +
				cacheData[i].posts[j].getTitle() + ".txt");

			if (cacheData[i].posts[j].reply.count() != 0)
				ofCommentFile << cacheData[i].posts[j].reply[0];

			for (int k = i; k < cacheData[i].posts[j].reply.count(); k++)
			{
				ofCommentFile << '\n' << cacheData[i].posts[j].reply[k];
			}
		}
	}
}

bool TopicDA::compareTime(Topic& a, Topic& b) { return a.isLaterThan(b); }

bool TopicDA::compareTitle(Topic& a, Topic& b) { return a.getTitle() < b.getTitle(); }

Vector<std::string> TopicDA::getTopics()
{
	Vector<std::string> topicNames;

	/* Gets the title of the topic and put them into an Vector and return it */
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

//use selection sort to sort topics by time created
void TopicDA::sortByLatest()
{
	/* Uses selectionSort to sort by Latest */
	Tools::selectionSort(cacheData, compareTime);
}

//use selection sort to sort topics by alphabet
void TopicDA::sortByAlphabet()
{
	/* Yses selectionSort to sort by alphabet */
	Tools::selectionSort(cacheData, compareTitle);
}