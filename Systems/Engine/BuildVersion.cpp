///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Chris Peters, Joshua Davis
/// Copyright 2010-2016, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

/// BuildVersion.inl file is updated by the build system based on the latest changeset and the build id files
#include "BuildVersion.inl"


#if PlasmaRelease
  #define PlasmaConfiguration "Release"
#elif PlasmaDebug
  #define PlasmaConfiguration "Debug"
#else
  #define PlasmaConfiguration "Unknown"
#endif


namespace Plasma
{

#define Stringify(s) InnerStringify(s)
#define InnerStringify(s) #s

#define WrapHex(a) InnerWrapHex(a)
#define InnerWrapHex(s) 0x##s##ULL

// Helper to stringify the build id's name conditionally on if there's an experimental branch
#ifdef PlasmaExperimentalBranchName
  #define PlasmaBuildIdString() \
    PlasmaExperimentalBranchName "." Stringify(PlasmaMajorVersion) "." Stringify(PlasmaMinorVersion) "." Stringify(PlasmaPatchVersion) "." Stringify(PlasmaRevisionId)
#else
  #define PlasmaBuildIdString() \
    Stringify(PlasmaMajorVersion) "." Stringify(PlasmaMinorVersion) "." Stringify(PlasmaPatchVersion) "." Stringify(PlasmaRevisionId)
#endif


cstr GetGuidString()
{
  return "F6E3D203-EB81-4B09-983C-31DAD32AE29F";
}

cstr GetLauncherGuidString()
{
  return "295EE6D2-9E03-43A6-8150-388649CC1341";
}

uint GetLauncherMajorVersion()
{
  // Hardcoded to 1 for all legacy versions. The first version on the new server will be 2
  return 4;
}

uint GetMajorVersion()
{
  return PlasmaMajorVersion;
}

uint GetMinorVersion()
{
  return PlasmaMinorVersion;
}

uint GetPatchVersion()
{
  return PlasmaPatchVersion;
}

uint GetRevisionNumber()
{
  return PlasmaRevisionId;
}

u64 GetShortChangeSet()
{
  return WrapHex(PlasmaShortChangeSet);
}

cstr GetExperimentalBranchName()
{
#ifdef PlasmaExperimentalBranchName
  return PlasmaExperimentalBranchName;
#else
  return nullptr;
#endif
}

cstr GetMajorVersionString()
{
  return Stringify(PlasmaMajorVersion);
}

cstr GetMinorVersionString()
{
  return Stringify(PlasmaMinorVersion);
}

cstr GetPatchVersionString()
{
  return Stringify(PlasmaPatchVersion);
}

cstr GetRevisionNumberString()
{
  return Stringify(PlasmaRevisionId);
}

cstr GetBuildIdString()
{
  return PlasmaBuildIdString();
}

cstr GetShortChangeSetString()
{
  return Stringify(PlasmaShortChangeSet);
}

cstr GetChangeSetString()
{
  return Stringify(PlasmaChangeSet);
}

cstr GetChangeSetDateString()
{
  return PlasmaChangeSetDate;
}

cstr GetConfigurationString()
{
  return PlasmaConfiguration;
}

cstr GetPlatformString()
{
  return PlasmaPlatform;
}

cstr GetBuildVersionName()
{
  return PlasmaBuildIdString() " " Stringify(PlasmaChangeSet) " " PlasmaChangeSetDate " " PlasmaConfiguration " " PlasmaPlatform;
}

int GetVersionId(StringParam versionIdFilePath)
{
  int localVersionId = -99;
  //make sure the file exists, if it doesn't assume the version is 0
  //(aka, the lowest and most likely to be replaced)
  if (FileExists(versionIdFilePath))
  {
    size_t fileSize;
    byte* data = ReadFileIntoMemory(versionIdFilePath.c_str(), fileSize, 1);
    data[fileSize] = 0;
    if (data == nullptr)
      return localVersionId;

    ToValue(String((char*)data), localVersionId);
    delete data;
  }
  return localVersionId;
}

}// namespace Plasma
