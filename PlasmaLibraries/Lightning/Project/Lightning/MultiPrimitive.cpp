/**************************************************************\
* Author: Andrew Colean
* Copyright 2016, DigiPen Institute of Technology
\**************************************************************/

#include "Precompiled.hpp"

namespace Lightning
{
  LightningDefineType(MultiPrimitive, builder, type)
  {
    type->HandleManager = LightningManagerId(PointerManager);
  }

  MultiPrimitive::MultiPrimitive(BoundType* primitiveMemberType, size_t primitiveMemberCount)
    : PrimitiveMemberType(primitiveMemberType),
      PrimitiveMemberCount(primitiveMemberCount)
  {
  }
}
