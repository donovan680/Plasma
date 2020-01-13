///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Joshua Davis
/// Copyright 2018, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Plasma
{

class LightningSpirVFrontEnd;
class LightningSpirVFrontEndContext;
class EntryPointInfo;

void ValidateEntryPoint(LightningSpirVFrontEnd* translator, Lightning::GenericFunctionNode* node, LightningSpirVFrontEndContext* context);
void ValidateBasicEntryPoint(LightningSpirVFrontEnd* translator, Lightning::GenericFunctionNode* node, LightningSpirVFrontEndContext* context);
void ValidateGeometryEntryPoint(LightningSpirVFrontEnd* translator, Lightning::GenericFunctionNode* node, LightningSpirVFrontEndContext* context);

}//namespace Plasma
