#include "Text.h"

Text::Text(std::string filepath) {
	m_filepath = filepath;
	// get filename from filepath
	m_filename = filepath.substr(filepath.rfind('\\') + 1);

	// check if text contains title
	std::ifstream ifs(m_filepath);
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

void Text::createHtml() {
	std::ifstream ifs(m_filepath);
	std::ofstream ofs(".\\dist\\" + m_filename.substr(0, m_filename.rfind('.')) + ".html");
	std::string title = m_filename;
	std::string tempString;

	// add html and header tags
	ofs << "<!doctype html>" << std::endl
		<< "<html lang = \"en\">" << std::endl
		<< "<head>" << std::endl
		<< "<meta charset = \"utf-8\">" << std::endl
		<< "<title>" << title << "</title>" << std::endl
		<< "<meta name = \"viewport\" content = \"width=device-width, initial-scale=1\">" << std::endl
		<< "</head>" << std::endl
		<< "<body>" << std::endl;

	// read and add title to top of page
	if (validTitle) {
		getline(ifs, title, '\n');
		ofs << "<h1>" << title << "</h1>" << std::endl;
	}

	// read body of text
	while (ifs) {
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
}