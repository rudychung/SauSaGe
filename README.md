# SauSaGe
A Static Site Generator. Reads text files and converts them into `.html` files.

## Usage
Download `SauSaGe.exe` and execute in command line interface using options.

## Options
`-v` or `--version` - display the application name and version

`-h` or `--help` - display application options

`-i` or `--input` - set the input file/directory

`-o` or `--output` - set the output directory (dist by default)

## Usage Examples 
`SauSaGe -i textFile.txt`

`SauSaGe -i inputDir`

`SauSaGe -i inputDir -o outputDir`

## Optional Requirements Implemented
1. Parses title from input files, changes HTML page title and header accordingly.

2. `-o` and `--output` options allow specification of output directory.

4. Recursively searches directory structure for text files and converts all of them into `.html` files.
