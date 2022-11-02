# Contributing
## Built using
[Visual Studio Community 2022](https://visualstudio.microsoft.com/vs/) - IDE

[Clang Power Tools](https://marketplace.visualstudio.com/items?itemName=caphyon.ClangPowerTools) - VS2022 extension for Editor clang-format, clang-tidy

**Command-line usage of clang requires clang components while installing VS2022:**

![install](https://user-images.githubusercontent.com/61764259/199850257-8936d373-3792-4489-a666-a1e16d36a508.PNG)

***
**Without VS2022**
[LLVM](https://releases.llvm.org/) - Command-line clang-format and clang-tidy

## Formatting
Refer to [this](https://www.clangpowertools.com/blog/getting-started-with-clang-format-style-options.html) link for details.

To run the formatter in the command-line
```
clang-format -i ./src/*
```
***
To run the formatter in VS2022:

![format](https://user-images.githubusercontent.com/61764259/199850275-afdde603-dbdc-4a59-8fd7-612b68b2fa0a.png)

Click this button in the toolbar.

## Linter
Refer to [this](https://clang.llvm.org/extra/clang-tidy/) link for details.

To run the linter in the command-line:
```
clang-tidy --config="" ./src/*
```
***
To run the linter in VS2022:

![format](https://user-images.githubusercontent.com/61764259/199850275-afdde603-dbdc-4a59-8fd7-612b68b2fa0a.png)

Click this button in the toolbar.
