#pragma once
#include <fstream>
#include <string>

class Text {
	std::string m_filepath;
	std::string m_filename;
	bool validTitle;
public:
	Text() = delete;
	Text(std::string);
	void createHtml();
};
