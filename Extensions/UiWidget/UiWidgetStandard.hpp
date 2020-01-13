///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Joshua Claeys
/// Copyright 2016, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

// External dependencies
#include "Engine/EngineStandard.hpp"
#include "Graphics/GraphicsStandard.hpp"
#include "Widget/WidgetStandard.hpp"
#include "Gameplay/GameplayStandard.hpp"

namespace Plasma
{

// UiWidget library
class PlasmaNoImportExport UiWidgetLibrary : public Lightning::StaticLibrary
{
public:
  LightningDeclareStaticLibraryInternals(UiWidgetLibrary, "PlasmaEngine");

  static void Initialize();
  static void Shutdown();
};

}//namespace Plasma

// Widget Core
#include "UiWidget.hpp"
#include "UiRootWidget.hpp"
#include "UiWidgetEvents.hpp"

// Layouts
#include "UiLayout.hpp"
#include "UiStackLayout.hpp"
#include "UiFillLayout.hpp"
#include "UiDockLayout.hpp"
