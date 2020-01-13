///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Joshua Claeys
/// Copyright 2015, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Plasma
{

//------------------------------------------------------------------ Fill Layout
class UiFillLayout : public UiLayout
{
public:
  /// Meta Initialization.
  LightningDeclareType(UiFillLayout, TypeCopyMode::ReferenceType);

  /// Component Interface.
  void Initialize(CogInitializer& initializer) override;

  /// UiLayout Interface.
  Vec2 Measure(Rectangle& rect) override;
  void DoLayout(Rectangle& rect, UiTransformUpdateEvent* e) override;

  static void FillToParent(UiWidget* child);
  static void FillToRectangle(RectangleParam rect, UiWidget* widget);
};

}//namespace Plasma
