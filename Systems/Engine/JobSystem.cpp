///////////////////////////////////////////////////////////////////////////////
///
/// \file JobSystem.cpp
/// 
///
/// Authors: Chris Peters
/// Copyright 2010-2011, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

namespace Plasma
{

LightningDefineType(Job, builder, type)
{
}

Job::Job() :
  mRunCount(0)
{
}

Job::~Job()
{
}

//-----------------------------------------------------------------------------
namespace PL
{
  JobSystem* gJobs = nullptr;
}

JobSystem::JobSystem()
{
  if (ThreadingEnabled)
  {
    mWorkers.Resize(10);

    for (uint i = 0; i < mWorkers.Size(); ++i)
    {
      mWorkers[i] = new Thread();
      Thread& thread = *mWorkers[i];
      thread.Initialize(&Thread::ObjectEntryCreator<JobSystem, &JobSystem::WorkerThreadEntry>, this, "Background");
    }
  }
}

JobSystem::~JobSystem()
{
  // Cancel all active Jobs.
  mLock.Lock();
  // Active job range is safe because of the lock.
  forRange(Job& job, mActiveJobs.All())
    job.Cancel();

  // Release all active and pending job references that we own (this may delete the jobs).
  mPendingJobs.Clear();
  mLock.Unlock();

  // Increment the counter but push no jobs
  // allowing each background thread to unblock.
  for (uint i = 0; i < mWorkers.Size(); ++i)
    mJobCounter.Increment();

  // Wait for each thread to shutdown.
  for (uint i = 0; i < mWorkers.Size(); ++i)
  {
    Thread& thread = *mWorkers[i];
    thread.WaitForCompletion();
  }

  // Clear all active jobs now that all threads have stopped (may release the memory for jobs).
  // There should be no more threads running, but we lock just to be safe.
  mLock.Lock();
  mActiveJobs.Clear();
  mLock.Unlock();

  // Delete all threads.
  DeleteObjectsInContainer(mWorkers);
}

Job* JobSystem::GetNextJob()
{
  Job* job = nullptr;

  //Locked pop front
  mLock.Lock();
  if (!mPendingJobs.Empty())
  {
    HandleOf<Job> jobHandle = mPendingJobs.Back();
    job = jobHandle;
    mPendingJobs.PopBack();
    mActiveJobs.PushBack(jobHandle);
  }
  mLock.Unlock();

  // We don't need to return a handle because the job will
  // be kept alive by being inside of mActiveJobs.
  return job;
}

OsInt JobSystem::WorkerThreadEntry()
{
  for(;;)
  {
    mJobCounter.WaitAndDecrement();
    Job* job = GetNextJob();

    // No jobs and Semaphore release
    // that means we are shutting down.
    if(job == nullptr)
      return 0;

    RunJob(job);
  }
}

void JobSystem::AddJob(Job* job)
{
  mLock.Lock();
  if (job->mRunCount == 0)
    mPendingJobs.PushBack(job);
  ++job->mRunCount;
  mLock.Unlock();

  if (!ThreadingEnabled)
  {
    // Run the job on the main thread.
    RunJob(job);
  }
  else
  {
    // Signal that a job has been added, which will unblock the waiting workers.
    mJobCounter.Increment();
  }
}

void JobSystem::RunJob(Job* job)
{
  bool completed = false;
  do
  {
    job->Execute();

    mLock.Lock();
    --job->mRunCount;
    completed = (job->mRunCount == 0);
    if (completed)
    {
      HandleOf<Job> jobHandle = job;
      mActiveJobs.EraseValue(jobHandle);
    }
    mLock.Unlock();
  }
  while (!completed);
}

}//Plasma
