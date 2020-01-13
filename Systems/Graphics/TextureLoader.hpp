// Authors: Nathan Carlson
// Copyright 2015, DigiPen Institute of Technology

#pragma once

namespace Plasma
{

class TextureLoader : public ResourceLoader
{
public:
  HandleOf<Resource> LoadFromFile(ResourceEntry& entry) override;
  void ReloadFromFile(Resource* resource, ResourceEntry& entry) override;
  HandleOf<Resource> LoadFromBlock(ResourceEntry& entry) override;
};

} // namespace Plasma
