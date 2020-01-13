///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Joshua Davis
/// Copyright 2018, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Plasma
{

//-------------------------------------------------------------------Hash Policy for enum types
template<>
struct PlasmaShared HashPolicy<spv::Op> : public HashPolicy<int>
{
};

template<>
struct PlasmaShared HashPolicy<spv::Capability> : public HashPolicy<int>
{
};

}//namespace Plasma
