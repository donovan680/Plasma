///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Josh Davis
/// Copyright 2015, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

namespace Plasma
{

void DeveloperNotes::Serialize(Serializer& stream)
{
  SerializeNameDefault(mFileName, String());
  SerializeNameDefault(mNotes, String());
  SerializeNameDefault(mDate, String());
}

}//namespace Plasma
