///////////////////////////////////////////////////////////////////////////////
///
/// \file EngineEvents.hpp
/// Declaration of the engine events.
///
/// Authors: Chris Peters
/// Copyright 2010-2012, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Plasma
{

namespace Events
{
  DeclareEvent(ScriptInitialize);
}//namespace Events


//------------------------------------------------------------------- Text Event
class TextEvent : public Event
{
public:
  LightningDeclareType(TextEvent, TypeCopyMode::ReferenceType);
  TextEvent(StringParam text) : Text(text) {}
  String Text;
};

//------------------------------------------------------------------ Error Event
class TextErrorEvent : public TextEvent
{
public:
  LightningDeclareType(TextErrorEvent, TypeCopyMode::ReferenceType);
  TextErrorEvent(StringParam text, int code) : TextEvent(text), Code(code) {}
  int Code;
};

//--------------------------------------------------------------- Progress Event

class ProgressEvent : public Event
{
public:
  LightningDeclareType(ProgressEvent, TypeCopyMode::ReferenceType);
  ProgressEvent();
  ProgressType::Enum ProgressType;
  String Operation;
  String CurrentTask;
  String ProgressLine;
  float Percentage;
};

//----------------------------------------------------------- BlockingTask Event
class BlockingTaskEvent : public Event
{
public:
  LightningDeclareType(BlockingTaskEvent, TypeCopyMode::ReferenceType);

  BlockingTaskEvent(StringParam taskName = String()) : mTaskName(taskName) {}
  String mTaskName;
};

}//namespace Plasma
