///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Joshua Davis, Chris Peters
/// Copyright 2015, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Plasma
{

class Cog;

// Hacks!!! Fix these later
typedef void(*CustomLibraryLoader)(Cog* configCog);
extern CustomLibraryLoader mCustomLibraryLoader;

} // namespace Plasma
