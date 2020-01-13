/**************************************************************\
* Author: Trevor Sundberg
* Copyright 2016, DigiPen Institute of Technology
\**************************************************************/

// This only exists to ensure that nothing conflicts with common os headers
#if WIN32
  #include <Windows.h>
#endif

#include "Lightning.hpp"
#include "String\String.hpp"
#include "StringRepresentations.hpp"
#include "CustomMath.hpp"
#include "Stress.hpp"
#include "Diff.hpp"

using namespace Lightning;
