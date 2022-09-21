#pragma once
#include <filesystem>

// open tags split into array to insert title
const std::string OPENTAGS[2] = {
	"<!doctype html>\n<html lang=\"en\">\n<head>\n<meta charset=\"utf-8\">\n<title>",
	"</title>\n <meta name=\"viewport\" content=\"width=device-width,initial-scale=1\">\n</head>\n<body>\n"
};
const std::string CLOSETAGS = "</body>\n</html>\n";
const std::string BOLDAS = "\*\*[^*]+\*\*";
const std::string BOLDUN = "__[^*]+__";
const std::string ITALAS = "\*[^*]+\*";
const std::string ITALUN = "_[^*]+_";

class Text {
	std::filesystem::path m_filePath;
	std::string m_fileName;
	bool validTitle;
public:
	Text() = delete;
	Text(std::filesystem::path filePath);
	void createHtml() const;
	//void findMd(&string in, &string regEx);
	std::string getHtmlName() const;
};
