Open
C:\Program Files\Epic Games\UE_4.22\Engine\Source\Programs\UnrealBuildTool\Platform\Windows\VCToolChain.cs

Modify the following function as follows
void AppendCLArguments_CPP(CppCompileEnvironment CompileEnvironment, List<string> Arguments)
{
    if (Target.WindowsPlatform.Compiler != WindowsCompiler.Clang)
    {
        // Explicitly compile the file as C++.
        Arguments.Add("/TP");
        Arguments.Add("/std:c++17"); // newly added
        Arguments.Add("/EHsc");      // newly added
        // ... remaining codes
}


Open
C:\Program Files\Epic Games\UE_4.22\Engine\Source\Programs\UnrealBuildTool\UnrealBuildTool.csproj
and build the project

Recompile the UE project to work with C++17