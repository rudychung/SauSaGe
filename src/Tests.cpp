#include "Files.h"
#include "Text.h"
#include "catch2/catch.hpp"
#include <filesystem>
#include <fstream>

bool compareFiles(std::string filePath1, std::string filePath2) {
	std::ifstream file1(filePath1), file2(filePath2);
	bool equal = false;
	char c1, c2;

	if (file1 && file2) {
		do {
			c1 = file1.get();
			c2 = file2.get();
			equal = c1 == c2;
		} while (equal && c1 != EOF && c2 != EOF);
	}

	return equal;
}

TEST_CASE("Input directory contents") {
	{
		SECTION(".txt -> .html") { REQUIRE_THROWS_AS(Files("./doesNotExist", "./outputPath"), std::invalid_argument); }
	}
}

TEST_CASE("Test get HTML name") {
	{
		Text testText("./tests/testTxt.txt");
		REQUIRE(testText.getHtmlName() == "testTxt.html");
	}
}

TEST_CASE("Output directory contents") {
	{
		Files files("./tests/testTxt.txt", "./testDir");
		files.createFiles();
		std::filesystem::path testOutput("./testDir/testTxt.html");
		SECTION("Single file") { REQUIRE(std::filesystem::exists(testOutput)); }
		std::filesystem::remove_all("./testDir");
	}

	{
		const char fileNames[5][18] = {"index.html", "test.html", "testMarkdown.html", "testMd.html", "testTxt.html"};
		int passedChecks = 0;
		int i = 0;
		Files files("./tests", "./testDir");
		files.createFiles();
		std::filesystem::path testOutput("./testDir");
		for (const std::filesystem::directory_entry& file : std::filesystem::recursive_directory_iterator{testOutput}) {
			if (fileNames[i] == file.path().filename()) {
				++passedChecks;
			}
			++i;
		}
		SECTION("Multiple files") { REQUIRE(passedChecks == 5); }
		std::filesystem::remove_all("./testDir");
	}
}

TEST_CASE("File conversions") {
	{
		Text testText("./tests/testTxt.txt");
		testText.createHtml();
		SECTION(".txt -> .html") { REQUIRE(compareFiles("./tests/test.html", "./testTxt.html") == true); }
		std::filesystem::remove("./testTxt.html");
	}

	{
		Text testMd("./tests/testMd.md");
		testMd.createHtml();
		SECTION(".md -> .html") { REQUIRE(compareFiles("./tests/test.html", "./testMd.html") == true); }
		std::filesystem::remove("./testMd.html");
	}

	{
		Text testWithMarkdown("./tests/testMarkdown.md");
		testWithMarkdown.createHtml();
		SECTION(".md -> .html with markdown syntax bold, italic, code") {
			REQUIRE(compareFiles("./tests/testMarkdownSyntax.html", "./testMarkdown.html") == true);
		}
		std::filesystem::remove("./testMarkdown.html");
	}
}
