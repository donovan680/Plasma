///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Joshua Claeys
/// Copyright 2015, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

namespace Plasma
{

// Global Access
namespace PL
{
  Launcher* gLauncher = nullptr;
}

void OnLauncherTweakablesModified()
{
  Tweakables::Save();
}

IntVec2 Launcher::mEulaWindowSize = IntVec2(700, 520);
IntVec2 Launcher::mLauncherWindowSize = IntVec2(1024, 595);

//--------------------------------------------------------------------- Launcher
//******************************************************************************
Launcher::Launcher(Cog* configCog, StringMap& arguments) : 
  mConfigCog(configCog),
  mArguments(arguments)
{
  mOsWindow = nullptr;
  mMainWindow = nullptr;
  mEulaWindow = nullptr;
  mLauncherWindow = nullptr;
}

//******************************************************************************
void Launcher::Startup()
{
  mMainWindow = new MainWindow(mOsWindow);
  mMainWindow->SetTitle("");

  // Don't pre-open the launcher unless the user has accepted the eula.
  // Technically the launcher runs logic on initialize even if it is inactive
  // that shouldn't happen unless the user has first accepted the eula.
  
  // If the newest Eula has been accepted, show the Eula window.
  // Otherwise, set the launcher window to visible as it has already been created
  bool showEula = ShouldOpenEula();
  if(showEula)
    OpenEulaWindow();
  else
    OpenLauncherWindow();

  if(Os::IsDebuggerAttached())
    OpenTweakablesWindow();
}

//******************************************************************************
void Launcher::EulaAccepted()
{
  // There's some delay/resizing issues now, so first open the launcher and then
  // resize after we destroy the eula window. This helps minimize
  // (although not remove) popping and sizes not updating.
  OpenLauncherWindow();

  // Store that we've accepted the eula
  UserConfig* userConfig = HasOrAdd<UserConfig>(mConfigCog);
  userConfig->LastAcceptedEulaHash = GetEulaHash();
  SaveLauncherConfig(mConfigCog);
  mEulaWindow->SetActive(false);
  mEulaWindow->Destroy();
  mEulaWindow = nullptr;

  // Display the launcher
  mOsWindow->SetClientSize(mLauncherWindowSize);
  mOsWindow->SetMinClientSize(mLauncherWindowSize);

  // Re-center the window
  OsShell* osShell = PL::gEngine->has(OsShell);
  IntRect monitorRect = osShell->GetPrimaryMonitorRectangle();
  IntVec2 monitorClientPosition = monitorRect.Center(mLauncherWindowSize);
  mOsWindow->SetMonitorClientPosition(monitorClientPosition);
}

//******************************************************************************
void Launcher::OpenEulaWindow()
{
  mOsWindow->SetMinClientSize(mEulaWindowSize);
  mOsWindow->SetClientSize(mEulaWindowSize);
  
  EulaWindow* window = new EulaWindow(mConfigCog, mMainWindow);
  window->SetSizing(SizeAxis::Y, SizePolicy::Flex, 1);
  mEulaWindow = window;
}

void Launcher::Initialize()
{
  // Hack for BraveCobra
  Cog* configCog = mConfigCog;
  IntVec2 minClientSize = mLauncherWindowSize;
  // Ideally we should change the window size here, but the loading progress bar looks wrong with
  // the window of this size. Fix later when we can override the loading.
  //if(ShouldOpenEula())
  //  minWindowSize = mEulaWindowSize;

  String windowName = "Plasma Launcher";
  bool mainWindow = true;
  bool visible = true;

  OsShell* osShell = PL::gEngine->has(OsShell);
  IntRect monitorRect = osShell->GetPrimaryMonitorRectangle();

  IntVec2 clientSize = minClientSize;
  IntVec2 monitorClientPos = monitorRect.Center(clientSize);

  BitField<WindowStyleFlags::Enum> mainStyle;
  mainStyle.U32Field =
    WindowStyleFlags::OnTaskBar |
    WindowStyleFlags::TitleBar |
    WindowStyleFlags::Close |
    WindowStyleFlags::ClientOnly |
    WindowStyleFlags::Resizable;

  if(mainWindow)
    mainStyle.SetFlag(WindowStyleFlags::MainWindow);

  if(!visible)
    mainStyle.SetFlag(WindowStyleFlags::NotVisible);

  OsWindow* window = osShell->CreateOsWindow(windowName, clientSize, monitorClientPos, nullptr, mainStyle.Field);
  window->SetMinClientSize(minClientSize);
  window->SetState(WindowState::Windowed);
  mOsWindow = window;

  PL::gEngine->has(GraphicsEngine)->CreateRenderer(window);
  
  // Fix any issue for Intel Drivers
  window->PlatformSpecificFixup();
}

//******************************************************************************
void Launcher::OpenLauncherWindow()
{
  mOsWindow->SetTitle("Plasma Launcher");

  LauncherConfig* versionConfig = mConfigCog->has(LauncherConfig);
  
  LauncherWindow* launcher = new LauncherWindow(mMainWindow, mConfigCog);
  launcher->SetSizing(SizeAxis::Y, SizePolicy::Flex, 1);
  
  // If there were any command-line arguments then create an event to send to the launcher's ui
  if(mArguments.Empty() == false)
  {
    LauncherCommunicationEvent toSend;
    toSend.LoadFromCommandArguments(mArguments);
    if(toSend.EventId.Empty() == false)
      launcher->DispatchEvent(toSend.EventId, &toSend);
  }
  
  // If the user has no recent projects then display the new project's page
  RecentProjects* recentProjects = mConfigCog->has(RecentProjects);
  if(recentProjects == nullptr || recentProjects->GetRecentProjectsCount() == 0)
  {
    LauncherCommunicationEvent toSend;
    launcher->DispatchEvent(Events::LauncherNewProject, &toSend);
  }
  
  mLauncherWindow = launcher;
}

//******************************************************************************
void Launcher::OpenTweakablesWindow()
{
  return;
  OsShell* osShell = PL::gEngine->has(OsShell);
  IntRect monitorRect = osShell->GetPrimaryMonitorRectangle();
  IntVec2 size = IntVec2(230, monitorRect.SizeY);

  // Create a window to hold the tweakables (so they can be moved, closed, etc...)
  Window* tweakablesWindow = new Window(mMainWindow);
  tweakablesWindow->SetSize(Pixels(300, 500));
  PropertyView* propertyGrid = new PropertyView(tweakablesWindow);
  propertyGrid->SetObject(PL::gTweakables);
  propertyGrid->SetSize(Vec2(float(size.x), float(size.y)));

  // Set the tweakables modified callback so that we can update the Ui
  Tweakables::sModifiedCallback = &OnLauncherTweakablesModified;
}

//******************************************************************************
size_t Launcher::GetEulaHash()
{
  String eulaFile = GetEulaFilePath(mConfigCog);
  String eulaText = ReadFileIntoString(eulaFile);
  return eulaText.Hash();
}

//******************************************************************************
bool Launcher::ShouldOpenEula()
{
  UserConfig* userConfig = HasOrAdd<UserConfig>(mConfigCog);
  return userConfig->LastAcceptedEulaHash != GetEulaHash();
}

}//namespace Plasma
