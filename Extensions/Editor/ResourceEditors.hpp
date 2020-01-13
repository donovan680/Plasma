///////////////////////////////////////////////////////////////////////////////
///
/// \file ResourceEditors.hpp
/// 
///
/// Authors: Chris Peters
/// Copyright 2014, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once
namespace Plasma
{
class Editor;

typedef void (*EditResourceFunction)(Editor*,Resource*);

/// Store resource editors
class ResourceEditors : public ExplicitSingleton<ResourceEditors, Object>
{
public:
  LightningDeclareType(ResourceEditors, TypeCopyMode::ReferenceType);
  typedef HashMap<BoundType*, EditResourceFunction> ResourceEditorMap;
  ResourceEditorMap Editors;

  ResourceEditors();

  void FindResourceEditor(Resource* resource);
};

}
