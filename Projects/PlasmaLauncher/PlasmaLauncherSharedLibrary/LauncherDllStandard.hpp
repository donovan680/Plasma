///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Joshua Davis
/// Copyright 2017, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Startup/StartupStandard.hpp"

namespace Plasma
{
extern const String mLauncherRegularFont;
extern const String mLauncherBoldFont;

// LauncherDll library
class PlasmaNoImportExport LauncherDllLibrary : public Lightning::StaticLibrary
{
public:
  LightningDeclareStaticLibraryInternals(LauncherDllLibrary, "PlasmaEngine");

  static void Initialize();
  static void Shutdown();
};

}//namespace Plasma

#include "ForwardDeclarations.hpp"

#include "Standalone.hpp"
#include "VersionSelector.hpp"
#include "LauncherComponents.hpp"

#include "DeveloperNotes.hpp"
#include "Eula.hpp"
#include "Launcher.hpp"
#include "LauncherTasks.hpp"
#include "LauncherWindow.hpp"
#include "ProjectCache.hpp"
#include "TagFiltering.hpp"


// Widgets
#include "BuildStatus.hpp"

// Menus
#include "ActiveProjectMenu.hpp"
#include "BuildsMenu.hpp"
#include "DiscoverMenu.hpp"
#include "NewProjectMenu.hpp"
#include "RecentProjectsMenu.hpp"
#include "SettingsMenu.hpp"

#include "ExtraModals.hpp"

#include "LauncherStartup.hpp"
#include "LauncherCrashCallbacks.hpp"

