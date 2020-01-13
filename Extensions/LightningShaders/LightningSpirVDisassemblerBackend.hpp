///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Joshua Davis
/// Copyright 2018, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Plasma
{

//-------------------------------------------------------------------LightningSpirVDisassemblerBackend
/// Backend that converts the input data to spir-v disassembly. The output data's
/// byte stream will be string data. Mostly used for debugging and unit tests.
class LightningSpirVDisassemblerBackend : public LightningShaderIRBackend
{
public:
  LightningSpirVDisassemblerBackend();

  String GetExtension() override;
  bool RunTranslationPass(ShaderTranslationPassResult& inputData, ShaderTranslationPassResult& outputData) override;
  String GetErrorLog() override;

  // The spirv target environment to run.
  int mTargetEnv;
  String mErrorLog;
};

}//namespace Plasma
