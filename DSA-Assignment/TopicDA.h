#pragma once

#include "DataAccessor.h"
#include "Topic.h"
#include <string>

class TopicDA : public DataAccessor<Topic>
{
	static bool compareTime(Topic& a, Topic& b);
	static bool compareTitle(Topic& a, Topic& b);

public:

	TopicDA();
	~TopicDA();
	Vector<std::string> getTopics();
	Topic& getTopic(int nIndex);
	bool findTopic(std::string topicName);
	void sortByLatest();
	void sortByAlphabet();
};