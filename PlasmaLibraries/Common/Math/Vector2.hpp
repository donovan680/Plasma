///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Joshua Davis, Benjamin Strukus
/// Copyright 2010-2012, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Math/Reals.hpp"
#include "Math/BoolVector2.hpp"

namespace Math
{

struct Vector2;
typedef Vector2 Vec2;
typedef const Vector2& Vec2Param;
typedef Vector2& Vec2Ref;
typedef Vector2* Vec2Ptr;

//--------------------------------------------------------------------- Vector 2
/// Two dimensional vector.
struct PlasmaShared Vector2
{
  Vector2() {};
  explicit Vector2(real x, real y);
  explicit Vector2(real xy);
  explicit Vector2(ConstRealPointer data);

  real& operator[](uint index);
  real operator[](uint index) const;

  // Unary Operators
  Vector2 operator-() const;

  // Binary Operators (reals)
  void operator*=(real rhs);
  void operator/=(real rhs);
  Vector2 operator*(real rhs) const;
  Vector2 operator/(real rhs) const;

  // Binary Operators (vectors)
  void operator+=(Vec2Param rhs);
  void operator-=(Vec2Param rhs);
  void operator*=(Vec2Param rhs);
  void operator/=(Vec2Param rhs);
  Vector2 operator+(Vec2Param rhs) const;
  Vector2 operator-(Vec2Param rhs) const;
  Vector2 operator*(Vec2Param rhs) const;
  Vector2 operator/(Vec2Param rhs) const;

  // Comparison operators
  bool operator==(Vec2Param rhs) const;
  bool operator!=(Vec2Param rhs) const;
  BoolVec2 operator< (Vec2Param rhs) const;
  BoolVec2 operator<=(Vec2Param rhs) const;
  BoolVec2 operator> (Vec2Param rhs) const;
  BoolVec2 operator>=(Vec2Param rhs) const;

  /// Set all of elements to 0.
  void ZeroOut();
  /// Set each value of the vector.
  void Set(real x, real y);
  /// Set all elements to the same value.
  void Splat(real value);
  
  /// Compute the dot product of two vectors.
  static real Dot(Vec2Param lhs, Vec2Param rhs);
  /// Equivalent to Cross(Vec3(lhs.x, lhs.y, 0), Vec3(rhs.x, rhs.y, 0))
  static real Cross(Vec2Param lhs, Vec2Param rhs);
  /// Equivalent to Cross(Vec3(0, 0, lhs), Vec3(rhs.x, rhs.y, 0))
  static Vector2 Cross(real lhs, Vec2Param rhs);
  /// Equivalent to Cross(Vec3(lhs.x, lhs.y, 0), Vec3(0, 0, rhs))
  static Vector2 Cross(Vec2Param lhs, real rhs);
  /// Get the length of a vector.
  static real Length(Vec2Param value);
  /// Get the squared length of a vector.
  static real LengthSq(Vec2Param value);
  /// Compute the distance between two vectors.
  static real Distance(Vec2Param lhs, Vec2Param rhs);
  /// Compute the squared distance between two vectors.
  static real DistanceSq(Vec2Param lhs, Vec2Param rhs);
  /// Make the given vector have a length of 1, returns the original length.
  static real Normalize(Vec2Ref value);
  /// Calculate and return a unit-length copy of the given vector.
  static Vector2 Normalized(Vec2Param value);
  /// Try to normalize the given vector if possible. Safeguards against zero divisions.
  static real AttemptNormalize(Vec2Ref value);
  /// Attempts to return a normalized given vector. Safeguards against zero divisions.
  static Vector2 AttemptNormalized(Vec2Param value);

  /// Fused multiply add:  v0 + v1 * scalar
  static Vector2 MultiplyAdd(Vec2Param v0, Vec2Param v1, real scalar);
  /// Fused multiply subtract:  v0 - v1 * scalar
  static Vector2 MultiplySubtract(Vec2Param v0, Vec2Param v1, real scalar);

  /// Returns a copy of value with the absolute value of each element.
  static Vector2 Abs(Vec2Param value);
  /// Returns a vector with the component-wise min between two vectors.
  static Vector2 Min(Vec2Param lhs, Vec2Param rhs);
  /// Returns a vector with the component-wise max between two vectors.
  static Vector2 Max(Vec2Param lhs, Vec2Param rhs);
  /// Returns a vector where each component is clamped between min and max.
  static Vector2 Clamp(Vec2Param value, Vec2Param minValue, Vec2Param maxValue) ;
  /// Same as clamp, however it fills out whether or not anything was clamped.
  /// Useful when an assert message should be shown if anything was clamped.
  static Vector2 DebugClamp(Vec2Param value, Vec2Param minValue, Vec2Param maxValue, bool& wasClamped);

  /// Return a copy of this vector with each element has been floored.
  static Vector2 Floor(Vec2Param value);
  /// Return a copy of this vector with each element has been ceiled.
  static Vector2 Ceil(Vec2Param value);
  /// Return a copy of this vector with each element has been truncated.
  static Vector2 Truncate(Vec2Param value);
  /// Return a copy of this vector with each element has been rounded.
  static Vector2 Round(Vec2Param value);

  /// Linearly interpolate between the two vectors, the t-value is restricted to [0, 1].
  static Vector2 Lerp(Vec2Param start, Vec2Param end, real tValue);
  /// Spherical linear interpolation. Interpolates along the surface of the unit sphere.
  /// Normalizes input, checks for degenerate/ambiguous cases.
  static Vector2 Slerp(Vec2Param start, Vec2Param end, real tValue);
  /// Same as Slerp except this function assumes the user has deal with degenerate/ambiguous cases.
  /// Used when multiple calls are made to Slerp and the user wants to fix degeneracies once ahead of time.
  static Vector2 SlerpFast(Vec2Param start, Vec2Param end, real tValue);
  /// Same as Slerp except this function does not normalize the input vectors. This is the 'pure' mathematical
  /// Slerp function. This effectively traces along an ellipse defined by the two input vectors.
  static Vector2 SlerpUnnormalized(Vec2Param start, Vec2Param end, real tValue);

  /// Projects the input vector onto the given vector (must be normalized)
  static Vector2 ProjectOnVector(Vec2Param input, Vec2Param normalizedVector);
  /// Projects the input vector onto a plane (the normal must be normalized)
  static Vector2 ProjectOnPlane(Vec2Param input, Vec2Param planeNormal);
  /// Calculates the reflection vector across a given vector.
  static Vector2 ReflectAcrossVector(Vec2Param input, Vec2Param normalizedVector);
  /// Calculates the reflection vector across a given plane.
  static Vector2 ReflectAcrossPlane(Vec2Param input, Vec2Param planeNormal);
  /// Calculates the refraction vector through a plane given a certain index of refraction.
  static Vector2 Refract(Vec2Param input, Vec2Param planeNormal, real refractionIndex);
  /// Get the angle between the two vectors in radians.
  static real AngleBetween(Vec2Param a, Vec2Param b);

  /// Returns if all elements of the two vectors are within epsilon of each other
  static bool ApproximatelyEqual(Vec2Param lhs, Vec2Param rhs, real epsilon);
  /// Checks to see if the values of this vector's elements are usable.
  bool Valid() const;

  /// Compute the dot product of this vector with the given vector.
  real Dot(Vec2Param rhs) const;
  /// Computes the 2d cross-product (pretend the z-axis is zero).
  Vector2 Cross(Vec2Param rhs) const;
  /// Get the length of this vector.
  real Length() const;
  /// Get the squared length of this vector.
  real LengthSq() const;
  /// Compute the distance of this vector to the given one.
  real Distance(Vec2Param rhs) const;
  /// Compute the squared distance of this vector to the given one.
  real DistanceSq(Vec2Param rhs) const;
  /// Make this vector have a length of 1, returns the original length.
  real Normalize();
  /// Calculate and return a unit-length copy of this vector.
  Vector2 Normalized() const;
  /// Attempt to give this vector a length of 1, but checks if it's possible.
  /// Instead of crashing, will return 0 if the vector was not able to be 
  /// normalized.
  real AttemptNormalize();
  /// Attempts to return a normalized copy of this vector. Safeguards against zero divisions.
  Vector2 AttemptNormalized() const;

  /// Projects this vector onto the given vector (must be normalized)
  Vector2 ProjectOnVector(Vec2Param normalizedVector) const;
  /// Projects this onto a plane (the normal must be normalized)
  Vector2 ProjectOnPlane(Vec2Param planeNormal) const;
  /// Calculates the reflection vector across a given vector.
  Vector2 ReflectAcrossVector(Vec2Param normalizedVector) const;
  /// Calculates the reflection vector across a given plane.
  Vector2 ReflectAcrossPlane(Vec2Param planeNormal) const;
  /// Calculates the refraction vector through a plane given a certain index of refraction.
  Vector2 Refract(Vec2Param planeNormal, real refractionIndex) const;

  /// Flips this vector so it's pointing in the opposite direction.
  Vec2Ref Negate();

  union
  {
    struct
    {
      real x, y;
    };
    real array[2];
  };

  static const Vector2 cZero;
  static const Vector2 cXAxis;
  static const Vector2 cYAxis;
  static const Vector2 Axes[2];
};

PlasmaShared Vector2 operator*(real lhs, Vec2Param rhs);

/// Compute the dot product of two vectors.
PlasmaShared real Dot(Vec2Param lhs, Vec2Param rhs);
/// Equivalent to Cross(Vec3(lhs.x, lhs.y, 0), Vec3(rhs.x, rhs.y, 0))
PlasmaShared real Cross(Vec2Param lhs, Vec2Param rhs);
/// Equivalent to Cross(Vec3(0, 0, lhs), Vec3(rhs.x, rhs.y, 0))
PlasmaShared Vector2 Cross(real lhs, Vec2Param rhs);
/// Equivalent to Cross(Vec3(lhs.x, lhs.y, 0), Vec3(0, 0, rhs))
PlasmaShared Vector2 Cross(Vec2Param lhs, real rhs);
/// Get the length of a vector.
PlasmaShared real Length(Vec2Param value);
/// Get the squared length of a vector.
PlasmaShared real LengthSq(Vec2Param value);
/// Compute the distance between two vectors.
PlasmaShared real Distance(Vec2Param lhs, Vec2Param rhs);
/// Compute the squared distance between two vectors.
PlasmaShared real DistanceSq(Vec2Param lhs, Vec2Param rhs);
/// Make the given vector have a length of 1, returns the original length.
PlasmaShared real Normalize(Vec2Ref value);
/// Calculate and return a unit-length copy of the given vector.
PlasmaShared Vector2 Normalized(Vec2Param value);
/// Try to normalize the given vector if possible. Safeguards against zero divisions.
PlasmaShared real AttemptNormalize(Vec2Ref value);
/// Attempts to return a normalized given vector. Safeguards against zero divisions.
PlasmaShared Vector2 AttemptNormalized(Vec2Param value);

/// Fused multiply add:  v0 + v1 * scalar
PlasmaShared Vector2 MultiplyAdd(Vec2Param v0, Vec2Param v1, real scalar);
/// Fused multiply subtract:  v0 - v1 * scalar
PlasmaShared Vector2 MultiplySubtract(Vec2Param v0, Vec2Param v1, real scalar);

/// Returns a copy of value with the absolute value of each element.
PlasmaShared Vector2 Abs(Vec2Param value);
/// Returns a vector with the component-wise min between two vectors.
PlasmaShared Vector2 Min(Vec2Param lhs, Vec2Param rhs);
/// Returns a vector with the component-wise max between two vectors.
PlasmaShared Vector2 Max(Vec2Param lhs, Vec2Param rhs);
/// Returns a vector where each component is clamped between min and max.
PlasmaShared Vector2 Clamp(Vec2Param value, Vec2Param minValue, Vec2Param maxValue);
/// Same as clamp, however it fills out whether or not anything was clamped.
/// Useful when an assert message should be shown if anything was clamped.
PlasmaShared Vector2 DebugClamp(Vec2Param value, Vec2Param minValue, Vec2Param maxValue, bool& wasClamped);

/// Return a copy of this vector with each element has been floored.
PlasmaShared Vector2 Floor(Vec2Param value);
/// Return a copy of this vector with each element has been ceiled.
PlasmaShared Vector2 Ceil(Vec2Param value);
/// Return a copy of this vector with each element has been truncated.
PlasmaShared Vector2 Truncate(Vec2Param value);
/// Return a copy of this vector with each element has been rounded.
PlasmaShared Vector2 Round(Vec2Param value);

/// Linearly interpolate between the two vectors, the t-value is restricted to [0, 1].
PlasmaShared Vector2 Lerp(Vec2Param start, Vec2Param end, real tValue);
/// Spherical linear interpolation. Interpolates along the surface of the unit sphere.
/// Normalizes input, checks for degenerate/ambiguous cases.
PlasmaShared Vector2 Slerp(Vec2Param start, Vec2Param end, real tValue);
/// Same as Slerp except this function assumes the user has deal with degenerate/ambiguous cases.
/// Used when multiple calls are made to Slerp and the user wants to fix degeneracies once ahead of time.
PlasmaShared Vector2 SlerpFast(Vec2Param start, Vec2Param end, real tValue);
/// Same as Slerp except this function does not normalize the input vectors. This is the 'pure' mathematical
/// Slerp function. This effectively traces along an ellipse defined by the two input vectors.
PlasmaShared Vector2 SlerpUnnormalized(Vec2Param start, Vec2Param end, real tValue);

/// Projects the input vector onto the given vector (must be normalized)
PlasmaShared Vector2 ProjectOnVector(Vec2Param input, Vec2Param normalizedVector);
/// Projects the input vector onto a plane (the normal must be normalized)
PlasmaShared Vector2 ProjectOnPlane(Vec2Param input, Vec2Param planeNormal);
/// Calculates the reflection vector across a given vector.
PlasmaShared Vector2 ReflectAcrossVector(Vec2Param input, Vec2Param normalizedVector);
/// Calculates the reflection vector across a given plane.
PlasmaShared Vector2 ReflectAcrossPlane(Vec2Param input, Vec2Param planeNormal);
/// Calculates the refraction vector through a plane given a certain index of refraction.
PlasmaShared Vector2 Refract(Vec2Param input, Vec2Param planeNormal, real refractionIndex);
/// Get the angle between the two vectors in radians.
PlasmaShared real AngleBetween(Vec2Param a, Vec2Param b);

//-------------------------------------------------------------------Legacy

/// Clamps each component of a vector between min/max.
PlasmaShared void Clamp(Vec2Ptr vec, real min, real max);

/// Flips the given vector so it's pointing in the opposite direction.
PlasmaShared void Negate(Vec2Ptr vec);

/// Returns a vector pointing in the opposite direction of the given vector.
PlasmaShared Vector2 Negated(Vec2Param vec);

}// namespace Math
