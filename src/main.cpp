#define CATCH_CONFIG_RUNNER
#include "catch2/catch.hpp"

#define VERSION "1.0.0"
#define NAME "SauSaGe"
#define AUTHOR "rudychung"

#include "Files.h"
#include <iostream>

int main(int argc, char* argv[]) {
	bool exit = false;
	std::string inputPath;
	std::string outputPath = "dist";

	// command line argument handling
	if (argc <= 1) {
		std::cout << "No arguments." << std::endl;
	} else {
		for (int i = 1; i < argc && !exit; i += 2) {
			if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
				// output name and version
				std::cout << NAME << std::endl << "Version " << VERSION << std::endl << "By " << AUTHOR << std::endl;
				exit = true;
			} else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
				// output help details
				std::cout << "-v/--version\t- outputs software version" << std::endl
						  << "-i/--input\t- input file/directory" << std::endl
						  << "-o/--output\t- output directory (dist by default)" << std::endl
						  << "-t/--test\t- run unit tests" << std::endl;
				exit = true;
			} else if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--test") == 0) {
				// run tests
				return Catch::Session().run();
			} else if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--input") == 0) {
				// set input file path
				inputPath = argv[i + 1];
			} else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
				// set input file path
				outputPath = argv[i + 1];
			} else {
				std::cout << "Unknown arguments found";
				exit = true;
			}
		}
	}

	// execute html file generation if not exiting and input file path is set
	if (!exit && inputPath.length() > 0) {
		try {
			Files files(inputPath, outputPath);
			files.createFiles();
		} catch (std::invalid_argument err) {
			std::cerr << err.what();
		}
	}
}
