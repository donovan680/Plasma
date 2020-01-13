///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Chris Peters
/// Copyright 2010-2013, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

namespace Plasma
{

namespace Events
{
  DefineEvent(CurrentInputDeviceChanged);
  DefineEvent(DebuggerPause);
  DefineEvent(DebuggerResume);
  DefineEvent(DebuggerPauseUpdate);
  DefineEvent(LoadingStart);
  DefineEvent(LoadingProgress);
  DefineEvent(LoadingFinish);
  DefineEvent(BlockingTaskStart);
  DefineEvent(BlockingTaskFinish);
}//namespace Events

namespace PL
{
  Engine* gEngine;
}

//******************************************************************************
void PlasmaDoNotify(StringParam title, StringParam message, StringParam icon, NotifyType::Enum type, NotifyException::Enum expections)
{
  if(type == NotifyType::Error)
  {
    fprintf(stderr, "Error: %s\n", message.c_str());
  }

  if(expections == NotifyException::Script)
    ExecutableState::CallingState->ThrowException(String::Format("%s: %s", title.c_str(), message.c_str()));

  // This would normally not be safe because in a threaded scenario, the gDispatch could be deleted between when we check
  // it and when we call Dispatch, however, the only threads that should be calling DoNotify are threads created by the job system
  // and those threads are shutdown before we delete the gDispatch, therefore the only thread that could call DoNotify after
  // would be the main thread (which is also the thread we are calling SafeDelete on the gDispatch)
  if(PL::gDispatch != nullptr)
  {
    Environment* environment = Environment::GetInstance();

    // Only pop up a notification if we aren't running UnitTests.
    if (!environment->mParsedCommandLineArguments.ContainsKey("RunUnitTests"))
    {
      NotifyEvent* event = new NotifyEvent();
      event->Name = title;
      event->Message = message;
      event->Icon = icon;
      event->Type = type;

      PL::gDispatch->Dispatch(PL::gEngine, Events::Notify, event);
    }    
  }
  
  ZPrintFilter(Filter::EngineFilter, "%s : %s\n", title.c_str(), message.c_str());
}

//-------------------------------------------------------------------Engine
bool Engine::sInLauncher = false;
//******************************************************************************
LightningDefineType(Engine, builder, type)
{
  type->HandleManager = LightningManagerId(PointerManager);

  PlasmaBindEvent(Events::EngineUpdate, UpdateEvent);
  PlasmaBindEvent(Events::CurrentInputDeviceChanged, UpdateEvent);

  LightningBindMethod(Terminate);
  LightningBindMethod(CreateGameSession);
  LightningBindMethod(CreateGameSessionFromArchetype);
  
  LightningBindMethod(GetCurrentInputDevice);
  LightningBindMethod(RebuildArchetypes);
  LightningBindGetter(GameSessions);
  
  LightningBindMethod(DebugBreak);
  LightningBindMethod(CrashEngine);
  
  type->Add(new EngineMetaComposition());
}

//******************************************************************************
Engine::Engine()
{
  PL::gNotifyCallbackStack.PushBack(PlasmaDoNotify);
  ErrorIf(PL::gEngine != nullptr, "Engine already created.");
  PL::gEngine = this;
  mEngineActive = true;
  mConfigCog = nullptr;
  mEngineSpace = nullptr;
  mTimeSystem = nullptr;
  mCurrentInputDevice = InputDevice::Mouse;
  mFrameCounter = 0;
  mHaveLoadingResources = false;
  mTimePassed = 0.0f;
  mAutoShutdown = false;
}

//******************************************************************************
Engine::~Engine()
{
}

//******************************************************************************
void Engine::Initialize(SystemInitializer& initializer)
{
  ZPrintFilter(Filter::DefaultFilter, "Initializing systems...\n");

  mConfigCog = initializer.Config;

  // Prevent components from being added or removed from the editor cog
  mConfigCog->mFlags.SetFlag(CogFlags::ScriptComponentsLocked);

  for(unsigned i = 0; i < mSystems.Size(); ++i)
  {
    System* system = mSystems[i];
    cstr systemName = system->GetName();
    TimerBlock time(systemName);
    ZPrintFilter(Filter::DefaultFilter, "Initializing %s...\n", systemName);
    system->Initialize(initializer);
  }

  PL::gSystemObjects->Add(this, LightningTypeId(Engine), ObjectCleanup::None);
  
  mTimeSystem = this->has(TimeSystem);
}

//******************************************************************************
void Engine::Run(bool autoShutdown)
{
  mAutoShutdown = autoShutdown;
  RunMainLoop(&Engine::MainLoopFunction, this);
}

//******************************************************************************
void Engine::MainLoopFunction(void* enginePointer)
{
  Engine* engine = (Engine*)enginePointer;

  if (!engine->mEngineActive)
  {
    if (engine->mAutoShutdown)
      engine->Shutdown();

    StopMainLoop();
    return;
  }

  engine->Update();
  YieldToOs();
}

//******************************************************************************
void Engine::Update()
{
  ProfileScope("Engine");

  PL::gTracker->ClearDeletedObjects();

  PL::gDispatch->DispatchEvents();

  LoadPendingLevels();

  // Update every system and tell each one how much
  // time has passed since the last update
  for(unsigned i = 0; i < mSystems.Size(); ++i)
  {
    mSystems[i]->Update();
  }

  float dt = mTimeSystem ? mTimeSystem->mEngineDt : 0.0f;
  mTimePassed += dt;
  UpdateEvent toSend(dt, dt, mTimePassed, 0);
  DispatchEvent(Events::EngineUpdate, &toSend);

  ++mFrameCounter;
}

//******************************************************************************
void Engine::Terminate()
{
  mEngineActive = false;
}

//******************************************************************************
GameSession* Engine::CreateGameSession()
{
  GameSession* game = (GameSession*)PL::gFactory->CreateCheckedType(LightningTypeId(GameSession), nullptr, 
    CoreArchetypes::Game, CreationFlags::Default, nullptr);

  return game;
}

//******************************************************************************
GameSession* Engine::CreateGameSessionFromArchetype(Archetype* archetype)
{
  CogCreationContext context;
  GameSession* game = (GameSession*)PL::gFactory->BuildFromArchetype(LightningTypeId(GameSession), archetype, &context);
  CogInitializer initializer(game->mSpace, game);
  
  if (game != nullptr)
    game->Initialize(initializer);

  initializer.AllCreated();

  return game;
}

//******************************************************************************
Engine::GameSessionArray::range Engine::GetGameSessions()
{
  return mGameSessions.All();
}

//******************************************************************************
void Engine::RebuildArchetypes(Archetype* archetype)
{
  ArchetypeRebuilder::RebuildArchetypes(archetype);
}

//******************************************************************************
void Engine::AddSystem(System* system)
{
  //Add a system to the core to be updated every frame
  mSystems.PushBack(system);

  BoundType* type = LightningVirtualTypeId(system);
  AddSystemInterface(type, system);
  PL::gSystemObjects->Add(system, type, ObjectCleanup::None);
}

//******************************************************************************
void Engine::AddSystemInterface(BoundType* typeId, System* system)
{
  mSystemMap.Insert(typeId, system);
}

//******************************************************************************
System* Engine::QueryComponentId(BoundType* typeId)
{
  return mSystemMap.FindValue(typeId, nullptr);
}

//******************************************************************************
void Engine::DestroySystems()
{
  // Delete all the systems in reverse order that they were added
  // in (to minimize any dependency problems between systems)
  for(unsigned i = 0; i < mSystems.Size(); ++i)
  {
    int reverseIndex = mSystems.Size() - i - 1;
    delete mSystems[reverseIndex];
  }
}

//******************************************************************************
Cog* Engine::GetConfigCog()
{
  return mConfigCog;
}

//******************************************************************************
ProjectSettings* Engine::GetProjectSettings()
{
  // Return the first project cog found in the engine space
  // (Note: This should be improved, but this works for now)
  forRange(Cog& cog, mEngineSpace->AllObjects())
  {
    if(ProjectSettings* project = cog.has(ProjectSettings))
      return project;
  }

  // No project cog found
  return nullptr;
}

//******************************************************************************
Space* Engine::GetEngineSpace()
{
  return mEngineSpace;
}

//******************************************************************************
Engine::SpaceListType::range Engine::GetSpaces()
{
  return mSpaceList.All();
}

//******************************************************************************
// This function should be removed and all Spaces (if not already) should belong to a GameSession
void Engine::DestroyAllSpaces()
{
  SpaceListType::range r = mSpaceList.All();
  while(!r.Empty())
  {
    r.Front().ForceDestroy();
    r.PopFront();
  }
}

//******************************************************************************
void Engine::LoadingStart()
{
  if (!mHaveLoadingResources || !SupportsRenderingOutsideMainLoop)
    return;

  Event toSend;
  DispatchEvent(Events::LoadingStart, &toSend);
}

//******************************************************************************
void Engine::LoadingUpdate(StringParam operation, StringParam currentTask, StringParam progress, ProgressType::Enum progressType, float percentage)
{
  if (!mHaveLoadingResources || !SupportsRenderingOutsideMainLoop)
    return;

  ProgressEvent progressEvent;
  progressEvent.ProgressType = progressType;
  progressEvent.Operation = operation;
  progressEvent.CurrentTask = currentTask;
  progressEvent.ProgressLine = progress;
  progressEvent.Percentage = percentage;

  DispatchEvent(Events::LoadingProgress, &progressEvent);
}

//******************************************************************************
void Engine::LoadingFinish()
{
  if (!mHaveLoadingResources || !SupportsRenderingOutsideMainLoop)
    return;

  Event toSend;
  DispatchEvent(Events::LoadingFinish, &toSend);
}

//******************************************************************************
InputDevice::Enum Engine::GetCurrentInputDevice()
{
  return mCurrentInputDevice;
}

//******************************************************************************
void Engine::SetCurrentInputDevice(InputDevice::Enum device)
{
  if (device == mCurrentInputDevice)
    return;

  InputDevice::Enum oldDevice = mCurrentInputDevice;
  mCurrentInputDevice = (InputDevice::Enum)device;

  // Send an event to let everyone know the input device that the user is using has changed
  InputDeviceEvent toSend;
  toSend.mDevice = device;
  toSend.mLastDevice = oldDevice;
  DispatchEvent(Events::CurrentInputDeviceChanged, &toSend);
}

//******************************************************************************
void Engine::Shutdown()
{
  Event event;
  DispatchEvent(Events::EngineShutdown, &event);

  DestroyAllSpaces();
  PL::gTracker->ClearDeletedObjects();

  // There could still be threaded events queued up. Make sure to delete all events
  // so that no events can use a destructed handle manager (such as ui widget handles
  // being destroyed after the widget system is shutdown).
  // Do NOT call ShutdownThreadSystem here because there are still systems that
  // are alive (and threaded) such as AsyncWebRequest that can be using gDispatch.
  PL::gDispatch->ClearEvents();
}

//******************************************************************************
void Engine::DebugBreak()
{
  Os::DebugBreak();
}

//******************************************************************************
void Engine::CrashEngine()
{
  memset((void*)PL::gEngine, 0xffffff, 9999);
  memset((void*)PL::gTracker, 0xffffff, 9999);
  memset(nullptr, 0xffffff, 9999);
}

//******************************************************************************
void Engine::LoadPendingLevels()
{
  forRange(Space& space, mSpaceList.All())
    space.LoadPendingLevel();
}

//-------------------------------------------------------------------EngineMetaComposition
//****************************************************************************
LightningDefineType(EngineMetaComposition, builder, type)
{
}

//****************************************************************************
EngineMetaComposition::EngineMetaComposition() : MetaComposition(LightningTypeId(System))
{

}

//****************************************************************************
uint EngineMetaComposition::GetComponentCount(HandleParam owner)
{
  Engine* engine = owner.Get<Engine*>(GetOptions::AssertOnNull);
  return engine->mSystems.Size();
}

//****************************************************************************
Handle EngineMetaComposition::GetComponent(HandleParam owner, BoundType* componentType)
{
  Engine* engine = owner.Get<Engine*>(GetOptions::AssertOnNull);
  return engine->QueryComponentId(componentType);
}

//****************************************************************************
Handle EngineMetaComposition::GetComponentAt(HandleParam owner, uint index)
{
  Engine* engine = owner.Get<Engine*>(GetOptions::AssertOnNull);
  return engine->mSystems[index];
}

//-------------------------------------------------------------------InputDeviceEvent
//******************************************************************************
LightningDefineType(InputDeviceEvent, builder, type)
{
  PlasmaBindDocumented();
  LightningBindFieldProperty(mDevice);
  LightningBindFieldProperty(mLastDevice);
}

//******************************************************************************
void FatalEngineError(cstr format, ...)
{
  va_list va;
  va_start(va, format);
  String message = String::FormatArgs(format, va);
  va_end(va);

  //Assert for developers
  ErrorIf(true, "%s", message.c_str());

  //Print for log
  ZPrint("%s", message.c_str());

  //Show Message Box 
  String finalMessage = BuildString(message, " The engine will now exit. If this issue persists please" 
                                              " reinstall Plasma Engine or contact support.");

  OsShell* shell = PL::gEngine->has(OsShell);
  shell->ShowMessageBox("Core Engine Error", finalMessage);

  //Terminate
  CrashHandler::FatalError(1);
}

}//namespace Plasma
