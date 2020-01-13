///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Trevor Sundberg
/// Copyright 2016, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

namespace Plasma
{
  //LightningDeclareRange(Range);

  LightningDefineStaticLibrary(ScintillaMetaLibrary)
  {
    //LightningInitializeRange(Range);

    LightningInitializeType(TextEditor);

    //PlasmaBindEnum(LayoutDirection); // METAREFACTOR
  }
}
