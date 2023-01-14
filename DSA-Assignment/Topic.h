#pragma once
#include <iostream>

class Topic {
	//attributes
private:
	std::string title;

	//methods
public:
	Topic();
	Topic(std::string);

	void setTitle(std::string);
	std::string getTitle();
};