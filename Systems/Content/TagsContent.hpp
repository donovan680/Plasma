///////////////////////////////////////////////////////////////////////////////
///
/// \file TagsContent.hpp
/// Declaration of the TagsContent content component.
/// 
/// Authors: Joshua Claeys
/// Copyright 2013, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Plasma
{

//------------------------------------------------------------------------- Tags
class ContentTags : public ContentComponent
{
public:
  LightningDeclareType(ContentTags, TypeCopyMode::ReferenceType);

  /// Constructor
  ContentTags(){}

  /// ContentComponent interface.
  void Serialize(Serializer& stream) override;
  void Generate(ContentInitializer& initializer){}
  
  /// All unique tags
  HashSet<String> mTags;
};

}// namespace Plasma
