/**************************************************************\
* Author: Trevor Sundberg
* Copyright 2016, DigiPen Institute of Technology
\**************************************************************/

#include "Precompiled.hpp"

namespace Lightning
{
  //***************************************************************************
  Composition::Composition()
  {
  }
  
  //***************************************************************************
  Composition::~Composition()
  {
  }

  //***************************************************************************
  Composition* Composition::GetBaseComposition()
  {
    return nullptr;
  }

  //***************************************************************************
  void Composition::ClearComponents()
  {
    this->Components.Clear();
  }
}
