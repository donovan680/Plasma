// Authors: Nathan Carlson
// Copyright 2015, DigiPen Institute of Technology

#pragma once

namespace Plasma
{

class ViewportInterface : public Component
{
public:
  virtual float GetAspectRatio() = 0;
  virtual Vec2 GetViewportSize() = 0;
  virtual void SendSortEvent(GraphicalSortEvent* event) = 0;
  virtual Cog* GetCameraCog() = 0;
};

} // namespace Plasma
