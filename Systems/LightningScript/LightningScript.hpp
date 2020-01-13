///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Trevor Sundberg, Joshua Claeys
/// Copyright 2017, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Plasma
{

//-------------------------------------------------------------- LightningScript Resource
/// Lightning script file Resource.
class LightningScript : public LightningDocumentResource
{
public:
  LightningDeclareType(LightningScript, TypeCopyMode::ReferenceType);

  // DocumentResource Interface.
  void ReloadData(StringRange data) override;

  // ICodeInspector Interface.
  void GetKeywords(Array<Completion>& keywordsOut) override;

  // LightningDocumentResource Interface.
  void GetLibraries(Array<LibraryRef>& libraries) override;
  void GetLibrariesRecursive(Array<LibraryRef>& libraries, ResourceLibrary* library);
};

//------------------------------------------------------------- LightningScriptLoader
class LightningScriptLoader : public ResourceLoader
{
public:
  HandleOf<Resource> LoadFromFile(ResourceEntry& entry) override;
  HandleOf<Resource> LoadFromBlock(ResourceEntry& entry) override;
  void ReloadFromFile(Resource* resource, ResourceEntry& entry) override;
};

//------------------------------------------------------------- LightningScript Manager
// Resource manager for LightningScript
class LightningScriptManager : public ResourceManager
{
public:
  DeclareResourceManager(LightningScriptManager, LightningScript);

  LightningScriptManager(BoundType* resourceType);
  
  // ResourceManager Interface
  void ValidateNewName(Status& status, StringParam name, BoundType* optionalType) override;
  void ValidateRawName(Status& status, StringParam name, BoundType* optionalType) override;
  String GetTemplateSourceFile(ResourceAdd& resourceAdd) override;

  //Internals
  void OnResourceLibraryConstructed(ObjectEvent* e);

  static void DispatchScriptError(StringParam eventId, StringParam shortMessage, StringParam fullMessage, const CodeLocation& location);
  static void DispatchPlasmaLightningError(const CodeLocation& location, StringParam message, Project* buildingProject);
  
  static void OnMemoryLeak(MemoryLeakEvent* event);
  
  // We ignore duplicate exceptions until the version is incremented
  HashSet<String> mDuplicateExceptions;
  int mLastExceptionVersion;
};

}//namespace Plasma
