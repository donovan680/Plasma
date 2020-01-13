///////////////////////////////////////////////////////////////////////////////
///  
///  Authors: Joshua Davis
///  Copyright 2014-2017, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

// Standard includes
#include "Common/CommonStandard.hpp"

#include "Lightning/Lightning.hpp"
using namespace Lightning;

namespace Geometry
{

using namespace Math;
using Plasma::Array;

}//namespace Geometry

namespace Plasma
{
#include "Math/MathImports.hpp"
using Geometry::Vec3Array;

typedef Array<Array<Vec2> > ContourArray;

namespace Csg
{
using Plasma::ContourArray;
}//namespace Csg

// Geometry library
class PlasmaNoImportExport GeometryLibrary : public Lightning::StaticLibrary
{
public:
  LightningDeclareStaticLibraryInternals(GeometryLibrary, "PlasmaEngine");

  static void Initialize();
  static void Shutdown();
};


}//namespace Plasma

namespace Intersection
{
using namespace Geometry;
using namespace Math;
}//namespace Intersection

namespace Csg
{
using namespace Geometry;
using namespace Math;
}//namespace Intersection

// Project includes
#include "Solids.hpp"
#include "Geometry.hpp"
#include "Intersection.hpp"
#include "Shapes.hpp"
#include "Aabb.hpp"
#include "Polygon.hpp"
#include "Clipper.hpp"
#include "Plane.hpp"
#include "Frustum.hpp"
#include "Sphere.hpp"
#include "DebugDraw.hpp"
#include "DebugDrawStack.hpp"
#include "IndexPool.hpp"
#include "TrapezoidMap.hpp"
#include "Triangulator.hpp"
#include "Shape2D.hpp"
#include "ConvexMeshShape.hpp"
#include "ConvexMeshDecomposition.hpp"
#include "ShapeHelpers.hpp"
#include "Geometry/Simplex.hpp"
#include "Geometry/Epa.hpp"
#include "Gjk.hpp"
#include "ExtendedCollision.hpp"
#include "ExtendedIntersection.hpp"
#include "GeodesicSphere.hpp"
#include "Hull2D.hpp"
#include "QuickHull3D.hpp"
#include "ToString.hpp"
