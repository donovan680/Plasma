///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Joshua Davis
/// Copyright 2018, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Plasma
{

//-------------------------------------------------------------------LightningShaderIRCore
/// The lightning shader wrapper around Lightning's core library. This needs to be
/// built and have the Parse function called once before all shader translation.
/// Contains the primitive types for translation.
class LightningShaderIRCore
{
public:
  static void InitializeInstance();
  static void Destroy();
  static LightningShaderIRCore& GetInstance();

  LightningShaderIRCore();
  /// Parse the core library and make all backing shader types.
  void Parse(LightningSpirVFrontEnd* translator);
  LightningShaderIRLibraryRef GetLibrary();

  TypeGroups mTypes;
  SpirVExtensionLibrary* mGlsl450ExtensionsLibrary;

private:
  void MakeMathTypes(LightningSpirVFrontEnd* translator, LightningShaderIRLibrary* shaderLibrary, TypeGroups& types);
  void RegisterPrimitiveFunctions(LightningSpirVFrontEnd* translator, LightningShaderIRLibrary* shaderLibrary, TypeGroups& types, LightningShaderIRType* shaderType);
  void RegisterVectorFunctions(LightningSpirVFrontEnd* translator, LightningShaderIRLibrary* shaderLibrary, TypeGroups& types, Array<LightningShaderIRType*>& vectorTypes);
  void RegisterMatrixFunctions(LightningSpirVFrontEnd* translator, LightningShaderIRLibrary* shaderLibrary, TypeGroups& types, Array<LightningShaderIRType*>& matrixTypes);
  void RegisterQuaternionFunctions(LightningSpirVFrontEnd* translator, LightningShaderIRLibrary* shaderLibrary, TypeGroups& types, LightningShaderIRType* quaternionType);

  LightningShaderIRLibraryRef mLibraryRef;
  static LightningShaderIRCore* mInstance;
};

}//namespace Plasma
