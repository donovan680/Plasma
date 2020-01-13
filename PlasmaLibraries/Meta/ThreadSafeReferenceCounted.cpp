///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Nathan Carlson
/// Copyright 2017, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

namespace Plasma
{

DefineThreadSafeReferenceCountedHandle(ThreadSafeReferenceCounted);

LightningDefineType(ThreadSafeReferenceCounted, builder, type)
{
  PlasmaBindThreadSafeReferenceCountedHandle();
}

ThreadSafeReferenceCounted::ThreadSafeReferenceCounted()
{
  ConstructThreadSafeReferenceCountedHandle();
}

ThreadSafeReferenceCounted::ThreadSafeReferenceCounted(const ThreadSafeReferenceCounted&)
{
  ConstructThreadSafeReferenceCountedHandle();
}

ThreadSafeReferenceCounted::~ThreadSafeReferenceCounted()
{
  DestructThreadSafeReferenceCountedHandle();
}

} // namespace Plasma
