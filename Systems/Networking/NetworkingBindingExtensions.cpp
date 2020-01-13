////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// Authors: Joshua Claeys
/// Copyright 2017, DigiPen Institute of Technology
///
////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

namespace Plasma
{

//-------------------------------------------------------------------------------- Meta Net Property
LightningDefineType(MetaNetProperty, builder, type)
{
  LightningBindField(mNetPropertyConfig)->AddAttribute(PropertyAttributes::cOptional);
  LightningBindField(mNetChannelConfig)->AddAttribute(PropertyAttributes::cOptional);
}

}//namespace Plasma
