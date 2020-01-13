///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Joshua Davis
/// Copyright 2015, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

class VisualStudioListener : public ConsoleListener
{
public:
  void Print(FilterType filterType, cstr message) override
  {
    OutputDebugStringA(message);
  }
};

void LightningCompilerErrorCallback(Lightning::ErrorEvent* e)
{
  ZPrint("%s", e->GetFormattedMessage(Lightning::MessageFormat::MsvcCpp).c_str());
  PlasmaDebugBreak();
}

void LightningTranslationErrorCallback(TranslationErrorEvent* e)
{
  ZPrint("%s", e->mFullMessage.c_str());
  __debugbreak();
}

void RunTests()
{
  // Hook up a listener to print all output to the visual studio console
  VisualStudioListener visualStudioOutput;
  if(Os::IsDebuggerAttached())
    Plasma::Console::Add(&visualStudioOutput);

  HWND hiddenWindow = CreateWindowA("STATIC", "", WS_POPUP | WS_DISABLED, 0, 0, mScreenWidth, mScreenHeight, NULL, NULL, GetModuleHandle(NULL), NULL);
  ShowWindow(hiddenWindow, SW_HIDE);
  HDC drawContext = GetDC(hiddenWindow);

  ErrorReporter glslReporter;
  GlslRenderer glslRenderer(drawContext);

  RendererPackage glslPackage;
  glslPackage.mErrorReporter = &glslReporter;
  glslPackage.mRenderer = &glslRenderer;
  LightningShaderGlslBackend* glslBackend = new LightningShaderGlslBackend();
  // Required to test runtime arrays
  glslBackend->mTargetVersion = 440;
  glslPackage.mBackend = glslBackend;

  UnitTestPackage unitTestPackage;
  unitTestPackage.mBackends.PushBack(new LightningSpirVDisassemblerBackend());
  unitTestPackage.mRenderPackages.PushBack(glslPackage);

  String extensionsPath = "FragmentExtensions";
  String fragmentSettingsPath = "../../Data/LightningFragmentSettings";

  SpirVNameSettings nameSettings;
  SimpleLightningShaderIRGenerator::LoadNameSettings(nameSettings);
  LightningShaderSpirVSettings* settings = SimpleLightningShaderIRGenerator::CreateUnitTestSettings(nameSettings);
  SimpleLightningShaderIRGenerator irGenerator(new LightningSpirVFrontEnd(), settings);
  Lightning::EventConnect(&irGenerator, Lightning::Events::CompilationError, LightningCompilerErrorCallback);
  Lightning::EventConnect(&irGenerator, Plasma::Events::TranslationError, &ErrorReporter::OnTranslationError, &glslReporter);
  Lightning::EventConnect(&irGenerator, Lightning::Events::CompilationError, &ErrorReporter::OnCompilationError, &glslReporter);
  Lightning::EventConnect(&irGenerator, Plasma::Events::ValidationError, &ErrorReporter::OnValidationError, &glslReporter);

  irGenerator.SetupDependencies(extensionsPath);

  TestDirectory(irGenerator, unitTestPackage, "IrTests", glslReporter, true);
  TestDirectory(irGenerator, unitTestPackage, "IrCompositeTests", glslReporter, true);

  // Currently requires 150 for how uniforms are passed through.
  // @JoshD: update to uniform buffers later.
  glslBackend->mTargetVersion = 150;
  TestRunning(irGenerator, unitTestPackage, "RunningIrTests", true);
  
  glslReporter.mAssert = false;
  TestDirectory(irGenerator, unitTestPackage, "IrErrorTests", glslReporter, true);

  // Run all of the unit test directories with our different translators/renderers
  //for(size_t i = 0; i < shaderLanguages.Size(); ++i)
  //{
  //  ShaderLanguageTestData& shaderLanguage = *(shaderLanguages[i]);
  //  SimpleLightningShaderGenerator& shaderGenerator = shaderLanguage.mShaderGenerator;
  //  Lightning::EventConnect(&shaderGenerator, Lightning::Events::CompilationError, LightningCompilerErrorCallback);
  //  Lightning::EventConnect(&shaderGenerator, Plasma::Events::TranslationError, LightningTranslationErrorCallback);
  //  shaderGenerator.LoadSettings(fragmentSettingsPath);
  //  shaderGenerator.SetupDependencies(extensionsPath);
  //
  //  ZPrint("Running %s tests\n", shaderGenerator.mTranslator->GetFullLanguageString().c_str());
  //  TestRenderer(shaderGenerator, *shaderLanguage.mRenderer, *shaderLanguage.mErrorReporter);
  //}
}

int main()
{
  Lightning::LightningSetup lightningSetup;

  Lightning::Module module;
  ExecutableState::CallingState = module.Link();

  ShaderSettingsLibrary::InitializeInstance();
  ShaderSettingsLibrary::GetInstance().GetLibrary();
  
  RunTests();

  ShaderSettingsLibrary::GetInstance().Destroy();
  delete ExecutableState::CallingState;

  return 0;
}
