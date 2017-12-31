#addin nuget:?package=Cake.Git&version=0.16.1
#addin nuget:?package=Cake.FileHelpers&version=2.0.0

// Fix up the working directory to be the root of the project even though we are in build\
System.IO.Directory.SetCurrentDirectory(System.IO.Path.GetDirectoryName(System.IO.Directory.GetCurrentDirectory()));

var target = Argument("target", "Default");
string currentCommit = null;
string sourceCommit = null;

Task("Clean")
	.Does(() =>
	{
		CleanDirectory("translated");
		CleanDirectory("target");
	});

Task("Build-Previous")
	.IsDependentOn("Clean")
	.Does(() =>
	{
		var hasUncommitedChanges = ReadProcess("git", "status --porcelain=v2").Any();
		int generation;
		if(hasUncommitedChanges)
		{
			Information("Uncommitted changes, using current commit source");
			currentCommit = null; // There is no commit for the uncommitted changes
			sourceCommit = GitRevParse("HEAD");
			Information("Source commit is {0}", sourceCommit);
			generation = 1;
		}
		else
		{
			Information("NO uncommitted changes, using parent commit source");
			currentCommit = GitRevParse("HEAD");
			Information("Current commit is {0}", currentCommit);
			sourceCommit = GitRevParse("HEAD~1");
			Information("Source commit is {0}", sourceCommit);
			generation = 2;
		}

		var sourceExists = GitTagExists("translated/" + sourceCommit);
		if(!sourceExists)
		{
			Warning("No source for commit. Searching ancestors.");
			var found = false;
			for(; generation < 100; generation++)
			{
				sourceCommit = GitRevParse("HEAD~" + generation);
				if(GitTagExists("translated/" + sourceCommit))
				{
					Warning("Found source for HEAD~{0} {1}", generation, sourceCommit);
					found = true;
					break;
				}
			}
			if(!found)
			{
				Error("No source for previous");
				throw new Exception("Couldn't find source to use for Build-Previous of the compiler");
			}
		}

		Information("Getting source for previous");
		Verbose("Checking out translated from previous source branch"); // Git commands don't have verbose output
		GitCheckout(".", "translated/" + sourceCommit, new FilePath[] { "translated" });
		// Git checkout stanges the changes, we don't want that
		Verbose("Unstaging files staged by checkout"); // Git commands don't have verbose output
		GitUnstage(".", new FilePath[] { "translated" });
		MoveDirectory("translated/current", "translated/previous");

		Information("Compiling previous C++");
		EnsureDirectoryExists("target/previous");
		CompileCpp("translated/previous/*.cpp", "target/previous/Program");
	});

Task("Build-Current")
	.IsDependentOn("Clean")
	.IsDependentOn("Build-Previous")
	.Does(() =>
	{
		Information("Compiling Adamant to C++");
		EnsureDirectoryExists("translated/current");
		CompileAdamant("previous", "current");

		Information("Compiling current C++");
		EnsureDirectoryExists("target/current");
		CompileCpp("translated/current/*.cpp", "target/current/Program");
	});

Task("Test-Current")
	.IsDependentOn("Clean")
	.IsDependentOn("Build-Current")
	.Does(() =>
	{
		Test("current");
	});

Task("Build-Bootstrapped")
	.IsDependentOn("Clean")
	.IsDependentOn("Build-Current")
	.Does(() =>
	{
		Information("Compiling Adamant to C++");
		EnsureDirectoryExists("translated/bootstrapped");
		CompileAdamant("current", "bootstrapped");

		Information("Compiling bootstrapped C++");
		EnsureDirectoryExists("target/bootstrapped");
		CompileCpp("translated/bootstrapped/*.cpp", "target/bootstrapped/Program");
	});

Task("Test-Bootstrapped")
	.IsDependentOn("Clean")
	.IsDependentOn("Build-Bootstrapped")
	.Does(() =>
	{
		Test("bootstrapped");
	});

Task("Build-Double-Bootstrapped")
	.IsDependentOn("Clean")
	.IsDependentOn("Build-Bootstrapped")
	.Does(() =>
	{
		Information("Compiling Adamant to C++");
		EnsureDirectoryExists("translated/double-bootstrapped");
		CompileAdamant("bootstrapped", "double-bootstrapped");

		Information("Compiling double-bootstrapped C++");
		EnsureDirectoryExists("target/double-bootstrapped");
		CompileCpp("translated/double-bootstrapped/*.cpp", "target/double-bootstrapped/Program");

		Information("Verifying bootstrapped and double-bootstrapped are equal");
		var bootstrappedFiles = GetFiles("translated/bootstrapped/**/*");
		var bootstrappedDir = MakeAbsolute(Directory("translated/bootstrapped"));
		foreach(var bootstrappedFile in bootstrappedFiles)
		{
			var relativeBootstrappedFile = bootstrappedDir.GetRelativePath(bootstrappedFile);
			var expected = Directory("translated/bootstrapped") + relativeBootstrappedFile;
			var actual = Directory("translated/double-bootstrapped") + relativeBootstrappedFile;
			Verbose("Checking {0} matches {1}", expected, actual);
			if(FileReadText(expected) != FileReadText(actual))
			{
				Error("Double bootstrapped version does not match bootstrapped.");
				Error(" {0}", actual);
				throw new Exception("Double boostrapping failed");
			}
		}
	});

Task("Test-Double-Bootstrapped")
	.IsDependentOn("Clean")
	.IsDependentOn("Build-Double-Bootstrapped")
	.Does(() =>
	{
		Test("double-bootstrapped");
	});

// Builds all the expected values of the test cases
Task("Build-Expected")
	.IsDependentOn("Clean")
	.Does(() =>
	{
		var wd = MakeAbsolute(Directory("."));
		var testCases = GetFiles("test-cases/**/*.cpp");
		Information("Found {0} Test Case Expected Outputs", testCases.Count);
		foreach(var testCase in testCases)
		{
			var relativePath = wd.GetRelativePath(testCase);
			var outputDir = Directory("target") + relativePath.GetDirectory();
			EnsureDirectoryExists(outputDir);
			var output = outputDir + relativePath.GetFilenameWithoutExtension();
			CompileCpp(new []{ relativePath.ToString(), "src/*.cpp" }, output, "src");
		}
		Information("Compiled {0} Test Case Expected Outputs", testCases.Count);
	});

// Runs all the expected values of the test cases
Task("Run-Expected")
	.IsDependentOn("Build-Expected")
	.Does(() =>
	{
		var wd = MakeAbsolute(Directory("."));
		var testCases = GetFiles("target/test-cases/**/*");
		Information("Found {0} Test Cases to Execute", testCases.Count);
		foreach(var testCase in testCases)
		{
			var program = wd.GetRelativePath(testCase);
			Information("Running {0}", program);
			var result = RunProcess(program, "", false);
			Information("Exit Code is {0}", result);
			// TODO if we had a way to know what the expected exit code was, we could check
			// TODO we could also check the actual output
		}
		Information("Ran {0} Test Cases", testCases.Count);
	});

Task("Default")
	.IsDependentOn("Build-Current")
	.IsDependentOn("Test-Current")
	.IsDependentOn("Build-Bootstrapped")
	.IsDependentOn("Test-Bootstrapped");

Task("All")
	.IsDependentOn("Test-Current")
	.IsDependentOn("Run-Expected")
	.IsDependentOn("Test-Bootstrapped")
	.IsDependentOn("Test-Double-Bootstrapped");

Task("Commit-Translated")
	// technically, this is all that is needed,
	// really though, you should run All as CI does
	.IsDependentOn("Build-Current")
	.Does(() =>
	{
		if(currentCommit == null)
		{
			Error("Building uncommitted changes, can't commit translated");
			throw new Exception("Uncommitted changes");
		}

		if(AppVeyor.IsRunningOnAppVeyor && AppVeyor.Environment.PullRequest.IsPullRequest)
		{
			Warning("Not committing translated code becuase this is a pull request build.");
			return;
		}
		var deleteSettings = new DeleteDirectorySettings()
			{
				Recursive = true,
				Force = true,
			};

		Information("Saving off translated current");
		if(DirectoryExists("saved"))
			DeleteDirectory("saved", deleteSettings);
		MoveDirectory("translated/current", "saved");

		Information("Checking out previous source {0}", sourceCommit);
		GitCheckout(".", "translated/" + sourceCommit);

		Information("Restoring saved source");
		DeleteDirectory("translated/current", deleteSettings);
		MoveDirectory("saved", "translated/current");

		Information("Staging files");
		GitAdd(".", "translated/current");
		RunProcess("git", "status --untracked-files=no");

		Information("Commiting changes");
		// Allow empty commits so we can make a properly named commit to match each commit
		var message = string.Format("Translated files for {0}", currentCommit);
		RunProcess("git", string.Format("commit -m \"{0}\" --allow-empty --untracked-files=no", message));

		var tag = "translated/"+currentCommit;
		if(GitTagExists(tag))
		{
			Warning("Tag {0} already exists, not modifying", tag);
		}
		else
		{
			Information("Applying tag {0}", tag);
			GitTag(".", tag);
		}

		if(AppVeyor.IsRunningOnAppVeyor)
		{
			Information("Pushing tag to server");
			// Have to use the command line because of authentication
			RunProcess("git", "push origin " + tag);
		}
		else
		{
			Warning("Skipping push of tag becuase not running in AppVeyor");
		}
	});

Task("CI")
	.IsDependentOn("All")
	.IsDependentOn("Commit-Translated");

RunTarget(target);


bool GitTagExists(string tag)
{
	try
	{
		Verbose("Checking if tag '{0}' exists", tag);
		GitDescribe(".", tag, false, GitDescribeStrategy.Tags, 0);
		return true; // if it succedes the tag exists
	}
	catch(LibGit2Sharp.NotFoundException)
	{
		// tag doesn't exist
		return false;
	}
}

string GitRevParse(string revision)
{
	return ReadProcess("git", string.Format("rev-parse \"{0}\"", revision)).SingleOrDefault().ToLower();
}

void CompileAdamant(string sourceVersion, string targetVersion)
{
	var compiler = string.Format("target/{0}/Program", sourceVersion);
	var sources = GetFiles("src/**/*.ad");
	var output = string.Format("translated/{0}/Program.cpp", targetVersion);
	var resources = new FilePath[] { "src/RuntimeLibrary.cpp", "src/RuntimeLibrary.h" };
	CompileAdamant(compiler, sources, output, resources);
}

void CompileAdamant(FilePath compiler, IEnumerable<FilePath> sources, FilePath output, IEnumerable<FilePath> resources)
{
	var windows = IsRunningOnWindows();
	if(IsRunningOnWindows())
	{
		compiler = compiler.AppendExtension("exe");
	}
	// Make sure the paths are relative.  To handle either, we first make absolute then compute relative
	var wd = MakeAbsolute(Directory("."));
	var relativeSources = sources.Select(s => wd.GetRelativePath(MakeAbsolute(s)));
	var relativeResources = resources.Select(r => wd.GetRelativePath(MakeAbsolute(r)));
	RunProcess(compiler, string.Join(" ", relativeSources) + " -o " + output + string.Concat(relativeResources.Select(r => " -r " + r)));
	if(!FileExists(output))
	{
		Error("Compilation output file '{0}' not created.", output);
		throw new Exception("Adamant compilation failed");
	}
}

void CompileCpp(string sourceGlob, FilePath output, FilePath includeDirectory = null)
{
	CompileCpp(new [] { sourceGlob }, output, includeDirectory);
}

void CompileCpp(string[] sourceGlobs, FilePath output, FilePath includeDirectory = null)
{
	var options =  " -std=c++14";
	if(includeDirectory != null)
	{
		options += string.Format(" --include-directory \"{0}\"", includeDirectory);
	}
	if(IsRunningOnWindows())
	{
		output = output.AppendExtension("exe");
		options += " -Xclang -flto-visibility-public-std";
	}

	// Becuase wildcard expansion is handled by the shell on Linux and Cake StartProcess() always
	// sets UseShellExecute=false, we just expand the wildcards ourselves
	var wd = MakeAbsolute(Directory("."));
	var sources = string.Join(" ", sourceGlobs.SelectMany(glob => GetFiles(glob)).Select(file => wd.GetRelativePath(file)));

	RunProcess("clang++", sources + " -o " + output + options);
}

void Test(string version)
{
	Information("Compiling Adamant test cases to C++");
	var compiler = string.Format("target/{0}/Program", version);
	var testCases = GetFiles("test-cases/**/*.ad");
	var testCasesDir = MakeAbsolute(Directory("test-cases"));
	var outputDir = Directory(string.Format("translated/{0}-test-cases", version));
	foreach(var testCase in testCases)
	{
		var output = outputDir + testCasesDir.GetRelativePath(testCase).ChangeExtension("cpp");
		EnsureDirectoryExists(output.Path.GetDirectory());
		var resources = GetFiles(testCase.GetDirectory().ToString() + "/*.rsrc");
		CompileAdamant(compiler, new [] { testCase }, output, resources);
	}

	Information("Checking test cases for {0}", version);
	var expectedResults = GetFiles("test-cases/**/*.cpp");
	var total = 0;
	var failed = 0;
	foreach(var expected in expectedResults)
	{
		total++;
		var relativeToExpected = testCasesDir.GetRelativePath(expected);
		var actual = outputDir + relativeToExpected;
		var testCase = relativeToExpected.ChangeExtension("ad");
		if(!FileExists(actual))
		{
			Error("  {0} [FAIL]", testCase);
			Information("    {0} does not exist.", actual);
			failed++;
		}
		else if(FileReadText(expected) != FileReadText(actual))
		{
			Error("  {0} [FAIL]", testCase);
			Information("    {0} does not match expected.", actual);
			failed++;
		}
		else
		{
			Verbose("  {0} [PASS]", testCase);
		}
	}

	Information("=== TEST EXECUTION SUMMARY ===");
	Information("  Total: {0}, Failed: {1}", total, failed);
	if(failed > 0)
		throw new Exception("Test cases failed for " + version);
}

// Run a process and report an error on failure
int RunProcess(FilePath command, string args, bool checkResult = true)
{
	Verbose(command + " " + args);
	var result = StartProcess(command, args);
	if(checkResult && result != 0)
		throw new Exception("Exited with result: "+result);

	return result;
}

// Run a process, return the ouput and report an error on failure
IEnumerable<string> ReadProcess(FilePath command, string args)
{
	Verbose(command + " " + args);
	var process = StartAndReturnProcess(command, new ProcessSettings()
		{
			Arguments = args,
			RedirectStandardOutput = true,
		});
	process.WaitForExit();
	var result = process.GetExitCode();
	if(result != 0)
		throw new Exception("Exited with result: "+result);
	return process.GetStandardOutput();
}