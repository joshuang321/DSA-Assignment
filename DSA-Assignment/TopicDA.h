//==================================================================
// Student Number : S10205140B, S10223630K
// Student Name :Joshua Ng, Armirola Roseller Iii Tumolva
// Module Group : P03
//==================================================================

#pragma once

#include "DataAccessor.h"
#include "Topic.h"
#include <string>

/* Used to read and write data for topics and data access for external purposes */
class TopicDA : public DataAccessor<Topic>
{
	/* Used to do sorting for time and tile */
	static bool compareTime(Topic& a, Topic& b);
	static bool compareTitle(Topic& a, Topic& b);

public:
	/* Constructor and Destructor */
	TopicDA();
	~TopicDA();

	/* Get all the topic names for display */
	Vector<std::string> getTopics();

	/* Get the topic according the the index in display */
	Topic& getTopic(int nIndex);

	/* Returns true if the topicName exists, false otherwise */
	bool findTopic(std::string topicName);

	/* Used for display styles */
	void sortByLatest();
	void sortByAlphabet();
};