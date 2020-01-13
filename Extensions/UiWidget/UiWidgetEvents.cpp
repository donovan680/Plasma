///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Chris Peters
/// Copyright 2015, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

namespace Plasma
{

namespace Events
{
  DefineEvent(UiFocusGainedPreview);
  DefineEvent(UiFocusLost);
  DefineEvent(UiFocusGained);
  DefineEvent(UiFocusLostHierarchy);
  DefineEvent(UiFocusGainedHierarchy);
  DefineEvent(UiFocusReset);

}//namespace Events

//------------------------------------------------------------------ Focus Event
//******************************************************************************
LightningDefineType(UiFocusEvent, builder, type)
{
  PlasmaBindDocumented();
  LightningBindFieldGetter(mReceivedFocus);
  LightningBindFieldGetter(mLostFocus);
}

//******************************************************************************
UiFocusEvent::UiFocusEvent(UiWidget* focusGained, UiWidget* focusLost)
  : mReceivedFocus(focusGained)
  , mLostFocus(focusLost)
{
}

}//namespace Plasma
