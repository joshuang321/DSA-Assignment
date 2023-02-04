#pragma once
#include <string>

class Comment
{
private:
	std::string title;
	time_t timeCreated;
	std::string username;
	int likes;

protected:
	Comment();
	Comment(const Comment& comment);
	Comment& operator=(const Comment& comment) = default;
	Comment(Comment&& comment);

	Comment(std::string strline);
	Comment(std::string title, std::string username);

	virtual void renderContent(std::ostream& os);
public:
	std::string getTitle();
	std::string getTimeCreated();
	std::string getUsername();
	int getLikes();
	void addLike();

	friend std::ostream& operator << (std::ostream& os, Comment& comment);
	bool operator==(Comment& comment);
};