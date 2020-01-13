// Authors: Nathan Carlson
// Copyright 2015, DigiPen Institute of Technology

#include "Precompiled.hpp"

namespace Plasma
{

//**************************************************************************************************
void ShaderInputSetValue(ShaderInput& input, AnyParam value)
{
  if (input.mShaderInputType == ShaderInputType::Texture)
  {
    Texture* texture = value.Get<Texture*>(GetOptions::ReturnDefaultOrNull);
    if (texture == nullptr)
      texture = TextureManager::GetDefault();

    *(TextureRenderData**)input.mValue = texture->mRenderData;
  }
  else if (value.IsNotNull())
  {
    ErrorIf(value.StoredType->GetAllocatedSize() > ShaderInput::MaxSize, "Type cannot be stored in ShaderInput.");
    memcpy(input.mValue, value.Dereference(), value.StoredType->GetAllocatedSize());
  }
  else
  {
    memset(input.mValue, 0, ShaderInput::MaxSize);
  }
}

} // namespace Plasma
