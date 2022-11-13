#ifndef FILES_H
#define FILES_H

#include "Text.h"
#include <filesystem>

class Files {
	std::filesystem::path inputPath;
	std::filesystem::path outputPath;
	std::vector<Text> texts;
	void createIndexPage();

  public:
	Files(const std::string& inputPath, const std::string& outputPath);
	void createFiles();
};
#endif
