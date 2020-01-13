///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Joshua Davis
/// Copyright 2017, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

namespace Plasma
{
const String mLauncherRegularFont = "NotoSans-Regular";
const String mLauncherBoldFont = "NotoSans-Bold";

LightningDefineEnum(LauncherStartupArguments);

//**************************************************************************************************
LightningDefineStaticLibrary(LauncherDllLibrary)
{
  builder.CreatableInScriptDefault = false;
  
  // Enums
  LightningInitializeEnum(LauncherStartupArguments);

  // Events
  LightningInitializeType(LauncherBuildEvent);

  // Components
  LightningInitializeType(PlasmaBuildContent);
  LightningInitializeType(PlasmaBuildReleaseNotes);
  LightningInitializeType(PlasmaBuildDeprecated);
  LightningInitializeType(PlasmaTemplate);
  LightningInitializeType(LauncherProjectInfo);
}

void LauncherDllLibrary::Initialize()
{
  BuildStaticLibrary();
  MetaDatabase::GetInstance()->AddNativeLibrary(GetLibrary());
}

void LauncherDllLibrary::Shutdown()
{

}

}//namespace Plasma
