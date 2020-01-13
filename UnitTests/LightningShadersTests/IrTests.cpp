#include "Precompiled.hpp"

//-------------------------------------------------------------------UnitTestCompilationPipeline
/// Helper to wrap running a unit test through a pipeline. In particular, this deals
/// with running the validator and appending the results to the final backend string.
struct UnitTestCompilationPipeline : Lightning::EventHandler
{
  typedef Lightning::Ref<ShaderTranslationPassResult> TranslationPassResultRef;
  TranslationPassResultRef mCompilationResult;
  Array<TranslationPassResultRef> mDebugResults;
  LightningShaderIRType* mCurrentType;
  LightningShaderSpirVSettings* mSettings;

  // Recursively set specialization constants. This will start from the given id and consume
  // as many values as necessary. This also does some simple increments on the given
  // bool, int, and real types to make each value unique.
  void RecursivelySetSpecializationConstants(SpecializationConstantEvent* e, LightningShaderIRType* fieldType, int& id,
    bool& boolValue, int& intValue, float& realValue)
  {
    ShaderIRTypeBaseType::Enum fieldBaseType = fieldType->mBaseType;
    if(fieldBaseType == ShaderIRTypeBaseType::Bool)
    {
      e->mSpecializationOverridesById[id] = boolValue ? "true" : "false";
      ++id;
      boolValue = !boolValue;
    }
    else if(fieldBaseType == ShaderIRTypeBaseType::Int)
    {
      e->mSpecializationOverridesById[id] = Plasma::ToString(intValue);
      ++id;
      ++intValue;
    }
    else if(fieldBaseType == ShaderIRTypeBaseType::Float)
    {
      e->mSpecializationOverridesById[id] = Plasma::ToString(realValue);
      ++id;
      realValue += 0.1f;
    }
    else if(fieldBaseType == ShaderIRTypeBaseType::Vector)
    {
      // Iterate over all scalars in the vector
      LightningShaderIRType* subType = GetComponentType(fieldType);
      for(size_t i = 0; i < fieldType->mComponents; ++i)
        RecursivelySetSpecializationConstants(e, subType, id, boolValue, intValue, realValue);
    }
    else if(fieldBaseType == ShaderIRTypeBaseType::Matrix)
    {
      // Iterate over all vectors in the matrix
      LightningShaderIRType* subType = GetComponentType(fieldType);
      for(size_t i = 0; i < fieldType->mComponents; ++i)
        RecursivelySetSpecializationConstants(e, subType, id, boolValue, intValue, realValue);
    }
    else if(fieldBaseType == ShaderIRTypeBaseType::Struct)
    {
      // Iterate over all members in this struct
      size_t subTypeCount = fieldType->GetSubTypeCount();
      for(size_t i = 0; i < subTypeCount; ++i)
      {
        LightningShaderIRType* subType = fieldType->GetSubType(i);
        RecursivelySetSpecializationConstants(e, subType, id, boolValue, intValue, realValue);
      }
    }
  }

  // Callback to set specialization constants, most for unit testing
  void SpecializationConstantsCallback(SpecializationConstantEvent* e)
  {
    // Set two special constants for the language id and version
    String languageSpecializationName = LightningShaderSpirVSettings::GetLanguageSpecializationName();
    int languageSpecializationId = e->GetFirstId(languageSpecializationName);
    if(languageSpecializationId != -1)
     e->mSpecializationOverridesById[languageSpecializationId] = "2";

    String languageVersionSpecializationName = LightningShaderSpirVSettings::GetLanguageVersionSpecializationName();
    int languageVersionSpecializationId = e->GetFirstId(languageVersionSpecializationName);
    if(languageVersionSpecializationId != -1)
      e->mSpecializationOverridesById[languageVersionSpecializationId] = "450";

    bool boolValue = true;
    int intValue = 1;
    float realValue = 0.1f;

    String specConstantAttribute = mSettings->mNameSettings.mSpecializationConstantAttribute;
    
    // For testing purposes, set all real constants to 
    ShaderIRTypeMeta* typeMeta = mCurrentType->mMeta;
    for(size_t i = 0; i < typeMeta->mFields.Size(); ++i)
    {
      ShaderIRFieldMeta* fieldMeta = typeMeta->mFields[i];
      if(!fieldMeta->ContainsAttribute(specConstantAttribute))
        continue;

      LightningShaderIRType* fieldType = mCurrentType->mShaderLibrary->FindType(fieldMeta->mLightningType);
      
      // Find the field's id. If it exists then we need to set all sub-ids recursively
      String propertyName = GenerateSpirVPropertyName(fieldMeta->mLightningName, mCurrentType);

      int firstId = e->GetFirstId(propertyName);
      if(firstId < 0)
        continue;

      RecursivelySetSpecializationConstants(e, fieldType, firstId, boolValue, intValue, realValue);
    }
  }

  /// Runs the shader generator on the given type with the given backend translator.
  /// Always adds the validator as a debug pass.
  bool CompilePipeline(SimpleLightningShaderIRGenerator& shaderGenerator, LightningShaderIRBackend* backendTranslator, LightningShaderIRType* type)
  {
    // Save the current type (for the specialization callback)
    mCurrentType = type;
    mSettings = shaderGenerator.mSettings;
    String binaryCachePath = GetTemporaryDirectory();

    // Create the pipeline
    ShaderPipelineDescription unitTestPipeline;
    unitTestPipeline.mBackend = backendTranslator;
    
    // Add a pass to set and freeze specialization constants
    SpirVSpecializationConstantPass* specializationConstantPass = new SpirVSpecializationConstantPass();
    specializationConstantPass->mFreezeAllConstants = false;
    Lightning::EventConnect(specializationConstantPass, Plasma::Events::CollectSpecializationConstants, &UnitTestCompilationPipeline::SpecializationConstantsCallback, this);
    unitTestPipeline.mToolPasses.PushBack(specializationConstantPass);

    // Add this line to run the optimizer
    //unitTestPipeline.mToolPasses.PushBack(new SpirVOptimizerPass());
    
    // Add the validator as a debug pass
    unitTestPipeline.mDebugPasses.PushBack(new SpirVValidatorPass());
    // Add a binary file writer as a debug pass (so we can look at the binary to debug errors if needed)
    unitTestPipeline.mDebugPasses.PushBack(new SpirVFileWriterPass(binaryCachePath));
    // Run the pipeline
    Array<TranslationPassResultRef> pipelineResults;
    bool success = shaderGenerator.CompilePipeline(type, unitTestPipeline, pipelineResults, mDebugResults);
    // Store the final results
    if(success)
      mCompilationResult = pipelineResults.Back();

    return success;
  }

  /// Returns the result as a string. Also pre-pends the string with the validator's result.
  String ToString()
  {
    // Get the validator results (if they exist)
    String validatorResult;
    if(!mDebugResults.Empty())
      validatorResult = mDebugResults[0]->ToString();

    // Get the backend results (if they exist)
    String backendResult;
    if(mCompilationResult != nullptr)
      backendResult = mCompilationResult->ToString();

    return BuildString(validatorResult, backendResult);
  }
};

bool TestDiff2(StringParam expectedFilePath, StringParam generatedFilePath, StringParam generatedFileContents, ErrorReporter& reporter)
{
  String expectedFileContents;
  if(FileExists(expectedFilePath))
  {
    expectedFileContents = ReadFileIntoString(expectedFilePath);
    // Deal with weirdness of line return characters (I don't care about that difference...)
    expectedFileContents = expectedFileContents.Replace("\r\n", "\n");
  }
  // there's no expected results yet, write out an empty file for the diff
  else
  {
    WriteStringRangeToFile(expectedFilePath, "");
  }

  String generatedFileContentsFixedNewlines = generatedFileContents.Replace("\r\n", "\n");
  if(generatedFileContentsFixedNewlines != expectedFileContents)
  {
    reporter.DisplayDiffs(expectedFilePath, generatedFilePath);
    return false;
  }
  return true;
}

void TestCompilation(SimpleLightningShaderIRGenerator& shaderGenerator, LightningShaderIRBackend* backendTranslator, LightningShaderSpirVSettings* settings, LightningShaderIRType* type, StringParam directory, ErrorReporter& reporter)
{
  // Don't test things that don't have meta (interface blocks, core types, etc...)
  ShaderIRTypeMeta* meta = type->mMeta;
  if(meta == nullptr)
    return;

  // Only emit things marked as a unit test (prevents outputting random classes twice)
  if(!meta->ContainsAttribute(settings->mNameSettings.mUnitTestAttribute))
    return;

  UnitTestCompilationPipeline unitTestPipeline;
  bool success = unitTestPipeline.CompilePipeline(shaderGenerator, backendTranslator, type);
  if(!success)
  {
    String msg = String::Format("Failed to compile pipeline for '%s'", meta->mLightningName.c_str());
    reporter.Report(msg);
    return;
  }

  String generatedResults = unitTestPipeline.ToString();

  String languageExt = backendTranslator->GetExtension();
  String extension = languageExt.ToLower();
  String testName = FilePath::GetFileNameWithoutExtension(type->mName);

  String expectedFilePath = FilePath::CombineWithExtension(directory, testName, BuildString(".expected.", extension));
  String generatedFilePath = FilePath::CombineWithExtension(directory, testName, BuildString(".generated.", extension));
  WriteStringRangeToFile(generatedFilePath, generatedResults.All());

  bool diffedCleanly = TestDiff2(expectedFilePath, generatedFilePath, generatedResults, reporter);
}

void TestCompilation(SimpleLightningShaderIRGenerator& shaderGenerator, LightningShaderIRType* type, UnitTestPackage& unitTestPackage, StringParam directory, ErrorReporter& reporter)
{
  for(size_t i = 0; i < unitTestPackage.mBackends.Size(); ++i)
    TestCompilation(shaderGenerator, unitTestPackage.mBackends[i], shaderGenerator.mSettings, type, directory, reporter);
}

void ReportErrors(SimpleLightningShaderIRGenerator& shaderGenerator, StringParam directory, ErrorReporter& reporter)
{
  // Walk over each code entry in the project
  for(size_t i = 0; i < shaderGenerator.mFragmentProject.mCodeEntries.Size(); ++i)
  {
    LightningShaderIRProject::CodeEntry& entry = shaderGenerator.mFragmentProject.mCodeEntries[i];
    
    // Find the error report for this code entry.
    String errorStr = reporter.FindErrorReport(entry.mCodeLocation);
    // If there was no error report then create a string anyways so going from error to no error will display a diff
    if(errorStr.Empty())
      errorStr = "No Error";

    // Build up various file paths.
    FilePathInfo pathInfo = FilePath::GetPathInfo(entry.mCodeLocation);
    String expectedFilePath = FilePath::CombineWithExtension(directory, pathInfo.FileName, ".expected.errors.txt");
    String generatedFilePath = FilePath::CombineWithExtension(directory, pathInfo.FileName, ".generated.errors.txt");

    // Alway write out the generated error message
    WriteStringRangeToFile(generatedFilePath, errorStr);
    // Diff the expected error msg with what we actually got
    TestDiff2(expectedFilePath, generatedFilePath, errorStr, reporter);
  }
}

void TestShaderFileCompilation(SimpleLightningShaderIRGenerator& shaderGenerator, UnitTestPackage& unitTestPackage, StringParam filePath, StringParam directory, ErrorReporter& reporter)
{
  // Clear the previous results
  shaderGenerator.ClearAll();
  reporter.ClearReports();

  // Load the fragment code and compile
  String fragmentCode = ReadFileIntoString(filePath);
  shaderGenerator.AddFragmentCode(fragmentCode, filePath, nullptr);

  bool success = shaderGenerator.CompileAndTranslateFragments();

  if(!success)
  {
    ReportErrors(shaderGenerator, directory, reporter);
    reporter.Report("Failed to compile project library");
    return;
  }

  LightningShaderIRLibraryRef libraryRef = shaderGenerator.mFragmentLibraryRef;
  AutoDeclare(typeRange, libraryRef->mTypes.Values());
  for(; !typeRange.Empty(); typeRange.PopFront())
  {
    LightningShaderIRType* type = typeRange.Front();
    if(type->mBaseType == ShaderIRTypeBaseType::Struct)
      TestCompilation(shaderGenerator, type, unitTestPackage, directory, reporter);
  }
}

void TestShaderCompilationOfDirectory(SimpleLightningShaderIRGenerator& shaderGenerator, UnitTestPackage& unitTestPackage, StringParam directory, ErrorReporter& reporter)
{
  LoadDirectorySettingsOrDefault(*shaderGenerator.mSettings, directory);

  FileRange range(directory);
  for(; !range.Empty(); range.PopFront())
  {
    FileEntry entry = range.FrontEntry();
    String filePath = entry.GetFullPath();

    if(FilePath::GetExtension(filePath).ToLower() == mFragmentExtension)
      TestShaderFileCompilation(shaderGenerator, unitTestPackage, filePath, directory, reporter);
  }
}

void TestCompositesOfDirectory(SimpleLightningShaderIRGenerator& shaderGenerator, UnitTestPackage& unitTestPackage, StringParam directory, ErrorReporter& reporter)
{
  LoadDirectorySettingsOrDefault(*shaderGenerator.mSettings, directory);

  // Clear the previous results
  shaderGenerator.ClearAll();
  reporter.ClearReports();

  // Load the code of the given directory
  LoadFragmentCodeDirectory(shaderGenerator, directory);

  // Compile the fragments together and check for errors
  bool success = shaderGenerator.CompileAndTranslateFragments();
  if(!success)
  {
    ReportErrors(shaderGenerator, directory, reporter);
    reporter.Report("Failed to compile project library");
    return;
  }

  LightningShaderIRLibraryRef libraryRef = shaderGenerator.mFragmentLibraryRef;

  // Load the shader def file
  Array<SerializedShaderDefinition> shaders;
  String defPath = FilePath::CombineWithExtension(directory, "ShaderDefinitions", ".txt");
  if(FileExists(defPath))
    LoadShaderDefinitions(shaders, defPath);

  for(size_t i = 0; i < shaders.Size(); ++i)
  {
    SerializedShaderDefinition& shaderDef = shaders[i];
    TestCompositeDefinition(shaderGenerator, shaderDef, unitTestPackage, directory, reporter);
  }
}

void TestCompositeDefinition(SimpleLightningShaderIRGenerator& shaderGenerator, SerializedShaderDefinition& shaderDef, UnitTestPackage& unitTestPackage, StringParam directory, ErrorReporter& reporter)
{
  // If the name is empty, auto generate the name.
  if(shaderDef.mShaderName.Empty())
    shaderDef.mShaderName  = String::JoinRange("_", shaderDef.mFragmentNames.All());

  ShaderCapabilities capabilities;
  LightningShaderIRLibraryRef libraryRef = shaderGenerator.mFragmentLibraryRef;

  LightningShaderIRCompositor::ShaderDefinition resultShader;
  resultShader.mShaderName = shaderDef.mShaderName;
  // Add the unit test attribute to this composite
  resultShader.mExtraAttributes.AddAttribute(shaderGenerator.mSettings->mNameSettings.mUnitTestAttribute, nullptr);

  // Look up all fragments in the def by name
  Array<LightningShaderIRType*>& fragments = resultShader.mFragments;
  for(size_t i = 0; i < shaderDef.mFragmentNames.Size(); ++i)
  {
    LightningShaderIRType* fragmentType = libraryRef->FindType(shaderDef.mFragmentNames[i]);
    ErrorIf(fragmentType == nullptr, "Bad shader def");
    fragments.PushBack(fragmentType);
  }

  // Clear the shaders before compositing
  shaderGenerator.ClearShadersProjectAndLibrary();

  // Compose them together
  bool successfulComposite = false;

  // @JoshD: Huge hack. Need to distinguish compute shader pipelines from rendering pipelines
  // in the shader def at some point. For now just rely on the shader name to contain compute.
  if(shaderDef.mShaderName.Contains("Compute"))
    successfulComposite = shaderGenerator.ComposeComputeShader(resultShader, capabilities);
  else
    successfulComposite = shaderGenerator.ComposeShader(resultShader, capabilities);
  if(!successfulComposite)
  {
    ReportErrors(shaderGenerator, directory, reporter);
    reporter.Report("Failed to compose shaders");
    return;
  }
  
  // Add all of the composited shader stages together into the shader library.
  for(size_t i = 0; i < FragmentType::Size; ++i)
  {
    LightningShaderIRCompositor::ShaderStageDescription& shaderInfo = resultShader.mResults[i];
    if(shaderInfo.mShaderCode.Empty())
      continue;

    shaderGenerator.AddShaderCode(shaderInfo.mShaderCode, shaderInfo.mClassName, nullptr);
  }

  // Make sure the shader library compiles.
  bool success = shaderGenerator.CompileAndTranslateShaders();
  if(!success)
  {
    reporter.Report("Composites failed to compile");
    return;
  }

  // Translate each composite to spirv and validate/diff the results
  Array<LightningShaderIRType*> compositedShaderTypes;
  for(size_t i = 0; i < FragmentType::Size; ++i)
  {
    LightningShaderIRCompositor::ShaderStageDescription& shaderInfo = resultShader.mResults[i];
    if(shaderInfo.mShaderCode.Empty())
      continue;

    // Write out the composited lightning shader
    String className = shaderInfo.mClassName;
    String extension = ".lightningFrag.txt";
    String generatedFilePath = FilePath::CombineWithExtension(directory, className, BuildString(".generated", extension));
    WriteStringRangeToFile(generatedFilePath, shaderInfo.mShaderCode);

    // Diff against expected results
    String expectedFilePath = FilePath::CombineWithExtension(directory, className, BuildString(".expected", extension));
    TestDiff2(expectedFilePath, generatedFilePath, shaderInfo.mShaderCode, reporter);

    // Additionally translate the shader through the backends
    LightningShaderIRType* type = shaderGenerator.mShaderLibraryRef->FindType(shaderInfo.mClassName);
    compositedShaderTypes.PushBack(type);
    TestCompilation(shaderGenerator, type, unitTestPackage, directory, reporter);
  }

  // Run all renderer packages (e.g. test glsl compilation and linkage)
  for(size_t i = 0; i < unitTestPackage.mRenderPackages.Size(); ++i)
  {
    RendererPackage& backendPackage = unitTestPackage.mRenderPackages[i];

    Array<FragmentInfo> results;
    for(size_t j = 0; j < compositedShaderTypes.Size(); ++j)
    {
      LightningShaderIRType* shaderType = compositedShaderTypes[j];
      Lightning::Ref<ShaderTranslationPassResult> resultRef;

      UnitTestCompilationPipeline unitTestPipeline;
      bool success = unitTestPipeline.CompilePipeline(shaderGenerator, backendPackage.mBackend, shaderType);

      FragmentInfo fragInfo;
      fragInfo.mFragmentCode = unitTestPipeline.ToString();
      fragInfo.mFragmentType = shaderType->mMeta->mFragmentType;
      results.PushBack(fragInfo);
    }

    backendPackage.mRenderer->CompileAndLinkShader(results, *backendPackage.mErrorReporter);
  }
}

void TestDirectory(SimpleLightningShaderIRGenerator& shaderGenerator, UnitTestPackage& unitTestPackage, StringParam directory, ErrorReporter& reporter, bool recurse)
{
  // Skip a whole directory if "Skip.txt" exists. Just makes it easier to temporarily ignore stuff I want to check later.
  String skipFile = FilePath::CombineWithExtension(directory, "Skip", ".txt");
  if(FileExists(skipFile))
    return;

  // If we recurse, iterate over all folders. Treat each folder as an independently library for compilation
  if(recurse)
  {
    FileRange range(directory);
    for(; !range.Empty(); range.PopFront())
    {
      FileEntry entry = range.FrontEntry();
      String filePath = entry.GetFullPath();

      // Recurse on only directories
      if(DirectoryExists(filePath))
        TestDirectory(shaderGenerator, unitTestPackage, filePath, reporter, recurse);
    }
  }

  String shaderDefFilePath = FilePath::CombineWithExtension(directory, "ShaderDefinitions", ".txt");
  if(FileExists(shaderDefFilePath))
    TestCompositesOfDirectory(shaderGenerator, unitTestPackage, directory, reporter);
  else
    TestShaderCompilationOfDirectory(shaderGenerator, unitTestPackage, directory, reporter);
}

void CollectMainResults(SimpleLightningShaderIRGenerator& shaderGenerator, Lightning::ExecutableState* state, Lightning::BoundType* boundType, RenderResults& results)
{
  SpirVNameSettings& nameSettings = shaderGenerator.mSettings->mNameSettings;

  Lightning::ExceptionReport report;
  // Construct the shader's bound type
  Lightning::Handle preconstructedObject = state->AllocateDefaultConstructedHeapObject(boundType, report, Lightning::HeapFlags::NonReferenceCounted);

  // Find and execute Main
  Lightning::Function* mainFunction = boundType->FindFunction("Main", Array<Lightning::Type*>(), Lightning::Core::GetInstance().VoidType, Lightning::FindMemberOptions::None);
  if(mainFunction == nullptr)
  {
    Error("This should never happen (failed to find main)");
    return;
  }

  Lightning::Call mainCall(mainFunction, state);
  mainCall.SetHandle(Lightning::Call::This, preconstructedObject);
  mainCall.Invoke(report);

  RenderResult& result = results.mLanguageResult[RenderResults::mLightningKey];
  Array<String>& renderTargetNames = shaderGenerator.mSettings->mRenderTargetNames;
  for(size_t i = 0; i < renderTargetNames.Size(); ++i)
  {
    // Find the property of this render target
    String renderTargetName = renderTargetNames[i];
    Lightning::Property* prop = boundType->FindProperty(renderTargetName, Lightning::FindMemberOptions::None);
    // If it doesn't exist (meaning the fragments/shader don't write to it)
    // or it's not actually marked as an output, then just mark result it as unused.
    if(prop == nullptr || !prop->HasAttribute(nameSettings.mStageOutputAttribute))
    {
      results.mTargets[i] = false;
      continue;
    }

    // Otherwise mark this target as used
    results.mTargets[i] = true;

    // Get the result of the property (call the "Get" function on it).
    Lightning::Call call(prop->Get, state);
    call.SetHandle(Lightning::Call::This, preconstructedObject);
    call.Invoke(report);

    result.mData[i] = call.Get<Vec4>(Lightning::Call::Return);
  }
}

void ComputeLightningIRRenderResults(SimpleLightningShaderIRGenerator& shaderGenerator, LightningShaderIRProject& project, LightningShaderIRLibraryRef& libraryRef, StringParam lightningTypeName, RenderResults& results)
{
  // Build the lightning module for the shader library
  Lightning::Module lightningModule;
  project.PopulateLightningModule(lightningModule, libraryRef->mDependencies);
  lightningModule.PushBack(libraryRef->mLightningLibrary);

  // Link the module into an exe
  Lightning::ExecutableState* state = lightningModule.Link();
  // Find the type that we're trying to collect results for
  Lightning::BoundType* boundType = lightningModule.FindType(lightningTypeName);

  CollectMainResults(shaderGenerator, state, boundType, results);

  delete state;
}

void ComputeLightningIRRenderResults(SimpleLightningShaderIRGenerator& shaderGenerator, StringParam lightningTypeName, RenderResults& results)
{
  ComputeLightningIRRenderResults(shaderGenerator, shaderGenerator.mFragmentProject, shaderGenerator.mFragmentLibraryRef, lightningTypeName, results);
}

void TestShaderDefinition(SimpleLightningShaderIRGenerator& shaderGenerator, RendererPackage& package, SerializedShaderDefinition& shaderDef)
{
  // Clear the previous shaders
  shaderGenerator.ClearShadersProjectAndLibrary();

  LightningShaderIRLibrary& library = *shaderGenerator.mFragmentLibraryRef;
  LightningShaderIRBackend* backend = package.mBackend;
  BaseRenderer* renderer = package.mRenderer;
  ErrorReporter* reporter = package.mErrorReporter;

  Array<LightningShaderIRType*> types;
  Array<FragmentInfo> fragments;
  String shaderName = shaderDef.mShaderName;

  for(size_t j = 0; j < shaderDef.mFragmentNames.Size(); ++j)
  {
    LightningShaderIRType* type = library.FindType(shaderDef.mFragmentNames[j]);

    UnitTestCompilationPipeline unitTestPipeline;
    bool success = unitTestPipeline.CompilePipeline(shaderGenerator, package.mBackend, type);

    // @JoshD: Fix for composites
    FragmentInfo fragData;
    fragData.mFragmentCode = unitTestPipeline.ToString();
    fragData.mFragmentType = type->mMeta->mFragmentType;
    if(fragData.mFragmentType == FragmentType::Pixel)
      shaderName = type->mMeta->mLightningName;
    fragments.PushBack(fragData);
    types.PushBack(type);
  }

  RenderResults results;
  ComputeLightningIRRenderResults(shaderGenerator, shaderName, results);
  RenderResult& glslResult = results.mLanguageResult[backend->GetExtension()];
  renderer->RunPostProcess(fragments, glslResult, *reporter);
  RenderResult& lightningResults = results.mLanguageResult[RenderResults::mLightningKey];

  for(size_t i = 0; i < mMaxRenderTargets; ++i)
  {
    // Skip inactive targets
    if(results.mTargets[i] == false)
      continue;

    Vec4 lightningData = lightningResults.mData[i];
    Vec4 shaderData = glslResult.mData[i];
    if(Math::LengthSq(lightningData - shaderData) > 0.0001f)
      reporter->ReportPostProcessError(shaderName, lightningData, shaderData, i);
  }
}

void TestRunning(SimpleLightningShaderIRGenerator& shaderGenerator, UnitTestPackage& unitTestPackage, StringParam directory, bool recurse)
{
  // Clear the previous results
  shaderGenerator.ClearAll();

  LoadFragmentCodeDirectory(shaderGenerator, directory);
  shaderGenerator.CompileAndTranslateFragments();

  Array<SerializedShaderDefinition> shaderDefs;
  String defFilePath = FilePath::CombineWithExtension(directory, "ShaderDefinitions", ".txt");
  LoadShaderDefinitions(shaderDefs, defFilePath);

  for(size_t i = 0; i < shaderDefs.Size(); ++i)
  {
    SerializedShaderDefinition& shaderDef = shaderDefs[i];
    for(size_t j = 0; j < unitTestPackage.mRenderPackages.Size(); ++j)
    {
      RendererPackage& package = unitTestPackage.mRenderPackages[j];
      TestShaderDefinition(shaderGenerator, package, shaderDef);
    }
  }
}
