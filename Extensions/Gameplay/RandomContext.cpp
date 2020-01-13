///////////////////////////////////////////////////////////////////////////////
///
/// \file RandomContext.cpp
///
/// Authors: Joshua Davis
/// Copyright 2013, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

namespace Plasma
{

LightningDefineType(RandomContext, builder, type)
{
  PlasmaBindComponent();
  PlasmaBindSetup(SetupMode::DefaultConstructor);
  PlasmaBindDocumented();

  LightningBindGetterSetterProperty(Seed);
  LightningBindFieldProperty(mRandomSeed);

  LightningBindGetterProperty(MaxInt);

  LightningBindMethod(Bool);
  LightningBindMethod(Int);
  LightningBindMethod(Float);
  LightningBindMethod(Real);
  LightningBindMethod(DoubleReal);
  LightningBindMethod(UnitVector2);
  LightningBindMethod(UnitReal2);
  LightningBindMethod(Vector2);
  LightningBindMethod(Real2);
  LightningBindMethod(UnitVector3);
  LightningBindMethod(UnitReal3);
  LightningBindMethod(Vector3);
  LightningBindMethod(Real3);
  LightningBindMethod(Quaternion);
  LightningBindMethod(RangeInclusiveMax);
  LightningBindMethod(RangeExclusiveMax);
  LightningBindMethod(IntVariance);
  LightningBindMethod(Range);
  LightningBindMethod(DoubleRange);
  LightningBindMethod(FloatVariance);
  LightningBindMethod(RealVariance);
  LightningBindMethod(DoubleRealVariance);
  LightningBindMethod(DieRoll);
  LightningBindMethod(Probability);
  LightningBindMethod(CoinFlip);
  LightningBindMethod(Rotation);
  LightningBindMethod(BellCurve);
  LightningBindMethod(BellCurveRange);
  LightningBindMethod(BellCurveDistribution);
}

void RandomContext::Serialize(Serializer& stream)
{
  SerializeNameDefault(mRandomSeed, true);

  uint Seed = mRandom.GetSeed();
  SerializeNameDefault(Seed, 0u);

  // If we're loading and we don't use a random seed then set the seed we just loaded
  if(stream.GetMode() == SerializerMode::Loading && mRandomSeed == false)
    mRandom.SetSeed(Seed);
}

uint RandomContext::GetSeed()
{
  return mRandom.GetSeed();
}

void RandomContext::SetSeed(uint seed)
{
  mRandom.SetSeed(seed);
}

int RandomContext::GetMaxInt()
{
  return Math::Random::cRandMax;
}

bool RandomContext::Bool()
{
  return mRandom.Bool();
}

int RandomContext::Int()
{
  return mRandom.Next();
}

float RandomContext::Float()
{
  return mRandom.Float();
}

float RandomContext::Real()
{
  return Float();
}

double RandomContext::DoubleReal()
{
  return mRandom.Double();
}

Vec2 RandomContext::UnitVector2()
{
  return mRandom.PointOnUnitCircle();
}

Vec2 RandomContext::UnitReal2()
{
  return UnitVector2();
}

Vec2 RandomContext::Vector2(float minLength, float maxLength)
{
  return mRandom.ScaledVector2(minLength, maxLength);
}

Vec2 RandomContext::Real2(float minLength, float maxLength)
{
  return Vector2(minLength, maxLength);
}

Vec3 RandomContext::UnitVector3()
{
  return mRandom.PointOnUnitSphere();
}

Vec3 RandomContext::UnitReal3()
{
  return UnitVector3();
}

Vec3 RandomContext::Vector3(float minLength, float maxLength)
{
  return mRandom.ScaledVector3(minLength, maxLength);
}

Vec3 RandomContext::Real3(float minLength, float maxLength)
{
  return Vector3(minLength, maxLength);
}

Quat RandomContext::Quaternion()
{
  return mRandom.RotationQuaternion();
}

int RandomContext::RangeInclusiveMax(int min, int max)
{
  if(min > max)
  {
    String msg = String::Format("The min value '%d' must be less than or equal to the max value '%d'", min, max);
    DoNotifyException("Invalid range", msg);
    return min;
  }
  return mRandom.IntRangeInIn(min, max);
}

int RandomContext::RangeExclusiveMax(int min, int max)
{
  if(min >= max)
  {
    String msg = String::Format("The min value '%d' must be less than the max value '%d'", min, max);
    DoNotifyException("Invalid range", msg);
    return min;
  }
  return mRandom.IntRangeInEx(min, max);
}

int RandomContext::IntVariance(int base, int variance)
{
  if(variance < 0)
  {
    String msg = String::Format("The variance value '%d' cannot be negative.", variance);
    DoNotifyException("Invalid variance", msg);
    return base;
  }
  return mRandom.IntVariance(base, variance);
}

float RandomContext::Range(float min, float max)
{
  return mRandom.FloatRange(min, max);
}

double RandomContext::DoubleRange(double min, double max)
{
  return mRandom.DoubleRange(min, max);
}

float RandomContext::FloatVariance(float base, float variance)
{
  return mRandom.FloatVariance(base, variance);
}

float RandomContext::RealVariance(float base, float variance)
{
  return FloatVariance(base, variance);
}

double RandomContext::DoubleRealVariance(double base, double variance)
{
  return mRandom.DoubleVariance(base, variance);
}

uint RandomContext::DieRoll(uint sides)
{
  if(sides == 0)
  {
    DoNotifyException("Invalid die roll", "Cannot roll a zero sided die");
    return 0;
  }

  return mRandom.DieRoll(sides);
}

bool RandomContext::Probability(float probOfTrue)
{
  return mRandom.Float() < probOfTrue;
}

bool RandomContext::CoinFlip()
{
  return mRandom.Bool();
}

Quat RandomContext::Rotation()
{
  return mRandom.RotationQuaternion();
}

float RandomContext::BellCurve()
{
  return mRandom.BellCurve(0.5f, 0.5f, 1.0f);
}

float RandomContext::BellCurveRange(float center, float range)
{
  return mRandom.BellCurve(center, range, 1.0f);
}

float RandomContext::BellCurveDistribution(float center, float range, float standardDeviation)
{
  return mRandom.BellCurve(center, range, standardDeviation);
}

} // namespace Plasma
