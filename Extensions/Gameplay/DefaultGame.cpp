///////////////////////////////////////////////////////////////////////////////
///
/// \file DefaultGame.cpp
/// 
/// 
/// Authors: Chris Peters
/// Copyright 2010-2012, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

namespace Plasma
{

//------------------------------------------------------------ DefaultGameSetup

LightningDefineType(DefaultGameSetup, builder, type)
{
  PlasmaBindComponent();
  PlasmaBindDependency(GameSession);
  PlasmaBindDocumented();
  PlasmaBindSetup(SetupMode::CallSetDefaults);

  MetaEditorResource* editorResource = new MetaEditorResource();
  editorResource->FilterTag = LightningTypeId(Space)->Name;
  LightningBindGetterSetterProperty(StartingSpace)->Add(editorResource);

  LightningBindGetterSetterProperty(StartingLevel);

  LightningBindFieldProperty(mLoadEditingLevel);
}

DefaultGameSetup::DefaultGameSetup()
{
  mLoadEditingLevel = true;
}

void DefaultGameSetup::Serialize(Serializer& stream)
{
  SerializeResourceName(mStartingSpace, ArchetypeManager);
  SerializeResourceName(mStartingLevel, LevelManager);
  SerializeNameDefault(mLoadEditingLevel, true);
}

void DefaultGameSetup::SetDefaults()
{
  mStartingSpace = ArchetypeManager::Find(CoreArchetypes::Space);
  mStartingLevel = LevelManager::GetDefault();
  mLoadEditingLevel = true;
}

void DefaultGameSetup::Initialize(CogInitializer& initializer)
{
  ConnectThisTo(GetOwner(), Events::GameSetup, OnSetup);
}

void DefaultGameSetup::OnSetup(GameEvent* event)
{
  GameSession* game = (GameSession*)this->GetOwner();
  Archetype* spaceArchetype = mStartingSpace;

  // Check to see if the starting space archetype is actually a space
  if(mStartingSpace->mStoredType != LightningTypeId(Space))
  {
    //Space archetype has been removed or an invalid archetype has been selected.
    DoNotifyError("Invalid Space Archetype", "The space archetype that was"
                  " loaded is either missing or does not contain a Space.");
    spaceArchetype = ArchetypeManager::GetDefault();
  }

  // Create the space
  Space* gameSpace = game->CreateSpace(spaceArchetype);

  // just a safeguard in case null got returned somehow
  if(gameSpace == NULL)
    return;

  if(gameSpace->mName.Empty())
    gameSpace->SetName(SpecialCogNames::Main);

  event->mSpace = gameSpace;

  // begin level loading, default to the starting level
  Level* levelToLoad = mStartingLevel;

  // If the game is created inside the editor attempt 
  // to load the level that is being edited
  if (PL::gRuntimeEditor && mLoadEditingLevel)
    levelToLoad = PL::gRuntimeEditor->GetEditingLevel();

  // If we have a valid level, load it
  if (levelToLoad)
    gameSpace->LoadLevelAdditive(levelToLoad);
}

} // namespace Plasma
