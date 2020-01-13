//////////////////////////////////////////////////////////////////////////
/// Authors: Dane Curbow
/// Copyright 2016, DigiPen Institute of Technology
//////////////////////////////////////////////////////////////////////////

namespace Plasma
{

class TextureProcessor
{
public:
  TextureProcessor(TextureContent* textureContent, String outputPath, String inputFile);

  void ExtractAndImportTextures(const aiScene* scene);
  void CreateTexture(aiTexture* texture, uint textureIndex, StringParam extension);

  TextureContent* mTextureContent;
  String mOutputPath;
  String mFilename;
};

}// namespace Plasma