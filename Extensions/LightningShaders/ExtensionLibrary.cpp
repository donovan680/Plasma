///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Joshua Davis
/// Copyright 2018, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

namespace Plasma
{

//-------------------------------------------------------------------SpirVExtensionInstruction
SpirVExtensionInstruction::SpirVExtensionInstruction()
{
  mResolverFn = nullptr;
}

//-------------------------------------------------------------------SpirVExtensionLibrary
SpirVExtensionInstruction* SpirVExtensionLibrary::CreateExtInst(Lightning::Function* lightningFn, SpirVExtensionInstructionResolverFn resolverFn)
{
  ErrorIf(lightningFn == nullptr, "Invalid lightning function");
  ErrorIf(mExtensions.ContainsKey(lightningFn), "Extension already exists");

  SpirVExtensionInstruction* instruction = new SpirVExtensionInstruction();
  instruction->mResolverFn = resolverFn;
  instruction->mLibrary = this;
  mExtensions[lightningFn] = instruction;
  // Store this extension instruction in the owning library
  mOwningLibrary->mExtensionInstructions.InsertOrError(lightningFn, instruction);
  return instruction;
}

}//namespace Plasma
