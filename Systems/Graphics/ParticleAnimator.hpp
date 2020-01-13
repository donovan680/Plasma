///////////////////////////////////////////////////////////////////////////////
///
/// \file ParticleAnimator.hpp
/// Declaration of the Particle animator component classes.
///
/// Authors: Chris Peters
/// Copyright 2010-2012, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Plasma
{

/// Particle Animator Interface. Particle Animators effect particles in the system.
class ParticleAnimator : public Component
{
public:
  LightningDeclareType(ParticleAnimator, TypeCopyMode::ReferenceType);

  ParticleAnimator();

  void Initialize(CogInitializer& initializer) override;

  //Particle Animator Interface
  virtual void Animate(ParticleList* particleList, float dt, Mat4Ref transform) = 0;

  Link<ParticleAnimator> link;
  GraphicsSpace* mGraphicsSpace;
};

typedef InList<ParticleAnimator> AnimatorList;

} // namespace Plasma
