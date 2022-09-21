#include <fstream>
#include <string>
#include <regex>
#include "Text.h"
#include <iostream>

Text::Text(std::filesystem::path filePath) {
	m_filePath = filePath;
	// get filename from filepath
	m_fileName = filePath.filename().string();
	// check if text contains title
	std::ifstream ifs(m_filePath);
	std::string tempString;
	int checkCount = 0;
	for (int i = 0; i < 3; i++) {
		std::getline(ifs, tempString, '\n');
		if (i == 0 && tempString.length() > 0) {
			checkCount++;
		}
		else if (i > 0 && tempString.length() == 0) {
			checkCount++;
		}
	}

	validTitle = checkCount == 3;
}

void Text::createHtml() const {
	// replace file extension with html for output file name
	std::string title = getHtmlName();
	std::ifstream ifs(m_filePath, std::ios::app);
	std::ofstream ofs(getHtmlName());
	bool inParagraph = false;

	std::regex boldAs("(\\*\\*)([^\\*]+)(\\*\\*)");
	std::regex boldUn("(\\_\\_)([^\\_]+)(\\_\\_)");
	std::regex italAs("(\\*)([^\\*]+)(\\*)");
	std::regex italUn("(\\_)([^\\_]+)(\\_)");

	// read title, if title is valid
	if (validTitle) {
		std::getline(ifs, title, '\n');
		ifs.ignore(2);
	}
	// add html and header tags
	ofs << OPENTAGS[0] << title << OPENTAGS[1];

	// add title to top of page
	if (validTitle) {
		ofs << "<h1>" << title << "</h1>" << std::endl;
	}

	// read body of text
	while (ifs) {
		std::string tempString;
		std::getline(ifs, tempString, '\n');
		if (tempString.length() > 0) {
			//Check if MD so that we can replace everything we need to replace
			if (std::regex_match(m_fileName, std::regex("(.*.md$)"))) {
				//TODO: Put logic to parse md here
				try {
					//tempString = std::regex_replace(tempString, std::regex("(\*\*[^*]\*\*)"), "i");
					//std::cout << std::regex_replace(tempString, std::regex("(\*\*[^\*]+\*\*)"), "<b>$&<\\b>");
					tempString = std::regex_replace(tempString, boldAs, "<b>$2<\/b>");
					tempString = std::regex_replace(tempString, boldUn, "<b>$2<\/b>");
					tempString = std::regex_replace(tempString, italUn, "<i>$2<\/i>");
					tempString = std::regex_replace(tempString, italAs, "<i>$2<\/i>");
				}
				catch (const std::regex_error& e) {
					std::cout << "regex error caught: " << e.what() << "\n";
				}
			}

			// if in paragraph output open paragraph tag, else output space (to account line break), then line
			ofs << (inParagraph ? " " : "<p>") << tempString;
			inParagraph = true;
		}
		// if line is blank, output close paragraph tag, no longer in paragraph
		else if (inParagraph == true && tempString.length() <= 0) {
			ofs << "</p>" << std::endl;
			inParagraph = false;
		}
	}

	// closing tags
	ofs << CLOSETAGS;
}

std::string Text::getHtmlName() const {
	return m_fileName.substr(0, m_fileName.rfind('.')) + ".html";
}