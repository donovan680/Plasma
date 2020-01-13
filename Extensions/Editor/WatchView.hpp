///////////////////////////////////////////////////////////////////////////////
///
/// \file WatchView.hpp
/// 
/// 
/// Authors: Joshua Claeys
/// Copyright 2013, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Plasma
{

class TreeView;
class TreeEvent;
class WatchViewSource;
struct TreeFormatting;

class WatchView : public Composite
{
public:
  typedef SpriteFrame LightningSelf;

  WatchView(Composite* parent);
  ~WatchView();

private:
  void BuildFormat(TreeFormatting& formatting);

  TreeView* mTree;
  WatchViewSource* mSource;
};

}// Namespace Plasma
