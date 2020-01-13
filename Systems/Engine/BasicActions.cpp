///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Joshua Claeys
/// Copyright 2017, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

namespace Plasma
{

LightningDefineType(ActionDelay, builder, type)
{
  PlasmaBindDocumented();

  LightningBindField(mTimeLeft);
}

} // namespace Plasma
