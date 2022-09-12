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

std::string Text::createHtml() const{
	std::string newFileName = m_fileName.substr(0, m_fileName.rfind('.')) + ".html";
	std::string title = newFileName;
	std::ifstream ifs(m_filePath);
	std::ofstream ofs(newFileName);

	// read title, if title is valid
	if (validTitle) {
		getline(ifs, title, '\n');
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
		if (tempString.length() > 0) {
			ofs << "<p>" << tempString << "</p>" << std::endl;
		}
		else {
			ofs << "<br>" << std::endl;
		}
	}

	// closing tags
	ofs << "</body>" << std::endl
		<< "</html>";

	return newFileName;
}