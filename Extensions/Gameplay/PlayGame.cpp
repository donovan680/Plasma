///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Joshua Davis, Chris Peters
/// Copyright 2015, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

namespace Plasma
{

CustomLibraryLoader mCustomLibraryLoader = nullptr;

void LoadResourcePackageRelative(StringParam baseDirectory, StringParam libraryName)
{
  String path = FilePath::Combine(baseDirectory, libraryName);
  String fileName = BuildString(libraryName, ".pack");
  String packageFile = FilePath::Combine(path, fileName);

  if(!FileExists(packageFile))
  {
    FatalEngineError("Failed to find needed content package. %s", libraryName.c_str());
  }

  ResourcePackage* package = new ResourcePackage();
  package->Load(packageFile);
  package->Location = path;

  Status status;
  PL::gResources->LoadPackage(status, package);
  if(!status)
    DoNotifyError("Failed to load resource package.",status.Message);
}

void GameRescueCall(void* userData)
{

}

void CreateGame(Cog* configCog, Cog* projectCog, StringParam projectFile)
{
  ZPrint("Loading in Game Mode.\n");

  CrashHandler::SetupRescueCallback(GameRescueCall, nullptr);

  String projectDirectory = FilePath::GetDirectoryPath(projectFile);

  OsShell* osShell = PL::gEngine->has(OsShell);
  ProjectSettings* project = projectCog->has(ProjectSettings);

  IntVec2 size = IntVec2(1280, 720);
  IntVec2 position = IntVec2(0, 0);

  WindowLaunchSettings* windowLaunch = projectCog->has(WindowLaunchSettings);
  if (windowLaunch != nullptr)
    size = windowLaunch->mWindowedResolution;

  // If changes are ever made to these flags, all platforms must be considered.
  WindowStyleFlags::Enum mainStyle = (WindowStyleFlags::Enum)(WindowStyleFlags::MainWindow | WindowStyleFlags::OnTaskBar | WindowStyleFlags::TitleBar | WindowStyleFlags::Resizable | WindowStyleFlags::Close);

  OsWindow* mainWindow = osShell->CreateOsWindow("MainWindow", size, position, nullptr, mainStyle);

  // On Emscripten, the window full screen can only be done by a user action.
  // Setting it on startup causes an abrupt change the first time the user click or hits a button.
#if !defined(PLATFORM_EMSCRIPTEN)
  if (windowLaunch == nullptr || windowLaunch->mLaunchFullscreen)
    mainWindow->SetState(WindowState::Fullscreen);
#endif

  //quick hack to make exports work better so they can trap the mouse
  PL::gMouse->mActiveWindow = mainWindow;

  mainWindow->SetTitle(project->ProjectName);

  // Pass window handle to initialize the graphics api
  PL::gEngine->has(GraphicsEngine)->CreateRenderer(mainWindow);
  PL::gEngine->has(GraphicsEngine)->SetSplashscreenLoading();

  ZPrint("Loading resource packages...\n");

  LoadResourcePackageRelative(projectDirectory, "FragmentCore");
  LoadResourcePackageRelative(projectDirectory, "Loading");
  LoadResourcePackageRelative(projectDirectory, "PlasmaCore");
  LoadResourcePackageRelative(projectDirectory, "UiWidget");
  LoadResourcePackageRelative(projectDirectory, "EditorUi");
  LoadResourcePackageRelative(projectDirectory, "Editor");

  // Hack!
  if(mCustomLibraryLoader != nullptr)
    mCustomLibraryLoader(configCog);

  if(SharedContent* sharedContent = projectCog->has(SharedContent))
  {
    forRange(ContentLibraryReference libraryRef, sharedContent->ExtraContentLibraries.All())
    {
      String libraryName = libraryRef.mContentLibraryName;
      LoadResourcePackageRelative(projectDirectory, libraryName);
    }
  }

  //Set the store name based on the project name.
  ObjectStore::GetInstance()->SetStoreName(project->ProjectName);

  LoadResourcePackageRelative(projectDirectory, project->ProjectName);

  // Make sure scripts in the project are compiled
  LightningManager::GetInstance()->TriggerCompileExternally();

  // Send after compiling since graphics uses this event to know to stop displaying the splash/loading screen
  ObjectEvent event(projectCog);
  PL::gEngine->DispatchEvent(Events::ProjectLoaded, &event);

  ZPrint("Creating game...\n");

  IntVec2 intViewportSize = mainWindow->GetClientSize();
  Vec2 mainViewportSize = Pixels(float(intViewportSize.x), float(intViewportSize.y));

  RootWidget* rootWidget = new RootWidget(mainWindow);
  rootWidget->SetSize(mainViewportSize);

  // In game mode only one widget that has the viewport
  GameWidget* gameWidget = new GameWidget(rootWidget);
  gameWidget->TakeFocus();
  gameWidget->SetSize(mainViewportSize);

  // Create the GameSession
  GameSession* game = PL::gEngine->CreateGameSession();
  game->mMainWindow = mainWindow;
  game->SetInEditor(false);
  
  game->mGameWidget = gameWidget;
  gameWidget->SetGameSession(game);

  game->Start();

  // Run all parsed command-line arguments once after the game is fully loaded.
  CommandManager* commandManager = CommandManager::GetInstance();
  commandManager->RunParsedCommands();
}

} // namespace Plasma
