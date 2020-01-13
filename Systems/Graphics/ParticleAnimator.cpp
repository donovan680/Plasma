///////////////////////////////////////////////////////////////////////////////
///
/// \file ParticleLogic.cpp
/// Implementation of the Particle system component classes.
///
/// Authors: Chris Peters
/// Copyright 2010-2012, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

namespace Plasma
{

LightningDefineType(ParticleAnimator, builder, type)
{
  PlasmaBindDocumented();
  PlasmaBindTag(Tags::Particle);
}

ParticleAnimator::ParticleAnimator()
  : mGraphicsSpace(nullptr)
{
}

void ParticleAnimator::Initialize(CogInitializer& initializer)
{
  mGraphicsSpace = GetSpace()->has(GraphicsSpace);
}

} // namespace Plasma
