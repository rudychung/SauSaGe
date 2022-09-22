# SauSaGe
A Static Site Generator. Reads text files and converts them into `.html` files.

## Usage
Download `SauSaGe.exe` from the releases and execute in command line interface using options.

Must be executed from the directory where `SauSaGe.exe` is located. 

## Options
- `-v` or `--version` - display the application name and version
- `-h` or `--help` - display application options
- `-i` or `--input` - set the input file/directory
- `-o` or `--output` - set the output directory (`./dist` by default)

## Usage Examples 
- `SauSaGe -i textFile.txt`
- `SauSaGe -i inputDir`
- `SauSaGe -i inputDir -o outputDir`

## Optional Requirements Implemented
- Parses title from input files, changes HTML page title and header accordingly.
- `-o` and `--output` options allow specification of output directory.
- Recursively searches directory structure for text files and converts all of them into `.html` files.
- Creates an `index.html` file that links to the output files created if a directory is specified as input
- Also is able to read `.md` files, where it successfully uses Heading 1 and 2 (# and ##) features of Markdown
