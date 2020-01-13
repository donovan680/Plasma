///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Joshua Davis
/// Copyright 2015, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Plasma
{

class HeightMap;
class UpdateEvent;

//-------------------------------------------------------------------HeightMapDebugDrawer
/// Helper class to draw information about a height map. Currently draws
/// triangles and is used by other debug helper classes.
class HeightMapDebugDrawer : public Component
{
public:
  LightningDeclareType(HeightMapDebugDrawer, TypeCopyMode::ReferenceType);

  HeightMapDebugDrawer();

  void Serialize(Serializer& stream) override;
  void Initialize(CogInitializer& initializer) override;
  void DebugDraw() override;

  void DrawPatch(IntVec2Param patchIndex);
  void DrawCell(IntVec2Param patchIndex, IntVec2Param cellIndex, bool skippedCell);
  void DrawRayProjection(Vec3Param start, Vec3Param dir, float maxT);
  void DrawAabbProjection(const Aabb& aabb);

  bool mDrawTriangles;
  real mDrawOffset;

  HeightMap* mMap;
  Transform* mTransform;
};

//-------------------------------------------------------------------HeightMapAabbChecker
/// Helper class to debug iterating over all triangles within an aabb. Uses the aabb of
/// the current object to test against the height-map specified by the given cogpath property.
class HeightMapAabbChecker : public Component
{
public:
  LightningDeclareType(HeightMapAabbChecker, TypeCopyMode::ReferenceType);

  HeightMapAabbChecker();

  void Serialize(Serializer& stream) override;
  void Initialize(CogInitializer& initializer) override;
  void OnAllObjectsCreated(CogInitializer& initializer) override;

  void OnFrameUpdate(UpdateEvent* e);
  void Draw();

  CogPath mHeightMapPath;
  bool mDrawHeightMap;
  bool mSkipNonCollidingCells;
};

}//namespace Plasma
