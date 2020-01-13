///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Joshua Claeys
/// Copyright 2015, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Plasma
{

//-------------------------------------------------------------- File Save State
class PlasmaShared FileModifiedState
{
public:
  FileModifiedState();

  static bool HasModifiedRecently(StringParam filePath);
  static bool HasModifiedSinceTime(StringParam filePath, TimeType time);

  static void BeginFileModified(StringParam filePath);
  static void EndFileModified(StringParam filePath);

private:
  static FileModifiedState* GetInstance();

  void Cleanup(TimeType currentTime);

  static float GetSecondsBetween(TimeType begin, TimeType end);

  // 1 as the TimeType means the file is currently open.
  typedef HashMap<String, TimeType> ModifiedMap;
  ModifiedMap mFileLastModified;
  ThreadLock mThreadLock;
  TimeType mLastCleanup;
};

}//namespace Plasma
