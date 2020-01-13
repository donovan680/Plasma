

void TestCompilation(SimpleLightningShaderIRGenerator& shaderGenerator, ILightningShaderIR* type, StringParam directory, ErrorReporter& reporter);
void TestShaderFileCompilation(SimpleLightningShaderIRGenerator& shaderGenerator, UnitTestPackage& unitTestPackage, StringParam filePath, StringParam directory, ErrorReporter& reporter);
void TestShaderCompilationOfDirectory(SimpleLightningShaderIRGenerator& shaderGenerator, UnitTestPackage& unitTestPackage, StringParam directory, ErrorReporter& reporter);
void TestCompositesOfDirectory(SimpleLightningShaderIRGenerator& shaderGenerator, UnitTestPackage& unitTestPackage, StringParam directory, ErrorReporter& reporter);
void TestCompositeDefinition(SimpleLightningShaderIRGenerator& shaderGenerator, SerializedShaderDefinition& shaderDef, UnitTestPackage& unitTestPackage, StringParam directory, ErrorReporter& reporter);
void TestDirectory(SimpleLightningShaderIRGenerator& shaderGenerator, UnitTestPackage& unitTestPackage, StringParam directory, ErrorReporter& reporter, bool recurse = true);
void TestRunning(SimpleLightningShaderIRGenerator& shaderGenerator, UnitTestPackage& unitTestPackage, StringParam directory, bool recurse = true);
