///////////////////////////////////////////////////////////////////////////////
/// 
/// Authors: Joshua Davis
/// Copyright 2016, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Plasma
{
typedef void* OsHandle;
typedef unsigned long OsInt;
const OsHandle cInvalidHandle = (OsHandle)(0xFFFFFFFF);
const uint cDebugNameMax = 32;

class PlasmaShared StackHandle
{
public:
  StackHandle()
  {
    mHandle = cInvalidHandle;
  }

  ~StackHandle()
  {
    Close();
  }

  OsHandle Transfer()
  {
    OsHandle handle = mHandle;
    mHandle = cInvalidHandle;
    return handle;
  }

  void operator=(OsHandle handle)
  {
    mHandle = handle;
  }

  operator OsHandle()
  {
    return mHandle;
  }

  void Close();

  OsHandle mHandle;
};
}//namespace Plasma
