///////////////////////////////////////////////////////////////////////////////
///
/// \file JobSystem.hpp
/// 
///
/// Authors: Chris Peters
/// Copyright 2010-2011, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

// Because windows...
#undef AddJob

namespace Plasma
{

//-------------------------------------------------------------------------- Job
class Job : public ReferenceCountedEventObject
{
public:
  friend class JobSystem;
  LightningDeclareType(Job, TypeCopyMode::ReferenceType);
  Job();
  virtual ~Job();

  // Entrant function of the job. If it returns Complete, the job may be destroyed
  // by the job system. Returning InProgress means the job will not be deleted
  // (you can call AddJob again from any thread, even on the same job class).
  virtual void Execute() = 0;

  // Called from a different thread, typically setting a bool to stop
  virtual int Cancel(){return 0;};

private:
  // This value is incremented by the job system every time we add the job.
  // If the value is greater than 1, the thread will run it multiple times.
  // Must be locked by the JobSystem.
  size_t mRunCount;
};

//------------------------------------------------------------------- Job System
class JobSystem : public EventObject
{
public:
  typedef JobSystem LightningSelf;
  JobSystem();
  ~JobSystem();
  
  // Add's a job to be worked on (can be called from any thread).
  // Note that a job can be queued up again after it completes.
  void AddJob(Job* job);
  OsInt WorkerThreadEntry();

private:
  void RunJob(Job* job);

  ThreadLock mLock;
  Array<HandleOf<Job>> mPendingJobs;
  Array<HandleOf<Job>> mActiveJobs;
  Array<Thread*> mWorkers;
  Semaphore mJobCounter;
  Job* GetNextJob();
  friend class Job;
};

namespace PL
{
  extern JobSystem* gJobs;
}

} // namespace Plasma
