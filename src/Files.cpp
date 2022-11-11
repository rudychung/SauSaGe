#include "Files.h"
#include <fstream>

Files::Files(const std::string& inputPathStr, const std::string& outputPathStr) {
	inputPath = std::filesystem::path(inputPathStr);
	outputPath = std::filesystem::path(outputPathStr);

	// if inputted file path exists
	if (std::filesystem::exists(inputPath)) {
		// if filepath is a directory
		if (std::filesystem::is_directory(inputPath)) {
			// iterate through files in the directory recursively
			for (const std::filesystem::directory_entry& file : std::filesystem::recursive_directory_iterator{inputPath}) {
				// if file is not a directory, add to texts vector
				if (!std::filesystem::is_directory(file.path()) &&
					(file.path().extension().string() == ".txt" || file.path().extension().string() == ".md")) {
					texts.emplace_back(file.path());
				}
			}
		} else {
			// add single file to texts
			texts.emplace_back(inputPath);
		}
	}
}

void Files::createFiles() {
	std::filesystem::remove_all(outputPath);
	std::filesystem::create_directory(outputPath);
	// create html files and move them to output directory
	for (const Text& text : texts) {
		// generate html
		text.createHtml();
		// move html file to output directory
		std::filesystem::rename(std::filesystem::path("./" + text.getHtmlName()).make_preferred(),
								std::filesystem::path("./" + outputPath.string() + "/" + text.getHtmlName()).make_preferred());
	}

	// if input path is a directory, generate an index page
	if (std::filesystem::is_directory(inputPath)) {
		createIndexPage();
	}
}

void Files::createIndexPage() {
	std::ofstream ofs("index.html");
	// index page opening tags
	ofs << OPENTAGS1 << "Index Page" << OPENTAGS2 << "<ul>\n";

	// links unordered list
	for (const Text& i : texts) {
		ofs << "<li><a href=\"" << i.getHtmlName() << "\">" << i.getHtmlName() << "</a></li>" << std::endl;
	}

	// index page closing tags
	ofs << "</ul>\n" << CLOSETAGS;

	// close file stream and move index html file to output directory
	ofs.close();
	std::filesystem::rename(std::filesystem::path("./index.html").make_preferred(),
							std::filesystem::path("./" + outputPath.string() + "/index.html").make_preferred());
}
