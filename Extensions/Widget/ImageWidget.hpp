///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Chris Peters
/// Copyright 2015, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Plasma
{

class SlicedDefinition;

class ImageWidget : public Widget
{
public:
  LightningDeclareType(ImageWidget, TypeCopyMode::ReferenceType);

  SlicedDefinition* mDef;
  ImageWidget(Composite* parent, StringParam style, AttachType::Enum attachType = AttachType::Normal);

  Thickness GetBorderThickness() override;
  Vec2 GetMinSize() override;
  void ChangeDefinition(BaseDefinition* def) override;

  DisplayOrigin::Type GetDisplayOrigin();
  void SetDisplayOrigin(DisplayOrigin::Type displayOrigin);

  void RenderUpdate(ViewBlock& viewBlock, FrameBlock& frameBlock, Mat4Param parentTx, ColorTransform colorTx, WidgetRect clipRect) override;

  String GetDebugName() override;
};

}
