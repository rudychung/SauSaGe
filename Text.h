#pragma once
#include <filesystem>

class Text {
	std::filesystem::path m_filePath;
	std::string m_fileName;
	bool validTitle;
public:
	Text() = delete;
	Text(std::filesystem::path filePath);
	void createHtml() const;
	std::string getHtmlName() const;
};
