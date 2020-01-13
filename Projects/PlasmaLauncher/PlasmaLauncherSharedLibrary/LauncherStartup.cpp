///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Josh Davis, Joshua Claeys
/// Copyright 2015, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

namespace Plasma
{

OsShell* CreateOsShellSystem();
System* CreateSoundSystem();
System* CreateGraphicsSystem();
System* CreatePhysicsSystem();
System* CreateTimeSystem();
System* CreateActionSystem();

bool LoadContent(Cog* configCog)
{
  PL::gContentSystem->DefaultBuildStream = new TextStreamDebugPrint();
  PL::gContentSystem->EnumerateLibraries();

  ZPrint("Loading Editor Content...\n");
  EditorPackageLoader* loader = EditorPackageLoader::GetInstance();

  Timer timer;
  timer.Update();

  String docDirectory = GetUserDocumentsDirectory();

  LoadContentLibrary("FragmentCore", true);
  bool coreContent = LoadContentLibrary("Loading", true);

  Array<String> coreLibs;
  
  coreLibs.PushBack("PlasmaCore");
  coreLibs.PushBack("PlasmaLauncherResources");

  forRange(String libraryName, coreLibs.All())
  {
    coreContent = coreContent && LoadContentLibrary(libraryName, true);
  }

  if(!coreContent)
  {
    FatalEngineError("Failed to load core content library for editor. Resources"
      " need to be in the working directory.");
    return false;
  }

  
  float time = (float)timer.UpdateAndGetTime();
  ZPrint("Finished Loading Editor Content in %.2f\n", time);
  return true;
}

bool LoadResources(Cog* configCog)
{
  LoadContentConfig(configCog);

  PL::gLauncher->Initialize();

  if(!LoadContent(configCog))
    return false;

  return true;
}

bool PlasmaLauncherStartup(Engine* engine, StringMap& arguments, StringParam dllPath)
{
  TimerBlock startUp("Engine Startup");
  String applicationName = "PlasmaVersionSelector";

  String project = GetStringValue<String>(arguments, "file", String());
  bool defaultConfig = GetStringValue<bool>(arguments, "safe", false);
  
  Cog* launcherConfigCog = PL::gEngine->GetConfigCog();
  
  SaveLauncherConfig(launcherConfigCog);

  //Profile initializing systems
  {
    TimerBlock block("Initializing core systems.");

    //Create all core systems
    engine->AddSystem(CreateUnitTestSystem());
    engine->AddSystem(CreateOsShellSystem());
    engine->AddSystem(CreateTimeSystem());
    engine->AddSystem(CreatePhysicsSystem());
    engine->AddSystem(CreateActionSystem());
    engine->AddSystem(CreateSoundSystem());
    engine->AddSystem(CreateGraphicsSystem());

    SystemInitializer initializer;
    initializer.mEngine = engine;
    initializer.Config = launcherConfigCog;

    //Initialize all systems.
    engine->Initialize(initializer);
  }

  Tweakables::Load("LauncherTweakables");

  PL::gLauncher = new Launcher(launcherConfigCog, arguments);
  LoadResources(launcherConfigCog);

  Event event;
  engine->DispatchEvent(Events::NoProjectLoaded, &event);

  // Start up the launcher
  PL::gLauncher->Startup();

  CommandManager* commands = CommandManager::GetInstance();
  BindAppCommands(launcherConfigCog, commands);
  commands->RunParsedCommands();

  // Extra debug stuff to test crashing
  if(arguments.ContainsKey("CrashEngine") && launcherConfigCog->has(DeveloperConfig))
  {
    CrashHandler::FatalError(1);
  }

  return true;
}

Cog* PlasmaLauncherStartupSettings::LoadConfig()
{
  Environment* environment = Environment::GetInstance();
  Cog* launcherConfigCog = LoadLauncherConfig(nullptr, environment->mParsedCommandLineArguments, true);
  ErrorIf(launcherConfigCog == nullptr, "Unable to load the launcher config");

  MainConfig* mainConfig = launcherConfigCog->has(MainConfig);
  mainConfig->ApplicationDirectory = mDllPath;
  //Also update the Data and Tools directory (if they exist, if they don't exist then we're likely
  //running in visual studio and we want the default behavior to run which will grab them from the source directory)
  String dataDir = FilePath::Combine(mDllPath, "Data");
  if(FileExists(dataDir))
    mainConfig->DataDirectory = dataDir;
  ContentConfig* contentConfig = launcherConfigCog->has(ContentConfig);
  String toolsDir = FilePath::Combine(mDllPath, "Tools");
  if(FileExists(toolsDir))
    contentConfig->ToolsDirectory = toolsDir;

  SaveLauncherConfig(launcherConfigCog);
  return launcherConfigCog;
}

void LauncherStartup::InitializeLibraries(PlasmaStartupSettings& settings)
{
  Engine::sInLauncher = true;

  // Initialize all of plasma's libraries
  PlasmaStartup::InitializeLibraries(settings);
  // Take care of our remaining libraries
  LauncherDllLibrary::Initialize();
}

void LauncherStartup::Shutdown()
{
  // Reverse order shutdown
  LauncherDllLibrary::Shutdown();
  LauncherDllLibrary::GetInstance().ClearLibrary();
  PlasmaStartup::Shutdown();
}

}//namespace Plasma
