//#include "Post.h"
//#include <fstream>
//#include <string>
//#include <chrono>
//#include <filesystem>
//#include <sstream>
//
//#include <Windows.h>
//
//using namespace std;
//
//static const char* PostSaveFileName = "Posts.txt";
//
//Post::Post() : text(), timeCreated(), username(), likes() {}
//
//Post::Post(const Post& post) :
//	text(post.text),
//	timeCreated(post.timeCreated),
//	username(post.username),
//	likes(post.likes)
//{
//}
//
//Post::Post(string text, time_t timeCreated, string username) :
//	text(text),
//	timeCreated(chrono::system_clock::to_time_t(chrono::system_clock::now())),
//	username(username),
//	likes(0)
//{
//}
//
//Post::Post(string strline)
//{
//
//}

//string Post::getText() { return text; }
//
//string Post::getTimeCreated()
//{
//	char strBuf[256];
//	size_t szCount;
//	tm _tm;
//
//	localtime_s(&_tm, &timeCreated);
//	szCount = strftime(strBuf, 256, "%Y-%m-%d %H:%M:%S", &_tm);
//
//	return std::string(strBuf, szCount);
//}
//
//string Post::getUsername() { return username; }
//
//int Post::getLikes() { return likes; }

//std::ostream& operator<<(std::ostream& os, Post& post)
//{
//	os << post.text << ';' << post.getTimeCreated() << ';' << post.username << ';' << post.likes;
//	return os;
//}
//
//bool Post::operator==(Post& post)
//{
//	return post.text == text;
//}