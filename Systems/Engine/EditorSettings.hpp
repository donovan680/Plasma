///////////////////////////////////////////////////////////////////////////////
///
/// \file EditorSettings.hpp
/// Declaration of the EditorSettings classes.
/// 
/// Authors: Joshua Claeys, Chris Peters
/// Copyright 2013, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Plasma
{

class ContentLibrary;

//--------------------------------------------------------------- EditorSettings
class EditorSettings : public Component
{
public:
  LightningDeclareType(EditorSettings, TypeCopyMode::ReferenceType);

  /// Constructor.
  EditorSettings();

  /// Component Interface.
  void Serialize(Serializer& stream) override;

  real GetViewCubeSize();
  void SetViewCubeSize(real size);

  /// Show/hide the orientation view cube
  bool mViewCube;

  /// Size in pixels of the viewport the view cube is shown in
  real mViewCubeSize;
  bool mAutoUpdateContentChanges;
};


}//namespace Plasma
