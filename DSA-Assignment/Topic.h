#pragma once
#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <Windows.h>

class Topic {
	//attributes
private:
	std::string title;
	SYSTEMTIME timeCreated;

	//methods
public:
	Topic();
	Topic(std::string);
};