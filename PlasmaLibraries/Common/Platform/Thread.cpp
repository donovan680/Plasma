///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Trevor Sundberg
/// Copyright 2018, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

namespace Plasma
{
size_t Thread::MainThreadId = 0;

bool Thread::IsMainThread()
{
  return GetCurrentThreadId() == MainThreadId;
}
}//namespace Plasma
