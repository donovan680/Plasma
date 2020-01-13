//////////////////////////////////////////////////////////////////////////
/// Authors: Dane Curbow
/// Copyright 2016, DigiPen Institute of Technology
//////////////////////////////////////////////////////////////////////////
#pragma once

namespace Plasma
{

typedef HashMap<String, String> AnimationNodeRedirectMap;

struct SceneTrack
{
  String FullPath;
  Array<PositionKey> PositionKeys;
  Array<RotationKey> RotationKeys;
  Array<ScalingKey>  ScalingKeys;
};

struct AnimationData
{
  String AnimationName;
  float AnimationDuration;
  float FramesPerSecond;
  Array<SceneTrack> ObjectTracks;
};

// animation data is keyed by its name
typedef Array<AnimationData> AnimationDataArray;

class AnimationProcessor
{
public:
  AnimationProcessor(AnimationBuilder* animationBuilder, HierarchyDataMap& hierarchyData, AnimationNodeRedirectMap& animationRedirectMap);
  ~AnimationProcessor();

  void ExtractAndProcessAnimationData(const aiScene* scene);
  void ExportAnimationData(String outputPath);

  AnimationBuilder* mBuilder;
  HierarchyDataMap& mHierarchyDataMap;
  AnimationDataArray mAnimationDataArray;
  AnimationNodeRedirectMap& mAnimationRedirectMap;
};

}// namespace Plasma
