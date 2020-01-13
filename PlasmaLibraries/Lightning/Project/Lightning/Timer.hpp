/**************************************************************\
* Author: Trevor Sundberg
* Copyright 2016, DigiPen Institute of Technology
\**************************************************************/

#pragma once
#ifndef LIGHTNING_TIMER_HPP
#define LIGHTNING_TIMER_HPP

namespace Lightning
{
  // The timer maintains a precision of at around 1ms and attempts to deal with wrap around
  class PlasmaShared Timer
  {
  public:
    // Constructor
    Timer();

    // The ticks that make up a second
    static const long long TicksPerSecond;

    // Updates the timer and returns its time
    long long GetAndUpdateTicks();

    // Resets the ticks that have been counted
    void Reset();

  private:

    // We keep our own tick count which is actually in the same
    // measurement as clock_t, but deals with wrap around
    long long TotalTicks;

    // Store the last sample we did to the clock
    long long LastClock;
  };
}

#endif
