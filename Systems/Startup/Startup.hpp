///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Joshua Claeys
/// Copyright 2017, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Plasma
{

//------------------------------------------------------------------------------------------ Startup
// Handles all platform agnostic initialization
class PlasmaStartup
{
public:
  Engine* Initialize(PlasmaStartupSettings& settings);
  void Shutdown();

protected:
  virtual void InitializeLibraries(PlasmaStartupSettings& settings);
  Engine* InitializeEngine();
  ExecutableState* mState;
  LightningSetup* mLightningSetup;
};

}//namespace Plasma
