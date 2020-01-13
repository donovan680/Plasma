///////////////////////////////////////////////////////////////////////////////
///
/// \file EditorSettings.hpp
/// Declaration of the EditorSettings classes.
/// 
/// Authors: Joshua Claeys
/// Copyright 2013, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

namespace Plasma
{

static const real sViewCubeMinSize = 0.1f;
static const real sViewCubeMaxSize = 0.3f;

//--------------------------------------------------------------- EditorSettings
LightningDefineType(EditorSettings, builder, type)
{
  type->AddAttribute(ObjectAttributes::cCore);
  
  PlasmaBindComponent();
  PlasmaBindSetup(SetupMode::DefaultSerialization);
  PlasmaBindDocumented();
  LightningBindFieldProperty(mViewCube);
  LightningBindGetterSetterProperty(ViewCubeSize)->Add(new EditorSlider(sViewCubeMinSize, sViewCubeMaxSize, 0.01f));
  LightningBindFieldProperty(mAutoUpdateContentChanges);
}

//******************************************************************************
EditorSettings::EditorSettings()
{

}

//******************************************************************************
void EditorSettings::Serialize(Serializer& stream)
{
  SerializeNameDefault(mViewCube, true);
  SerializeNameDefault(mViewCubeSize, 0.1f);
  SerializeNameDefault(mAutoUpdateContentChanges, true);
}

real EditorSettings::GetViewCubeSize()
{
  return mViewCubeSize;
}

void EditorSettings::SetViewCubeSize(real size)
{
  mViewCubeSize = Math::Clamp(size, sViewCubeMinSize, sViewCubeMaxSize);
}

}//namespace Plasma
