///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Dane Curbow, Trevor Sundberg
/// Copyright 2018, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

namespace Plasma
{
const bool ThreadingEnabled = false;

struct ThreadPrivateData
{
};

Thread::Thread()
{
  PlasmaConstructPrivateData(ThreadPrivateData);
}

Thread::~Thread()
{
  PlasmaDestructPrivateData(ThreadPrivateData);
}

bool Thread::IsValid()
{
  return false;
}

bool Thread::Initialize(EntryFunction entryFunction, void* instance, StringParam threadName)
{
  Error("Cannot initialize thread '%s' on a single threaded platform (check Plasma::ThreadingEnabled)", threadName.c_str());
  return false;
}

void Thread::Close()
{
}

OsInt Thread::WaitForCompletion()
{
  return 0;
}

OsInt Thread::WaitForCompletion(unsigned long milliseconds)
{
  return 0;
}

bool Thread::IsCompleted()
{
  return true;
}

OsHandle Thread::Detach()
{
  return nullptr;
}

OsHandle Thread::GetThreadHandle()
{
  return nullptr;
}

size_t Thread::GetThreadId()
{
  return 0;
}

size_t Thread::GetCurrentThreadId()
{
  return 0;
}

}//namespace Plasma
