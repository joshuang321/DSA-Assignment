#include "Post.h"

Post::Post() {}
Post::Post(std::string text, std::string d, Topic t) : text(text), date(d), topic(t) {}

//functions for methods
void Post::setText(std::string t) { text = t; }
std::string Post::getText() { return text; }

void Post::setDate(std::string d) { date = d; }
std::string Post::getDate() { return date; }