///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Joshua Claeys
/// Copyright 2015, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Plasma
{

//------------------------------------------------------------------ Dock Layout
class UiDockLayout : public UiLayout
{
public:
  /// Meta Initialization.
  LightningDeclareType(UiDockLayout, TypeCopyMode::ReferenceType);

  /// Component Interface.
  void Initialize(CogInitializer& initializer) override;
  void Serialize(Serializer& stream) override;

  /// UiLayout Interface.
  Vec2 Measure(Rectangle& rect) override;
  void DoLayout(Rectangle& rect, UiTransformUpdateEvent* e) override;

  Vec2 mSpacing;
};

}//namespace Plasma
