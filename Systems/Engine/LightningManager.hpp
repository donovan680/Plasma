////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// Authors: Trevor Sundberg, Joshua Claeys
/// Copyright 2017, DigiPen Institute of Technology
///
////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Plasma
{

namespace Events
{
// Sent out if scripts successfully compiled before setting mLibrary
DeclareEvent(ScriptsCompiledPrePatch);
// Sent out if scripts successfully compiled before setting mLibrary
// Sync point for other systems to commit their pending libraries
DeclareEvent(ScriptsCompiledCommit);
// Sent out immediately before 'ScriptsCompiledPostPatch', allowing the editor
// to build script objects back up before post patch event handlers execute.
DeclareEvent(ScriptsCompiledPatch);
// Sent out if scripts successfully compiled after setting mLibrary
DeclareEvent(ScriptsCompiledPostPatch);
// Sent if scripts failed to compile
DeclareEvent(ScriptCompilationFailed);
}

//------------------------------------------------------------------------------ Lightning Compile Event
class LightningCompileEvent : public Event
{
public:
  LightningDeclareType(LightningCompileEvent, TypeCopyMode::ReferenceType);
  LightningCompileEvent(HashSet<ResourceLibrary*>& modifiedLibraries);

  bool WasTypeModified(BoundType* type);
  BoundType* GetReplacingType(BoundType* oldType);

  HashSet<ResourceLibrary*>& mModifiedLibraries;
};

//------------------------------------------------------------------------------------ Lightning Manager
DeclareEnum2(CompileResult, CompilationFailed, CompilationSucceeded);

class LightningManager : public ExplicitSingleton<LightningManager, EventObject>
{
public:
  typedef LightningManager LightningSelf;
  typedef ExplicitSingleton<LightningManager, EventObject> LightningBase;

  /// Constructor.
  LightningManager();

  /// Compiles all Scripts and Fragments and allow duplicate errors to re-appear.
  void TriggerCompileExternally();

  /// Compiles all Scripts and Fragments.
  void InternalCompile();

  // If dirtied we attempt to compile every engine update (checks dirty flag)
  void OnEngineUpdate(UpdateEvent* event);

  // Tells the debugger to start hosting.
  void HostDebugger();

  // The last library we properly built (set inside CompileLoadedScriptsIntoLibrary)
  // Once this library becomes in use by an executable state, we CANNOT update it, or any LightningMeta types
  LibraryRef mCurrentFragmentProjectLibrary;
  LibraryRef mPendingFragmentProjectLibrary;

  // @TrevorS: We need to remove libraries from here if we remove them from the project.
  HashSet<ResourceLibrary*> mPendingLibraries;

  // If any scripts, fragments, or plugins have been modified we should attempt to compile once on engine update
  bool mShouldAttemptCompile;

  // We need to store the last result because we don't always attempt to recompile
  CompileResult::Enum mLastCompileResult;

  // Every time we recompile libraries we increment a version globally.
  // This lets us know elsewhere that anything related to types or scripts have changed.
  // For example: We prevent duplicate exceptions until this version changes.
  int mVersion;

  // The debugger interface that we register states with
  Debugger mDebugger;
};

}//namespace Plasma
