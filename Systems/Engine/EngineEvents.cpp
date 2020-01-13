///////////////////////////////////////////////////////////////////////////////
///
/// \file EngineEvents.cpp
/// Implementation of the basic event classes.
///
/// Authors: Chris Peters
/// Copyright 2010-2012, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

namespace Plasma
{

namespace Events
{
  DefineEvent(ScriptInitialize);
}//namespace Events

LightningDefineType(TextEvent, builder, type)
{
  LightningBindFieldProperty(Text);
}

LightningDefineType(TextErrorEvent, builder, type)
{
}

LightningDefineType(ProgressEvent, builder, type)
{
}

LightningDefineType(BlockingTaskEvent, builder, type)
{
}

//--------------------------------------------------------------- Progress Event
ProgressEvent::ProgressEvent()
{
  ProgressType = ProgressType::Normal;
  Percentage = 0.0f;
}

}//namespace Plasma
