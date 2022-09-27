#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include "Text.h"


Text::Text(std::filesystem::path filePath) {
	m_filePath = filePath;
	// get filename and extension from filepath
	m_fileName = filePath.filename().string();
	m_fileExt = m_fileName.substr(m_fileName.rfind('.'));
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

	std::regex boldAs("(\\*\\*)([^*]+)(\\*\\*)");
	std::regex boldUn("(__)([^_]+)(__)");
	std::regex italAs("(\\*)([^*]+)(\\*)");
	std::regex italUn("(_)([^_]+)(_)");

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
			if (m_fileExt == ".md") {
				try {
					tempString = std::regex_replace(tempString, boldAs, "<b>$2</b>");
					tempString = std::regex_replace(tempString, boldUn, "<b>$2</b>");
					tempString = std::regex_replace(tempString, italUn, "<i>$2</i>");
					tempString = std::regex_replace(tempString, italAs, "<i>$2</i>");
				}
				catch (const std::regex_error& e) {
					std::cout << "regex error caught: " << e.what() << "\n";
				}
				if (tempString.find("## ", 0, 3) != std::string::npos) {
					ofs << (inParagraph ? "</p>\n" : "") << "<h2>" << tempString.substr(3) << "</h2>" << std::endl;
					inParagraph = false;
				}
				else if (tempString.find("# ", 0, 2) != std::string::npos) {
					ofs << (inParagraph ? "</p>\n" : "") << "<h1>" << tempString.substr(2) << "</h1>" << std::endl;
					inParagraph = false;
				}
			}
			else {
				// if in paragraph output open paragraph tag, else output space (to account line break), then line
				ofs << (inParagraph ? " " : "<p>") << tempString;
				inParagraph = true;
			}
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