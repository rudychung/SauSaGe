#include <iostream>
#include <fstream>
#include "Text.h"
#include "maddy/parser.h"

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
		// 1st check, title is present
		if (i == 0 && tempString.length() > 0) {
			checkCount++;
		}
		// 2nd and 3rd check, subsequent 2 lines are empty
		else if (i > 0 && tempString.length() == 0) {
			checkCount++;
		}
	}

	validTitle = checkCount == 3;
}

void Text::createHtml() const {
	// replace file extension with html for output file name
	std::string title = getHtmlName();
	std::ifstream ifs(m_filePath);
	std::ofstream ofs(getHtmlName());
	std::shared_ptr<maddy::Parser> parser = std::make_shared<maddy::Parser>();
	bool inParagraph = false;

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
				std::stringstream markdownInput(tempString);
				ofs << parser->Parse(markdownInput);
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