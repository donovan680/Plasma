/**************************************************************\
* Author: Andrew Colean
* Copyright 2016, DigiPen Institute of Technology
\**************************************************************/

#pragma once
#ifndef LIGHTNING_MULTIPRIMITIVE_HPP
#define LIGHTNING_MULTIPRIMITIVE_HPP

namespace Lightning
{
  // Represents a type containing multiple primitives (ex. Real3 has 3 Real members)
  class PlasmaShared MultiPrimitive
  {
  public:
    LightningDeclareType(MultiPrimitive, TypeCopyMode::ReferenceType);

    MultiPrimitive(BoundType* primitiveMemberType, size_t primitiveMemberCount);

    BoundType* PrimitiveMemberType;
    size_t PrimitiveMemberCount;
  };
}

#endif
