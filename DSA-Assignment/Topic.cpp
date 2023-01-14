#include "Topic.h"

Topic::Topic() {}
Topic::Topic(std::string t) :title(t) {}

//functions for methods
void Topic::setTitle(std::string t) { title = t; }
std::string Topic::getTitle() { return title; }