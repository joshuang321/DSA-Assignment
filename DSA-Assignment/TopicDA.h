#pragma once

#include "DataAccessor.h"
#include "Topic.h"
#include <string>

class TopicDA : public DataAccessor<Topic>
{
public:

	TopicDA();
	~TopicDA();
	Vector<std::string> getTopics();
	Topic& getTopic(int nIndex);
	bool findTopic(std::string topicName);
	void sortByLatest();
	int hash(std::string topicName);
	void sortByAlphabet();
};