#pragma once
#include <iostream>
#include <ctime>
#include "Account.h"

using namespace std;
//
class Post {
	//attributes
private:
	string text;
	time_t timeCreated;
	string username;
	int likes;
//
//public:
//	Post();
//	Post(const Post& post);
//	Post(string text, time_t timeCreated, string username);
//	Post(string strline);
//
//
//	string getText();
//	string getTimeCreated();
//	string getUsername();
//	int getLikes();
//
//	friend ostream& operator << (ostream& os, Post& post);
//	bool operator==(Post& acc);
};