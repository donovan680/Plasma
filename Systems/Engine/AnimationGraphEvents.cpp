///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Joshua Claeys
/// Copyright 2015, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

namespace Plasma
{

namespace Events
{
  DefineEvent(AnimationBlendEnded);
  DefineEvent(AnimationEnded);
  DefineEvent(AnimationLooped);
  DefineEvent(AnimationPostUpdate);
}//namespace Events

 //-------------------------------------------------------- Animation Graph Event
LightningDefineType(AnimationGraphEvent, builder, type)
{
  PlasmaBindDocumented();
  LightningBindFieldGetter(mAnimation);
  LightningBindFieldGetter(mNode);
  LightningBindFieldGetter(mPlayMode);
}

}//namespace Plasma
