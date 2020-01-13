///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Trevor Sundberg
/// Copyright 2018, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "CommonStandard.hpp"

namespace Plasma
{

int PlatformMain(const Array<String>& arguments)
{
  CommonLibrary::Initialize();
  int result = BrowserSubProcess::Execute();
  CommonLibrary::Shutdown();
  return result;
}

} // namespace Plasma