///////////////////////////////////////////////////////////////////////////////
/// Authors: Chris Peters, Joshua Claeys
/// Copyright 2010-2015, DigiPen Institute of Technology
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

namespace Plasma
{

DirectoryWatcher::DirectoryWatcher(cstr directoryToWatch, CallbackFunction callback, void* callbackInstance)
{
  PlasmaCStringCopy(mDirectoryToWatch, File::MaxPath, directoryToWatch, strlen(directoryToWatch));

  mCallbackInstance = callbackInstance;
  mCallback = callback;

  if (ThreadingEnabled)
  {
    mWorkThread.Initialize(Thread::ObjectEntryCreator<DirectoryWatcher, &DirectoryWatcher::RunThreadEntryPoint>, this, "DirectoryWatcherWorker");
    mCancelEvent.Initialize(true, false);
  }
}

DirectoryWatcher::~DirectoryWatcher()
{
  Shutdown();
}

void DirectoryWatcher::Shutdown()
{
  if (ThreadingEnabled)
  {
    mCancelEvent.Signal();
    mWorkThread.WaitForCompletion();
  }
}

}// namespace Plasma
