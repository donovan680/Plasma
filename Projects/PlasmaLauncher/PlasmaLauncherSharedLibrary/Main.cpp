///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Josh Davis
/// Copyright 2015, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

namespace Plasma
{

//Application Startup Function
bool PlasmaLauncherStartup(Engine* engine, StringMap& parameters, StringParam dllPath);

}//namespace Plasma

using namespace Plasma;

extern "C" PlasmaShared int RunPlasmaLauncher(const char* dllPath)
{
  // This is not quite correct, but since we don't have a
  // typical platform main we don't get everything initialized.
  Plasma::gCommandLineArguments.PushBack(FilePath::Combine(dllPath, "PlasmaLauncherSharedLibrary.dll"));

  //Set the log and error handlers so debug printing
  //and asserts will print to the Visual Studio Output Window.
  DebuggerListener debuggerOutput;
  Plasma::Console::Add(&debuggerOutput);
  
  //Mirror console output to a log file
  FileListener fileListener;
  // Change the base log file's name
  fileListener.mBaseLogFileName = "PlasmaLauncherLog_";
  Plasma::Console::Add(&fileListener);

  //Used custom dialog box
  ErrorSignaler::SetErrorHandler(Os::ErrorProcessHandler);

  //Enable the crash handler
  CrashHandler::Enable();
  CrashHandler::AppendToExtraSymbolPath(dllPath);

  CrashHandler::SetPreMemoryDumpCallback(Plasma::LauncherCrashPreMemoryDumpCallback, NULL);
  CrashHandler::SetCustomMemoryCallback(Plasma::LauncherCrashCustomMemoryCallback, NULL);
  CrashHandler::SetLoggingCallback(Plasma::LauncherCrashLoggingCallback, &fileListener);
  CrashHandler::SetSendCrashReportCallback(Plasma::LauncherSendCrashReport, NULL);
  CrashHandler::SetCrashStartCallback(Plasma::LauncherCrashStartCallback, NULL);

  ZPrint("Loading PlasmaLauncher %d.0.\n", GetLauncherMajorVersion());

  Environment* environment = Environment::GetInstance();
  environment->ParseCommandArgs(gCommandLineArguments);

  // Startup the engine
  PlasmaLauncherStartupSettings settings;
  settings.mTweakableFileName = "LauncherTweakables";
  settings.mEmbeddedPackage = false;
  settings.mDllPath = dllPath;

  // Startup the engine
  Plasma::LauncherStartup startup;
  Engine* engine = startup.Initialize(settings);

  // Check and see if another launcher is already open (has to happen after startup)
  Status status;
  String mutexId = BuildString("PlasmaLauncherMutex:{", GetLauncherGuidString(), "}");
  InterprocessMutex mutex;
  mutex.Initialize(status, mutexId.c_str(), true);
  if(status.Failed())
  {
    ZPrint("Mutex is already open. Sending a message to the open launcher and closing\n");
    Plasma::LauncherSingletonCommunication communicator(environment->mParsedCommandLineArguments);
    return 0;
  }

  CrashHandler::SetRestartCommandLine(environment->mCommandLine);
  
  //Run application startup
  bool success = Plasma::PlasmaLauncherStartup(engine, environment->mParsedCommandLineArguments, String(dllPath));
  //Failed startup do not run
  if(!success)
    return 0;

  // Return code of 0 means don't restart the launcher
  int returnCode = 0;
  //Run engine until termination
  engine->Run(false);

  // Check to see if we need to restart after we close (in order to update)
  // and if so change the return code to tell the exe.
  Cog* configCog = engine->GetConfigCog();
  LauncherConfig* config = configCog->has(LauncherConfig);
  if(config->mRestartOnClose)
    returnCode = 1;

  engine->Shutdown();
  // Free the launcher
  SafeDelete(PL::gLauncher);

  startup.Shutdown();

  ZPrint("Terminated\n");

  return returnCode;
}
