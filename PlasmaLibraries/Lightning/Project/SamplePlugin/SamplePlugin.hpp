/**************************************************************\
* Author: Trevor Sundberg
* Copyright 2015, DigiPen Institute of Technology
\**************************************************************/

// Include protection
#pragma once
#ifndef LIGHTNING_SAMPLE_PLUGIN_HPP
#define LIGHTNING_SAMPLE_PLUGIN_HPP

#define PlasmaImportDll
#include "Lightning.hpp"
using namespace Lightning;

//***************************************************************************
LightningDeclareStaticLibraryAndPlugin(SampleLibrary, SamplePlugin);

//***************************************************************************
class Sample
{
public:
  LightningDeclareType(Sample, TypeCopyMode::ReferenceType);
  static void Run(StringBuilderExtended* builder, ArrayClass<Byte>* bytes);
};

// End header protection
#endif
