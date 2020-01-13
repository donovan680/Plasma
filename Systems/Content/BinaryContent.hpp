///////////////////////////////////////////////////////////////////////////////
///
/// \file BinaryContent.hpp
/// Declaration of the Binary content classes.
/// 
/// Authors: Chris Peters
/// Copyright 2012, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Plasma
{

// BinaryContent Item. Binary content is content that is directly edited 
// by the editor in its binary form, or just generic binary data that requires no
// processing.
class BinaryContent : public ContentComposition
{
public:
  LightningDeclareType(BinaryContent, TypeCopyMode::ReferenceType);

  BinaryContent();
};

/// Binary builder just copies the data over with no processing.
class BinaryBuilder : public DirectBuilderComponent
{
public:
  LightningDeclareType(BinaryBuilder, TypeCopyMode::ReferenceType);

  BinaryBuilder()
    :DirectBuilderComponent(0, ".bin", String())
  {}

  uint Version;
  String FilterTag;

  //BuilderComponent Interface
  void Serialize(Serializer& stream) override;
  void Generate(ContentInitializer& initializer) override;
  String GetTag() override { return FilterTag; }

};

}//namespace Plasma
