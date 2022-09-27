#pragma once
#include <filesystem>
#include "Text.h"

class Files {
	std::filesystem::path inputPath;
	std::filesystem::path outputPath;
	std::vector<Text> texts;
	void createIndexPage();
public:
	Files(std::string inputPath, std::string outputPath);
	void createFiles();
};
