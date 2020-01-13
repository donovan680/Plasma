///////////////////////////////////////////////////////////////////////////////
///
/// \file TagsContent.Cpp
/// Implementation of the TagsContent content component.
/// 
/// Authors: Joshua Claeys
/// Copyright 2013, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"
#include "TagsContent.hpp"

namespace Plasma
{

//------------------------------------------------------------------------- Tags
LightningDefineType(ContentTags, builder, type)
{
  PlasmaBindComponent();
  PlasmaBindSetup(SetupMode::CallSetDefaults);
}

//******************************************************************************
void ContentTags::Serialize(Serializer& stream)
{
  SerializeName(mTags);
}

}// namespace Plasma
