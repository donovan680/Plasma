////////////////////////////////////////////////////////////////////////////////
///
/// Authors: Nathan Carlson
/// Copyright 2016, DigiPen Institute of Technology
///
////////////////////////////////////////////////////////////////////////////////
#pragma once

#define AddDeclarations(DebugObjectType)                              \
  static void Add(Debug::DebugObjectType& debugObject);               \
  static void Add(uint spaceId, Debug::DebugObjectType& debugObject); \
  static void Add(Space* space, Debug::DebugObjectType& debugObject);

namespace Plasma
{

class DebugDraw
{
public:
  LightningDeclareType(DebugDraw, TypeCopyMode::ReferenceType);
  typedef DebugDraw self_type;

  #define PlasmaDebugPrimitive(X) AddDeclarations(X);
  #include "Geometry/DebugPrimitives.inl"
  #undef PlasmaDebugPrimitive
};

} // namespace Plasma

#undef AddDeclarations
