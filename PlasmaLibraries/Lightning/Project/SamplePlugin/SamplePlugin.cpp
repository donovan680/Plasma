/**************************************************************\
* Author: Trevor Sundberg
* Copyright 2015, DigiPen Institute of Technology
\**************************************************************/

#include "SamplePlugin.hpp"

//***************************************************************************
LightningDefineStaticLibraryAndPlugin(SampleLibrary, SamplePlugin)
{
  LightningInitializeType(Sample);
}

//***************************************************************************
void SamplePlugin::Initialize(Lightning::BuildEvent* event)
{
}

//***************************************************************************
void SamplePlugin::Uninitialize()
{
}

//***************************************************************************
LightningDefineType(Sample, builder, type)
{
  LightningBindMethod(Run);
}

//***************************************************************************
void Sample::Run(StringBuilderExtended* builder, ArrayClass<Byte>* bytes)
{
  String s = builder->ToString();
  printf("It's ALIVE %s YAY!\n", s.c_str());
}
