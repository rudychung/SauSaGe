#define VERSION "0.0.1"
#define NAME "SauSaGe"
#define AUTHOR "rudychung"

#include <iostream>
#include <filesystem>
#include "Text.h"

int main(int argc, char* argv[]) {
	bool exit = false;
	std::string inputPath;
	std::string outputPath = "dist";

	if (argc <= 1) {
		std::cout << "No arguments." << std::endl;
	}
	else {
		for (int i = 1; i < argc && !exit; i += 2) {
			if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
				// output name and version
				std::cout << NAME << std::endl
					<< "Version " << VERSION << std::endl
					<< "By " << AUTHOR << std::endl;
				exit = true;
			}
			else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
				// output help details
				std::cout << "-v/--version\t- outputs software version" << std::endl
					<< "-i/--input\t- input file/directory" << std::endl
					<< "-o/--output\t- output directory (dist by default)" << std::endl;
				exit = true;
			}
			else if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--input") == 0) {
				// set input file path
				inputPath = argv[i + 1];
			}
			else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
				// set input file path
				outputPath = argv[i + 1];
			}
			else {
				std::cout << "Unknown arguments found";
				exit = true;
			}
		}
	}

	// execute if not exiting and input file path is set
	if (!exit && inputPath.length() > 0) {
		std::filesystem::path filePath(inputPath);
		std::filesystem::remove_all(outputPath);
		std::filesystem::create_directory(outputPath);
		std::vector<Text> texts;

		// if filepath is a directory
		if (std::filesystem::is_directory(filePath)) {
			// iterate through files in the directory recursively
			for (const std::filesystem::directory_entry& i : std::filesystem::recursive_directory_iterator{ filePath })
			{
				// if file is not a directory, add to texts vector
				if (!std::filesystem::is_directory(i.path().string())) {
					texts.push_back(i.path());
				}
			}
		}
		else {
			// add single file to texts
			texts.push_back(filePath);
		}

		// create html files and move them to output directory
		for (const Text& i : texts) {
			std::string htmlName = i.createHtml();
			std::filesystem::rename(std::filesystem::path("./" + htmlName).make_preferred(), std::filesystem::path("./" + outputPath + "/" + htmlName).make_preferred());
		}
	}
}