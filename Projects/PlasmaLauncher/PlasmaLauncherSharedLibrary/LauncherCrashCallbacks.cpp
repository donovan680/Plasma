///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Joshua Davis
/// Copyright 2010-2014, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

namespace Plasma
{

// We want to avoid allocations, so store how many memory ranges we want to add to the crash dumper
MemoryRange gMemoryRanges[64] = { 0 };
size_t gMemoryRangeCount = 0;

// How many ranges we've written to the dump (re-entrant callback from mini dump)
size_t gMemoryRangesWritten = 0;

void LauncherCrashStartCallback(CrashInfo& info, void* userData)
{
  info.mDumpName = BuildString("PlasmaLauncherDump_", gEngineStartTime.c_str(), ".dmp");
  info.mLogName = BuildString("PlasmaLauncherLog_", gEngineStartTime.c_str(), ".txt");
  info.mStackName = BuildString("PlasmaLauncherStack_", gEngineStartTime.c_str(), ".txt");
  info.mModuleName = "PlasmaLauncher";
  info.mStripModules = true;

  //hide the window
  Editor* editor = PL::gEditor;
  if(editor != NULL)
  {
    RootWidget* rootWidget = editor->GetRootWidget();
    OsWindow* osWindow = rootWidget->GetOsWindow();
    osWindow->SetVisible(false);
  }
}

void LauncherCrashPreMemoryDumpCallback(void* userData)
{
}

bool LauncherCrashCustomMemoryCallback(MemoryRange& memRange, void* userData)
{
  if(gMemoryRangesWritten == gMemoryRangeCount)
    return false;

  memRange.Begin = gMemoryRanges[gMemoryRangesWritten].Begin;
  memRange.Length = gMemoryRanges[gMemoryRangesWritten].Length;
  ++gMemoryRangesWritten;
  return true;
}

void LauncherCrashLoggingCallback(CrashHandlerParameters& params, CrashInfo& info, void* userData)
{
  String tempDirectory = GetTemporaryDirectory();
  
  //Get the log file
  String logFileName = FilePath::Combine(tempDirectory, info.mLogName);
  Console::FlushAll();

  //close the file listener so that there's no race condition on the log file.
  FileListener* fileListener = (FileListener*)userData;
  fileListener->Close();
  Console::Remove(fileListener);

  // Parameters that we provide to shell execute
  params.AddParameter("Log", logFileName.c_str());
}

String LauncherGetToolsPath()
{
  if(PL::gContentSystem && !PL::gContentSystem->ToolPath.Empty())
  {
    return FilePath::Combine(PL::gContentSystem->ToolPath, "PlasmaCrashHandler.exe");
  }
  else
  {
    return FilePath::Combine(GetApplicationDirectory(), "Tools", "PlasmaCrashHandler.exe");
  }
}

void LauncherSendCrashReport(CrashHandlerParameters& params, void* userData)
{
  params.AddParameter("Version", GetBuildIdString());
  params.AddParameter("Name", "Plasma Launcher");
  params.AddParameter("Guid", GetLauncherGuidString());
  params.AddParameter("Revision", GetRevisionNumberString());
  params.AddParameter("ChangeSet", GetChangeSetString());
  params.AddParameter("ChangeSetDate", GetChangeSetDateString());
  params.AddParameter("Configuration", GetConfigurationString());
  params.AddParameter("Platform", GetPlatformString());

  params.AddParameter("ExePath", GetApplication().Data());


  String paramString = params.GetParameterString();

  // Now shell out to our application and tell it to upload the dump

  String crashToolPathA = LauncherGetToolsPath();

  Status status;
  bool success = Os::SystemOpenFile(status, crashToolPathA.c_str(), NULL, paramString.c_str());
}

}//namespace Plasma
