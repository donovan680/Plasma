///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Joshua Davis
/// Copyright 2018, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Plasma
{

//-------------------------------------------------------------------LightningShaderGlslBackend
/// Plasma's version of the glsl backend. Needed to
/// set specific options on the compiler for Plasma.
class PlasmaLightningShaderGlslBackend : public LightningShaderGlslBackend
{
public:
  PlasmaLightningShaderGlslBackend();

  String GetExtension() override;
  bool RunTranslationPass(ShaderTranslationPassResult& inputData, ShaderTranslationPassResult& outputData) override;
  String GetErrorLog() override;

  int mTargetVersion;
  bool mTargetGlslEs;
  String mErrorLog;
};

}//namespace Plasma
