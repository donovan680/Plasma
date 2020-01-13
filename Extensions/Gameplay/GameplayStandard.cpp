///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Andrew Colean
/// Copyright 2016, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

#include "IndexedHalfEdgeMesh.hpp"
#include "QuickHull3DBindings.hpp"

namespace Plasma
{

// Enums
LightningDefineEnum(BrowserModifiers);
LightningDefineEnum(OrientationBases);
LightningDefineEnum(SplineAnimatorMode);

LightningDefineRange(IndexedHalfEdgeMeshVertexArray::RangeType);
LightningDefineRange(IndexedHalfEdgeMeshEdgeArray::RangeType);
LightningDefineRange(IndexedHalfEdgeFaceEdgeIndexArray::RangeType);
LightningDefineRange(IndexedHalfEdgeMeshFaceArray::RangeType);

//**************************************************************************************************
LightningDefineStaticLibrary(GameplayLibrary)
{
  builder.CreatableInScriptDefault = false;
  
  // Enums
  LightningInitializeEnumAs(BrowserModifiers, "WebBrowserModifiers");
  LightningInitializeEnum(OrientationBases);
  LightningInitializeEnum(SplineAnimatorMode);

  // Ranges
  LightningInitializeRangeAs(IndexedHalfEdgeMeshVertexArray::RangeType, "IndexedHalfEdgeMeshVertexArrayRange");
  LightningInitializeRangeAs(IndexedHalfEdgeMeshEdgeArray::RangeType, "IndexedHalfEdgeMeshEdgeArrayRange");
  LightningInitializeRangeAs(IndexedHalfEdgeFaceEdgeIndexArray::RangeType, "IndexedHalfEdgeFaceEdgeIndexArrayRange");
  LightningInitializeRangeAs(IndexedHalfEdgeMeshFaceArray::RangeType, "IndexedHalfEdgeMeshFaceArrayRange");

  // Events
  LightningInitializeType(MouseEvent);
  LightningInitializeType(MouseFileDropEvent);
  LightningInitializeType(ViewportMouseEvent);
  LightningInitializeType(WebBrowserEvent);
  LightningInitializeType(WebBrowserConsoleEvent);
  LightningInitializeType(WebBrowserCursorEvent);
  LightningInitializeType(WebBrowserDownloadEvent);
  LightningInitializeType(WebBrowserPopupCreateEvent);
  LightningInitializeType(WebBrowserPointQueryEvent);
  LightningInitializeType(WebBrowserTextEvent);
  LightningInitializeType(WebBrowserUrlEvent);

  LightningInitializeType(Viewport);
  LightningInitializeType(ReactiveViewport);
  LightningInitializeType(GameWidget);

  LightningInitializeType(WebBrowser);
  LightningInitializeType(WebBrowserSetup);
  LightningInitializeType(WebBrowserManager);
  LightningInitializeType(WebBrowserWidget);
  LightningInitializeType(TileMapSource);
  LightningInitializeType(Reactive);
  LightningInitializeType(ReactiveSpace);
  LightningInitializeType(MouseCapture);
  LightningInitializeType(Orientation);
  LightningInitializeType(TileMap);
  LightningInitializeType(RandomContext);
  LightningInitializeType(CameraViewport);
  LightningInitializeType(DefaultGameSetup);

  LightningInitializeType(SplineParticleEmitter);
  LightningInitializeType(SplineParticleAnimator);

  LightningInitializeType(UnitTestSystem);
  LightningInitializeType(UnitTestEvent);
  LightningInitializeType(UnitTestEndFrameEvent);
  LightningInitializeType(UnitTestBaseMouseEvent);
  LightningInitializeType(UnitTestMouseEvent);
  LightningInitializeType(UnitTestMouseDropEvent);
  LightningInitializeType(UnitTestKeyboardEvent);
  LightningInitializeType(UnitTestKeyboardTextEvent);
  LightningInitializeType(UnitTestWindowEvent);

  LightningInitializeType(IndexedHalfEdgeMeshVertexArray);
  LightningInitializeType(IndexedHalfEdgeMeshEdgeArray);
  LightningInitializeType(IndexedHalfEdgeFaceEdgeIndexArray);
  LightningInitializeType(IndexedHalfEdgeMeshFaceArray);
  LightningInitializeType(IndexedHalfEdge);
  LightningInitializeType(IndexedHalfEdgeFace);
  LightningInitializeType(IndexedHalfEdgeMesh);
  LightningInitializeTypeAs(QuickHull3DInterface, "QuickHull3D");

  LightningInitializeTypeAs(PlasmaStatic, "Plasma");

  // @trevor.sundberg: The Gameplay and Editor libraries are co-dependent
  LightningTypeId(Editor)->AssertOnInvalidBinding = &IgnoreOnInvalidBinding;

  EngineLibraryExtensions::AddNativeExtensions(builder);
}

//**************************************************************************************************
void GameplayLibrary::Initialize()
{
  BuildStaticLibrary();
  MetaDatabase::GetInstance()->AddNativeLibrary(GetLibrary());

  InitializeResourceManager(TileMapSourceManager);

  WebBrowserManager::Initialize();
}

//**************************************************************************************************
void GameplayLibrary::Shutdown()
{
  GetLibrary()->ClearComponents();

  WebBrowserManager::Destroy();
}

} // namespace Plasma
