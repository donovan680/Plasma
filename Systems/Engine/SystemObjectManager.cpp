///////////////////////////////////////////////////////////////////////////////
///
/// \file Engine.cpp
/// Implementation of the SystemObjectManager.
///
/// Authors: Chris Peters
/// Copyright 2010-2011, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

namespace Plasma
{

namespace PL
{
  SystemObjectManager* gSystemObjects;
}

SystemObjectManager::SystemObjectManager()
{
}

SystemObjectManager::~SystemObjectManager()
{
  forRange(ObjectInstance& objectInstance, Objects.Values())
  {
    if(objectInstance.Cleanup == ObjectCleanup::AutoDelete)
    {
      delete objectInstance.Instance;
    }
  }
}

void SystemObjectManager::Add(Object* object, BoundType* metaType, ObjectCleanup::Enum cleanup)
{
  ObjectInstance none = {object, metaType, cleanup};
  Objects.InsertOrError(metaType->Name, none);
}

void SystemObjectManager::Add(Object* object, ObjectCleanup::Enum cleanup)
{
  Add(object, LightningVirtualTypeId(object), cleanup);
}

void StartSystemObjects()
{
  PL::gSystemObjects = new SystemObjectManager();
}

void CleanUpSystemObjects()
{
  delete PL::gSystemObjects;
}

}
