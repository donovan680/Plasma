///////////////////////////////////////////////////////////////////////////////
/// 
/// Authors: Chris Peters
/// Copyright 2010-2011, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Plasma
{

typedef uint ThreadContextId;

struct QueuedEvent
{
  Handle Object;
  String EventId;
  Event* EventToSend;
  EventDispatcher* EventDispatcherOn;
};

//-------------------------------------------------------------------ThreadDispatch
class ThreadDispatch
{
public:
  ThreadDispatch();
  ~ThreadDispatch();

  template<typename type>
  void Dispatch(type* object, StringParam eventId, Event* event)
  {
    DispatchOn(object, object->GetDispatcher(), eventId, event);
  }

  void DispatchOn(HandleParam object, EventDispatcher* eventDispatcher, StringParam eventId, Event* event);
  void DispatchEvents();
  void ClearEvents();

private:
  ThreadLock mLock;
  Array<QueuedEvent> mEvents;
};

//-------------------------------------------------------------------ObjectThreadDispatch
/// A thread dispatch list for storage by an event receiver. Connects to EngineUpdate to automatically
/// pump events on the main thread, but can also be manually pumped or cleared. Doesn't store handles to
/// objects since it should be owned by the receiver.
class ObjectThreadDispatch : public EventObject
{
public:
  typedef ObjectThreadDispatch LightningSelf;
  struct ObjectQueuedEvent
  {
    String EventId;
    Event* EventToSend;
    EventDispatcher* EventDispatcherOn;
  };

  ObjectThreadDispatch();
  ~ObjectThreadDispatch();

  /// Queue up an event for dispatching on the main thread.
  void Dispatch(Object* object, StringParam eventId, Event* event);

  /// Sends the current buffer of events. Note: Should only be called on the main thread.
  void DispatchEvents();
  /// Clears the buffer of events.
  void ClearEvents();

  /// Automatically flushes the event list each engine update.
  void OnEngineUpdate(Event* e);
private:
  ThreadLock mLock;
  Array<ObjectQueuedEvent> mEvents;
};

namespace PL
{
  extern ThreadDispatch* gDispatch;
}

void StartThreadSystem();
void ShutdownThreadSystem();

inline void SendBlockingTaskStart(StringParam taskName)
{
  PL::gDispatch->Dispatch(PL::gEngine, Events::BlockingTaskStart, new BlockingTaskEvent(taskName));
}

inline void SendBlockingTaskFinish()
{
  PL::gDispatch->Dispatch(PL::gEngine, Events::BlockingTaskFinish, new Event());
}

}
