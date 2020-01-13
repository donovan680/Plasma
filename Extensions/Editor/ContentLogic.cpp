///////////////////////////////////////////////////////////////////////////////
///
/// \file ContentLogic.cpp
/// 
///
/// Authors: Chris Peters
/// Copyright 2010-2012, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

namespace Plasma
{

ExtraLibrarySearchPathCallback mExtraLibrarySearchPaths = nullptr;

void LoadContentConfig(Cog* configCog)
{
  InitializeContentSystem();

  ContentSystem* contentSystem = PL::gContentSystem;

  MainConfig* mainConfig = configCog->has(MainConfig);

  Array<String>& librarySearchPaths = contentSystem->LibrarySearchPaths;
  ContentConfig* contentConfig = configCog->has(ContentConfig);
  String appCacheDirectory = GetUserLocalDirectory();
  String applicationDirectory = mainConfig->ApplicationDirectory;
  String documentDirectory = GetUserDocumentsDirectory();
  String workingDirectory = GetWorkingDirectory();

  
  String applicationName = mainConfig->ApplicationName;

  String sourceDirectory = mainConfig->SourceDirectory;

  if(contentConfig)
    librarySearchPaths.InsertAt(0, contentConfig->LibraryDirectories.All());

  CreateDirectoryAndParents(FilePath::Combine(appCacheDirectory, applicationName));

  //Add application directory resources if available
  if(!applicationDirectory.Empty())
  {
    librarySearchPaths.PushBack(FilePath::Combine(applicationDirectory, "Resources"));
  }

  //Add the source path for resources
  if(!sourceDirectory.Empty())
    librarySearchPaths.PushBack(FilePath::Combine(sourceDirectory, "Resources"));

  //Add working directory resources
  librarySearchPaths.PushBack(FilePath::Combine(workingDirectory, "Resources"));

  // Hack!
  if(mExtraLibrarySearchPaths != nullptr)
    mExtraLibrarySearchPaths(configCog, librarySearchPaths);

  //First try to use the tools directory specified in the user config
  if(contentConfig && !contentConfig->ToolsDirectory.Empty() && FileExists(contentConfig->ToolsDirectory))
    contentSystem->ToolPath = FilePath::Normalize(contentConfig->ToolsDirectory);
  else if(!sourceDirectory.Empty())
    //Use the build info version if it is not empty
    contentSystem->ToolPath = FilePath::Combine(sourceDirectory, "Tools");
  else if(!applicationDirectory.Empty())
    contentSystem->ToolPath = FilePath::Combine(applicationDirectory, "Tools");
  else
    //Just use working directory
    contentSystem->ToolPath = FilePath::Combine(workingDirectory, "Tools");

  contentSystem->mHistoryEnabled = contentConfig->HistoryEnabled;

  //To avoid conflicts of assets of different versions(especially when the version selector goes live)
  //set the content folder to a unique directory based upon the version number
  String revisionChangesetName = BuildString("PlasmaVersion", GetRevisionNumberString(), "-", GetChangeSetString());
  contentSystem->ContentOutputPath = FilePath::Combine(appCacheDirectory, "PlasmaContent", revisionChangesetName);

  // If we don't already have the content output directory, then see if we have local prebuilt content
  // that can be copied into the output directory (this is faster than building the content ourselves, if it exists).
  if (!DirectoryExists(contentSystem->ContentOutputPath))
  {
    String prebuiltContent = FilePath::Combine(applicationDirectory, "PrebuiltPlasmaContent");
    if (DirectoryExists(prebuiltContent))
    {
      ZPrint("Copying prebuilt content from '%s' to '%s'\n", prebuiltContent.c_str(), contentSystem->ContentOutputPath.c_str());
      CopyFolderContents(contentSystem->ContentOutputPath, prebuiltContent);
    }
  }

  contentSystem->SystemVerbosity = contentConfig->ContentVerbosity;
}

bool LoadContentLibrary(StringParam name, bool isCore)
{
  ContentLibrary* library = PL::gContentSystem->Libraries.FindValue(name, nullptr);
  if(library)
  {
    if(isCore)
      library->SetReadOnly(true);
    
    Status status;
    ResourcePackage package;
    PL::gContentSystem->BuildLibrary(status, library, package);

    if(status)
    {
      if(isCore)
      {
        forRange(ResourceEntry& entry, package.Resources.All())
        {
          if(entry.mLibrarySource)
          {
            if(ContentEditorOptions* options = entry.mLibrarySource->has(ContentEditorOptions))
              entry.mLibrarySource->ShowInEditor = options->mShowInEditor;
            else
              entry.mLibrarySource->ShowInEditor = false;
          }
        }
      }

      Status status;
      PL::gResources->LoadPackage(status, &package);
      if(!status)
        DoNotifyError("Failed to load resource package.",status.Message);

      return (bool)status;
    }
    else
    {
      return false;
    }

    return true;
  }
  else
  {
    ZPrint("Failed to find core content library %s.\n", name.c_str());
    return false;
  }
}

//-------------------------------------------------------- Editor Package Loader
LightningDefineType(EditorPackageLoader, builder, type)
{
}

EditorPackageLoader::EditorPackageLoader()
{
  ConnectThisTo(PL::gContentSystem, Events::PackageBuilt, OnPackagedBuilt);
}

void EditorPackageLoader::OnPackagedBuilt(ContentSystemEvent* event)
{
  LoadPackage(PL::gEditor, PL::gEditor->mProject, event->mLibrary, event->mPackage);
}

bool EditorPackageLoader::LoadPackage(Editor* editor, Cog* projectCog, ContentLibrary* library,
                  ResourcePackage* package)
{
  ProjectSettings* project = projectCog->has(ProjectSettings);

  ResourceSystem* resourceSystem = PL::gResources;

  if(project->ProjectContentLibrary == library)
  {
    //Load all packages
    forRange(ResourcePackage* dependentPackage, PackagesToLoad.All())
    {
      Status status;
      ResourceLibrary* library = resourceSystem->LoadPackage(status, dependentPackage);
      if(!status)
        DoNotifyError("Failed to load resource package.",status.Message);

      project->SharedResourceLibraries.PushBack(library);
      delete dependentPackage;
    }
    PackagesToLoad.Clear();

    //Set the content library so Loading may try to create new content for
    //fixing old content elements.
    editor->mProjectLibrary = library;

    Status status;
    project->ProjectResourceLibrary = resourceSystem->LoadPackage(status, package);
    if(!status)
      DoNotifyError("Failed to load resource package.",status.Message);

    //?
    DoEditorSideImporting(package, nullptr);
    delete package;

    PL::gEditor->SetExploded(false, true);
    PL::gEditor->ProjectLoaded();
    return true;
  }
  else
  {
    PackagesToLoad.PushBack(package);
  }

  return false;
}

template<typename ManagerType>
void ShowBuiltInResource(StringParam name)
{
  Resource* resource = ManagerType::Find(name);
  if(resource && resource->mContentItem)
    resource->mContentItem->ShowInEditor = true;
}

bool LoadEditorContent(Cog* configCog)
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
  coreLibs.PushBack("UiWidget");
  coreLibs.PushBack("EditorUi");
  coreLibs.PushBack("Editor");

  forRange(String libraryName, coreLibs.All())
  {
    coreContent = coreContent && LoadContentLibrary(libraryName, true);
  }

  // Hack!
  if(mCustomLibraryLoader != nullptr)
    mCustomLibraryLoader(configCog);

  if(!coreContent)
  {
    FatalEngineError("Failed to load core content library for editor. Resources"
                     " need to be in the working directory.");
    return false;
  }

  //Show all default resources
  forRange(ResourceManager* manager, PL::gResources->Managers.Values())
  {
    if(manager->mCanCreateNew)
      ErrorIf(manager->mExtension.Empty(), "Must set an extension on %s", manager->GetResourceType()->Name.c_str());

    Resource* resource = manager->GetResource(manager->DefaultResourceName, ResourceNotFound::ReturnNull);
    if(resource && resource->mContentItem)
    {
      resource->mContentItem->ShowInEditor = true;

      // Moved default font to the Loading library for progress display
      ErrorIf(resource->mContentItem->mLibrary->Name != "PlasmaCore" && resource->mContentItem->mLibrary->Name != "Loading", 
        "Only resources that are in core can be defaults");
    }
    else
    {
      ErrorIf(!manager->mNoFallbackNeeded, "Failed to find default resource for resource type %s", 
              manager->mResourceTypeName.c_str());
    }
  }

  // The UVS on these need to be verified (currently they are incorrect)
  //MeshManager::Find("Cube")->PrimitiveShape = MeshPrimitiveShape::Box;
  //MeshManager::Find("Sphere")->PrimitiveShape = MeshPrimitiveShape::Sphere;
  //MeshManager::Find("Cylinder")->PrimitiveShape = MeshPrimitiveShape::Cylinder;

  float time = (float)timer.UpdateAndGetTime();
  ZPrint("Finished Loading Editor Content in %.2f\n", time);
  return true;
}

} // namespace Plasma
