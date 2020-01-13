///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Trevor Sundberg
/// Copyright 2016, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Support/SupportStandard.hpp"
#include "Platform/PlatformStandard.hpp"
#include "Meta/MetaStandard.hpp"

#include "Lightning/Lightning.hpp"
using namespace Lightning;

namespace Plasma
{

// Serialization library
class PlasmaNoImportExport SerializationLibrary : public Lightning::StaticLibrary
{
public:
  LightningDeclareStaticLibraryInternals(SerializationLibrary, "PlasmaEngine");

  static void Initialize();
  static void Shutdown();
};

}

#include "Serialization.hpp"
#include "PlasmaContainers.hpp"
#include "SerializationBuilder.hpp"
#include "Tokenizer.hpp"
#include "Text.hpp"
#include "Binary.hpp"
#include "DataTreeNode.hpp"
#include "DataTree.hpp"
#include "Simple.hpp"
#include "DefaultSerializer.hpp"
#include "Tokenizer.hpp"
#include "SerializationTraits.hpp"
#include "EnumSerialization.hpp"
#include "MetaSerialization.hpp"
#include "MathSerialization.hpp"
#include "SerializationUtility.hpp"
