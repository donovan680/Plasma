///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Trevor Sundberg
/// Copyright 2018, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Plasma
{

/// Encodes a string to be safely passed as a parameter
/// in a Url using Percent-encoding.
String UrlParamEncode(StringParam string);

/// Decodes a string from a Url using Percent-encoding.
String UrlParamDecode(StringParam string);

} // namespace Plasma
