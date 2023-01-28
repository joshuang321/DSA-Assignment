#pragma once
#include <iostream>
#include "Account.h"

class Post {
	//attributes
private:
	std::string text;
	std::time_t timeCreated;
	std::string username;
};