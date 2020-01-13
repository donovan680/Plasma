///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Joshua Davis
/// Copyright 2017, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Plasma
{

bool PlasmaLauncherStartup(Engine* engine, StringMap& arguments, StringParam dllPath);

class PlasmaLauncherStartupSettings : public PlasmaStartupSettings
{
public:
  String mDllPath;
  Cog* LoadConfig() override;
};

/// Helper to initialize libraries for the launcher
class LauncherStartup : public PlasmaStartup
{
public:
  void Shutdown();

protected:
  void InitializeLibraries(PlasmaStartupSettings& settings) override;
};

}//namespace Plasma
