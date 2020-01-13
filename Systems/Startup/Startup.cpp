///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Joshua Claeys
/// Copyright 2017, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

namespace Plasma
{

//------------------------------------------------------------------------------------------ Startup
//**************************************************************************************************
Engine* PlasmaStartup::Initialize(PlasmaStartupSettings& settings)
{
  InitializeLibraries(settings);
  return InitializeEngine();
}

//**************************************************************************************************
void PlasmaStartup::InitializeLibraries(PlasmaStartupSettings& settings)
{
  CommonLibrary::Initialize();

  // Temporary location for registering handle managers
  //LightningRegisterSharedHandleManager(ReferenceCountedHandleManager);
  LightningRegisterSharedHandleManager(CogHandleManager);
  LightningRegisterSharedHandleManager(ComponentHandleManager);
  LightningRegisterSharedHandleManager(ResourceHandleManager);
  LightningRegisterSharedHandleManager(WidgetHandleManager);
  LightningRegisterSharedHandleManager(ContentItemHandleManager);

  RegisterCommonHandleManagers();

  PlasmaRegisterHandleManager(ContentComposition);

  // Graphics specific
  PlasmaRegisterThreadSafeReferenceCountedHandleManager(ThreadSafeReferenceCounted);
  PlasmaRegisterThreadSafeReferenceCountedHandleManager(GraphicsBlendSettings);
  PlasmaRegisterThreadSafeReferenceCountedHandleManager(GraphicsDepthSettings);

  // Setup the core Lightning library
  mLightningSetup = new LightningSetup(SetupFlags::DoNotShutdownMemory);

  // We need the calling state to be set so we can create Handles for Meta Components
  Lightning::Module module;
  mState = module.Link();
  
#if !defined(PlasmaDebug) && !defined(PLATFORM_EMSCRIPTEN)
  mState->SetTimeout(5);
#endif

  ExecutableState::CallingState = mState;

  MetaDatabase::Initialize();

  // Add the core library to the meta database
  MetaDatabase::GetInstance()->AddNativeLibrary(Core::GetInstance().GetLibrary());

  // Initialize Plasma Libraries
  PlatformLibrary::Initialize();
  GeometryLibrary::Initialize();
  // Geometry doesn't know about the Meta Library, so it cannot add itself to the MetaDatabase
  MetaDatabase::GetInstance()->AddNativeLibrary(GeometryLibrary::GetLibrary());
  MetaLibrary::Initialize();
  SerializationLibrary::Initialize();
  ContentMetaLibrary::Initialize();
  SpatialPartitionLibrary::Initialize();

  EngineLibrary::Initialize(settings);
  GraphicsLibrary::Initialize();
  PhysicsLibrary::Initialize();
  NetworkingLibrary::Initialize();
  SoundLibrary::Initialize();

  WidgetLibrary::Initialize();
  GameplayLibrary::Initialize();
  EditorLibrary::Initialize();
  UiWidgetLibrary::Initialize();

  LightningScriptLibrary::Initialize();

  NativeBindingList::ValidateTypes();

  // Load documentation for all native libraries
  DocumentationLibrary::GetInstance()->LoadDocumentation(FilePath::Combine(PL::gEngine->GetConfigCog()->has(MainConfig)->DataDirectory, "Documentation.data"));

  ZPrint("Os: %s\n", Os::GetVersionString().c_str());
}

//**************************************************************************************************
Engine* PlasmaStartup::InitializeEngine()
{
  return PL::gEngine;
}

//**************************************************************************************************
void PlasmaStartup::Shutdown()
{
  Plasma::TimerBlock block("Shutting down Libraries.");

  Core::GetInstance().GetLibrary()->ClearComponents();

  // Shutdown in reverse order
  LightningScriptLibrary::Shutdown();

  UiWidgetLibrary::Shutdown();
  EditorLibrary::Shutdown();
  GameplayLibrary::Shutdown();
  WidgetLibrary::Shutdown();

  SoundLibrary::Shutdown();
  NetworkingLibrary::Shutdown();
  PhysicsLibrary::Shutdown();
  GraphicsLibrary::Shutdown();
  EngineLibrary::Shutdown();

  SpatialPartitionLibrary::Shutdown();
  ContentMetaLibrary::Shutdown();
  SerializationLibrary::Shutdown();
  MetaLibrary::Shutdown();
  GeometryLibrary::Shutdown();
  PlatformLibrary::Shutdown();
  
  // ClearLibrary
  LightningScriptLibrary::GetInstance().ClearLibrary();

  UiWidgetLibrary::GetInstance().ClearLibrary();
  EditorLibrary::GetInstance().ClearLibrary();
  GameplayLibrary::GetInstance().ClearLibrary();
  WidgetLibrary::GetInstance().ClearLibrary();

  SoundLibrary::GetInstance().ClearLibrary();
  NetworkingLibrary::GetInstance().ClearLibrary();
  PhysicsLibrary::GetInstance().ClearLibrary();
  GraphicsLibrary::GetInstance().ClearLibrary();
  EngineLibrary::GetInstance().ClearLibrary();

  SpatialPartitionLibrary::GetInstance().ClearLibrary();
  ContentMetaLibrary::GetInstance().ClearLibrary();
  SerializationLibrary::GetInstance().ClearLibrary();
  MetaLibrary::GetInstance().ClearLibrary();
  GeometryLibrary::GetInstance().ClearLibrary();

  // Destroy
  LightningScriptLibrary::Destroy();

  UiWidgetLibrary::Destroy();
  EditorLibrary::Destroy();
  GameplayLibrary::Destroy();
  WidgetLibrary::Destroy();

  SoundLibrary::Destroy();
  NetworkingLibrary::Destroy();
  PhysicsLibrary::Destroy();
  GraphicsLibrary::Destroy();
  EngineLibrary::Destroy();

  SpatialPartitionLibrary::Destroy();
  ContentMetaLibrary::Destroy();
  SerializationLibrary::Destroy();
  MetaLibrary::Destroy();
  GeometryLibrary::Destroy();

  LightningManager::Destroy();
  MetaDatabase::Destroy();
  
  delete mState;
  delete mLightningSetup;

  CommonLibrary::Shutdown();
}

}//namespace Plasma
