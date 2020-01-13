///////////////////////////////////////////////////////////////////////////////
///
/// \file Utilities.hpp
/// Declaration of the Utilities class.
/// 
/// Authors: Trevor Sundberg, Chris Peters
/// Copyright 2011, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Plasma
{
/// System Memory Information
struct PlasmaShared MemoryInfo
{
  uint Reserve;
  uint Commit;
  uint Free;
};

namespace Os
{

// Sleep the current thread for ms milliseconds.
PlasmaShared void Sleep(uint ms);

// Set the Timer Frequency (How often the OS checks threads for sleep, etc)
PlasmaShared void SetTimerFrequency(uint ms);

// Get the user name for the current profile
PlasmaShared String UserName();

// Get the computer name
PlasmaShared String ComputerName();

// Get computer Mac Address of adapter 0
PlasmaShared u64 GetMacAddress();

// Check if a debugger is attached
PlasmaShared bool IsDebuggerAttached();

// Output a message to any attached debuggers
PlasmaShared void DebuggerOutput(const char* message);

// Debug break (only if a debugger is attached)
PlasmaShared void DebugBreak();

// Attempts to enable memory leak checking (break on 
PlasmaShared void EnableMemoryLeakChecking(int breakOnAllocation = -1);

// When a diagnostic error occurs, this is the default response
PlasmaShared bool ErrorProcessHandler(ErrorSignaler::ErrorData& errorData);

// Verb used to open file
DeclareEnum4(Verb, Default, Open, Edit, Run);

// Open the file using the appropriate Os application or
// launch an external application.
PlasmaShared void SystemOpenFile(cstr file, uint verb=Verb::Default, cstr parameters = nullptr, cstr workingDirectory = nullptr);
PlasmaShared bool SystemOpenFile(Status& status, cstr file, uint verb=Verb::Default, cstr parameters = nullptr, cstr workingDirectory = nullptr);

// Open the network file (including urls) using the appropriate
// Os application or launch an external application
PlasmaShared void SystemOpenNetworkFile(cstr file, uint verb = Verb::Default, cstr parameters = nullptr, cstr workingDirectory = nullptr);
PlasmaShared bool SystemOpenNetworkFile(Status& status, cstr file, uint verb = Verb::Default, cstr parameters = nullptr, cstr workingDirectory = nullptr);

// Get the memory status of the Os.
PlasmaShared void GetMemoryStatus(MemoryInfo& memoryInfo);

// Get an Environmental variable
PlasmaShared String GetEnvironmentalVariable(StringParam variable);

// Get a string describing the current operating system version.
PlasmaShared String GetVersionString();

}

// Generate a 64 bit unique Id. Uses system timer and mac
// address to generate the id.
PlasmaShared u64 GenerateUniqueId64();

// Waits for expression to evaluate to true, checking approximately every pollPeriod (in milliseconds)
#define WaitUntil(expression, pollPeriod) \
do { while(!(expression)) { Os::Sleep(pollPeriod); } } while(gConditionalFalseConstant)

}//namespace Plasma
