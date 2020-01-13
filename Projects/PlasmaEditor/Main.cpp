///////////////////////////////////////////////////////////////////////////////
///
/// \file WinMain.cpp
/// Entry Point and Initialization
///
/// Authors: Chris Peters
/// Copyright 2010-2012, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

namespace Plasma
{

//Application Startup Function
bool Startup(Engine* engine, StringMap& parameters, String projectFile);

void DebugRunEngine(void* voidEngine)
{
  Plasma::Engine* engine = (Plasma::Engine*)voidEngine;
  engine->Run();
}

int PlatformMain(const Array<String>& arguments)
{
  //Set the log and error handlers so debug printing
  //and asserts will print to the Visual Studio Output Window.
  DebuggerListener debuggerOutput;
  Plasma::Console::Add(&debuggerOutput);

  FileSystemInitializer fileSystemInitializer(&EngineLibrary::PopulateVirtualFileSystem);

  //Mirror console output to a log file
  FileListener fileListener;
  Plasma::Console::Add(&fileListener);

  TimerBlock totalEngineTimer("Total engine run time:");

  //This assert will bring up a dialog box.
  ErrorSignaler::SetErrorHandler(Os::ErrorProcessHandler);

  //Enable the crash handler
  CrashHandler::Enable();
  CrashHandler::SetPreMemoryDumpCallback(Plasma::CrashPreMemoryDumpCallback, NULL);
  CrashHandler::SetCustomMemoryCallback(Plasma::CrashCustomMemoryCallback, NULL);
  CrashHandler::SetLoggingCallback(Plasma::CrashLoggingCallback, &fileListener);
  CrashHandler::SetSendCrashReportCallback(Plasma::SendCrashReport, NULL);
  CrashHandler::SetCrashStartCallback(Plasma::CrashStartCallback, NULL);

  Importer importer;
  ImporterResult::Type importResult = importer.CheckForImport();
  if(importResult == ImporterResult::ExecutedAnotherProcess)
    return 1;

  // Initialize environments
  Environment* environment = Environment::GetInstance();
  environment->ParseCommandArgs(arguments);

  // Add stdout listener (requires engine initialization to get the Environment object)
  StdOutListener stdoutListener;
  if(!environment->GetParsedArgument("logStdOut").Empty())
    Plasma::Console::Add(&stdoutListener);

  String appDirectory = GetApplicationDirectory();
  String projectFile = FilePath::Combine(appDirectory, "Project.plasmaproj");
  
  // Fix the project file path for exports to be in the import's output directory
  bool embededPackage = (importResult == ImporterResult::Embeded);
  if(embededPackage)
    projectFile = FilePath::Combine(importer.mOutputDirectory, "Project.plasmaproj");

  // Startup the engine
  PlasmaStartupSettings settings;
  settings.mTweakableFileName = "EditorTweakables";
  settings.mEmbeddedPackage = embededPackage;
  settings.mEmbeddedWorkingDirectory = importer.mOutputDirectory;

  PlasmaStartup startup;
  Engine* engine = startup.Initialize(settings);

  //Run application specific startup
  bool success = Plasma::Startup(engine, environment->mParsedCommandLineArguments, projectFile);

  //Failed startup do not run
  if(!success)
    return 1;

  //Use this line to test the crash handler running in
  //visual studio and remove the line below
  //Plasma::RunEngine(DebugRunEngine, engine);
  
  //Run engine until termination
  engine->Run();

  startup.Shutdown();

  //Assert(!Plasma::Socket::IsSocketLibraryInitialized());

  // Uninitialize platform socket library
  Plasma::Status socketLibraryUninitStatus;
  Plasma::Socket::UninitializeSocketLibrary(socketLibraryUninitStatus);
  //Assert(!Plasma::Socket::IsSocketLibraryInitialized());

  ZPrint("Terminated\n");

  return 0;
}
} // namespace Plasma
