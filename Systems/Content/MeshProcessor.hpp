//////////////////////////////////////////////////////////////////////////
/// Authors: Dane Curbow
/// Copyright 2016, DigiPen Institute of Technology
//////////////////////////////////////////////////////////////////////////
#pragma once

namespace Plasma
{

class MeshProcessor
{
public:
  MeshProcessor(MeshBuilder* meshBuilder, MeshDataMap& meshDataMap);
  ~MeshProcessor();

  void SetupTransformationMatricies();
  void ExtractAndProcessMeshData(const aiScene* scene);
  void ExportMeshData(String outputPath);

  void WriteSingleMeshes(String outputPath);
  void WriteCombinedMesh(String outputPath);

  MeshBuilder* mBuilder;

  MeshDataMap& mMeshDataMap;
};

}// namespace Plasma