////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// Authors: Joshua Claeys
/// Copyright 2017, DigiPen Institute of Technology
///
////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Plasma
{

//-------------------------------------------------------------------------------- Meta Net Property
class MetaNetProperty : public MetaAttribute
{
public:
  LightningDeclareType(MetaNetProperty, TypeCopyMode::ReferenceType);

  /// The net property type name.
  String mNetPropertyConfig;
  
  /// Desired net channel name.
  String mNetChannelConfig;
};

}//namespace Plasma
