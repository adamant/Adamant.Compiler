# Adamant Compiler

A compiler for the [Adamant language](http://adamant-lang.org) that is in the process of being bootstrapped. The compiler currently compiles a small subset of the Adamant language to C++.  It is capable of compiling itself and a small test suite.  Additional language features are being implemented and the compiler code refactored to take advantages of them.

## Project Status: Alpha Active

The compiler is under active development. It is in a very early stage, and there are likely issues and limitations. APIs are subject to frequent breaking changes.

## Implementation Notes

The list of the currently [implemented language features](docs/ImplementedLanguageFeatures.md) can be found in the docs directory.

## Contributing

Fork the project and then clone the repository.  Submit changes as a pull request.  Language features should have a test in the test suite for them.

The compiler translates into code that is compiled using the [clang++ compiler](https://clang.llvm.org) version 5.0.  Older versions of the C++ compiler may work, but this is not being tested and may change.  It builds on both Windows and Linux with CI builds on every commit in the repo.

Please read all of this section, particularly about the development cycle before attempting to contribute.

### Bootstrapping Structure

Because the Adamant compiler is being bootstrapped, there are multiple versions of the compiler that must be dealt with at any given time.  This can be confusing at first if one is not used to thinking about the bootstrapping process.  Many of the directories contain subdirectories for each version of the compiler.  The four versions of the compiler are:

  * **previous**:  the previous version of the compiler is used as a stable development environment for the next version of the compiler.
  * **current**: the version of the compiler being developed at any given time *as compiled by the previous version of the compiler*.
  * **bootstrapped**: to ensure that the current version doesn't introduce any breaking issues, it is used to recompile its own source.  The version produced is the bootstrapped version.
  * **double-bootstrapped**: to avoid some very unusual edge cases, the compiler is recompiled using the bootstrapped version to make sure that the same output is produced.

### Directory Structure

  * **src**: the source code of the compiler
  * **target**: where executable binaries are placed.  Contains a directory for each version of the compiler as well as a directory for the compiled test cases.
  * **test-cases**: contains Adamant code files representing test cases for the compiler functionality and matching C++ code files that are the expected output of the compiler for the given input.
  * **translated**: where the Adamant code that has been compiled to C++ is placed before compiling to binary.  Contains a directory for each version of the compiler and for the test cases.

### Build and Test Scripts

The build uses the [Cake build tool](https://cakebuild.net/) and runs cross platform.  To run the build on Linux or MacOS you will need [Mono](http://www.mono-project.com/) installed.  To build, simply run the Cake build tool either with the default target or the partigular target you want to build.

#### Building on Windows

From a Powershell command prompt at the root of the repo run:

	.\build.ps1

or:

	.\bulld.ps1 -Target <Target>

#### Building on Linux and MacOS

From the command prompt at the root of the repo run:

	./build.sh

or:

	./build.sh -Target=All

#### Build Targets

You can read the `build\build.cake` file to see the full list of targets.  The targets that will normally be used are:

  * **Default**: The default target, builds and tests both current and bootstrapped versions.
  * **Build-Current**: Just builds the current version.
  * **Test-Current**: Builds and tests the current version.
  * **Build-Bootstrapped**: Builds current and bootstrapped.
  * **Test-Bootstrapped**: Builds current and bootstrapped, then tests bootstrapped.
  * **Build-Expected**: Builds the expected C++ results of the test cases.  That is the `*.cpp` files in the `test-cases` directory.
  * **Run-Expected**: Builds and runs the expected C++ results of the test cases.  That is the `*.cpp` files in the `test-cases` directory.
  * **All**: This is what the CI build will check. Builds and tests all versions of the compiler. Also, builds and runs the expected results of the test cases.

###  Development Cycle

Since the compiler is being bootstrapped, the versions of the compiler discussed above must be managed.  Additionally, to avoid issues with trying to distributing binaries of the compiler for each commit, the C++ for each version is committed on a separate branch in the repository.  This enables someone to clone the repository, compile the C++ code and begin development.  When you build, you will be using the last version of the compiler that was published to the main repo.  Commits must be pushed to the main repo before the CI build can pick them up and check in the matching C++ source. That source is on a separate branch accessible only by tags.  As such, you will need to fetch tags by running `git fetch --tags` to get the built C++ code.

Several directories are intentionally not committed and are in the `.gitignore` file.  These are:

  * target
  * translated
