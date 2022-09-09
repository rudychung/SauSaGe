#define VERSION "0.0.1"
#define NAME "SauSaGe"

#include <iostream>
#include <filesystem>
#include <algorithm>
#include "Text.h"

int main(int argc, char* argv[]) {
	if (argc <= 1) {
		std::cout << "No arguments.";
	}
	else if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) {
		// output name and version
		std::cout << NAME << std::endl << "Version " << VERSION;
	}
	else if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
		// output help
		std::cout << "-v/--version - outputs software version" << std::endl
			<< "-i/--input - input file" << std::endl;
	}
	else if (strcmp(argv[1], "-i") == 0 || strcmp(argv[1], "--input") == 0) {
		std::filesystem::path filepath(argv[2]);
		std::filesystem::remove_all("dist");
		std::filesystem::create_directory("dist");
		// if filepath is a directory
		if (std::filesystem::is_directory(filepath)) {
			std::vector<Text> files;
			// iterate through files in the directory recursively
			for (const std::filesystem::directory_entry& dir_entry : std::filesystem::recursive_directory_iterator{ filepath })
			{
				// if file is not a directory
				if (!std::filesystem::is_directory(dir_entry.path().string())) {
					// add file to vector
					files.push_back(dir_entry.path().string());
				}
			}
			// create html file for each file
			std::for_each(files.begin(), files.end(), [&files](Text i) {i.createHtml(); });
		}
		else {
			// create a single html file
			Text t(filepath.string());
			t.createHtml();
		}
	}
	else {
		std::cout << "Unknown arguments";
	}
}