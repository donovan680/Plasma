///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Chris Peters
/// Copyright 2015, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Plasma
{

class RootWidget;

class WidgetManager : public ExplicitSingleton<WidgetManager, EventObject>
{
public:
  LightningDeclareType(WidgetManager, TypeCopyMode::ReferenceType);

  WidgetManager();
  ~WidgetManager();

  u64 IdCounter;
  HashMap<u64, Widget*> Widgets;
  InList<RootWidget> RootWidgets;
  Array<Widget*> DestroyList;
  ActionSpace* mWidgetActionSpace;

  void CleanUp();
  void OnEngineUpdate(UpdateEvent* event);
  void OnShutdown(Event* event);
};

namespace PL
{
  extern WidgetManager* gWidgetManager;
}

}
