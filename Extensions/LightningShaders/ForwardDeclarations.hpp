///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Joshua Davis
/// Copyright 2016, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Lightning
{
class SyntaxTree;
}

namespace Plasma
{

class ShaderCodeBuilder;
class ShaderCompilationErrors;
class LightningShaderSettings;
class TranslationErrorEvent;
class LightningShaderSpirVSettings;

typedef Lightning::Ref<LightningShaderSettings> LightningShaderSettingsRef;
typedef Lightning::Ref<LightningShaderSpirVSettings> LightningShaderSpirVSettingsRef;

}//namespace Plasma
