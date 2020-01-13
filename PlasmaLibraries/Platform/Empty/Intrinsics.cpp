////////////////////////////////////////////////////////////////////////////////
/// Authors: Dane Curbow
/// Copyright 2018, DigiPen Institute of Technology
////////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

namespace Plasma
{

u32 CountTrailingZeros(u32 x)
{
  return CountTrailingZerosNonIntrinsic(x);
}

u32 CountLeadingZeros(u32 x)
{
  return CountLeadingZerosNonIntrinsic(x);
}

}// namespace Plasma
