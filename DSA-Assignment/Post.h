#pragma once
#include <iostream>
#include "Topic.h"

class Post {
	//attributes
private:
	std::string text;
	std::string date;
	Topic topic;

	//methods
public:
	Post();
	Post(std::string, std::string, Topic);

	void setText(std::string);
	std::string getText();
	void setDate(std::string);
	std::string getDate();
};