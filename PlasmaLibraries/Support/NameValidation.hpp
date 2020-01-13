///////////////////////////////////////////////////////////////////////////////
///
/// \file NameValidation.hpp
///
/// 
/// Authors: Chris Peters
/// Copyright 2010-2012, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include "String/String.hpp"
#include "Utility/Status.hpp"

namespace Plasma
{

//------------------------------------------------------------------- Validation
bool IsValidFilename(StringParam filename, Status& status);

String ConvertToValidName(StringParam source);

}//namespace Plasma
