///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Trevor Sundberg
/// Copyright 2018, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

namespace Plasma
{

static const u32 CtzLookupTable[] =
{
  8, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  7, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
};

u32 CountTrailingZerosNonIntrinsic(u32 x)
{
  u32 n = 0;
  if ((x & 0x0000FFFF) == 0) { n += 16; x >>= 16; }
  if ((x & 0x000000FF) == 0) { n +=  8; x >>=  8; }
  // if ((x & 0x0000000F) == 0) { n +=  4; x >>=  4; }
  // if ((x & 0x00000003) == 0) { n +=  2; x >>=  2; }
  // if ((x & 0x00000001) == 0) { n +=  1; }
  return n + CtzLookupTable[x & 0xFF];
}

u32 CountLeadingZerosNonIntrinsic(u32 x)
{
  u32 n = 0;
  if ((x & 0xFFFF0000) == 0) { n += 16; x <<= 16; }
  if ((x & 0xFF000000) == 0) { n +=  8; x <<=  8; }
  if ((x & 0xF0000000) == 0) { n +=  4; x <<=  4; }
  if ((x & 0xC0000000) == 0) { n +=  2; x <<=  2; }
  if ((x & 0x80000000) == 0) { n +=  1; }
  return n;
}

} // namespace Plasma
