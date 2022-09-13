#include <fstream>
#include <string>
#include "Text.h"

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
	std::string newFileName = getHtmlName();
	std::string title = newFileName;
	std::ifstream ifs(m_filePath);
	std::ofstream ofs(newFileName);
	bool inParagraph = false;

	// read title, if title is valid
	if (validTitle) {
		std::getline(ifs, title, '\n');
		ifs.ignore(2);
	}
	// add html and header tags
	ofs << "<!doctype html>" << std::endl
		<< "<html lang = \"en\">" << std::endl
		<< "<head>" << std::endl
		<< "<meta charset = \"utf-8\">" << std::endl
		<< "<title>" << title << "</title>" << std::endl
		<< "<meta name = \"viewport\" content = \"width=device-width, initial-scale=1\">" << std::endl
		<< "</head>" << std::endl
		<< "<body>" << std::endl;

	// add title to top of page
	if (validTitle) {
		ofs << "<h1>" << title << "</h1>" << std::endl;
	}

	// read body of text
	while (ifs) {
		std::string tempString;
		std::getline(ifs, tempString, '\n');
		if (tempString.length() > 0 ) {
			// if in paragraph output open paragraph tag, else output space (to account line break), then line
			ofs << (inParagraph ? " " : "<p>") << tempString;
			inParagraph = true;
		}
		// if line is blank, output close paragraph tag, no longer in paragraph
		else {
			ofs << "</p>" << std::endl;
			inParagraph = false;
		}
	}

	// closing tags
	ofs << "</body>" << std::endl
		<< "</html>";
}

std::string Text::getHtmlName() const{
	return m_fileName.substr(0, m_fileName.rfind('.')) + ".html";
}