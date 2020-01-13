///////////////////////////////////////////////////////////////////////////////
///
/// \file Process.cpp
/// Declaration of the Process class.
///
/// Authors: Chris Peters
/// Copyright 2010-2012, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

namespace Plasma
{

struct ProcessPrivateData
{
};

Process::Process()
{
}

Process::~Process()
{
}

void Process::Start(Status& status, ProcessStartInfo& info)
{
}

void Process::Start(Status& status, StringRange commandLine, bool redirectOut,
                      bool redirectError, bool redirectIn, bool showWindow)
{
}

int Process::WaitForClose()
{
  return 0;
}

int Process::WaitForClose(unsigned long milliseconds)
{
  return 0;
}

bool Process::IsRunning()
{
  return false;
}

void Process::Close()
{
}

void Process::Terminate()
{
}

void Process::OpenStandardOut(File& fileStream)
{
}

void Process::OpenStandardError(File& fileStream)
{
}

void Process::OpenStandardIn(File& fileStream)
{
}

bool Process::IsStandardOutRedirected()
{
  return false;
}

bool Process::IsStandardErrorRedirected()
{
  return false;
}

bool Process::IsStandardInRedirected()
{
  return false;
}

void GetProcesses(Array<ProcessInfo>& results)
{
}

void KillProcess(OsInt processId, int exitCode)
{
}

void RegisterApplicationRestartCommand(StringParam commandLineArgs, uint flags)
{
}

}