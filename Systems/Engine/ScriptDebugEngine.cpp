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
  DefineEvent(DebugBreak);
  DefineEvent(DebugException);
  DefineEvent(SyntaxError);
  DefineEvent(UnhandledException);
}//namespace Events


LightningDefineType(DebugEngineEvent, builder, type)
{
}

}//namespace Plasma
